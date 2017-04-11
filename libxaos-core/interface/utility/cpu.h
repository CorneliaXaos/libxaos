/**
 *  @file cpu.h
 *  @brief CPU Architecture Detection Macro Definitions
 *
 *  This file contains macros that detect which CPU architecture the code is
 *  being compiled for.  It primarily uses macro definitions defined here:
 *  https://sourceforge.net/p/predef/wiki/Architectures/
 *  and here:
 *  http://nadeausoftware.com/articles/2012/02/c_c_tip_how_detect_processor_type_using_compiler_predefined_macros
 *
 *  This software only exposes the following architectures:
 *  - x86 / x86_64 (Intel assumed)
 *  - ARM
 *  - PowerPC (32 or 64 bit)
 *
 *  Including this header will define numerous LIBXAOS_FLAG s depending on the
 *  compiling CPU architecture:
 *  - LIBXAOS_FLAG_CPU_INTEL : CPU is Intel
 *  - LIBXAOS_FLAG_CPU_ARM : CPU is ARM (either 32 or 64 bit)
 *  - LIBXAOS_FLAG_CPU_POWERPC : CPU is PowerPC
 *
 *  In addition to CPU vender defines, including this header will attempt to
 *  determine the cpu's bit depth (i.e. 32 vs 64 bit):
 *  - LIBXAOS_FLAG_CPU_INTEL_X86 : CPU is Intel x86 / 32 bit
 *  - LIBXAOS_FLAG_CPU_INTEL_X64 : CPU is Intel x86_64 / 64 bit
 *  - LIBXAOS_FLAG_CPU_POWERPC_32 : CPU is PowerPC 32 bit
 *  - LIBXAOS_FLAG_CPU_POWERPC_64 : CPU is PowerPC 64 bit
 *
 *  However, it is recommended that these not be used.  Instead, write code that
 *  doesn't care what bit depth the data is.  (Though if the bit depth is needed
 *  to determine which intrinsic to use, which is the primary purpose of this
 *  header, that makes sense.)
 *
 *  (Developer's note: I'm unsure if those MSVC define checks will stay..  I'm
 *  planning on dropping support for that compiler...)
 */

#ifndef     LIBXAOS_CORE_UTILITY_CPU_H
#define     LIBXAOS_CORE_UTILITY_CPU_H

#if defined(__i386__) || defined(_M_IX86) // Intel x86
    #define LIBXAOS_FLAG_CPU_INTEL
    #define LIBXAOS_FLAG_CPU_INTEL_X86
#elif defined(__x86_64__) || defined(_M_X64) // Intel x86_64
    #define LIBXAOS_FLAG_CPU_INTEL
    #define LIBXAOS_FLAG_CPU_INTEL_X64
#elif defined(__arm__) || defined(_M_ARM) // ARM (either 32 or 64 bit)
    #define LIBXAOS_FLAG_CPU_ARM
#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__) // PowerPC 32
    #define LIBXAOS_FLAG_CPU_POWERPC
    #define LIBXAOS_FLAG_CPU_POWERPC_32
#elif defined(__powerpc64__) || defined (__ppc64__) || defined(__PPC64__) // PowerPC 64
    #define LIBXAOS_FLAG_CPU_POWERPC
    #define LIBXAOS_FLAG_CPU_POWERPC_64
#else
    #define LIBXAOS_FLAG_CPU_UNKNOWN
#endif



#endif   // LIBXAOS_CORE_UTILITY_CPU_H
