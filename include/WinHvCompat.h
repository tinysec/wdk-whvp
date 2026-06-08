/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Compatibility wrapper for using the Windows Hypervisor Platform public
headers with the Windows 7 WDK user-mode toolchain.

--*/

#ifndef _WINHVCOMPAT_H_
#define _WINHVCOMPAT_H_

#if defined(_M_AMD64) || defined(_M_X64) || defined(__x86_64__) || defined(__amd64__)
#ifndef _AMD64_
#define _AMD64_
#endif
#endif

#ifndef _AMD64_
#error wdk-whvp only provides amd64 headers and import libraries.
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif

#include <windows.h>

#ifndef WINAPI_PARTITION_DESKTOP
#define WINAPI_PARTITION_DESKTOP 0x00000001
#endif

#ifndef WINAPI_PARTITION_SYSTEM
#define WINAPI_PARTITION_SYSTEM 0x00000002
#endif

#ifndef WINAPI_FAMILY_PARTITION
#define WINAPI_FAMILY_PARTITION(Partitions) (1)
#endif

#ifndef _In_
#define _In_
#endif

#ifndef _In_opt_
#define _In_opt_
#endif

#ifndef _In_reads_
#define _In_reads_(size)
#endif

#ifndef _In_reads_opt_
#define _In_reads_opt_(size)
#endif

#ifndef _In_reads_bytes_
#define _In_reads_bytes_(size)
#endif

#ifndef _Inout_
#define _Inout_
#endif

#ifndef _Out_
#define _Out_
#endif

#ifndef _Out_opt_
#define _Out_opt_
#endif

#ifndef _Out_writes_
#define _Out_writes_(size)
#endif

#ifndef _Out_writes_to_
#define _Out_writes_to_(size, count)
#endif

#ifndef _Out_writes_bytes_
#define _Out_writes_bytes_(size)
#endif

#ifndef _Out_writes_bytes_to_
#define _Out_writes_bytes_to_(size, count)
#endif

#ifndef _Out_writes_bytes_to_opt_
#define _Out_writes_bytes_to_opt_(size, count)
#endif

#ifndef _Outptr_result_buffer_
#define _Outptr_result_buffer_(size)
#endif

#endif /* _WINHVCOMPAT_H_ */
