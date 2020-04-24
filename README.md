# github.com/ianlancetaylor/cgosymbolizer

A Go package that can be used to convert cgo function pointers into
useful backtrace information.

This is an experimental package intended for use with the [`runtime.SetCgoTraceback`](https://golang.org/pkg/runtime/?m=all#SetCgoTraceback) function.
