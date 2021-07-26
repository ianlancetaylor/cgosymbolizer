// Copyright 2015 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package cgosymbolizer provides a cgo symbolizer based on libbacktrace.
// This will be used to provide a symbolic backtrace of cgo functions.
// This package does not export any symbols.
// To use it, add a line like
//   import _ "github.com/ianlancetaylor/cgosymbolizer"
// somewhere in your program.
package cgosymbolizer

// #include <stdint.h>
// extern void cgoSymbolizerInit(char*);
// extern void cgoTraceback(void*);
// extern void cgoSymbolizer(void*);
// extern void cgoHookCallers(uintptr_t cgoCallerPtr);
import "C"

import (
	"os"
	"runtime"
	"unsafe"
)

//go:linkname _cgo_callers _cgo_callers
var _cgo_callers byte
var _cgo_callers_ptr = uintptr(unsafe.Pointer(&_cgo_callers))

func init() {
	C.cgoSymbolizerInit(C.CString(os.Args[0]))
	C.cgoHookCallers(C.uintptr_t(_cgo_callers_ptr))
	runtime.SetCgoTraceback(0, unsafe.Pointer(C.cgoTraceback), nil, unsafe.Pointer(C.cgoSymbolizer))
}
