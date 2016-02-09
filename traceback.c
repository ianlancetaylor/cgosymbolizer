// Copyright 2016 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build cgo
// +build linux

#include <stddef.h>
#include <stdint.h>
#include <unwind.h>

struct unwind_data {
	uintptr_t* addrs;
	int        idx;
	int        max;
	uintptr_t  cfa;
};

static _Unwind_Reason_Code
unwind(struct _Unwind_Context* context, void* data)
{
	struct unwind_data* ud = (struct unwind_data*)data;
	uintptr_t cfa;
	uintptr_t pc;
	int ip_before_insn;

	if (ud->idx >= ud->max) {
		return _URC_END_OF_STACK;
	}

	if (ud->idx < 0) {
		ud->idx++;
		return _URC_NO_REASON; 
	}

	cfa = _Unwind_GetCFA(context);
	if (ud->cfa == 0) {
		ud->cfa = (uintptr_t)(cfa);
	} else {
		// If we are no longer in a plausible stack range, give up.
		// Default thread stack size on GNU/Linux is 2MB, allow 1MB.
		// Remember we are on the system stack here.
		if (cfa < ud->cfa || cfa >= ud->cfa + (1 << 10)) {
			return _URC_END_OF_STACK;
		}
	}

	pc = _Unwind_GetIPInfo(context, &ip_before_insn);
	if (!ip_before_insn) {
		--pc;
	}
	ud->addrs[ud->idx] = pc;
	ud->idx++;
	return _URC_NO_REASON;
}

struct cgoTracebackArg {
	uintptr_t  pc;
	uintptr_t  sp;
	uintptr_t  lr;
	uintptr_t* buf;
	uintptr_t  max;
};

// Gather addresses from the call stack.
void cgoTraceback(void* parg) {
	struct cgoTracebackArg* arg = (struct cgoTracebackArg*)(parg);
	struct unwind_data ud;

	// We can only unwind the current stack.
	if (arg->pc != 0 || arg->sp != 0) {
		arg->buf[0] = 0;
		return;
	}

	// Skip this frame, the runtime/cgo function, and the sigreturn frame.
	ud.idx = -3;
	ud.addrs = arg->buf;
	ud.max = arg->max;
	ud.cfa = 0;
	_Unwind_Backtrace(unwind, (void*)&ud);

	// The list of addresses terminates at a 0, so make sure there is one.
	if (ud.idx < 0) {
		arg->buf[0] = 0;
	} else if (ud.idx < arg->max) {
		arg->buf[ud.idx] = 0;
	}
}
