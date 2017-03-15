#!/usr/bin/env bash

set -eu

rm -rf internal/*
find . -type l -not -path './.git/*' -exec rm {} \;
curl -sfSL https://github.com/gcc-mirror/gcc/archive/gcc-6_3_0-release.tar.gz | \
  tar xzf - -C internal --strip-components=1 '*-release/'{libbacktrace/'*'.{c,h},include/{{ansidecl,filenames,hashtab}.h,dwarf2.{def,h}}}

patch -p1 < build.patch

# symlink so cgo compiles them
find internal -name '*.c' \
  -not -name btest.c \
  -not -name stest.c \
  -not -name mmap.c \
  -not -name mmapio.c \
  -not -name nounwind.c \
  -exec ln -sf {} . \;

git clean -dXf
