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

// #cgo CFLAGS: -Iinternal/include -Iinternal/libbacktrace
// extern void cgoSymbolizerInit(char*);
// extern void cgoTraceback(void*);
// extern void cgoSymbolizer(void*);
import "C"

import (
	"os"
	"runtime"
	"unsafe"
)

func init() {
	C.cgoSymbolizerInit(C.CString(os.Args[0]))
	runtime.SetCgoTraceback(0, unsafe.Pointer(C.cgoTraceback), nil, unsafe.Pointer(C.cgoSymbolizer))
}
