// Copyright 2015 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "config.h"

#include <stdint.h>
#include <string.h>
#include <sys/types.h>

#include "backtrace.h"
#include "internal.h"

static void createStateErrorCallback(void* data, const char* msg, int errnum) {
}

static struct backtrace_state *cgoBacktraceState;

// Initialize the backtrace state.
void cgoSymbolizerInit(char* filename) {
	cgoBacktraceState = backtrace_create_state(filename, 1, createStateErrorCallback, NULL);
}

struct cgoSymbolizerArg {
	uintptr_t   pc;
	const char* file;
	uintptr_t   lineno;
	const char* func;
	uintptr_t   entry;
	uintptr_t   more;
	uintptr_t   data;
};

struct cgoSymbolizerMore {
	struct cgoSymbolizerMore *more;

	const char* file;
	uintptr_t   lineno;
	const char* func;
};

// Called via backtrace_pcinfo.
static int callback(void* data, uintptr_t pc, const char* filename, int lineno, const char* function) {
	struct cgoSymbolizerArg* arg = (struct cgoSymbolizerArg*)(data);
	struct cgoSymbolizerMore* more;
	struct cgoSymbolizerMore** pp;
	if (arg->file == NULL) {
		arg->file = filename;
		arg->lineno = lineno;
		arg->func = function;
		return 0;
	}
	more = backtrace_alloc(cgoBacktraceState, sizeof(*more), NULL, NULL);
	if (more == NULL) {
		return 1;
	}
	more->more = NULL;
	more->file = filename;
	more->lineno = lineno;
	more->func = function;
	for (pp = (struct cgoSymbolizerMore**)(&arg->data); *pp != NULL; pp = &(*pp)->more) {
	}
	*pp = more;
	arg->more = 1;
	return 0;
}

// Called via backtrace_pcinfo.
// Just ignore errors and let the caller indicate missing information.
static void errorCallback(void* data, const char* msg, int errnum) {
}

// Called via backtrace_syminfo.
// Just set the entry field.
static void syminfoCallback(void* data, uintptr_t pc, const char* symname, uintptr_t symval, uintptr_t symsize) {
	struct cgoSymbolizerArg* arg = (struct cgoSymbolizerArg*)(data);
	arg->entry = symval;
}

// For the details of how this is called see runtime.SetCgoSymbolizer.
void cgoSymbolizer(void* parg) {
	struct cgoSymbolizerArg* arg = (struct cgoSymbolizerArg*)(parg);
	if (arg->data != 0) {
		struct cgoSymbolizerMore* more = (struct cgoSymbolizerMore*)(arg->data);
		arg->file = more->file;
		arg->lineno = more->lineno;
		arg->func = more->func;
		arg->more = more->more != NULL;
		arg->data = (uintptr_t)(more->more);

		// If returning the last file/line, we can set the
		// entry point field.
		if (!arg->more) {
			backtrace_syminfo(cgoBacktraceState, arg->pc, syminfoCallback, errorCallback, (void*)arg);
		}

		return;
	}
	arg->file = NULL;
	arg->lineno = 0;
	arg->func = NULL;
	arg->more = 0;
	if (cgoBacktraceState == NULL || arg->pc == 0) {
		return;
	}
	backtrace_pcinfo(cgoBacktraceState, arg->pc, callback, errorCallback, (void*)(arg));

	// If returning only one file/line, we can set the entry point field.
	if (!arg->more) {
		backtrace_syminfo(cgoBacktraceState, arg->pc, syminfoCallback, errorCallback, (void*)arg);
	}
}
