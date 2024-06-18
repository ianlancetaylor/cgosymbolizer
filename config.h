/* Hand written config.h suitable for a modern GNU/Linux system.  */

/* ELF size: 32 or 64 */
#if defined(__x86_64__) || defined(__aarch64__) || defined(__mips64) || defined(_ARCH_PPC64) || defined(__s390x__) || (defined(__riscv) && __riscv_xlen == 64) || defined(__loongarch64)
#define BACKTRACE_ELF_SIZE 64
#elif defined(__i386__) || defined(__arm__) || defined(__mips__) || defined(_ARCH_PPC) || defined(__riscv)
#define BACKTRACE_ELF_SIZE 32
#else
#error BACKTRACE_ELF_SIZE unknown
#endif

/* XCOFF size: 32 or 64 */
/* #undef BACKTRACE_XCOFF_SIZE */

/* Define to 1 if you have the __atomic functions */
#define HAVE_ATOMIC_FUNCTIONS 1

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define to 1 if you have the declaration of `getpagesize', and to 0 if you
   don't. */
#define HAVE_DECL_GETPAGESIZE 1

/* Define to 1 if you have the declaration of `strnlen', and to 0 if you
   don't. */
#define HAVE_DECL_STRNLEN 1

/* Define to 1 if you have the declaration of `_pgmptr', and to 0 if you
   don't. */
#define HAVE_DECL__PGMPTR 0

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define if dl_iterate_phdr is available. */
#define HAVE_DL_ITERATE_PHDR 1

/* Define to 1 if you have the fcntl function */
#define HAVE_FCNTL 1

/* Define if getexecname is available. */
/* #undef HAVE_GETEXECNAME */

/* Define if _Unwind_GetIPInfo is available. */
#define HAVE_GETIPINFO 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have KERN_PROC and KERN_PROC_PATHNAME in <sys/sysctl.h>.
   */
/* #undef HAVE_KERN_PROC */

/* Define to 1 if you have KERN_PROCARGS and KERN_PROC_PATHNAME in
   <sys/sysctl.h>. */
/* #undef HAVE_KERN_PROC_ARGS */

/* Define if -llzma is available. */
/* #undef HAVE_LIBLZMA */

/* Define to 1 if you have the <link.h> header file. */
#define HAVE_LINK_H 1

/* Define if AIX loadquery is available. */
/* #undef HAVE_LOADQUERY */

/* Define to 1 if you have the `lstat' function. */
#define HAVE_LSTAT 1

/* Define to 1 if you have the <mach-o/dyld.h> header file. */
/* #undef HAVE_MACH_O_DYLD_H */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `readlink' function. */
#define HAVE_READLINK 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the __sync functions */
#define HAVE_SYNC_FUNCTIONS 1

/* Define to 1 if you have the <sys/ldr.h> header file. */
/* #undef HAVE_SYS_LDR_H */

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <tlhelp32.h> header file. */
/* #undef HAVE_TLHELP32_H */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define if -lz is available. */
/* #undef HAVE_ZLIB */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#undef LT_OBJDIR

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "iant@golang.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "cgosymbolizer"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "cgosymbolizer"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "cgosymbolizer"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://github.com/ianlancetaylor/cgosymbolizer"

/* Define to the version of this package. */
#define PACKAGE_VERSION "version-unused"

/* The size of `char', as computed by sizeof. */
/* #undef SIZEOF_CHAR */

/* The size of `int', as computed by sizeof. */
/* #undef SIZEOF_INT */

/* The size of `long', as computed by sizeof. */
/* #undef SIZEOF_LONG */

/* The size of `short', as computed by sizeof. */
/* #undef SIZEOF_SHORT */

/* The size of `void *', as computed by sizeof. */
/* #undef SIZEOF_VOID_P */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */
