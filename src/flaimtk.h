//------------------------------------------------------------------------------
// Desc:	FLAIM's cross-platform toolkit public definitions and interfaces
//
// Tabs:	3
//
//		Copyright (c) 2003-2006 Novell, Inc. All Rights Reserved.
//
//		This program is free software; you can redistribute it and/or
//		modify it under the terms of version 2 of the GNU General Public
//		License as published by the Free Software Foundation.
//
//		This program is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//		GNU General Public License for more details.
//
//		You should have received a copy of the GNU General Public License
//		along with this program; if not, contact Novell, Inc.
//
//		To contact Novell about this file by physical or electronic mail,
//		you may find current contact information at www.novell.com
//
// $Id$
//------------------------------------------------------------------------------

/// \file

#ifndef FTK_H
#define FTK_H

	/// \defgroup retcodes Return Codes
	
	#ifndef FLM_PLATFORM_CONFIGURED
		#define FLM_PLATFORM_CONFIGURED
	
		// Determine the build platform
	
		#undef FLM_WIN
		#undef FLM_NLM
		#undef FLM_UNIX
		#undef FLM_AIX
		#undef FLM_LINUX
		#undef FLM_SOLARIS
		#undef FLM_HPUX
		#undef FLM_OSX
		#undef FLM_S390
		#undef FLM_IA64
		#undef FLM_PPC
		#undef FLM_SPARC
		#undef FLM_SPARC_PLUS
		#undef FLM_X86
		#undef FLM_BIG_ENDIAN
		#undef FLM_STRICT_ALIGNMENT
		#undef FLM_GNUC
		#undef FLM_HAS_ASYNC_IO
		#undef FLM_HAS_DIRECT_IO
		
		#if defined( __GNUC__)
			#define FLM_GNUC
			#if defined( __arch64__)
				#if !defined( FLM_64BIT)
					#define FLM_64BIT
				#endif
			#endif
		#endif		

		#if defined( __NETWARE__) || defined( NLM) || defined( N_PLAT_NLM)
			#if defined( __WATCOMC__) && defined( __386__)
				#define FLM_X86
			#else
				#error Platform architecture not supported
			#endif
			#define FLM_NLM
			#if !defined( FLM_RING_ZERO_NLM) && !defined( FLM_LIBC_NLM)
				#define FLM_RING_ZERO_NLM
			#endif
			#define FLM_OSTYPE_STR "NetWare"
			#if defined( __WATCOMC__)
				#define FLM_WATCOM_NLM
			#elif defined( __MWERKS__)
				#define FLM_MWERKS_NLM
			#endif
			#if defined( FLM_RING_ZERO_NLM)
				#define FLM_HAS_ASYNC_IO
				#define FLM_HAS_DIRECT_IO
			#endif
		#elif defined( _WIN64)
			#if defined( _M_IX6) || defined( _M_X64)
				#define FLM_X86
			#endif
			#define FLM_WIN
			#define FLM_OSTYPE_STR "Windows"
			#ifndef FLM_64BIT
				#define FLM_64BIT
			#endif
			#define FLM_STRICT_ALIGNMENT
			#define FLM_HAS_ASYNC_IO
			#define FLM_HAS_DIRECT_IO
		#elif defined( _WIN32)
			#if defined( _M_IX86) || defined( _M_X64)
				#define FLM_X86
			#else
				#error Platform architecture not supported
			#endif
			#define FLM_WIN
			#define FLM_OSTYPE_STR "Windows"
			#define FLM_HAS_ASYNC_IO
			#define FLM_HAS_DIRECT_IO
		#elif defined( _AIX)
			#define FLM_AIX
			#define FLM_OSTYPE_STR "AIX"
			#define FLM_UNIX
			#define FLM_BIG_ENDIAN
			#define FLM_STRICT_ALIGNMENT
		#elif defined( linux)
			#define FLM_LINUX
			#define FLM_OSTYPE_STR "Linux"
			#define FLM_UNIX
			#if defined( __PPC__) || defined( __ppc__)
				#define FLM_PPC
				#define FLM_BIG_ENDIAN
				#define FLM_STRICT_ALIGNMENT
			#elif defined( __s390__)
				#define FLM_S390
				#define FLM_BIG_ENDIAN
				#define FLM_STRICT_ALIGNMENT
			#elif defined( __s390x__)
				#define FLM_S390
				#ifndef FLM_64BIT
					#define FLM_64BIT
				#endif
				#define FLM_BIG_ENDIAN
				#define FLM_STRICT_ALIGNMENT
			#elif defined( __ia64__)
				#define FLM_IA64
				#ifndef FLM_64BIT
					#define FLM_64BIT
				#endif
				#define FLM_STRICT_ALIGNMENT
			#elif defined( sparc) || defined( __sparc) || defined( __sparc__)
				#define FLM_SPARC
				#define FLM_BIG_ENDIAN
				#define FLM_STRICT_ALIGNMENT
				#if !defined ( FLM_SPARC_GENERIC)
					#if defined( __sparcv8plus) || defined( __sparcv9) || defined( __sparcv9__) || \
						 defined( __sparc_v8__) || defined( __sparc_v9__) || defined( __arch64__)
						#define FLM_SPARC_PLUS
					#endif
				#endif
			#elif defined( __x86__) || defined( __i386__) || defined( __x86_64__)  
				#define FLM_X86
			#else
				#error Platform architecture not supported
			#endif
			#define FLM_HAS_ASYNC_IO
			#define FLM_HAS_DIRECT_IO
		#elif defined( sun)
			#define FLM_SOLARIS
			#define FLM_OSTYPE_STR "Solaris"
			#define FLM_UNIX
			#define FLM_STRICT_ALIGNMENT
			#if defined( sparc) || defined( __sparc) || defined( __sparc__)
				#define FLM_SPARC
				#define FLM_BIG_ENDIAN
				#if !defined ( FLM_SPARC_GENERIC)
					#if defined( __sparcv8plus) || defined( __sparcv9)
						#define FLM_SPARC_PLUS
					#endif
				#endif
			#elif defined( i386) || defined( _i386)
				#define FLM_X86
			#else
				#error Platform architecture not supported
			#endif
			#define FLM_HAS_ASYNC_IO
			#define FLM_HAS_DIRECT_IO
		#elif defined( __hpux) || defined( hpux)
			#define FLM_HPUX
			#define FLM_OSTYPE_STR "HPUX"
			#define FLM_UNIX
			#define FLM_BIG_ENDIAN
			#define FLM_STRICT_ALIGNMENT
			#define FLM_HAS_ASYNC_IO
			#define FLM_HAS_DIRECT_IO
		#elif defined( __APPLE__)
			#define FLM_OSX
			#define FLM_OSTYPE_STR "OSX"
			#define FLM_UNIX
			#if (defined( __ppc__) || defined( __ppc64__))
				#define FLM_PPC
				#define FLM_BIG_ENDIAN
				#define FLM_STRICT_ALIGNMENT			
			#elif defined( __x86__) || defined( __i386__) || defined( __x86_64__)  
				#define FLM_X86
			#else
				#error Platform architecture not supported
			#endif
			#define FLM_HAS_ASYNC_IO
			#define FLM_HAS_DIRECT_IO
		#else
				#error Platform architecture is undefined.
		#endif
	
		#if !defined( FLM_64BIT) && !defined( FLM_32BIT)
			#if defined( FLM_UNIX)
				#if defined( __x86_64__) || defined( _M_X64) || \
					 defined( _LP64) || defined( __LP64__) || \
					 defined ( __64BIT__) || defined( __arch64__) || \
					 defined( __sparcv9) || defined( __sparcv9__) 
					#define FLM_64BIT
				#endif
			#endif
		#endif
		
		#if !defined( FLM_64BIT)
			#define FLM_32BIT
		#elif defined( FLM_32BIT)
			#error Cannot define both FLM_32BIT and FLM_64BIT
		#endif
		
		#if defined( __x86_64__) || defined( _M_X64) || \
			 defined( _LP64) || defined( __LP64__) || \
			 defined ( __64BIT__) || defined( __arch64__) || \
			 defined( __sparcv9) || defined( __sparcv9__) 
			#if !defined( FLM_64BIT)
				#error Platform word size is incorrect
			#endif
		#else
			#if !defined( FLM_32BIT)
				#error Platform word size is incorrect
			#endif
		#endif
					 
 		#ifdef FLM_NLM
			#define FSTATIC
		#else
			#define FSTATIC		static
		#endif
		
		// Debug or release build?
	
		#ifndef FLM_DEBUG
			#if defined( DEBUG) || (defined( PRECHECKIN) && PRECHECKIN != 0)
				#define FLM_DEBUG
			#endif
		#endif

		// Alignment
	
		#if defined( FLM_UNIX) || defined( FLM_64BIT)
			#define FLM_ALLOC_ALIGN					0x0007
			#define FLM_ALIGN_SIZE					8
		#elif defined( FLM_WIN) || defined( FLM_NLM)
			#define FLM_ALLOC_ALIGN					0x0003
			#define FLM_ALIGN_SIZE					4
		#else
			#error Platform not supported
		#endif
		
		// Basic type definitions

		#if defined( FLM_UNIX)
			typedef unsigned long					FLMUINT;
			typedef long								FLMINT;
			typedef unsigned char					FLMBYTE;
			typedef unsigned short					FLMUNICODE;

			typedef unsigned long long				FLMUINT64;
			typedef unsigned int						FLMUINT32;
			typedef unsigned short					FLMUINT16;
			typedef unsigned char					FLMUINT8;
			typedef long long							FLMINT64;
			typedef int									FLMINT32;
			typedef short								FLMINT16;
			typedef signed char						FLMINT8;

			#if defined( FLM_64BIT) || defined( FLM_OSX) || \
				 defined( FLM_S390) || defined( FLM_HPUX) || defined( FLM_AIX)
				typedef unsigned long				FLMSIZET;
			#else
				typedef unsigned 						FLMSIZET;
			#endif
		#else
		
			#if defined( FLM_WIN)
			
				#if defined( FLM_64BIT)
					typedef unsigned __int64		FLMUINT;
					typedef __int64					FLMINT;
					typedef unsigned __int64		FLMSIZET;
					typedef unsigned int				FLMUINT32;
				#elif _MSC_VER >= 1300
					typedef unsigned long __w64	FLMUINT;
					typedef long __w64				FLMINT;
					typedef __w64 unsigned int		FLMUINT32;
					typedef __w64 unsigned int		FLMSIZET;
				#else
					typedef unsigned long			FLMUINT;
					typedef long						FLMINT;
					typedef unsigned int				FLMUINT32;
					typedef unsigned int				FLMSIZET;
				#endif
			#elif defined( FLM_NLM)
			
				typedef unsigned long int			FLMUINT;
				typedef long int						FLMINT;
				typedef unsigned long int			FLMUINT32;
				typedef unsigned						FLMSIZET;
			#else
				#error Platform not supported
			#endif

			typedef unsigned char					FLMBYTE;
			typedef unsigned short int				FLMUNICODE;

			typedef unsigned short int				FLMUINT16;
			typedef unsigned char					FLMUINT8;
			typedef signed int						FLMINT32;
			typedef signed short int				FLMINT16;
			typedef signed char						FLMINT8;

			#if defined( __MWERKS__)
				typedef unsigned long long			FLMUINT64;
				typedef long long						FLMINT64;
			#else
				typedef unsigned __int64 			FLMUINT64;
				typedef __int64 						FLMINT64;
			#endif

		#endif

		#if defined( FLM_WIN) || defined( FLM_NLM)
			#define FLMATOMIC		volatile long
		#else
			#define FLMATOMIC		volatile int
		#endif
	
		/// \addtogroup retcodes
		/// @{
		typedef FLMINT32								RCODE;			///< Return code
		/// @}
		typedef FLMINT32								FLMBOOL;
		
		#define F_FILENAME_SIZE						256
		#define F_PATH_MAX_SIZE						256
		#define F_WAITFOREVER						(0xFFFFFFFF)

		#define FLM_MAX_UINT							((FLMUINT)(-1L))
		#define FLM_MAX_INT							((FLMINT)(((FLMUINT)(-1L)) >> 1))
		#define FLM_MIN_INT							((FLMINT)((((FLMUINT)(-1L)) >> 1) + 1))
		#define FLM_MAX_UINT32						((FLMUINT32)(0xFFFFFFFFL))
		#define FLM_MAX_INT32						((FLMINT32)(0x7FFFFFFFL))
		#define FLM_MIN_INT32						((FLMINT32)(0x80000000L))
		#define FLM_MAX_UINT16						((FLMUINT16)(0xFFFF))
		#define FLM_MAX_INT16						((FLMINT16)(0x7FFF))
		#define FLM_MIN_INT16						((FLMINT16)(0x8000))
		#define FLM_MAX_UINT8						((FLMUINT8)0xFF)
	
		#if ((_MSC_VER >= 1200) && (_MSC_VER < 1300)) || defined( FLM_NLM)
			#define FLM_MAX_UINT64					((FLMUINT64)(0xFFFFFFFFFFFFFFFFL))
			#define FLM_MAX_INT64					((FLMINT64)(0x7FFFFFFFFFFFFFFFL))
			#define FLM_MIN_INT64					((FLMINT64)(0x8000000000000000L))
		#else
			#define FLM_MAX_UINT64					((FLMUINT64)(0xFFFFFFFFFFFFFFFFLL))
			#define FLM_MAX_INT64					((FLMINT64)(0x7FFFFFFFFFFFFFFFLL))
			#define FLM_MIN_INT64					((FLMINT64)(0x8000000000000000LL))
		#endif
	
	#endif

	// xpcselany keeps MS compilers from complaining about multiple definitions
	
	#if defined(_MSC_VER)
		#define xpcselany __declspec(selectany)
	#else
		#define xpcselany
	#endif
	
	#if !defined( FLM_UNIX) && !defined( FLM_64BIT)
		#define FLM_PACK_STRUCTS
		#ifdef FLM_WIN

			// For some reason, Windows emits a warning when the packing
			// is changed.

			#pragma warning( disable : 4103)
		#endif
	#endif

	#ifdef FLM_PACK_STRUCTS
		#pragma pack(push, 1)
	#endif

	typedef struct
	{
		FLMUINT32	l;
		FLMUINT16	w1;
		FLMUINT16	w2;
		FLMUINT8		b[ 8];
	} FLM_GUID;
	
	#ifdef FLM_PACK_STRUCTS
		#pragma pack(pop)
	#endif

	#define RFLMIID		const FLM_GUID &
	#define RFLMCLSID		const FLM_GUID &
	#define FLMGUID		FLM_GUID
	#define FLMCLSID		FLM_GUID
	
	// FLM_DEFINE_GUID may be used to define or declare a GUID
	// #define FLM_INIT_GUID before including this header file when
	// you want to define the guid, all other inclusions will only declare
	// the guid, not define it.
	
	#if !defined( PCOM_INIT_GUID)
		#define FLM_DEFINE_GUID( name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
				extern const FLMGUID name
	#else
		#define FLM_DEFINE_GUID( name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
				extern const xpcselany FLMGUID name \
						= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
	#endif
	
	#define FLMEXTC								extern "C"

	#if defined( FLM_WIN)
		#define FLMAPI     						__stdcall
		#define FLMEXP								__declspec(dllexport)
		#ifdef FLM_DEBUG
			#define FINLINE						inline
		#else
			#define FINLINE						__forceinline
		#endif
	#elif defined( FLM_NLM)
		#define FLMAPI     						__stdcall
		#define FLMEXP
		#define FINLINE							inline
	#elif defined( FLM_UNIX)
		#define FLMAPI     		
		#define FLMEXP
		#define FINLINE							inline
	#else
		#error Platform not supported
	#endif
	
	/****************************************************************************
	Desc:	Argument lists
	****************************************************************************/
	
	#define f_alignedsize(n) \
		((sizeof(n) + FLM_ALIGN_SIZE - 1) & ~(FLM_ALIGN_SIZE - 1) )

	#if defined( FLM_RING_ZERO_NLM)
		#define f_argsize(x) \
			((sizeof(x)+sizeof(int)-1) & ~(sizeof(int)-1))

		typedef unsigned long	f_va_list;
		
		#define f_va_start(ap, parmN) \
			((void)((ap) = (unsigned long)&(parmN) + f_argsize(parmN)))
			
		#define f_va_arg(ap, type) \
			(*(type *)(((ap) += f_argsize(type)) - (f_argsize(type))))
			
		#define f_va_end(ap) ((void)0)
	#else
		#include <stdarg.h>
		#define f_va_list		va_list
		#define f_va_start	va_start
		#define f_va_arg		va_arg
		#define f_va_end		va_end
	#endif

	// flmnovtbl keeps MS compilers from generating vtables for interfaces
	
	#ifdef _MSC_VER
		#define flmnovtbl 		__declspec( novtable)
	#else
		#define flmnovtbl
	#endif
	
	#define flminterface struct flmnovtbl
	
	/****************************************************************************
	Desc: General errors
	****************************************************************************/
	/// \addtogroup retcodes
	/// @{
		
	#define NE_FLM_OK												0					///< 0 - Operation was successful.
	
	// Error codes that need to be the same as they were for FLAIM
	
	#define NE_FLM_BOF_HIT										0xC001			///< 0xC001 - Beginning of results encountered.
	#define NE_FLM_EOF_HIT										0xC002			///< 0xC002 - End of results encountered.
	#define NE_FLM_EXISTS										0xC004			///< 0xC004 - Object already exists.
	#define NE_FLM_FAILURE										0xC005			///< 0xC005 - Internal failure.
	#define NE_FLM_NOT_FOUND									0xC006			///< 0xC006 - An object was not found.
	#define NE_FLM_BTREE_ERROR									0xC012			///< 0xC012 - Corruption found in b-tree.
	#define NE_FLM_BTREE_FULL									0xC013			///< 0xC013 - B-tree cannot grow beyond current size.
	#define NE_FLM_CONV_DEST_OVERFLOW						0xC01C			///< 0xC01C - Destination buffer not large enough to hold data.
	#define NE_FLM_CONV_ILLEGAL								0xC01D			///< 0xC01D - Attempt to convert between data types is an unsupported conversion.
	#define NE_FLM_CONV_NUM_OVERFLOW							0xC020			///< 0xC020 - Numeric overflow (> upper bound) converting to numeric type.
	#define NE_FLM_DATA_ERROR									0xC022			///< 0xC022 - Corruption found in b-tree.
	#define NE_FLM_ILLEGAL_OP									0xC026			///< 0xC026 - Illegal operation
	#define NE_FLM_MEM											0xC037			///< 0xC037 - Attempt to allocate memory failed.
	#define NE_FLM_NOT_UNIQUE									0xC03E			///< 0xC03E - Non-unique key.
	#define NE_FLM_SYNTAX										0xC045			///< 0xC045 - Syntax error while parsing.
	#define NE_FLM_NOT_IMPLEMENTED							0xC05F			///< 0xC05F - Attempt was made to use a feature that is not implemented.
	#define NE_FLM_INVALID_PARM								0xC08B			///< 0xC08B - Invalid parameter passed into a function.

	// I/O Errors - Must be the same as they were for FLAIM.

	#define NE_FLM_IO_ACCESS_DENIED							0xC201			///< 0xC201 - Access to file is denied.\  Caller is not allowed access to a file.
	#define NE_FLM_IO_BAD_FILE_HANDLE						0xC202			///< 0xC202 - Bad file handle or file descriptor.
	#define NE_FLM_IO_COPY_ERR									0xC203			///< 0xC203 - Error occurred while copying a file.
	#define NE_FLM_IO_DISK_FULL								0xC204			///< 0xC204 - Disk full.
	#define NE_FLM_IO_END_OF_FILE								0xC205			///< 0xC205 - End of file reached while reading from the file.
	#define NE_FLM_IO_OPEN_ERR									0xC206			///< 0xC206 - Error while opening the file.
	#define NE_FLM_IO_SEEK_ERR									0xC207			///< 0xC207 - Error occurred while positioning (seeking) within a file.
	#define NE_FLM_IO_DIRECTORY_ERR							0xC208			///< 0xC208 - Error occurred while accessing or deleting a directory.
	#define NE_FLM_IO_PATH_NOT_FOUND							0xC209			///< 0xC209 - File not found.
	#define NE_FLM_IO_TOO_MANY_OPEN_FILES					0xC20A			///< 0xC20A - Too many files open.
	#define NE_FLM_IO_PATH_TOO_LONG							0xC20B			///< 0xC20B - File name too long.
	#define NE_FLM_IO_NO_MORE_FILES							0xC20C			///< 0xC20C - No more files in directory.
	#define NE_FLM_IO_DELETING_FILE							0xC20D			///< 0xC20D - Error occurred while deleting a file.
	#define NE_FLM_IO_FILE_LOCK_ERR							0xC20E			///< 0xC20E - Error attempting to acquire a byte-range lock on a file.
	#define NE_FLM_IO_FILE_UNLOCK_ERR						0xC20F			///< 0xC20F - Error attempting to release a byte-range lock on a file.
	#define NE_FLM_IO_PATH_CREATE_FAILURE					0xC210			///< 0xC210 - Error occurred while attempting to create a directory or sub-directory.
	#define NE_FLM_IO_RENAME_FAILURE							0xC211			///< 0xC211 - Error occurred while renaming a file.
	#define NE_FLM_IO_INVALID_PASSWORD						0xC212			///< 0xC212 - Invalid file password.
	#define NE_FLM_SETTING_UP_FOR_READ						0xC213			///< 0xC213 - Error occurred while setting up to perform a file read operation.
	#define NE_FLM_SETTING_UP_FOR_WRITE						0xC214			///< 0xC214 - Error occurred while setting up to perform a file write operation.
	#define NE_FLM_IO_CANNOT_REDUCE_PATH					0xC215			///< 0xC215 - Cannot reduce file name into more components.
	#define NE_FLM_INITIALIZING_IO_SYSTEM					0xC216			///< 0xC216 - Error occurred while setting up to access the file system.
	#define NE_FLM_FLUSHING_FILE								0xC217			///< 0xC217 - Error occurred while flushing file data buffers to disk.
	#define NE_FLM_IO_INVALID_FILENAME						0xC218			///< 0xC218 - Invalid file name.
	#define NE_FLM_IO_CONNECT_ERROR							0xC219			///< 0xC219 - Error connecting to a remote network resource.
	#define NE_FLM_OPENING_FILE								0xC21A			///< 0xC21A - Unexpected error occurred while opening a file.
	#define NE_FLM_DIRECT_OPENING_FILE						0xC21B			///< 0xC21B - Unexpected error occurred while opening a file in direct access mode.
	#define NE_FLM_CREATING_FILE								0xC21C			///< 0xC21C - Unexpected error occurred while creating a file.
	#define NE_FLM_DIRECT_CREATING_FILE						0xC21D			///< 0xC21D - Unexpected error occurred while creating a file in direct access mode.
	#define NE_FLM_READING_FILE								0xC21E			///< 0xC21E - Unexpected error occurred while reading a file.
	#define NE_FLM_DIRECT_READING_FILE						0xC21F			///< 0xC21F - Unexpected error occurred while reading a file in direct access mode.
	#define NE_FLM_WRITING_FILE								0xC220			///< 0xC220 - Unexpected error occurred while writing to a file.
	#define NE_FLM_DIRECT_WRITING_FILE						0xC221			///< 0xC221 - Unexpected error occurred while writing a file in direct access mode.
	#define NE_FLM_POSITIONING_IN_FILE						0xC222			///< 0xC222 - Unexpected error occurred while positioning within a file.
	#define NE_FLM_GETTING_FILE_SIZE							0xC223			///< 0xC223 - Unexpected error occurred while getting a file's size.
	#define NE_FLM_TRUNCATING_FILE							0xC224			///< 0xC224 - Unexpected error occurred while truncating a file.
	#define NE_FLM_PARSING_FILE_NAME							0xC225			///< 0xC225 - Unexpected error occurred while parsing a file's name.
	#define NE_FLM_CLOSING_FILE								0xC226			///< 0xC226 - Unexpected error occurred while closing a file.
	#define NE_FLM_GETTING_FILE_INFO							0xC227			///< 0xC227 - Unexpected error occurred while getting information about a file.
	#define NE_FLM_EXPANDING_FILE								0xC228			///< 0xC228 - Unexpected error occurred while expanding a file.
	#define NE_FLM_GETTING_FREE_BLOCKS						0xC229			///< 0xC229 - Unexpected error getting free blocks from file system.
	#define NE_FLM_CHECKING_FILE_EXISTENCE					0xC22A			///< 0xC22A - Unexpected error occurred while checking to see if a file exists.
	#define NE_FLM_RENAMING_FILE								0xC22B			///< 0xC22B - Unexpected error occurred while renaming a file.
	#define NE_FLM_SETTING_FILE_INFO							0xC22C			///< 0xC22C - Unexpected error occurred while setting a file's information.
	#define NE_FLM_IO_PENDING									0xC22D			///< 0xC22D - I/O has not yet completed
	#define NE_FLM_ASYNC_FAILED								0xC22E			///< 0xC22E - An async I/O operation failed
	#define NE_FLM_MISALIGNED_IO								0xC22F			///< 0xC22F - Misaligned buffer or offset encountered during I/O request
	
	// Stream Errors - These are new

	#define NE_FLM_STREAM_DECOMPRESS_ERROR					0xC400			///< 0xC400 - Error decompressing data stream.
	#define NE_FLM_STREAM_NOT_COMPRESSED					0xC401			///< 0xC401 - Attempting to decompress a data stream that is not compressed.
	#define NE_FLM_STREAM_TOO_MANY_FILES					0xC402			///< 0xC402 - Too many files in input stream.
	
	// Miscellaneous new toolkit errors
	
	#define NE_FLM_COULD_NOT_CREATE_SEMAPHORE				0xC500			///< 0xC500 - Could not create a semaphore.
	#define NE_FLM_BAD_UTF8										0xC501			///< 0xC501 - An invalid byte sequence was found in a UTF-8 string
	#define NE_FLM_ERROR_WAITING_ON_SEMAPHORE				0xC502			///< 0xC502 - Error occurred while waiting on a sempahore.
	#define NE_FLM_BAD_SEN										0xC503			///< 0xC503 - Invalid simple encoded number.
	#define NE_FLM_COULD_NOT_START_THREAD					0xC504			///< 0xC504 - Problem starting a new thread.
	#define NE_FLM_BAD_BASE64_ENCODING						0xC505			///< 0xC505 - Invalid base64 sequence encountered.
	#define NE_FLM_STREAM_EXISTS								0xC506			///< 0xC506 - Stream file already exists.
	#define NE_FLM_MULTIPLE_MATCHES							0xC507			///< 0xC507 - Multiple items matched but only one match was expected.
	#define NE_FLM_BTREE_KEY_SIZE								0xC508			///< 0xC508 - Invalid b-tree key size.
	#define NE_FLM_BTREE_BAD_STATE							0xC509			///< 0xC509 - B-tree operation cannot be completed.
	#define NE_FLM_COULD_NOT_CREATE_MUTEX					0xC50A			///< 0xC50A - Error occurred while creating or initializing a mutex.
	#define NE_FLM_BAD_PLATFORM_FORMAT						0xC50B			///< 0xC50B	- In-memory alignment of disk structures is incorrect
	#define NE_FLM_LOCK_REQ_TIMEOUT							0xC50C			///< 0xC50C	- Timeout while waiting for a lock object
	#define NE_FLM_WAIT_TIMEOUT								0xC50D			///< 0xC50D - Timeout while waiting on a semaphore, condition variable, or reader/writer lock
	
	// Network Errors - Must be the same as they were for FLAIM

	#define NE_FLM_NOIP_ADDR									0xC900			///< 0xC900 - IP address not found
	#define NE_FLM_SOCKET_FAIL									0xC901			///< 0xC901 - IP socket failure
	#define NE_FLM_CONNECT_FAIL								0xC902			///< 0xC902 - TCP/IP connection failure
	#define NE_FLM_BIND_FAIL									0xC903			///< 0xC903 - The TCP/IP services on your system may not be configured or installed.
	#define NE_FLM_LISTEN_FAIL									0xC904			///< 0xC904 - TCP/IP listen failed
	#define NE_FLM_ACCEPT_FAIL									0xC905			///< 0xC905 - TCP/IP accept failed
	#define NE_FLM_SELECT_ERR									0xC906			///< 0xC906 - TCP/IP select failed
	#define NE_FLM_SOCKET_SET_OPT_FAIL						0xC907			///< 0xC907 - TCP/IP socket operation failed
	#define NE_FLM_SOCKET_DISCONNECT							0xC908			///< 0xC908 - TCP/IP disconnected
	#define NE_FLM_SOCKET_READ_FAIL							0xC909			///< 0xC909 - TCP/IP read failed
	#define NE_FLM_SOCKET_WRITE_FAIL							0xC90A			///< 0xC90A - TCP/IP write failed
	#define NE_FLM_SOCKET_READ_TIMEOUT						0xC90B			///< 0xC90B - TCP/IP read timeout
	#define NE_FLM_SOCKET_WRITE_TIMEOUT						0xC90C			///< 0xC90C - TCP/IP write timeout
	#define NE_FLM_SOCKET_ALREADY_CLOSED					0xC90D			///< 0xC90D - Connection already closed

	/// @}

	/****************************************************************************
	Desc: Return code functions and macros
	****************************************************************************/
	
	#ifndef RC_OK
		#define RC_OK( rc)			((rc) == NE_FLM_OK)
	#endif

	#ifndef RC_BAD
		#define RC_BAD( rc)        ((rc) != NE_FLM_OK)
	#endif

	RCODE FLMAPI f_mapPlatformError(
		FLMINT						iError,
		RCODE							defaultRc);
		
	/****************************************************************************
	Desc: Forward References
	****************************************************************************/
	
	flminterface IF_DirHdl;
	flminterface IF_FileHdl;
	flminterface IF_FileSystem;
	flminterface IF_FileHdlCache;
	flminterface IF_IStream;
	flminterface IF_PosIStream;
	flminterface IF_ResultSet;
	flminterface IF_ThreadInfo;
	flminterface IF_OStream;
	flminterface IF_IOStream;
	flminterface IF_LogMessageClient;
	flminterface IF_Thread;
	flminterface IF_IOBuffer;
	flminterface IF_AsyncClient;
	flminterface IF_Block;
	
	class F_Pool;
	class F_DynaBuf;
	class F_ListItem;
	class F_ListManager;

	/****************************************************************************
	Desc: Cross-platform definitions
	****************************************************************************/

	#ifndef NULL
		#define NULL   0
	#endif

	#ifndef TRUE
		#define TRUE   1
	#endif

	#ifndef FALSE
		#define FALSE  0
	#endif
	
	#define f_offsetof(s,m) \
		(((FLMSIZET)&((s *)1)->m) - 1) 
	
	/****************************************************************************
	Desc:	Language constants
	IMPORTANT NOTE: If langes are added or changed, the corresponding definitions
	in java and C# must also be updated.
	****************************************************************************/
	
	/// \addtogroup flm_languages
	/// @{
	#define FLM_US_LANG								0			///< English, United States
	#define FLM_AF_LANG								1			///< Afrikaans
	#define FLM_AR_LANG								2			///< Arabic
	#define FLM_CA_LANG								3			///< Catalan
	#define FLM_HR_LANG								4			///< Croatian
	#define FLM_CZ_LANG								5			///< Czech
	#define FLM_DK_LANG								6			///< Danish
	#define FLM_NL_LANG								7			///< Dutch
	#define FLM_OZ_LANG								8			///< English, Australia
	#define FLM_CE_LANG								9			///< English, Canada
	#define FLM_UK_LANG								10			///< English, United Kingdom
	#define FLM_FA_LANG 								11			///< Farsi
	#define FLM_SU_LANG								12			///< Finnish
	#define FLM_CF_LANG								13			///< French, Canada
	#define FLM_FR_LANG								14			///< French, France
	#define FLM_GA_LANG								15			///< Galician
	#define FLM_DE_LANG								16			///< German, Germany
	#define FLM_SD_LANG								17			///< German, Switzerland
	#define FLM_GR_LANG								18			///< Greek
	#define FLM_HE_LANG								19			///< Hebrew
	#define FLM_HU_LANG								20			///< Hungarian
	#define FLM_IS_LANG								21			///< Icelandic
	#define FLM_IT_LANG								22			///< Italian
	#define FLM_NO_LANG								23			///< Norwegian
	#define FLM_PL_LANG								24			///< Polish
	#define FLM_BR_LANG								25			///< Portuguese, Brazil
	#define FLM_PO_LANG								26			///< Portuguese, Portugal
	#define FLM_RU_LANG								27			///< Russian
	#define FLM_SL_LANG								28			///< Slovak
	#define FLM_ES_LANG								29			///< Spanish
	#define FLM_SV_LANG								30			///< Swedish
	#define FLM_YK_LANG								31			///< Ukrainian
	#define FLM_UR_LANG								32			///< Urdu
	#define FLM_TK_LANG								33			///< Turkey
	#define FLM_JP_LANG								34			///< Japanese
	#define FLM_KO_LANG								35			///< Korean
	#define FLM_CT_LANG								36			///< Chinese-Traditional
	#define FLM_CS_LANG								37			///< Chinese-Simplified
	#define FLM_LA_LANG								38			///< another Asian language
	/// @}
	
	#define FLM_LAST_LANG 							(FLM_LA_LANG + 1)
	#define FLM_FIRST_DBCS_LANG					(FLM_JP_LANG)
	#define FLM_LAST_DBCS_LANG						(FLM_LA_LANG)

	/****************************************************************************
	Desc:	Collation flags and constants
	****************************************************************************/
	
	#define F_HAD_SUB_COLLATION					0x01			// Set if had sub-collating values-diacritics
	#define F_HAD_LOWER_CASE						0x02			// Set if you hit a lowercase character
	#define F_COLL_FIRST_SUBSTRING				0x03			// First substring marker
	#define F_COLL_MARKER 							0x04			// Marks place of sub-collation
	
	#define F_SC_LOWER								0x00			// Only lowercase characters exist
	#define F_SC_MIXED								0x01			// Lower/uppercase flags follow in next byte
	#define F_SC_UPPER								0x02			// Only upper characters exist
	#define F_SC_SUB_COL								0x03			// Sub-collation follows (diacritics|extCh)
	
	#define F_COLL_TRUNCATED						0x0C			// This key piece has been truncated from original
	#define F_MAX_COL_OPCODE						F_COLL_TRUNCATED

	#define F_CHSASCI									0				// ASCII
	#define F_CHSMUL1									1				// Multinational 1
	#define F_CHSMUL2									2				// Multinational 2
	#define F_CHSBOXD									3				// Box drawing
	#define F_CHSSYM1									4				// Typographic Symbols
	#define F_CHSSYM2									5				// Iconic Symbols
	#define F_CHSMATH									6				// Math
	#define F_CHMATHX									7				// Math Extension
	#define F_CHSGREK									8				// Greek
	#define F_CHSHEB									9				// Hebrew
	#define F_CHSCYR									10				// Cyrillic
	#define F_CHSKANA									11				// Japanese Kana
	#define F_CHSUSER									12				// User-defined
	#define F_CHSARB1									13				// Arabic
	#define F_CHSARB2									14				// Arabic script
	
	#define F_NCHSETS									15				// # of character sets (excluding asian)
	#define F_ACHSETS									0x0E0			// maximum character set value - asian
	#define F_ACHSMIN									0x024			// minimum character set value - asian
	#define F_ACHCMAX									0x0FE			// maxmimum character value in asian sets

	/****************************************************************************
	Desc:	Diacritics
	****************************************************************************/
	
	#define F_GRAVE									0
	#define F_CENTERD									1
	#define F_TILDE									2
	#define F_CIRCUM									3
	#define F_CROSSB									4
	#define F_SLASH									5
	#define F_ACUTE									6
	#define F_UMLAUT									7
	#define F_MACRON									8
	
	#define F_APOSAB									9
	#define F_APOSBES									10
	#define F_APOSBA									11
	
	#define F_RING										14
	#define F_DOTA										15
	#define F_DACUTE									16
	#define F_CEDILLA									17
	#define F_OGONEK									18
	#define F_CARON									19
	#define F_STROKE									20
	
	#define F_BREVE									22
	#define F_DOTLESI									239
	#define F_DOTLESJ									25
	
	#define F_GACUTE									83					// greek acute
	#define F_GDIA										84					// greek diaeresis
	#define F_GACTDIA									85					// acute diaeresis
	#define F_GGRVDIA									86					// grave diaeresis
	#define F_GGRAVE									87					// greek grave
	#define F_GCIRCM									88					// greek circumflex
	#define F_GSMOOTH									89					// smooth breathing
	#define F_GROUGH									90					// rough breathing
	#define F_GIOTA									91					// iota subscript
	#define F_GSMACT									92					// smooth breathing acute
	#define F_GRGACT									93					// rough breathing acute
	#define F_GSMGRV									94					// smooth breathing grave
	#define F_GRGGRV									95					// rough breathing grave
	#define F_GSMCIR									96					// smooth breathing circumflex
	#define F_GRGCIR									97					// rough breathing circumflex
	#define F_GACTIO									98					// acute iota
	#define F_GGRVIO									99					// grave iota
	#define F_GCIRIO									100				// circumflex iota
	#define F_GSMIO									101				// smooth iota
	#define F_GRGIO									102				// rough iota
	#define F_GSMAIO									103				// smooth acute iota
	#define F_GRGAIO									104				// rough acute iota
	#define F_GSMGVIO									105				// smooth grave iota
	#define F_GRGGVIO									106				// rough grave iota
	#define F_GSMCIO									107				// smooth circumflex iota
	#define F_GRGCIO									108				// rough circumflex iota
	#define F_GHPRIME									81					// high prime
	#define F_GLPRIME									82					// low prime
	
	#define F_RACUTE									200				// russian acute
	#define F_RGRAVE									201				// russian grave
	#define F_RRTDESC									204				// russian right descender
	#define F_ROGONEK									205				// russian ogonek
	#define F_RMACRON									206				// russian macron

	/****************************************************************************
	Desc:	I/O Flags
	****************************************************************************/
	#define FLM_IO_CURRENT_POS						FLM_MAX_UINT64

	#define FLM_IO_RDONLY							0x0001
	#define FLM_IO_RDWR								0x0002
	#define FLM_IO_EXCL								0x0004
	#define FLM_IO_CREATE_DIR						0x0008
	#define FLM_IO_SH_DENYRW						0x0010
	#define FLM_IO_SH_DENYWR						0x0020
	#define FLM_IO_SH_DENYNONE						0x0040
	#define FLM_IO_DIRECT							0x0080
	#define FLM_IO_DELETE_ON_RELEASE				0x0100
	#define FLM_IO_NO_MISALIGNED					0x0200

	// File Positioning Definitions

	#define FLM_IO_SEEK_SET							0			// Beginning of File
	#define FLM_IO_SEEK_CUR							1			// Current File Pointer Position
	#define FLM_IO_SEEK_END							2			// End of File

	// Maximum file size

	#define FLM_MAXIMUM_FILE_SIZE					0xFFFC0000
	
	// Maximum SEN (compressed number) length
	
	#define FLM_MAX_SEN_LEN							9
	
	// Retrieval flags
	
	#define FLM_INCL									0x0010
	#define FLM_EXCL									0x0020
	#define FLM_EXACT									0x0040
	#define FLM_KEY_EXACT							0x0080
	#define FLM_FIRST									0x0100
	#define FLM_LAST									0x0200
	
	/****************************************************************************
	Desc:	Comparison flags for strings
	IMPORTANT NOTE: If changes are made to these, corresponding changes need to
	be made in the java and C# code where they are defined.
	****************************************************************************/
	/// \addtogroup compare_rules
	/// @{
	#define FLM_COMP_CASE_INSENSITIVE			0x0001		///< 0x0001 = Do case sensitive comparison.
	#define FLM_COMP_COMPRESS_WHITESPACE		0x0002		///< 0x0002 = Compare multiple whitespace characters as a single space.
	#define FLM_COMP_NO_WHITESPACE				0x0004		///< 0x0004 = Ignore all whitespace during comparison.
	#define FLM_COMP_NO_UNDERSCORES				0x0008		///< 0x0008 = Ignore all underscore characters during comparison.
	#define FLM_COMP_NO_DASHES						0x0010		///< 0x0010 = Ignore all dash characters during comparison.
	#define FLM_COMP_WHITESPACE_AS_SPACE		0x0020		///< 0x0020 = Treat newlines and tabs as spaces during comparison.
	#define FLM_COMP_IGNORE_LEADING_SPACE		0x0040		///< 0x0040 = Ignore leading space characters during comparison.
	#define FLM_COMP_IGNORE_TRAILING_SPACE		0x0080		///< 0x0080 = Ignore trailing space characters during comparison.
	#define FLM_COMP_WILD							0x0100
	/// @}

	/****************************************************************************
	Desc:	Colors
	****************************************************************************/
	/// Colors used for logging messages
	typedef enum
	{
 		FLM_BLACK = 0,					///< 0 = Black
		FLM_BLUE,						///< 1 = Blue
		FLM_GREEN,						///< 2 = Green
		FLM_CYAN,						///< 3 = Cyan
		FLM_RED,							///< 4 = Red
		FLM_MAGENTA,					///< 5 = Magenta
		FLM_BROWN,						///< 6 = Brown
		FLM_LIGHTGRAY,					///< 7 = Light Gray
		FLM_DARKGRAY,					///< 8 = Dark Gray
		FLM_LIGHTBLUE,					///< 9 = Light Blue
		FLM_LIGHTGREEN,				///< 10 = Light Green
		FLM_LIGHTCYAN,					///< 11 = Light Cyan
		FLM_LIGHTRED,					///< 12 = Light Red
		FLM_LIGHTMAGENTA,				///< 13 = Light Magenta
		FLM_YELLOW,						///< 14 = Light Yellow
		FLM_WHITE,						///< 15 = White
		FLM_NUM_COLORS,
		FLM_CURRENT_COLOR
	} eColorType;
	
	#define F_FOREBLACK			"%0F"
	#define F_FOREBLUE			"%1F"
	#define F_FOREGREEN			"%2F"
	#define F_FORECYAN			"%3F"
	#define F_FORERED 			"%4F"
	#define F_FOREMAGENTA		"%5F"
	#define F_FOREBROWN			"%6F"
	#define F_FORELIGHTGRAY		"%7F"
	#define F_FOREDARKGRAY		"%8F"
	#define F_FORELIGHTBLUE		"%9F"
	#define F_FORELIGHTGREEN 	"%10F"
	#define F_FORELIGHTCYAN		"%11F"
	#define F_FORELIGHTRED		"%12F"
	#define F_FORELIGHTMAGENTA	"%13F"
	#define F_FOREYELLOW			"%14F"
	#define F_FOREWHITE			"%15F"
	
	#define F_BACKBLACK			"%0B"
	#define F_BACKBLUE			"%1B"
	#define F_BACKGREEN			"%2B"
	#define F_BACKCYAN			"%3B"
	#define F_BACKRED 			"%4B"
	#define F_BACKMAGENTA		"%5B"
	#define F_BACKBROWN			"%6B"
	#define F_BACKLIGHTGRAY		"%7B"
	#define F_BACKDARKGRAY		"%8B"
	#define F_BACKLIGHTBLUE		"%9B"
	#define F_BACKLIGHTGREEN 	"%10B"
	#define F_BACKLIGHTCYAN		"%11B"
	#define F_BACKLIGHTRED		"%12B"
	#define F_BACKLIGHTMAGENTA	"%13B"
	#define F_BACKYELLOW			"%14B"
	#define F_BACKWHITE			"%15B"
	
	#define F_PUSH_FORECOLOR	"%+F"
	#define F_POP_FORECOLOR		"%-F"
	
	#define F_PUSH_BACKCOLOR	"%+B"
	#define F_POP_BACKCOLOR		"%-B"

	#define F_PUSHCOLOR			F_PUSH_FORECOLOR F_PUSH_BACKCOLOR
	#define F_POPCOLOR			F_POP_FORECOLOR F_POP_BACKCOLOR

	#ifdef FLM_PACK_STRUCTS
		#pragma pack(push, 1)
	#endif

	// IMPORTANT NOTE: This structure needs to be kept in sync with corresponding
	// structures and classes in java and C#.
	/****************************************************************************
	/// Structure for reporting slab usage information in cache.
	****************************************************************************/
	typedef struct
	{
		FLMUINT64			ui64Slabs;						///< Total slabs currently allocated.
		FLMUINT64			ui64SlabBytes;					///< Total bytes currently allocated in slabs.
		FLMUINT64			ui64AllocatedCells;			///< Total cells allocated within slabs.
		FLMUINT64			ui64FreeCells;					///< Total cells that are free within slabs.
	} FLM_SLAB_USAGE;

	/****************************************************************************
	/// Structure returned from FlmGetThreadInfo() - contains information about a thread.
	****************************************************************************/
	typedef struct
	{
		FLMUINT		uiThreadId;				///< Operating system thread ID.
		FLMUINT		uiThreadGroup;			///< Thread group this thread belongs to.
		FLMUINT		uiAppId;					///< Application ID that was assigned to the thread when it was started.
		FLMUINT		uiStartTime;			///< Time the thread was started.
		char *		pszThreadName;			///< Name of the thread.
		char *		pszThreadStatus;		///< String indicating the last action the thread reported it was performing.
	} F_THREAD_INFO;

	typedef enum
	{
		FLM_THREAD_STATUS_UNKNOWN = 0,
		FLM_THREAD_STATUS_INITIALIZING,
		FLM_THREAD_STATUS_RUNNING,
		FLM_THREAD_STATUS_SLEEPING,
		FLM_THREAD_STATUS_TERMINATING
	} eThreadStatus;
	
	#define F_THREAD_MIN_STACK_SIZE				(16 * 1024)
	#define F_THREAD_DEFAULT_STACK_SIZE			(16 * 1024)
	
	#define F_DEFAULT_THREAD_GROUP				0
	#define F_INVALID_THREAD_GROUP				0xFFFFFFFF
	
	typedef RCODE (FLMAPI * F_THREAD_FUNC)(IF_Thread *);
	
	/****************************************************************************
	Desc:	Startup and shutdown
	****************************************************************************/
	
	RCODE FLMAPI ftkStartup( void);

	void FLMAPI ftkShutdown( void);

	/****************************************************************************
	Desc: Global data
	****************************************************************************/

	extern FLMUINT16 *	gv_pui16USCollationTable;

	/****************************************************************************
	/// This is a pure virtual base class that other classes inherit from.\   It
	/// provides methods for reference counting (AddRef, Release).
	****************************************************************************/
	flminterface FLMEXP IF_Object
	{
		virtual ~IF_Object()
		{
		}

		virtual FLMINT FLMAPI AddRef( void) = 0;

		virtual FLMINT FLMAPI Release( void) = 0;
		
		virtual FLMINT FLMAPI getRefCount( void) = 0;
	};

	/****************************************************************************
	/// This is the base class that all other classes inherit from.\   It
	/// provides methods for reference counting (AddRef, Release) as well as
	/// methods for overloading new and delete operators.
	****************************************************************************/
	class FLMEXP F_Object : public IF_Object
	{
	public:

		F_Object()
		{
			m_refCnt = 1;
		}

		virtual ~F_Object()
		{
		}

		/// Increment the reference count for this object.
		/// The reference count is the number of pointers that are referencing this object.
		/// Return value is the incremented reference count.
		virtual FLMINT FLMAPI AddRef( void);

		/// Decrement the reference count for this object.
		/// The reference count is the number of pointers that are referencing this object.
		/// Return value is the decremented reference count.  If the reference count goes to
		/// zero, the object will be deleted.
		virtual FLMINT FLMAPI Release( void);

		/// Return the current reference count on the object.
		virtual FLMINT FLMAPI getRefCount( void);

		/// Overloaded new operator for objects of this class.
		void * FLMAPI operator new(
			FLMSIZET			uiSize,				///< Number of bytes to allocate - should be sizeof( ThisClass).
			const char *	pszFile,				///< Name of source file where this allocation is made.
			int				iLine)				///< Line number in source file where this allocation request is made.
		#ifndef FLM_WATCOM_NLM
			throw()
		#endif
			;

		/// Overloaded new operator for objects of this class.
		void * FLMAPI operator new(
			FLMSIZET			uiSize)				///< Number of bytes to allocate - should be sizeof( ThisClass).
		#ifndef FLM_WATCOM_NLM
			throw()
		#endif
			;
	
		/// Overloaded new operator (array) for objects of this class (with source file and line number).
		/// This new operator is called when an array of objects of this class are allocated.
		/// This new operator passes in the current file and line number.  This information is
		/// useful in tracking memory allocations to determine where memory leaks are coming from.
		void * FLMAPI operator new[](
			FLMSIZET			uiSize,				///< Number of bytes to allocate - should be sizeof( ThisClass).
			const char *	pszFile,				///< Name of source file where this allocation is made.
			int				iLine)				///< Line number in source file where this allocation request is made.
		#ifndef FLM_WATCOM_NLM
			throw()
		#endif
			;
		
		/// Overloaded new operator (array) for objects of this class.
		/// This new operator is called when an array of objects of this class are allocated.
		void * FLMAPI operator new[](
			FLMSIZET			uiSize)				///< Number of bytes to allocate - should be sizeof( ThisClass).
		#ifndef FLM_WATCOM_NLM
			throw()
		#endif
			;
		
		/// Overloaded delete operator for objects of this class.
		void FLMAPI operator delete(
			void *			ptr);					///< Pointer to object being freed.
	
		/// Overloaded delete operator (array) for objects of this class.
		void FLMAPI operator delete[](
			void *			ptr);					///< Pointer to array of objects being freed.
			
	#ifndef FLM_WATCOM_NLM
		/// Overloaded delete operator for objects of this class (with source file and line number).
		/// This delete operator passes in the current file and line number.  This information is
		/// useful in tracking memory allocations to determine where memory leaks are coming from.
		void FLMAPI operator delete(
			void *			ptr,					///< Pointer to object being freed.
			const char *	file,					///< Name of source file where this delete occurs.
			int				line);				///< Line number in source file where this delete occurs.
	#endif
	
	#ifndef FLM_WATCOM_NLM
		/// Overloaded delete operator (array) for objects of this class (with source file and line number).
		/// This delete operator is called when an array of objects of this class is freed.
		/// This delete operator passes in the current file and line number.  This information is
		/// useful in tracking memory allocations to determine where memory leaks are coming from.
		void FLMAPI operator delete[](
			void *			ptr,					///< Pointer to object being freed.
			const char *	file,					///< Name of source file where this delete occurs.
			int				line);				///< Line number in source file where this delete occurs.
	#endif

	protected:

		FLMATOMIC		m_refCnt;
	};
	
	/****************************************************************************
	Desc: Internal base class
	****************************************************************************/
	class FLMEXP F_OSBase
	{
	public:

		F_OSBase()
		{ 
			m_refCnt = 1;	
		}

		virtual ~F_OSBase()
		{
		}

		void * operator new(
			FLMSIZET			uiSize,
			const char *	pszFile,
			int				iLine)
		#ifndef FLM_WATCOM_NLM
			throw()
		#endif
			;
	
		void * operator new[](
			FLMSIZET			uiSize,
			const char *	pszFile,
			int				iLine)
		#ifndef FLM_WATCOM_NLM
			throw()
		#endif
			;
		
		void operator delete(
			void *			ptr);
	
		void operator delete[](
			void *			ptr);
			
	#ifndef FLM_WATCOM_NLM
		void operator delete(
			void *			ptr,
			const char *	file,
			int				line);
	#endif
	
	#ifndef FLM_WATCOM_NLM
		void operator delete[](
			void *			ptr,
			const char *	file,
			int				line);
	#endif
			
		virtual FINLINE FLMINT FLMAPI AddRef( void)
		{
			return( ++m_refCnt);
		}

		virtual FINLINE FLMINT FLMAPI Release( void)
		{
			FLMINT		iRefCnt = --m_refCnt;

			if( !iRefCnt)
			{
				delete this;
			}

			return( iRefCnt);
		}

		virtual FINLINE FLMINT FLMAPI getRefCount( void)
		{
			return( m_refCnt);
		}

	protected:

		FLMATOMIC		m_refCnt;
	};

	/****************************************************************************
	Desc:	Errors
	****************************************************************************/
	#ifdef FLM_DEBUG
		RCODE	FLMAPI f_makeErr(
			RCODE				rc,
			const char *	pszFile,
			int				iLine,
			FLMBOOL			bAssert);
			
		FLMINT FLMAPI f_enterDebugger(
			const char *	pszFile,
			int				iLine);
			
		#define RC_SET( rc) \
			f_makeErr( rc, __FILE__, __LINE__, FALSE)
			
		#define RC_SET_AND_ASSERT( rc) \
			f_makeErr( rc, __FILE__, __LINE__, TRUE)
			
		#define RC_UNEXPECTED_ASSERT( rc) \
			f_makeErr( rc, __FILE__, __LINE__, TRUE)
			
		#define f_assert( c) \
			(void)((c) ? 0 : f_enterDebugger( __FILE__, __LINE__))
			
		#define flmAssert( c) \
			f_assert( c)
	#else
		#define RC_SET( rc)							(rc)
		#define RC_SET_AND_ASSERT( rc)			(rc)
		#define RC_UNEXPECTED_ASSERT( rc)
		#define f_assert(c)
		#define flmAssert(c)
	#endif

	/****************************************************************************
	Desc: Memory
	****************************************************************************/
	
	RCODE FLMAPI f_allocImp(
		FLMUINT			uiSize,
		void **			ppvPtr,
		FLMBOOL			bFromNewOp,
		const char *	pszFile,
		int				iLine);
		
	#define f_alloc(s,p) \
		f_allocImp( (s), (void **)(p), FALSE, __FILE__, __LINE__)
		
	RCODE FLMAPI f_callocImp(
		FLMUINT			uiSize,
		void **			ppvPtr,
		const char *	pszFile,
		int				iLine);
	
	#define f_calloc(s,p) \
		f_callocImp( (s), (void **)(p), __FILE__, __LINE__)
		
	RCODE FLMAPI f_reallocImp(
		FLMUINT			uiSize,
		void **			ppvPtr,
		const char *	pszFile,
		int				iLine);
		
	#define f_realloc(s,p) \
		f_reallocImp( (s), (void **)(p), __FILE__, __LINE__)
		
	RCODE FLMAPI f_recallocImp(
		FLMUINT			uiSize,
		void **			ppvPtr,
		const char *	pszFile,
		int				iLine);
		
	#define f_recalloc(s,p) \
		f_recallocImp( (s), (void **)(p), __FILE__, __LINE__)
		
	#define f_new \
		new( __FILE__, __LINE__)
	
	void FLMAPI f_freeImp(
		void **			ppvPtr,
		FLMBOOL			bFromDelOp);
		
	#define f_free(p) \
		f_freeImp( (void **)(p), FALSE)
		
	void f_resetStackInfoImp(
		void *			pvPtr,
		const char *	pszFileName,
		int				iLineNumber);
		
	#define f_resetStackInfo(p) \
		f_resetStackInfoImp( (p), __FILE__, __LINE__)
		
	FLMUINT f_msize(
		void *			pvPtr);
		
	RCODE FLMAPI f_allocAlignedBufferImp(
		FLMUINT			uiMinSize,
		void **			ppvAlloc);
		
	#define f_allocAlignedBuffer(s,p) \
		f_allocAlignedBufferImp( (s), (void **)(p))
		
	void FLMAPI f_freeAlignedBufferImp(
		void **			ppvAlloc);
		
	#define f_freeAlignedBuffer(p) \
		f_freeAlignedBufferImp( (void **)(p))
		
	RCODE FLMAPI f_getMemoryInfo(
		FLMUINT64 *		pui64TotalPhysMem,
		FLMUINT64 *		pui64AvailPhysMem);
	
	FLMBOOL FLMAPI f_canGetMemoryInfo( void);

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_ThreadInfo : public F_Object
	{
		virtual FLMUINT FLMAPI getNumThreads( void) = 0;

		virtual void FLMAPI getThreadInfo(
			FLMUINT					uiThreadNum,
			FLMUINT *				puiThreadId,
			FLMUINT *				puiThreadGroup,
			FLMUINT *				puiAppId,
			FLMUINT *				puiStartTime,
			const char **			ppszThreadName,
			const char **			ppszThreadStatus) = 0;
	};
	
	RCODE FLMAPI FlmGetThreadInfo(
		IF_ThreadInfo **			ppThreadInfo);

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_IStream : public F_Object
	{
		virtual RCODE FLMAPI read(
			void *					pvBuffer,
			FLMUINT					uiBytesToRead,
			FLMUINT *				puiBytesRead = NULL) = 0;

		virtual RCODE FLMAPI closeStream( void) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_PosIStream : public IF_IStream
	{
		virtual FLMUINT64 FLMAPI totalSize( void) = 0;
			
		virtual FLMUINT64 FLMAPI remainingSize( void) = 0;

		virtual RCODE FLMAPI positionTo(
			FLMUINT64				ui64Position) = 0;

		virtual FLMUINT64 FLMAPI getCurrPosition( void) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_BufferIStream : public IF_PosIStream
	{
		virtual RCODE FLMAPI openStream(
			const char *			pucBuffer,
			FLMUINT					uiLength,
			char **					ppucAllocatedBuffer = NULL) = 0;
	
		virtual FLMUINT64 FLMAPI totalSize( void) = 0;
	
		virtual FLMUINT64 FLMAPI remainingSize( void) = 0;
	
		virtual RCODE FLMAPI closeStream( void) = 0;
	
		virtual RCODE FLMAPI positionTo(
			FLMUINT64				ui64Position) = 0;
	
		virtual FLMUINT64 FLMAPI getCurrPosition( void) = 0;
	
		virtual void FLMAPI truncateStream(
			FLMUINT64				ui64Offset = 0) = 0;
			
		virtual RCODE FLMAPI read(
			void *					pvBuffer,
			FLMUINT					uiBytesToRead,
			FLMUINT *				puiBytesRead) = 0;
			
		virtual const FLMBYTE * FLMAPI getBufferAtCurrentOffset( void) = 0;
	};

	RCODE FLMAPI FlmAllocBufferIStream( 
		IF_BufferIStream **		ppIStream);
		
	RCODE FLMAPI FlmOpenBufferIStream( 
		const char *				pucBuffer,
		FLMUINT						uiLength,
		IF_PosIStream **			ppIStream);
		
	RCODE FLMAPI FlmOpenBase64EncoderIStream(
		IF_IStream *				pSourceIStream,
		FLMBOOL						bLineBreaks,
		IF_IStream **				ppIStream);

	RCODE FLMAPI FlmOpenBase64DecoderIStream(
		IF_IStream *				pSourceIStream,
		IF_IStream **				ppIStream);
		
	RCODE FLMAPI FlmOpenFileIStream(
		const char *				pszPath,
		IF_PosIStream **			ppIStream);
		
	RCODE FLMAPI FlmOpenMultiFileIStream(
		const char *				pszDirectory,
		const char *				pszBaseName,
		IF_IStream **				ppIStream);
		
	RCODE FLMAPI FlmOpenBufferedIStream(
		IF_IStream *				pSourceIStream,
		FLMUINT						uiBufferSize,
		IF_IStream **				ppIStream);
		
	RCODE FLMAPI FlmOpenUncompressingIStream(
		IF_IStream *				pIStream,
		IF_IStream **				ppIStream);
		
	RCODE FLMAPI FlmOpenFileOStream(
		const char *				pszFileName,
		FLMBOOL						bTruncateIfExists,
		IF_OStream **				ppOStream);
		
	RCODE FLMAPI FlmOpenMultiFileOStream(
		const char *				pszDirectory,
		const char *				pszBaseName,
		FLMUINT						uiMaxFileSize,
		FLMBOOL						bOkToOverwrite,
		IF_OStream **				ppStream);
		
	RCODE FLMAPI FlmOpenBufferedOStream(
		IF_OStream *				pOStream,
		FLMUINT						uiBufferSize,
		IF_OStream **				ppOStream);
		
	RCODE FLMAPI FlmOpenCompressingOStream(
		IF_OStream *				pOStream,
		IF_OStream **				ppOStream);
		
	RCODE FLMAPI FlmRemoveMultiFileStream(
		const char *				pszDirectory,
		const char *				pszBaseName);
			
	RCODE FLMAPI FlmWriteToOStream(
		IF_IStream *				pIStream,
		IF_OStream *				pOStream);
			
	/****************************************************************************
	Desc:
	****************************************************************************/

	typedef struct
	{
		FLMUINT64		ui64Position;
		FLMUNICODE		uNextChar;
	} F_CollStreamPos;

	flminterface FLMEXP IF_CollIStream : public IF_PosIStream
	{
		virtual RCODE FLMAPI openStream(
			IF_PosIStream *		pIStream,
			FLMBOOL					bUnicodeStream,
			FLMUINT					uiLanguage,
			FLMUINT					uiCompareRules,
			FLMBOOL					bMayHaveWildCards) = 0;
			
		virtual RCODE FLMAPI closeStream( void) = 0;
	
		virtual RCODE FLMAPI read(
			void *					pvBuffer,
			FLMUINT					uiBytesToRead,
			FLMUINT *				puiBytesRead) = 0;
	
		virtual RCODE FLMAPI read(
			FLMBOOL					bAllowTwoIntoOne,
			FLMUNICODE *			puChar,
			FLMBOOL *				pbCharIsWild,
			FLMUINT16 *				pui16Col,
			FLMUINT16 *				pui16SubCol,
			FLMBYTE *				pucCase) = 0;
			
		virtual FLMUINT64 FLMAPI totalSize( void) = 0;
	
		virtual FLMUINT64 FLMAPI remainingSize( void) = 0;
	
		virtual RCODE FLMAPI positionTo(
			FLMUINT64				ui64Position) = 0;
	
		virtual FLMUINT64 FLMAPI getCurrPosition( void) = 0;

		virtual RCODE FLMAPI positionTo(
			F_CollStreamPos *		pPos) = 0;

		virtual void FLMAPI getCurrPosition(
			F_CollStreamPos *		pPos) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_OStream : public F_Object
	{
		virtual RCODE FLMAPI write(
			const void *			pvBuffer,
			FLMUINT					uiBytesToWrite,
			FLMUINT *				puiBytesWritten = NULL) = 0;

		virtual RCODE FLMAPI closeStream( void) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_IOStream : public IF_IStream, public IF_OStream
	{
		#if defined( FLM_WIN) && _MSC_VER < 1300
			using IF_IStream::operator delete;
		#endif
	};
	
	/****************************************************************************
	/// Message severity.
	****************************************************************************/
	typedef enum
	{
		F_FATAL_MESSAGE = 0,			///< Indicates that a fatal error occurred - the kind that would normally
											///< require a shutdown or other corrective action by an administrator.
		F_WARN_MESSAGE,				///< Warning message.
		F_ERR_MESSAGE,					///< Non-fatal error message.
		F_INFO_MESSAGE,				///< Information-only message.
		F_DEBUG_MESSAGE				///< Debug message.
	} eLogMessageSeverity;
	
	/****************************************************************************
	Desc: Logging
	****************************************************************************/

	IF_LogMessageClient * FLMAPI f_beginLogMessage(
		FLMUINT						uiMsgType,
		eLogMessageSeverity		eMsgSeverity);

	void FLMAPI f_logPrintf(
		IF_LogMessageClient *	pLogMessage,
		const char *				pszFormatStr, ...);
	
	void FLMAPI f_logVPrintf(
		IF_LogMessageClient *	pLogMessage,
		const char *				szFormatStr,
		f_va_list *					args);
	
	void FLMAPI f_endLogMessage(
		IF_LogMessageClient **	ppLogMessage);

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_LoggerClient : public F_Object
	{
		virtual IF_LogMessageClient * FLMAPI beginMessage(
			FLMUINT					uiMsgType,
			eLogMessageSeverity	eMsgSeverity = F_DEBUG_MESSAGE) = 0;
	};
	
	void f_setLoggerClient(
		IF_LoggerClient *	pLogger);

	/****************************************************************************
	/// This is an abstract base class that allows an application to catch 
	/// messages.  The application must create an implementation for this class
	/// and then return an object of that class when the 
	/// IF_LoggerClient::beginMessage() method is called.
	****************************************************************************/
	flminterface FLMEXP IF_LogMessageClient : public F_Object
	{
		/// Set the current foreground and background colors for the message.  
		virtual void FLMAPI changeColor(
			eColorType				eForeColor,
			eColorType				eBackColor) = 0;

		/// Append a string to the message.  This method may be called
		/// multiple times by to format a complete message.  The message is not
		/// complete until the ::endMessage() method is called.
		virtual void FLMAPI appendString(
			const char *			pszStr) = 0;

		/// Append a newline to the message.  This method is called when a 
		/// multi-line message is being created.  Rather than embedding a
		/// newline character, this method is used.  This allows an application
		/// to recognize the fact that there are multiple lines in the message
		/// and to log, display, store, etc. (whatever) them accordingly.
		virtual void FLMAPI newline( void) = 0;

		/// End the current message.  The application should finish logging,
		/// displaying, storing, etc. (whatever) the message.  The object
		/// should be reset in case a new message is subsequently started.
		virtual void FLMAPI endMessage( void) = 0;

		virtual void FLMAPI pushForegroundColor( void) = 0;

		virtual void FLMAPI popForegroundColor( void) = 0;

		virtual void FLMAPI pushBackgroundColor( void) = 0;

		virtual void FLMAPI popBackgroundColor( void) = 0;
	};

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_FileSystem : public F_Object
	{
		virtual RCODE FLMAPI createFile(
			const char *			pszFileName,
			FLMUINT					uiIoFlags,
			IF_FileHdl **			ppFile) = 0;

		virtual RCODE FLMAPI createUniqueFile(
			char *					pszPath,
			const char *			pszFileExtension,
			FLMUINT					uiIoFlags,
			IF_FileHdl **			ppFile) = 0;

		virtual RCODE FLMAPI createLockFile(
			const char *			pszPath,
			IF_FileHdl **			ppLockFileHdl) = 0;
	
		virtual RCODE FLMAPI openFile(
			const char *			pszFileName,
			FLMUINT					uiIoFlags,
			IF_FileHdl **			ppFile) = 0;

		virtual RCODE FLMAPI openDir(
			const char *			pszDirName,
			const char *			pszPattern,
			IF_DirHdl **			ppDir) = 0;

		virtual RCODE FLMAPI createDir(
			const char *			pszDirName) = 0;

		virtual RCODE FLMAPI removeDir(
			const char *			pszDirName,
			FLMBOOL					bClear = FALSE) = 0;

		virtual RCODE FLMAPI doesFileExist(
			const char *			pszFileName) = 0;

		virtual FLMBOOL FLMAPI isDir(
			const char *			pszFileName) = 0;

		virtual RCODE FLMAPI getFileTimeStamp(
			const char *			pszFileName,
			FLMUINT *				puiTimeStamp) = 0;

		virtual RCODE FLMAPI getFileSize(
			const char *			pszFileName,
			FLMUINT64 *				pui64FileSize) = 0;
			
		virtual RCODE FLMAPI deleteFile(
			const char *			pszFileName) = 0;

		virtual RCODE FLMAPI deleteMultiFileStream(
			const char *			pszDirectory,
			const char *			pszBaseName) = 0;
	
		virtual RCODE FLMAPI copyFile(
			const char *			pszSrcFileName,
			const char *			pszDestFileName,
			FLMBOOL					bOverwrite,
			FLMUINT64 *				pui64BytesCopied) = 0;

		virtual RCODE FLMAPI copyPartialFile(
			IF_FileHdl *			pSrcFileHdl,
			FLMUINT64				ui64SrcOffset,
			FLMUINT64				ui64SrcSize,
			IF_FileHdl *			pDestFileHdl,
			FLMUINT64				ui64DestOffset,
			FLMUINT64 *				pui64BytesCopiedRV) = 0;
	
		virtual RCODE FLMAPI renameFile(
			const char *			pszFileName,
			const char *			pszNewFileName) = 0;

		virtual RCODE FLMAPI setReadOnly(
			const char *			pszFileName,
			FLMBOOL					bReadOnly) = 0;
			
		virtual RCODE FLMAPI getSectorSize(
			const char *			pszFileName,
			FLMUINT *				puiSectorSize) = 0;
			
		virtual void FLMAPI pathCreateUniqueName(
			FLMUINT *				puiTime,
			char *					pFileName,
			const char *			pFileExt,
			FLMBYTE *				pHighChars,
			FLMBOOL					bModext) = 0;

		virtual void FLMAPI pathParse(
			const char *			pszPath,
			char *					pszServer,
			char *					pszVolume,
			char *					pszDirPath,
			char *					pszFileName) = 0;
	
		virtual RCODE FLMAPI pathReduce(
			const char *			pszSourcePath,
			char *					pszDestPath,
			char *					pszString) = 0;
	
		virtual RCODE FLMAPI pathAppend(
			char *					pszPath,
			const char *			pszPathComponent) = 0;
	
		virtual RCODE FLMAPI pathToStorageString(
			const char *			pPath,
			char *					pszString) = 0;
	
		virtual FLMBOOL FLMAPI doesFileMatch(
			const char *			pszFileName,
			const char *			pszTemplate) = 0;
			
		virtual FLMBOOL FLMAPI canDoAsync( void) = 0;
		
		virtual RCODE FLMAPI allocIOBuffer(
			FLMUINT					uiMinSize,
			IF_IOBuffer **			ppIOBuffer) = 0;
			
		virtual RCODE FLMAPI allocFileHandleCache(
			FLMUINT					uiMaxCachedFiles,
			FLMUINT					uiIdleTimeoutSecs,
			IF_FileHdlCache **	ppFileHdlCache) = 0;
	};
	
	RCODE FLMAPI FlmGetFileSystem(
		IF_FileSystem **		ppFileSystem);

	IF_FileSystem * FLMAPI f_getFileSysPtr( void);

	FLMUINT FLMAPI f_getOpenFileCount( void);
	
	RCODE FLMAPI f_chdir(
		const char *			pszDir);
		
	RCODE FLMAPI f_getcwd(
		char *					pszDir);
		
	RCODE FLMAPI f_pathReduce(
		const char *			pszSourcePath,
		char *					pszDestPath,
		char *					pszString);

	RCODE FLMAPI f_pathAppend(
		char *					pszPath,
		const char *			pszPathComponent);
			
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_FileHdl : virtual public F_Object
	{
		virtual RCODE FLMAPI flush( void) = 0;

		virtual RCODE FLMAPI read(
			FLMUINT64				ui64Offset,
			FLMUINT					uiLength,
			void *					pvBuffer,
			FLMUINT *				puiBytesRead = NULL) = 0;

		virtual RCODE FLMAPI read(
			FLMUINT64				ui64ReadOffset,
			FLMUINT					uiBytesToRead,
			IF_IOBuffer *			pIOBuffer) = 0;
			
		virtual RCODE FLMAPI write(
			FLMUINT64				ui64Offset,
			FLMUINT					uiLength,
			const void *			pvBuffer,
			FLMUINT *				puiBytesWritten = NULL) = 0;

		virtual RCODE FLMAPI write(
			FLMUINT64				ui64WriteOffset,
			FLMUINT					uiBytesToWrite,
			IF_IOBuffer *			pIOBuffer) = 0;
			
		virtual RCODE FLMAPI seek(
			FLMUINT64				ui64Offset,
			FLMINT					iWhence,
			FLMUINT64 *				pui64NewOffset = NULL) = 0;

		virtual RCODE FLMAPI size(
			FLMUINT64 *				pui64Size) = 0;

		virtual RCODE FLMAPI tell(
			FLMUINT64 *				pui64Offset) = 0;
			
		virtual RCODE FLMAPI extendFile(
			FLMUINT64				ui64FileSize) = 0;

		virtual RCODE FLMAPI truncateFile(
			FLMUINT64				ui64FileSize = 0) = 0;

		virtual RCODE FLMAPI closeFile( void) = 0;

		virtual FLMBOOL FLMAPI canDoAsync( void) = 0;
		
		virtual FLMBOOL FLMAPI canDoDirectIO( void) = 0;

		virtual void FLMAPI setExtendSize(
			FLMUINT					uiExtendSize) = 0;

		virtual void FLMAPI setMaxAutoExtendSize(
			FLMUINT					uiMaxAutoExtendSize) = 0;
			
		virtual FLMUINT FLMAPI getSectorSize( void) = 0;
			
		virtual FLMBOOL FLMAPI isReadOnly( void) = 0;
		
		virtual FLMBOOL FLMAPI isOpen( void) = 0;
		
		virtual RCODE FLMAPI lock( void) = 0;
	
		virtual RCODE FLMAPI unlock( void) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_FileHdlCache : public F_Object
	{
		virtual RCODE FLMAPI openFile(
			const char *			pszFileName,
			FLMUINT					uiIoFlags,
			IF_FileHdl **			ppFile) = 0;
		
		virtual RCODE FLMAPI createFile(
			const char *			pszFileName,
			FLMUINT					uiIoFlags,
			IF_FileHdl **			ppFile) = 0;

		virtual void FLMAPI closeUnusedFiles( 
			FLMUINT					uiUnusedTime = 0) = 0;
			
		virtual FLMUINT FLMAPI getOpenThreshold( void) = 0;
		
		virtual RCODE FLMAPI setOpenThreshold(
			FLMUINT					uiMaxOpenFiles) = 0;
	};

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_MultiFileHdl : public F_Object
	{
		virtual RCODE FLMAPI createFile(
			const char *			pszPath) = 0;
	
		virtual RCODE FLMAPI createUniqueFile(
			const char *			pszPath,
			const char *			pszFileExtension) = 0;
	
		virtual RCODE FLMAPI openFile(
			const char *			pszPath) = 0;
	
		virtual RCODE FLMAPI deleteMultiFile(
			const char *			pszPath) = 0;
	
		virtual RCODE FLMAPI flush( void) = 0;
	
		virtual RCODE FLMAPI read(
			FLMUINT64				ui64Offset,
			FLMUINT					uiLength,
			void *					pvBuffer,
			FLMUINT *				puiBytesRead = NULL) = 0;
	
		virtual RCODE FLMAPI write(
			FLMUINT64				ui64Offset,
			FLMUINT					uiLength,
			void *					pvBuffer,
			FLMUINT *				puiBytesWritten = NULL) = 0;
	
		virtual RCODE FLMAPI getPath(
			char *					pszFilePath) = 0;
	
		virtual RCODE FLMAPI size(
			FLMUINT64 *				pui64FileSize) = 0;
	
		virtual RCODE FLMAPI truncateFile(
			FLMUINT64				ui64Offset = 0) = 0;
			
		virtual void FLMAPI closeFile(
			FLMBOOL					bDelete = FALSE) = 0;
	};
	
	RCODE FLMAPI FlmAllocMultiFileHdl(
		IF_MultiFileHdl **		ppFileHdl);
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_SuperFileClient : public F_Object
	{
		virtual FLMUINT FLMAPI getFileNumber(
			FLMUINT					uiBlockAddr) = 0;
			
		virtual FLMUINT FLMAPI getFileOffset(
			FLMUINT					uiBlockAddr) = 0;
			
		virtual FLMUINT FLMAPI getBlockAddress(
			FLMUINT					uiFileNumber,
			FLMUINT					uiFileOffset) = 0;
			
		virtual RCODE FLMAPI getFilePath(
			FLMUINT					uiFileNumber,
			char *					pszPath) = 0;
			
		virtual FLMUINT64 FLMAPI getMaxFileSize( void) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class F_SuperFileHdl : public F_Object
	{
	public:
	
		F_SuperFileHdl();
	
		virtual ~F_SuperFileHdl();
	
		RCODE FLMAPI setup(
			IF_SuperFileClient *		pSuperFileClient,
			IF_FileHdlCache *			pFileHdlCache,
			FLMUINT						uiFileOpenFlags,
			FLMUINT						uiFileCreateFlags);
	
		RCODE FLMAPI createFile(
			FLMUINT					uiFileNumber,
			IF_FileHdl **			ppFileHdl = NULL);
			
		RCODE	FLMAPI getFileHdl(
			FLMUINT					uiFileNumber,
			FLMBOOL					bGetForUpdate,
			IF_FileHdl **			ppFileHdlRV);
	
		RCODE FLMAPI readBlock(
			FLMUINT					uiBlkAddress,
			FLMUINT					uiBytesToRead,
			void *					pvBuffer,
			FLMUINT *				puiBytesRead);
	
		RCODE FLMAPI writeBlock(
			FLMUINT					uiBlkAddress,
			FLMUINT					uiBytesToWrite,
			const void *			pvBuffer,
			FLMUINT *				puiBytesWritten);
	
		RCODE FLMAPI writeBlock(
			FLMUINT					uiBlkAddress,
			FLMUINT					uiBytesToWrite,
			IF_IOBuffer *			pIOBuffer);
			
		RCODE FLMAPI getFilePath(
			FLMUINT					uiFileNumber,
			char *					pszPath);
	
		RCODE FLMAPI getFileSize(
			FLMUINT					uiFileNumber,
			FLMUINT64 *				pui64FileSize);
	
		RCODE FLMAPI releaseFiles( void);
	
		RCODE	FLMAPI allocateBlocks(
			FLMUINT					uiStartAddress,
			FLMUINT					uiEndAddress);
			
		RCODE FLMAPI truncateFile(
			FLMUINT					uiEOFBlkAddress);
	
		RCODE FLMAPI truncateFile(
			FLMUINT					uiFileNumber,
			FLMUINT					uiOffset);

		void FLMAPI truncateFiles(
			FLMUINT					uiStartFileNum,
			FLMUINT					uiEndFileNum);
	
		RCODE FLMAPI flush( void);
	
		FINLINE void FLMAPI setExtendSize(
			FLMUINT		uiExtendSize)
		{
			m_uiExtendSize = uiExtendSize;
		}
	
		FINLINE void FLMAPI setMaxAutoExtendSize(
			FLMUINT		uiMaxAutoExtendSize)
		{
			m_uiMaxAutoExtendSize = uiMaxAutoExtendSize;
		}
	
		FLMBOOL FLMAPI canDoAsync( void);
		
		FLMBOOL FLMAPI canDoDirectIO( void);
	
	private:
	
		IF_SuperFileClient *		m_pSuperFileClient;
		IF_FileHdlCache *			m_pFileHdlCache;
		IF_FileHdl *				m_pCFileHdl;
		IF_FileHdl *				m_pBlockFileHdl;
		FLMBOOL						m_bCFileDirty;
		FLMBOOL						m_bBlockFileDirty;
		FLMUINT						m_uiBlockFileNum;
		FLMUINT						m_uiMaxFileSize;
		FLMUINT						m_uiExtendSize;
		FLMUINT						m_uiMaxAutoExtendSize;
		FLMUINT						m_uiFileOpenFlags;
		FLMUINT						m_uiFileCreateFlags;
	};

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_AsyncClient : virtual public F_Object
	{
		virtual RCODE FLMAPI waitToComplete( void) = 0;
		
		virtual RCODE FLMAPI getCompletionCode( void) = 0;
		
		virtual FLMUINT FLMAPI getElapsedTime( void) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	typedef void (FLMAPI * F_BUFFER_COMPLETION_FUNC)(IF_IOBuffer *, void *);

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_IOBuffer : virtual public F_Object
	{
		virtual FLMBYTE * FLMAPI getBufferPtr( void) = 0;
	
		virtual FLMUINT FLMAPI getBufferSize( void) = 0;
		
		virtual void FLMAPI setCompletionCallback(
			F_BUFFER_COMPLETION_FUNC	fnCompletion,
			void *							pvData) = 0;
			
		virtual RCODE FLMAPI addCallbackData(
			void *							pvData) = 0;
			
		virtual void * FLMAPI getCallbackData(
			FLMUINT							uiSlot) = 0;
			
		virtual FLMUINT FLMAPI getCallbackDataCount( void) = 0;
			
		virtual void FLMAPI setAsyncClient(
			IF_AsyncClient *				pAsyncClient) = 0;
			
		virtual void FLMAPI notifyComplete(
			RCODE								completionRc) = 0;
			
		virtual void FLMAPI setPending( void) = 0;
		
		virtual void FLMAPI clearPending( void) = 0;
		
		virtual FLMBOOL FLMAPI isPending( void) = 0;
		
		virtual FLMBOOL FLMAPI isComplete( void) = 0;
		
		virtual RCODE FLMAPI waitToComplete( void) = 0;
		
		virtual RCODE FLMAPI getCompletionCode( void) = 0;

		virtual FLMUINT FLMAPI getElapsedTime( void) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_IOBufferMgr : public F_Object
	{
		virtual RCODE FLMAPI getBuffer(
			FLMUINT					uiBufferSize,
			IF_IOBuffer **			ppIOBuffer) = 0;
	
		virtual FLMBOOL FLMAPI isIOPending( void) = 0;
		
		virtual RCODE FLMAPI waitForAllPendingIO( void) = 0;
	};
	
	RCODE FLMAPI FlmAllocIOBufferMgr(
		FLMUINT					uiMaxBuffers,
		FLMUINT					uiMaxBytes,
		FLMBOOL					bReuseBuffers,
		IF_IOBufferMgr **		ppIOBufferMgr);
		
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_DirHdl : public F_Object
	{
		virtual RCODE FLMAPI next( void) = 0;

		virtual const char * FLMAPI currentItemName( void) = 0;

		virtual void FLMAPI currentItemPath(
			char *					pszPath) = 0;

		virtual FLMUINT64 FLMAPI currentItemSize( void) = 0;

		virtual FLMBOOL FLMAPI currentItemIsDir( void) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_ResultSetCompare : public F_Object
	{
		virtual RCODE FLMAPI compare(
			const void *			pvData1,
			FLMUINT					uiLength1,
			const void *			pvData2,
			FLMUINT					uiLength2,
			FLMINT *					piCompare) = 0;
	};

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_ResultSetSortStatus : public F_Object
	{
		virtual RCODE FLMAPI reportSortStatus(
			FLMUINT64				ui64EstTotalUnits,
			FLMUINT64				ui64UnitsDone) = 0;
	};

	#define RS_POSITION_NOT_SET			FLM_MAX_UINT64

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_ResultSet : public F_Object
	{
		virtual RCODE FLMAPI setupResultSet(
			const char *				pszPath,
			IF_ResultSetCompare *	pCompare,
			FLMUINT						uiEntrySize,
			FLMBOOL						bDropDuplicates = TRUE,
			FLMBOOL						bEntriesInOrder = FALSE,
			const char *				pszFileName = NULL) = 0;

		virtual FLMUINT64 FLMAPI getTotalEntries( void) = 0;

		virtual RCODE FLMAPI addEntry(
			const void *			pvEntry,
			FLMUINT					uiEntryLength = 0) = 0;

		virtual RCODE FLMAPI finalizeResultSet(
			IF_ResultSetSortStatus *	pSortStatus = NULL,
			FLMUINT64 *						pui64TotalEntries = NULL) = 0;

		virtual RCODE FLMAPI getFirst(
			void *					pvEntryBuffer,
			FLMUINT					uiBufferLength = 0,
			FLMUINT *				puiEntryLength = NULL) = 0;

		virtual RCODE FLMAPI getNext(
			void *					pvEntryBuffer,
			FLMUINT					uiBufferLength = 0,
			FLMUINT *				puiEntryLength = NULL) = 0;

		virtual RCODE FLMAPI getLast(
			void *					pvEntryBuffer,
			FLMUINT					uiBufferLength = 0,
			FLMUINT *				puiEntryLength = NULL) = 0;

		virtual RCODE FLMAPI getPrev(
			void *					pvEntryBuffer,
			FLMUINT					uiBufferLength = 0,
			FLMUINT *				puiEntryLength = NULL) = 0;

		virtual RCODE FLMAPI getCurrent(
			void *					pvEntryBuffer,
			FLMUINT					uiBufferLength = 0,
			FLMUINT *				puiEntryLength = NULL) = 0;

		virtual RCODE FLMAPI findMatch(
			const void *			pvMatchEntry,
			void *					pvFoundEntry) = 0;

		virtual RCODE FLMAPI findMatch(
			const void *			pvMatchEntry,
			FLMUINT					uiMatchEntryLength,
			void *					pvFoundEntry,
			FLMUINT *				puiFoundEntryLength) = 0;

		virtual RCODE FLMAPI modifyCurrent(
			const void *			pvEntry,
			FLMUINT					uiEntryLength = 0) = 0;

		virtual FLMUINT64 FLMAPI getPosition( void) = 0;

		virtual RCODE FLMAPI setPosition(
			FLMUINT64				ui64Position) = 0;

		virtual RCODE FLMAPI resetResultSet(
			FLMBOOL					bDelete = TRUE) = 0;

		virtual RCODE FLMAPI flushToFile( void) = 0;

	};
	
	RCODE FLMAPI FlmAllocResultSet(
		IF_ResultSet **			ppResultSet);

	/*****************************************************************************
	Desc:
	*****************************************************************************/
	flminterface FLMEXP IF_BTreeResultSet : public F_Object
	{
		virtual RCODE FLMAPI addEntry(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyLength,
			FLMBYTE *				pucEntry,
			FLMUINT					uiEntryLength) = 0;
	
		virtual RCODE FLMAPI modifyEntry(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyLength,
			FLMBYTE *				pucEntry,
			FLMUINT					uiEntryLength) = 0;
	
		virtual RCODE FLMAPI getCurrent(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyLength,
			FLMBYTE *				pucEntry,
			FLMUINT					uiEntryLength,
			FLMUINT *				puiReturnLength) = 0;
	
		virtual RCODE FLMAPI getNext(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyBufLen,
			FLMUINT *				puiKeylen,
			FLMBYTE *				pucBuffer,
			FLMUINT					uiBufferLength,
			FLMUINT *				puiReturnLength) = 0;
	
		virtual RCODE FLMAPI getPrev(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyBufLen,
			FLMUINT *				puiKeylen,
			FLMBYTE *				pucBuffer,
			FLMUINT					uiBufferLength,
			FLMUINT *				puiReturnLength) = 0;
	
		virtual RCODE FLMAPI getFirst(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyBufLen,
			FLMUINT *				puiKeylen,
			FLMBYTE *				pucBuffer,
			FLMUINT					uiBufferLength,
			FLMUINT *				puiReturnLength) = 0;
	
		virtual RCODE FLMAPI getLast(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyBufLen,
			FLMUINT *				puiKeylen,
			FLMBYTE *				pucBuffer,
			FLMUINT					uiBufferLength,
			FLMUINT *				puiReturnLength) = 0;
	
		virtual RCODE FLMAPI findEntry(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyBufLen,
			FLMUINT *				puiKeylen,
			FLMBYTE *				pucBuffer,
			FLMUINT					uiBufferLength,
			FLMUINT *				puiReturnLength) = 0;
	
		virtual RCODE FLMAPI deleteEntry(
			FLMBYTE *				pucKey,
			FLMUINT					uiKeyLength) = 0;
	};

	/****************************************************************************
	Desc: Random numbers
	****************************************************************************/
	
	#define FLM_MAX_RANDOM  ((FLMUINT32)2147483646)

	flminterface FLMEXP IF_RandomGenerator : public F_Object
	{
		virtual void FLMAPI randomize( void) = 0;

		virtual void FLMAPI setSeed(
			FLMUINT32				ui32seed) = 0;
			
		virtual FLMUINT32 FLMAPI getSeed( void) = 0;

		virtual FLMUINT32 FLMAPI getUINT32(
			FLMUINT32 				ui32Low = 0,
			FLMUINT32 				ui32High = FLM_MAX_RANDOM) = 0;

		virtual FLMBOOL FLMAPI getBoolean( void) = 0;
	};
	
	RCODE FLMAPI FlmAllocRandomGenerator(
		IF_RandomGenerator **	ppRandomGenerator);
		
	FLMUINT32 FLMAPI f_getRandomUINT32(
		FLMUINT32					ui32Low = 0,
		FLMUINT32					ui32High = FLM_MAX_RANDOM);
	
	FLMBYTE FLMAPI f_getRandomByte( void);
		
	/**********************************************************************
	Desc:	Atomic operations
	**********************************************************************/
	FLMINT32 FLMAPI f_atomicInc(
		FLMATOMIC *					piTarget);
	
	FLMINT32 FLMAPI f_atomicDec(
		FLMATOMIC *					piTarget);
	
	FLMINT32 FLMAPI f_atomicExchange(
		FLMATOMIC *					piTarget,
		FLMINT32						i32NewVal);
		
	/****************************************************************************
	Desc: Mutexes
	****************************************************************************/
	typedef void *					F_MUTEX;
	#define F_MUTEX_NULL			NULL
	
	RCODE FLMAPI f_mutexCreate(
		F_MUTEX *					phMutex);
	
	void FLMAPI f_mutexDestroy(
		F_MUTEX *					phMutex);
			
	void FLMAPI f_mutexLock(
		F_MUTEX						hMutex);
		
	void FLMAPI f_mutexUnlock(
		F_MUTEX						hMutex);

#ifdef FLM_DEBUG
	void FLMAPI f_assertMutexLocked(
		F_MUTEX						hMutex);
#else
	#define f_assertMutexLocked( h) (void)(h)
#endif

#ifdef FLM_DEBUG
	void FLMAPI f_assertMutexNotLocked(
		F_MUTEX						hMutex);
#else
	#define f_assertMutexNotLocked( h) (void)(h)
#endif
		
	/****************************************************************************
	Desc: Semaphores
	****************************************************************************/
	typedef void *					F_SEM;
	#define F_SEM_NULL			NULL
	
	RCODE FLMAPI f_semCreate(
		F_SEM *						phSem);
	
	void FLMAPI f_semDestroy(
		F_SEM *						phSem);
	
	RCODE FLMAPI f_semWait(
		F_SEM							hSem,
		FLMUINT						uiTimeout);
	
	void FLMAPI f_semSignal(
		F_SEM							hSem);

	FLMUINT FLMAPI f_semGetSignalCount(
		F_SEM							hSem);

	/****************************************************************************
	Desc: Notify Lists
	****************************************************************************/
		
	typedef struct F_NOTIFY_LIST_ITEM
	{
		F_NOTIFY_LIST_ITEM *		pNext;		///< Pointer to next F_NOTIFY_LIST_ITEM structure in list.
		FLMUINT						uiThreadId;	///< ID of thread requesting the notify
		RCODE  *						pRc;			///< Pointer to a return code variable that is to
														///< be filled in when the operation is completed.
														///< The thread requesting notification supplies
														///< the return code variable to be filled in.
		void *						pvData;		///< Data that is passed through to a custom
														///< notify routine
		F_SEM							hSem;			///< Semaphore that will be signaled when the
														///< operation is complete.
	} F_NOTIFY_LIST_ITEM;

	RCODE FLMAPI f_notifyWait(
		F_MUTEX						hMutex,
		F_SEM							hSem,
		void *						pvData,
		F_NOTIFY_LIST_ITEM **	ppNotifyList);
		
	void FLMAPI f_notifySignal(
		F_NOTIFY_LIST_ITEM *		pNotifyList,
		RCODE							notifyRc);
		
	/****************************************************************************
	Desc: Reader / Writer Locks
	****************************************************************************/
	typedef void *					F_RWLOCK;
	#define F_RWLOCK_NULL		NULL
	
	RCODE FLMAPI f_rwlockCreate(
		F_RWLOCK *					phReadWriteLock);
		
	void FLMAPI f_rwlockDestroy(
		F_RWLOCK *					phReadWriteLock);
		
	RCODE FLMAPI f_rwlockAcquire(
		F_RWLOCK						hReadWriteLock,
		F_SEM							hSem,
		FLMBOOL						bWriter);
		
	RCODE FLMAPI f_rwlockPromote(
		F_RWLOCK						hReadWriteLock,
		F_SEM							hSem);
		
	RCODE FLMAPI f_rwlockRelease(
		F_RWLOCK						hReadWriteLock);
	
	/****************************************************************************
	Desc: Thread manager
	****************************************************************************/
	flminterface FLMEXP IF_ThreadMgr : public F_Object
	{
		virtual RCODE FLMAPI setupThreadMgr( void) = 0;
		
		virtual RCODE FLMAPI createThread(
			IF_Thread **			ppThread,
			F_THREAD_FUNC			fnThread,
			const char *			pszThreadName = NULL,
			FLMUINT					uiThreadGroup = 0,
			FLMUINT					uiAppId = 0,
			void *					pvParm1 = NULL,
			void *					pvParm2 = NULL,
			FLMUINT					uiStackSize = F_THREAD_DEFAULT_STACK_SIZE) = 0;
	
		virtual void FLMAPI shutdownThreadGroup(
			FLMUINT					uiThreadGroup) = 0;
	
		virtual void FLMAPI setThreadShutdownFlag(
			FLMUINT					uiThreadId) = 0;
	
		virtual RCODE FLMAPI findThread(
			IF_Thread **			ppThread,
			FLMUINT					uiThreadGroup,
			FLMUINT					uiAppId = 0,
			FLMBOOL					bOkToFindMe = TRUE) = 0;
	
		virtual RCODE FLMAPI getNextGroupThread(
			IF_Thread **			ppThread,
			FLMUINT					uiThreadGroup,
			FLMUINT *				puiThreadId) = 0;
	
		virtual RCODE FLMAPI getThreadInfo(
			F_Pool *					pPool,
			F_THREAD_INFO **		ppThreadInfo,
			FLMUINT *				puiNumThreads) = 0;
			
		virtual RCODE FLMAPI getThreadName(
			FLMUINT					uiThreadId,
			char *					pszThreadName,
			FLMUINT *				puiLength) = 0;
	
		virtual FLMUINT FLMAPI getThreadGroupCount(
			FLMUINT					uiThreadGroup) = 0;
			
		virtual FLMUINT FLMAPI allocGroupId( void) = 0;
	};
	
	RCODE FLMAPI FlmGetThreadMgr(
		IF_ThreadMgr **			ppThreadMgr);

	/****************************************************************************
	Desc: Thread
	****************************************************************************/
	flminterface FLMEXP IF_Thread : public F_Object
	{
		virtual RCODE FLMAPI startThread(
			F_THREAD_FUNC			fnThread,
			const char *			pszThreadName = NULL,
			FLMUINT					uiThreadGroup = F_DEFAULT_THREAD_GROUP,
			FLMUINT					uiAppId = 0,
			void *					pvParm1 = NULL,
			void *					pvParm2 = NULL,
			FLMUINT        		uiStackSize = F_THREAD_DEFAULT_STACK_SIZE) = 0;
	
		virtual void FLMAPI stopThread( void) = 0;
	
		virtual FLMUINT FLMAPI getThreadId( void) = 0;
	
		virtual FLMBOOL FLMAPI getShutdownFlag( void) = 0;
	
		virtual RCODE FLMAPI getExitCode( void) = 0;
	
		virtual void * FLMAPI getParm1( void) = 0;
	
		virtual void FLMAPI setParm1(
			void *					pvParm) = 0;
	
		virtual void * FLMAPI getParm2( void) = 0;
	
		virtual void FLMAPI setParm2(
			void *					pvParm) = 0;
	
		virtual void FLMAPI setShutdownFlag( void) = 0;
	
		virtual FLMBOOL FLMAPI isThreadRunning( void) = 0;
	
		virtual void FLMAPI setThreadStatusStr(
			const char *			pszStatus) = 0;
	
		virtual void FLMAPI setThreadStatus(
			const char *			pszBuffer, ...) = 0;
	
		virtual void FLMAPI setThreadStatus(
			eThreadStatus			genericStatus) = 0;
	
		virtual void FLMAPI setThreadAppId(
			FLMUINT					uiAppId) = 0;
	
		virtual FLMUINT FLMAPI getThreadAppId( void) = 0;
	
		virtual FLMUINT FLMAPI getThreadGroup( void) = 0;
	
		virtual void FLMAPI cleanupThread( void) = 0;
		
		virtual void FLMAPI sleep(
			FLMUINT					uiMilliseconds) = 0;
			
		virtual void FLMAPI waitToComplete( void) = 0;
	};
	
	RCODE FLMAPI f_threadCreate(
		IF_Thread **			ppThread,
		F_THREAD_FUNC			fnThread,
		const char *			pszThreadName = NULL,
		FLMUINT					uiThreadGroup = F_DEFAULT_THREAD_GROUP,
		FLMUINT					uiAppId = 0,
		void *					pvParm1 = NULL,
		void *					pvParm2 = NULL,
		FLMUINT					uiStackSize = F_THREAD_DEFAULT_STACK_SIZE);
	
	void FLMAPI f_threadDestroy(
		IF_Thread **			ppThread);
	
	FLMUINT FLMAPI f_threadId( void);

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_IniFile : public F_Object
	{
		virtual RCODE FLMAPI read(
			const char *			pszFileName) = 0;
			
		virtual RCODE FLMAPI write( void) = 0;
	
		virtual FLMBOOL FLMAPI getParam(
			const char *			pszParamName,
			FLMUINT *				puiParamVal) = 0;
		
		virtual FLMBOOL FLMAPI getParam(
			const char *			pszParamName,
			FLMBOOL *				pbParamVal) = 0;
		
		virtual FLMBOOL FLMAPI getParam(
			const char *			pszParamName,
			char **					ppszParamVal) = 0;
		
		virtual RCODE FLMAPI setParam(
			const char *			pszParamName,
			FLMUINT 					uiParamVal) = 0;
	
		virtual RCODE FLMAPI setParam(
			const char *			pszParamName,
			FLMBOOL					bParamVal) = 0;
	
		virtual RCODE FLMAPI setParam(
			const char *			pszParamName,
			const char *			pszParamVal) = 0;
	
		virtual FLMBOOL FLMAPI testParam(
			const char *			pszParamName) = 0;
	};
	
	RCODE FLMAPI FlmAllocIniFile(
		IF_IniFile **				ppIniFile);
	
	/****************************************************************************
	Desc: Serial numbers
	****************************************************************************/
	RCODE FLMAPI f_createSerialNumber(
		FLMBYTE *					pszSerialNumber);

	#define F_SERIAL_NUM_SIZE				16

	/****************************************************************************
	Desc: Checksum
	****************************************************************************/
	void FLMAPI f_updateCRC(
		const void *				pvBuffer,
		FLMUINT						uiLength,
		FLMUINT32 *					pui32CRC);
		
	FLMUINT32 FLMAPI f_calcFastChecksum(
		const void *				pvBuffer,
		FLMUINT						uiLength,
		FLMUINT *					puiSum = NULL,
		FLMUINT *					puiXOR = NULL);

	FLMBYTE FLMAPI f_calcPacketChecksum(
		const void *				pvPacket,
		FLMUINT						uiBytesToChecksum);
		
	/****************************************************************************
	Desc:
	****************************************************************************/
	char * FLMAPI f_uwtoa(
		FLMUINT16					value,
		char *						ptr);

	char * FLMAPI f_udtoa(
		FLMUINT						value,
		char *						ptr);

	char * FLMAPI f_wtoa(
		FLMINT16						value,
		char *						ptr);

	char * FLMAPI f_dtoa(
		FLMINT						value,
		char *						ptr);

	char * FLMAPI f_ui64toa(
		FLMUINT64					value,
		char *						ptr);

	char * FLMAPI f_i64toa(
		FLMINT64						value,
		char *						ptr);

	FLMINT FLMAPI f_atoi(
		const char *				ptr);

	FLMINT FLMAPI f_atol(
		const char *				ptr);

	FLMINT FLMAPI f_atod(
		const char *				ptr);

	FLMUINT FLMAPI f_atoud(
		const char *				ptr,
		FLMBOOL						bAllowUnprefixedHex = FALSE);

	FLMUINT64 FLMAPI f_atou64(
		const char *  				pszBuf);

	FLMUINT FLMAPI f_unilen(
		const FLMUNICODE *		puzStr);

	FLMUNICODE * FLMAPI f_unicpy(
		FLMUNICODE *				puzDestStr,
		const FLMUNICODE *		puzSrcStr);

	FLMBOOL FLMAPI f_uniIsUpper(
		FLMUNICODE					uChar);
		
	FLMBOOL FLMAPI f_uniIsLower(
		FLMUNICODE					uChar);
	
	FLMBOOL FLMAPI f_uniIsAlpha(
		FLMUNICODE					uChar);
	
	FLMBOOL FLMAPI f_uniIsDecimalDigit(
		FLMUNICODE					uChar);
	
	FLMUNICODE FLMAPI f_uniToLower(
		FLMUNICODE					uChar);

	FLMINT FLMAPI f_unicmp(
		const FLMUNICODE *		puzStr1,
		const FLMUNICODE *		puzStr2);

	FLMINT FLMAPI f_uniicmp(
		const FLMUNICODE *		puzStr1,
		const FLMUNICODE *		puzStr2);

	FLMINT FLMAPI f_uninativecmp(
		const FLMUNICODE *		puzStr1,
		const char *				pszStr2);

	FLMINT FLMAPI f_uninativencmp(
		const FLMUNICODE *		puzStr1,
		const char  *				pszStr2,
		FLMUINT						uiCount);

	RCODE	FLMAPI f_nextUCS2Char(
		const FLMBYTE **			ppszUTF8,
		const FLMBYTE *			pszEndOfUTF8String,
		FLMUNICODE *				puzChar);
	
	RCODE FLMAPI f_numUCS2Chars(
		const FLMBYTE *			pszUTF8,
		FLMUINT *					puiNumChars);
	
	FLMBOOL FLMAPI f_isWhitespace(
		FLMUNICODE					ucChar);

	FLMUNICODE FLMAPI f_convertChar(
		FLMUNICODE					uzChar,
		FLMUINT						uiCompareRules);
	
	RCODE FLMAPI f_wpToUnicode(
		FLMUINT16					ui16WPChar,
		FLMUNICODE *				puUniChar);
	
	FLMBOOL FLMAPI f_unicodeToWP(
		FLMUNICODE					uUniChar,
		FLMUINT16 *					pui16WPChar);
		
	FLMBOOL FLMAPI f_depricatedUnicodeToWP(
		FLMUNICODE					uUniChar,
		FLMUINT16 *					pui16WPChar);

	FLMUINT16 FLMAPI f_wpUpper(
		FLMUINT16					ui16WpChar);
	
	FLMBOOL FLMAPI f_wpIsUpper(
		FLMUINT16					ui16WpChar);
	
	FLMUINT16 FLMAPI f_wpLower(
		FLMUINT16					ui16WpChar);
	
	FLMBOOL FLMAPI f_breakWPChar(	
		FLMUINT16					ui16WpChar,
		FLMUINT16 *					pui16BaseChar,
		FLMUINT16 *					pui16DiacriticChar);

	FLMBOOL FLMAPI f_combineWPChar(
		FLMUINT16 *					pui16WpChar,
		FLMUINT16					ui16BaseChar,
		FLMINT16						ui16DiacriticChar);

	FLMUINT16 FLMAPI f_wpGetCollationImp(
		FLMUINT16					ui16WpChar,
		FLMUINT						uiLanguage);

	FINLINE FLMUINT16 FLMAPI f_wpGetCollation(
		FLMUINT16					ui16WpChar,
		FLMUINT						uiLanguage)
	{
		if( uiLanguage == FLM_US_LANG)
		{
			return( gv_pui16USCollationTable[ ui16WpChar]);
		}

		return( f_wpGetCollationImp( ui16WpChar, uiLanguage));
	}

	RCODE FLMAPI f_wpCheckDoubleCollation(
		IF_PosIStream *			pIStream,
		FLMBOOL						bUnicodeStream,
		FLMBOOL						bAllowTwoIntoOne,
		FLMUNICODE *				puzChar,
		FLMUNICODE *				puzChar2,
		FLMBOOL *					pbTwoIntoOne,
		FLMUINT						uiLanguage);
	
	FLMUINT16 FLMAPI f_wpCheckDoubleCollation(
		FLMUINT16 *					pui16WpChar,
		FLMBOOL *					pbTwoIntoOne,
		const FLMBYTE **			ppucInputStr,
		FLMUINT						uiLanguage);
	
	FLMUINT16 FLMAPI f_wpHanToZenkaku(
		FLMUINT16					ui16WpChar,
		FLMUINT16					ui16NextWpChar,
		FLMUINT16 *					pui16Zenkaku);

	FLMUINT16 FLMAPI f_wpZenToHankaku(
		FLMUINT16					ui16WpChar,
		FLMUINT16 * 				pui16DakutenOrHandakuten);
	
	FLMUINT FLMAPI f_wpToMixed(
		FLMBYTE *					pucWPStr,
		FLMUINT						uiWPStrLen,
		const FLMBYTE *			pucLowUpBitStr,
		FLMUINT						uiLang);

	RCODE FLMAPI f_asiaParseSubCol(
		FLMBYTE *					pucWPStr,
		FLMUINT *					puiWPStrLen,
		FLMUINT						uiMaxWPBytes,
		const FLMBYTE *			pucSubColBuf,
		FLMUINT *					puiSubColBitPos);

	RCODE FLMAPI f_asiaColStr2WPStr(
		const FLMBYTE *			pucColStr,
		FLMUINT						uiColStrLen,
		FLMBYTE *					pucWPStr,
		FLMUINT *					puiWPStrLen,
		FLMUINT *					puiUnconvChars,
		FLMBOOL *					pbDataTruncated,
		FLMBOOL *					pbFirstSubstring);
	
	RCODE FLMAPI f_colStr2WPStr(
		const FLMBYTE *			pucColStr,
		FLMUINT						uiColStrLen,
		FLMBYTE *					pucWPStr,
		FLMUINT *					puiWPStrLen,
		FLMUINT						uiLang,
		FLMUINT *					puiUnconvChars,
		FLMBOOL *					pbDataTruncated,
		FLMBOOL *					pbFirstSubstring);
	
	RCODE FLMAPI f_asiaUTF8ToColText(
		IF_PosIStream *			pIStream,
		FLMBYTE *					pucColStr,
		FLMUINT *					puiColStrLen,
		FLMBOOL						bCaseInsensitive,
		FLMUINT *					puiCollationLen,
		FLMUINT *					puiCaseLen,
		FLMUINT						uiCharLimit,
		FLMBOOL						bFirstSubstring,
		FLMBOOL						bDataTruncated,
		FLMBOOL *					pbDataTruncated);
	
	RCODE FLMAPI f_compareUTF8Strings(
		const FLMBYTE *			pucLString,
		FLMUINT						uiLStrBytes,
		FLMBOOL						bLeftWild,
		const FLMBYTE *			pucRString,
		FLMUINT						uiRStrBytes,
		FLMBOOL						bRightWild,
		FLMUINT						uiCompareRules,
		FLMUINT						uiLanguage,
		FLMINT *						piResult);
			
	RCODE FLMAPI f_compareUTF8Streams(
		IF_PosIStream *			pLStream,
		FLMBOOL						bLeftWild,
		IF_PosIStream *			pRStream,
		FLMBOOL						bRightWild,
		FLMUINT						uiCompareRules,
		FLMUINT						uiLanguage,
		FLMINT *						piResult);
		
	RCODE FLMAPI f_compareUnicodeStrings(
		const FLMUNICODE *		puzLString,
		FLMUINT						uiLStrBytes,
		FLMBOOL						bLeftWild,
		const FLMUNICODE *		puzRString,
		FLMUINT						uiRStrBytes,
		FLMBOOL						bRightWild,
		FLMUINT						uiCompareRules,
		FLMUINT						uiLanguage,
		FLMINT *						piResult);

	RCODE FLMAPI f_compareUnicodeStreams(
		IF_PosIStream *			pLStream,
		FLMBOOL						bLeftWild,
		IF_PosIStream *			pRStream,
		FLMBOOL						bRightWild,
		FLMUINT						uiCompareRules,
		FLMUINT						uiLanguage,
		FLMINT *						piResult);
	
	RCODE FLMAPI f_compareCollStreams(
		IF_CollIStream *			pLStream,
		IF_CollIStream *			pRStream,
		FLMBOOL						bOpIsMatch,
		FLMUINT						uiLanguage,
		FLMINT *						piResult);
		
	RCODE FLMAPI f_utf8IsSubStr(
		const FLMBYTE *			pszString,
		const FLMBYTE *			pszSubString,
		FLMUINT						uiCompareRules,
		FLMUINT						uiLanguage,
		FLMBOOL *					pbExists);
		
	RCODE FLMAPI f_readUTF8CharAsUnicode(
		IF_IStream *				pStream,
		FLMUNICODE *				puChar);
	
	RCODE FLMAPI f_readUTF8CharAsUTF8(
		IF_IStream *				pIStream,
		FLMBYTE *					pucBuf,
		FLMUINT *					puiLen);
	
	RCODE FLMAPI f_formatUTF8Text(
		IF_PosIStream *			pIStream,
		FLMBOOL						bAllowEscapes,
		FLMUINT						uiCompareRules,
		F_DynaBuf *					pDynaBuf);
		
	RCODE FLMAPI f_getNextMetaphone(
		IF_IStream *				pIStream,
		FLMUINT *					puiMetaphone,
		FLMUINT *					puiAltMetaphone = NULL);
	
	FLMUINT FLMAPI f_getSENLength(
		FLMBYTE 						ucByte);

	FLMUINT FLMAPI f_getSENByteCount(
		FLMUINT64					ui64Num);
		
	FLMUINT FLMAPI f_encodeSEN(
		FLMUINT64					ui64Value,
		FLMBYTE **					ppucBuffer,
		FLMUINT						uiBytesWanted = 0);
		
	RCODE FLMAPI f_encodeSEN(
		FLMUINT64					ui64Value,
		FLMBYTE **					ppucBuffer,
		FLMBYTE *					pucEnd);
	
	FLMUINT FLMAPI f_encodeSENKnownLength(
		FLMUINT64					ui64Value,
		FLMUINT						uiSenLen,
		FLMBYTE **					ppucBuffer);

	RCODE FLMAPI f_decodeSEN(
		const FLMBYTE **			ppucBuffer,
		const FLMBYTE *			pucEnd,
		FLMUINT *					puiValue);
	
	RCODE FLMAPI f_decodeSEN64(
		const FLMBYTE **			ppucBuffer,
		const FLMBYTE *			pucEnd,
		FLMUINT64 *					pui64Value);
	
	RCODE FLMAPI f_readSEN(
		IF_IStream *				pIStream,
		FLMUINT *					puiValue,
		FLMUINT *					puiLength = NULL);
		
	RCODE FLMAPI f_readSEN64(
		IF_IStream *				pIStream,
		FLMUINT64 *					pui64Value,
		FLMUINT *					puiLength = NULL);
		
	/// Get the language string from a language code
	/// \ingroup language
	FLMUINT FLMAPI f_languageToNum(
		const char *				pszLanguage);

	/// Convert a language string to the appropriate language code.
	/// \ingroup language
	void FLMAPI f_languageToStr(
		FLMINT						iLangNum,
		char *						pszLanguage		///< Language string that is to be converted to a code.
		);

	/****************************************************************************
	Desc: ASCII character constants and macros
	****************************************************************************/

	#define ASCII_TAB						0x09
	#define ASCII_NEWLINE				0x0A
	#define ASCII_CR                 0x0D
	#define ASCII_CTRLZ              0x1A
	#define ASCII_SPACE              0x20
	#define ASCII_DQUOTE					0x22
	#define ASCII_POUND              0x23
	#define ASCII_DOLLAR             0x24
	#define ASCII_SQUOTE             0x27
	#define ASCII_WILDCARD           0x2A
	#define ASCII_PLUS               0x2B
	#define ASCII_COMMA              0x2C
	#define ASCII_DASH               0x2D
	#define ASCII_MINUS              0x2D
	#define ASCII_DOT                0x2E
	#define ASCII_SLASH              0x2F
	#define ASCII_COLON              0x3A
	#define ASCII_SEMICOLON				0x3B
	#define ASCII_EQUAL              0x3D
	#define ASCII_QUESTIONMARK			0x3F
	#define ASCII_AT                 0x40
	#define ASCII_BACKSLASH				0x5C
	#define ASCII_CARAT					0x5E
	#define ASCII_UNDERSCORE			0x5F
	#define ASCII_TILDE					0x7E
	#define ASCII_AMP						0x26

	#define ASCII_UPPER_A				0x41
	#define ASCII_UPPER_B				0x42
	#define ASCII_UPPER_C				0x43
	#define ASCII_UPPER_D				0x44
	#define ASCII_UPPER_E				0x45
	#define ASCII_UPPER_F				0x46
	#define ASCII_UPPER_G				0x47
	#define ASCII_UPPER_H				0x48
	#define ASCII_UPPER_I				0x49
	#define ASCII_UPPER_J				0x4A
	#define ASCII_UPPER_K				0x4B
	#define ASCII_UPPER_L				0x4C
	#define ASCII_UPPER_M				0x4D
	#define ASCII_UPPER_N				0x4E
	#define ASCII_UPPER_O				0x4F
	#define ASCII_UPPER_P				0x50
	#define ASCII_UPPER_Q				0x51
	#define ASCII_UPPER_R				0x52
	#define ASCII_UPPER_S				0x53
	#define ASCII_UPPER_T				0x54
	#define ASCII_UPPER_U				0x55
	#define ASCII_UPPER_V				0x56
	#define ASCII_UPPER_W				0x57
	#define ASCII_UPPER_X				0x58
	#define ASCII_UPPER_Y				0x59
	#define ASCII_UPPER_Z				0x5A

	#define ASCII_LOWER_A				0x61
	#define ASCII_LOWER_B				0x62
	#define ASCII_LOWER_C				0x63
	#define ASCII_LOWER_D				0x64
	#define ASCII_LOWER_E				0x65
	#define ASCII_LOWER_F				0x66
	#define ASCII_LOWER_G				0x67
	#define ASCII_LOWER_H				0x68
	#define ASCII_LOWER_I				0x69
	#define ASCII_LOWER_J				0x6A
	#define ASCII_LOWER_K				0x6B
	#define ASCII_LOWER_L				0x6C
	#define ASCII_LOWER_M				0x6D
	#define ASCII_LOWER_N				0x6E
	#define ASCII_LOWER_O				0x6F
	#define ASCII_LOWER_P				0x70
	#define ASCII_LOWER_Q				0x71
	#define ASCII_LOWER_R				0x72
	#define ASCII_LOWER_S				0x73
	#define ASCII_LOWER_T				0x74
	#define ASCII_LOWER_U				0x75
	#define ASCII_LOWER_V				0x76
	#define ASCII_LOWER_W				0x77
	#define ASCII_LOWER_X				0x78
	#define ASCII_LOWER_Y				0x79
	#define ASCII_LOWER_Z				0x7A

	#define ASCII_ZERO					0x30
	#define ASCII_ONE						0x31
	#define ASCII_TWO						0x32
	#define ASCII_THREE					0x33
	#define ASCII_FOUR					0x34
	#define ASCII_FIVE					0x35
	#define ASCII_SIX						0x36
	#define ASCII_SEVEN					0x37
	#define ASCII_EIGHT					0x38
	#define ASCII_NINE					0x39

	/****************************************************************************
	Desc: Native character constants and macros
	****************************************************************************/
	
	#define NATIVE_SPACE             ' '
	#define NATIVE_DOT               '.'
	#define NATIVE_PLUS              '+'
	#define NATIVE_MINUS					'-'
	#define NATIVE_WILDCARD				'*'
	#define NATIVE_QUESTIONMARK		'?'

	#define NATIVE_UPPER_A				'A'
	#define NATIVE_UPPER_F				'F'
	#define NATIVE_UPPER_X				'X'
	#define NATIVE_UPPER_Z				'Z'
	#define NATIVE_LOWER_A				'a'
	#define NATIVE_LOWER_F				'f'
	#define NATIVE_LOWER_X				'x'
	#define NATIVE_LOWER_Z				'z'
	#define NATIVE_ZERO              '0'
	#define NATIVE_NINE              '9'

	#define f_stringToAscii( str)

	#define f_toascii( native) \
		(native)

	#define f_tonative( ascii) \
		(ascii)

	#define f_toupper( native) \
		(((native) >= 'a' && (native) <= 'z') \
				? (native) - 'a' + 'A' \
				: (native))

	#define f_tolower( native) \
		(((native) >= 'A' && (native) <= 'Z') \
				? (native) - 'A' + 'a' \
				: (native))

	#define f_islower( native) \
		((native) >= 'a' && (native) <= 'z')

	#ifndef FLM_ASCII_PLATFORM
		#define FLM_ASCII_PLATFORM
	#endif

	/****************************************************************************
	Desc: Unicode character constants and macros
	****************************************************************************/
	
	#define FLM_UNICODE_LINEFEED			((FLMUNICODE)10)
	#define FLM_UNICODE_SPACE				((FLMUNICODE)32)
	#define FLM_UNICODE_BANG				((FLMUNICODE)33)
	#define FLM_UNICODE_QUOTE				((FLMUNICODE)34)
	#define FLM_UNICODE_POUND				((FLMUNICODE)35)
	#define FLM_UNICODE_DOLLAR				((FLMUNICODE)36)
	#define FLM_UNICODE_PERCENT			((FLMUNICODE)37)
	#define FLM_UNICODE_AMP					((FLMUNICODE)38)
	#define FLM_UNICODE_APOS				((FLMUNICODE)39)
	#define FLM_UNICODE_LPAREN				((FLMUNICODE)40)
	#define FLM_UNICODE_RPAREN				((FLMUNICODE)41)
	#define FLM_UNICODE_ASTERISK			((FLMUNICODE)42)
	#define FLM_UNICODE_PLUS				((FLMUNICODE)43)
	#define FLM_UNICODE_COMMA				((FLMUNICODE)44)
	#define FLM_UNICODE_HYPHEN				((FLMUNICODE)45)
	#define FLM_UNICODE_PERIOD				((FLMUNICODE)46)
	#define FLM_UNICODE_FSLASH				((FLMUNICODE)47)

	#define FLM_UNICODE_0					((FLMUNICODE)48)
	#define FLM_UNICODE_1					((FLMUNICODE)49)
	#define FLM_UNICODE_2					((FLMUNICODE)50)
	#define FLM_UNICODE_3					((FLMUNICODE)51)
	#define FLM_UNICODE_4					((FLMUNICODE)52)
	#define FLM_UNICODE_5					((FLMUNICODE)53)
	#define FLM_UNICODE_6					((FLMUNICODE)54)
	#define FLM_UNICODE_7					((FLMUNICODE)55)
	#define FLM_UNICODE_8					((FLMUNICODE)56)
	#define FLM_UNICODE_9					((FLMUNICODE)57)

	#define FLM_UNICODE_COLON				((FLMUNICODE)58)
	#define FLM_UNICODE_SEMI				((FLMUNICODE)59)
	#define FLM_UNICODE_LT					((FLMUNICODE)60)
	#define FLM_UNICODE_EQ					((FLMUNICODE)61)
	#define FLM_UNICODE_GT					((FLMUNICODE)62)
	#define FLM_UNICODE_QUEST				((FLMUNICODE)63)
	#define FLM_UNICODE_ATSIGN				((FLMUNICODE)64)

	#define FLM_UNICODE_A					((FLMUNICODE)65)
	#define FLM_UNICODE_B					((FLMUNICODE)66)
	#define FLM_UNICODE_C					((FLMUNICODE)67)
	#define FLM_UNICODE_D					((FLMUNICODE)68)
	#define FLM_UNICODE_E					((FLMUNICODE)69)
	#define FLM_UNICODE_F					((FLMUNICODE)70)
	#define FLM_UNICODE_G					((FLMUNICODE)71)
	#define FLM_UNICODE_H					((FLMUNICODE)72)
	#define FLM_UNICODE_I					((FLMUNICODE)73)
	#define FLM_UNICODE_J					((FLMUNICODE)74)
	#define FLM_UNICODE_K					((FLMUNICODE)75)
	#define FLM_UNICODE_L					((FLMUNICODE)76)
	#define FLM_UNICODE_M					((FLMUNICODE)77)
	#define FLM_UNICODE_N					((FLMUNICODE)78)
	#define FLM_UNICODE_O					((FLMUNICODE)79)
	#define FLM_UNICODE_P					((FLMUNICODE)80)
	#define FLM_UNICODE_Q					((FLMUNICODE)81)
	#define FLM_UNICODE_R					((FLMUNICODE)82)
	#define FLM_UNICODE_S					((FLMUNICODE)83)
	#define FLM_UNICODE_T					((FLMUNICODE)84)
	#define FLM_UNICODE_U					((FLMUNICODE)85)
	#define FLM_UNICODE_V					((FLMUNICODE)86)
	#define FLM_UNICODE_W					((FLMUNICODE)87)
	#define FLM_UNICODE_X					((FLMUNICODE)88)
	#define FLM_UNICODE_Y					((FLMUNICODE)89)
	#define FLM_UNICODE_Z					((FLMUNICODE)90)

	#define FLM_UNICODE_LBRACKET			((FLMUNICODE)91)
	#define FLM_UNICODE_BACKSLASH			((FLMUNICODE)92)
	#define FLM_UNICODE_RBRACKET			((FLMUNICODE)93)
	#define FLM_UNICODE_UNDERSCORE		((FLMUNICODE)95)

	#define FLM_UNICODE_a					((FLMUNICODE)97)
	#define FLM_UNICODE_b					((FLMUNICODE)98)
	#define FLM_UNICODE_c					((FLMUNICODE)99)
	#define FLM_UNICODE_d					((FLMUNICODE)100)
	#define FLM_UNICODE_e					((FLMUNICODE)101)
	#define FLM_UNICODE_f					((FLMUNICODE)102)
	#define FLM_UNICODE_g					((FLMUNICODE)103)
	#define FLM_UNICODE_h					((FLMUNICODE)104)
	#define FLM_UNICODE_i					((FLMUNICODE)105)
	#define FLM_UNICODE_j					((FLMUNICODE)106)
	#define FLM_UNICODE_k					((FLMUNICODE)107)
	#define FLM_UNICODE_l					((FLMUNICODE)108)
	#define FLM_UNICODE_m					((FLMUNICODE)109)
	#define FLM_UNICODE_n					((FLMUNICODE)110)
	#define FLM_UNICODE_o					((FLMUNICODE)111)
	#define FLM_UNICODE_p					((FLMUNICODE)112)
	#define FLM_UNICODE_q					((FLMUNICODE)113)
	#define FLM_UNICODE_r					((FLMUNICODE)114)
	#define FLM_UNICODE_s					((FLMUNICODE)115)
	#define FLM_UNICODE_t					((FLMUNICODE)116)
	#define FLM_UNICODE_u					((FLMUNICODE)117)
	#define FLM_UNICODE_v					((FLMUNICODE)118)
	#define FLM_UNICODE_w					((FLMUNICODE)119)
	#define FLM_UNICODE_x					((FLMUNICODE)120)
	#define FLM_UNICODE_y					((FLMUNICODE)121)
	#define FLM_UNICODE_z					((FLMUNICODE)122)

	#define FLM_UNICODE_LBRACE				((FLMUNICODE)123)
	#define FLM_UNICODE_PIPE				((FLMUNICODE)124)
	#define FLM_UNICODE_RBRACE				((FLMUNICODE)125)
	#define FLM_UNICODE_TILDE				((FLMUNICODE)126)
	#define FLM_UNICODE_C_CEDILLA			((FLMUNICODE)199)
	#define FLM_UNICODE_N_TILDE			((FLMUNICODE)209)
	#define FLM_UNICODE_c_CEDILLA			((FLMUNICODE)231)
	#define FLM_UNICODE_n_TILDE			((FLMUNICODE)241)

	FINLINE FLMBOOL f_isvowel(
		FLMUNICODE		uChar)
	{
		uChar = f_uniToLower( uChar);

		if( uChar == FLM_UNICODE_a ||
			 uChar == FLM_UNICODE_e ||
			 uChar == FLM_UNICODE_i ||
			 uChar == FLM_UNICODE_o ||
			 uChar == FLM_UNICODE_u ||
			 uChar == FLM_UNICODE_y)
		{
			return( TRUE);
		}

		return( FALSE);
	}

	/****************************************************************************
	Desc: Endian macros
	****************************************************************************/

	FINLINE FLMUINT16 f_littleEndianToUINT16( 
		const FLMBYTE *		pucBuf)
	{
		FLMUINT16		ui16Val = 0;
		
		ui16Val |= ((FLMUINT16)pucBuf[ 1]) << 8;
		ui16Val |= ((FLMUINT16)pucBuf[ 0]);
		
		return( ui16Val);
	}
	
	FINLINE FLMUINT32 f_littleEndianToUINT32(
		const FLMBYTE *		pucBuf)
	{
		FLMUINT32		ui32Val = 0;

		ui32Val |= ((FLMUINT32)pucBuf[ 3]) << 24;
		ui32Val |= ((FLMUINT32)pucBuf[ 2]) << 16;
		ui32Val |= ((FLMUINT32)pucBuf[ 1]) << 8;
		ui32Val |= ((FLMUINT32)pucBuf[ 0]);

		return( ui32Val);
	}
	
	FINLINE FLMUINT64 f_littleEndianToUINT64(
		const FLMBYTE *		pucBuf)
	{
		FLMUINT64		ui64Val = 0;

		ui64Val |= ((FLMUINT64)pucBuf[ 7]) << 56;
		ui64Val |= ((FLMUINT64)pucBuf[ 6]) << 48;
		ui64Val |= ((FLMUINT64)pucBuf[ 5]) << 40;
		ui64Val |= ((FLMUINT64)pucBuf[ 4]) << 32;
		ui64Val |= ((FLMUINT64)pucBuf[ 3]) << 24;
		ui64Val |= ((FLMUINT64)pucBuf[ 2]) << 16;
		ui64Val |= ((FLMUINT64)pucBuf[ 1]) << 8;
		ui64Val |= ((FLMUINT64)pucBuf[ 0]);

		return( ui64Val);
	}

	FINLINE void f_UINT16ToLittleEndian(
		FLMUINT16				ui16Num,
		FLMBYTE *				pucBuf)
	{
		pucBuf[ 1] = (FLMBYTE) (ui16Num >>  8);
		pucBuf[ 0] = (FLMBYTE) (ui16Num);
	}
	
	FINLINE void f_UINT32ToLittleEndian(
		FLMUINT32				ui32Num,
		FLMBYTE *				pucBuf)
	{
		pucBuf[ 3] = (FLMBYTE) (ui32Num >> 24);
		pucBuf[ 2] = (FLMBYTE) (ui32Num >> 16);
		pucBuf[ 1] = (FLMBYTE) (ui32Num >>  8);
		pucBuf[ 0] = (FLMBYTE) (ui32Num);
	}
	
	FINLINE void f_UINT64ToLittleEndian(
		FLMUINT64				ui64Num,
		FLMBYTE *				pucBuf)
	{
		pucBuf[ 7] = (FLMBYTE) (ui64Num >> 56);
		pucBuf[ 6] = (FLMBYTE) (ui64Num >> 48);
		pucBuf[ 5] = (FLMBYTE) (ui64Num >> 40);
		pucBuf[ 4] = (FLMBYTE) (ui64Num >> 32);
		pucBuf[ 3] = (FLMBYTE) (ui64Num >> 24);
		pucBuf[ 2] = (FLMBYTE) (ui64Num >> 16);
		pucBuf[ 1] = (FLMBYTE) (ui64Num >>  8);
		pucBuf[ 0] = (FLMBYTE) (ui64Num);
	}
	
	FINLINE FLMUINT16 f_bigEndianToUINT16(
		const FLMBYTE *		pucBuf)
	{
		FLMUINT16	ui16Val = 0;
		
		ui16Val |= ((FLMUINT16)pucBuf[ 0]) << 8;
		ui16Val |= ((FLMUINT16)pucBuf[ 1]);
		
		return( ui16Val);
	}
	
	FINLINE FLMUINT32 f_bigEndianToUINT32( 
		const FLMBYTE *		pucBuf)
	{
		FLMUINT32		ui32Val = 0;

		ui32Val |= ((FLMUINT32)pucBuf[ 0]) << 24;
		ui32Val |= ((FLMUINT32)pucBuf[ 1]) << 16;
		ui32Val |= ((FLMUINT32)pucBuf[ 2]) << 8;
		ui32Val |= ((FLMUINT32)pucBuf[ 3]);
		
		return( ui32Val);
	}
	
	FINLINE FLMUINT64 f_bigEndianToUINT64( 
		const FLMBYTE *		pucBuf)
	{
		FLMUINT64		ui64Val = 0;
	
		ui64Val |= ((FLMUINT64)pucBuf[ 0]) << 56;
		ui64Val |= ((FLMUINT64)pucBuf[ 1]) << 48;
		ui64Val |= ((FLMUINT64)pucBuf[ 2]) << 40;
		ui64Val |= ((FLMUINT64)pucBuf[ 3]) << 32;
		ui64Val |= ((FLMUINT64)pucBuf[ 4]) << 24;
		ui64Val |= ((FLMUINT64)pucBuf[ 5]) << 16;
		ui64Val |= ((FLMUINT64)pucBuf[ 6]) << 8;
		ui64Val |= ((FLMUINT64)pucBuf[ 7]);
	
		return( ui64Val);
	}
	
	FINLINE FLMINT16 f_bigEndianToINT16(
		const FLMBYTE *		pucBuf)
	{
		FLMINT16			i16Val = 0;
		
		i16Val |= ((FLMINT16)pucBuf[ 0]) << 8;
		i16Val |= ((FLMINT16)pucBuf[ 1]);
		
		return( i16Val);
	}
	
	FINLINE FLMINT32 f_bigEndianToINT32( 
		const FLMBYTE *		pucBuf)
	{
		FLMINT32			i32Val = 0;

		i32Val |= ((FLMINT32)pucBuf[ 0]) << 24;
		i32Val |= ((FLMINT32)pucBuf[ 1]) << 16;
		i32Val |= ((FLMINT32)pucBuf[ 2]) << 8;
		i32Val |= ((FLMINT32)pucBuf[ 3]);
		
		return( i32Val);
	}
	
	FINLINE FLMINT64 f_bigEndianToINT64( 
		const FLMBYTE *		pucBuf)
	{
		FLMINT64			i64Val = 0;
	
		i64Val |= ((FLMINT64)pucBuf[ 0]) << 56;
		i64Val |= ((FLMINT64)pucBuf[ 1]) << 48;
		i64Val |= ((FLMINT64)pucBuf[ 2]) << 40;
		i64Val |= ((FLMINT64)pucBuf[ 3]) << 32;
		i64Val |= ((FLMINT64)pucBuf[ 4]) << 24;
		i64Val |= ((FLMINT64)pucBuf[ 5]) << 16;
		i64Val |= ((FLMINT64)pucBuf[ 6]) << 8;
		i64Val |= ((FLMINT64)pucBuf[ 7]);
	
		return( i64Val);
	}
	
	FINLINE void f_UINT32ToBigEndian( 
		FLMUINT32		ui32Num,
		FLMBYTE *		pucBuf)
	{
		pucBuf[ 0] = (FLMBYTE) (ui32Num >> 24);
		pucBuf[ 1] = (FLMBYTE) (ui32Num >> 16);
		pucBuf[ 2] = (FLMBYTE) (ui32Num >>  8);
		pucBuf[ 3] = (FLMBYTE) (ui32Num);
	}
	
	FINLINE void f_INT32ToBigEndian( 
		FLMINT32			i32Num,
		FLMBYTE *		pucBuf)
	{
		pucBuf[ 0] = (FLMBYTE) (i32Num >> 24);
		pucBuf[ 1] = (FLMBYTE) (i32Num >> 16);
		pucBuf[ 2] = (FLMBYTE) (i32Num >>  8);
		pucBuf[ 3] = (FLMBYTE) (i32Num);
	}
	
	FINLINE void f_INT64ToBigEndian( 
		FLMINT64			i64Num,
		FLMBYTE *		pucBuf)
	{
		pucBuf[ 0] = (FLMBYTE) (i64Num >> 56);
		pucBuf[ 1] = (FLMBYTE) (i64Num >> 48);
		pucBuf[ 2] = (FLMBYTE) (i64Num >> 40);
		pucBuf[ 3] = (FLMBYTE) (i64Num >> 32);
		pucBuf[ 4] = (FLMBYTE) (i64Num >> 24);
		pucBuf[ 5] = (FLMBYTE) (i64Num >> 16);
		pucBuf[ 6] = (FLMBYTE) (i64Num >>  8);
		pucBuf[ 7] = (FLMBYTE) (i64Num);
	}
	
	FINLINE void f_UINT64ToBigEndian( 
		FLMUINT64		ui64Num,
		FLMBYTE *		pucBuf)
	{
		pucBuf[ 0] = (FLMBYTE) (ui64Num >> 56);
		pucBuf[ 1] = (FLMBYTE) (ui64Num >> 48);
		pucBuf[ 2] = (FLMBYTE) (ui64Num >> 40);
		pucBuf[ 3] = (FLMBYTE) (ui64Num >> 32);
		pucBuf[ 4] = (FLMBYTE) (ui64Num >> 24);
		pucBuf[ 5] = (FLMBYTE) (ui64Num >> 16);
		pucBuf[ 6] = (FLMBYTE) (ui64Num >>  8);
		pucBuf[ 7] = (FLMBYTE) (ui64Num);
	}
	
	FINLINE void f_INT16ToBigEndian( 
		FLMINT16			i16Num,
		FLMBYTE *		pucBuf)
	{
		pucBuf[ 0] = (FLMBYTE) (i16Num >> 8);
		pucBuf[ 1] = (FLMBYTE) (i16Num);
	}
	
	FINLINE void f_UINT16ToBigEndian( 
		FLMUINT16		ui16Num,
		FLMBYTE *		pucBuf)
	{
		pucBuf[ 0] = (FLMBYTE) (ui16Num >> 8);
		pucBuf[ 1] = (FLMBYTE) (ui16Num);
	}

	#if defined( FLM_STRICT_ALIGNMENT) || defined( FLM_BIG_ENDIAN)
	
		FINLINE FLMUINT16 FB2UW(	
			const FLMBYTE *	pucBuf)
		{
			FLMUINT16		ui16Val = 0;
			
			ui16Val |= ((FLMUINT16)pucBuf[ 1]) << 8;
			ui16Val |= ((FLMUINT16)pucBuf[ 0]);
			
			return( ui16Val);
		}

		FINLINE FLMUINT32 FB2UD(	
			const FLMBYTE *	pucBuf)
		{
			FLMUINT32		ui32Val = 0;
			
			ui32Val |= ((FLMUINT32)pucBuf[ 3]) << 24;
			ui32Val |= ((FLMUINT32)pucBuf[ 2]) << 16;
			ui32Val |= ((FLMUINT32)pucBuf[ 1]) << 8;
			ui32Val |= ((FLMUINT32)pucBuf[ 0]);
			
			return( ui32Val);
		}
		
		FINLINE FLMUINT64 FB2U64(	
			const FLMBYTE *	pucBuf)
		{
			FLMUINT64		ui64Val = 0;
			
			ui64Val |= ((FLMUINT64)pucBuf[ 7]) << 56;
			ui64Val |= ((FLMUINT64)pucBuf[ 6]) << 48;
			ui64Val |= ((FLMUINT64)pucBuf[ 5]) << 40;
			ui64Val |= ((FLMUINT64)pucBuf[ 4]) << 32;
			ui64Val |= ((FLMUINT64)pucBuf[ 3]) << 24;
			ui64Val |= ((FLMUINT64)pucBuf[ 2]) << 16;
			ui64Val |= ((FLMUINT64)pucBuf[ 1]) << 8;
			ui64Val |= ((FLMUINT64)pucBuf[ 0]);
			
			return( ui64Val);
		}
		
		FINLINE void UW2FBA(
			FLMUINT			uiNum,
			FLMBYTE *		pucBuf)
		{
			f_assert( uiNum <= FLM_MAX_UINT16);
			
			pucBuf[ 1] = (FLMBYTE) (uiNum >>  8);
			pucBuf[ 0] = (FLMBYTE) (uiNum);
		}
		
		FINLINE void UD2FBA(
			FLMUINT			uiNum,
			FLMBYTE *		pucBuf)
		{
			f_assert( uiNum <= FLM_MAX_UINT32);
			
			pucBuf[ 3] = (FLMBYTE) (uiNum >> 24);
			pucBuf[ 2] = (FLMBYTE) (uiNum >> 16);
			pucBuf[ 1] = (FLMBYTE) (uiNum >>  8);
			pucBuf[ 0] = (FLMBYTE) (uiNum);
		}
		
		FINLINE void U642FBA(
			FLMUINT64		ui64Num,
			FLMBYTE *		pucBuf)
		{
			pucBuf[ 7] = (FLMBYTE) (ui64Num >> 56);
			pucBuf[ 6] = (FLMBYTE) (ui64Num >> 48);
			pucBuf[ 5] = (FLMBYTE) (ui64Num >> 40);
			pucBuf[ 4] = (FLMBYTE) (ui64Num >> 32);
			pucBuf[ 3] = (FLMBYTE) (ui64Num >> 24);
			pucBuf[ 2] = (FLMBYTE) (ui64Num >> 16);
			pucBuf[ 1] = (FLMBYTE) (ui64Num >>  8);
			pucBuf[ 0] = (FLMBYTE) (ui64Num);
		}
			 
	#else
	
		#define FB2UW( fbp) \
			(*((FLMUINT16 *)(fbp)))
			
		#define FB2UD( fbp) \
			(*((FLMUINT32 *)(fbp)))
			
		#define FB2U64( fbp) \
			(*((FLMUINT64 *)(fbp)))
			
		#define UW2FBA( uw, fbp) \
			(*((FLMUINT16 *)(fbp)) = ((FLMUINT16) (uw)))
			
		#define UD2FBA( uw, fbp) \
			(*((FLMUINT32 *)(fbp)) = ((FLMUINT32) (uw)))
			
		#define U642FBA( uw, fbp) \
			(*((FLMUINT64 *)(fbp)) = ((FLMUINT64) (uw)))

	#endif
	
	#ifdef FLM_BIG_ENDIAN
		#define LO( wrd) \
			(*((FLMUINT8 *)&wrd + 1))
			
		#define HI( wrd) \
			(*(FLMUINT8 *)&wrd)
	#else
		#define LO(wrd) \
			(*(FLMUINT8 *)&wrd)
		
		#define HI(wrd) \
			(*((FLMUINT8 *)&wrd + 1))
	#endif

	/****************************************************************************
	Desc: File path functions and macros
	****************************************************************************/

	#if defined( FLM_WIN) || defined( FLM_NLM)
		#define FWSLASH     		'/'
		#define SLASH       		'\\'
		#define SSLASH      		"\\"
		#define COLON       		':'
		#define PERIOD      		'.'
		#define PARENT_DIR  		".."
		#define CURRENT_DIR 		"."
	#else
		#ifndef FWSLASH
			#define FWSLASH 		'/'
		#endif

		#ifndef SLASH
			#define SLASH  		'/'
		#endif

		#ifndef SSLASH
			#define SSLASH			"/"
		#endif

		#ifndef COLON
			#define COLON  		':'
		#endif

		#ifndef PERIOD
			#define PERIOD 		'.'
		#endif

		#ifndef PARENT_DIR
			#define PARENT_DIR 	".."
		#endif

		#ifndef CURRENT_DIR
			#define CURRENT_DIR 	"."
		#endif
	#endif
	
	FLMUINT FLMAPI f_getMaxFileSize( void);

	/****************************************************************************
	Desc: CPU release and sleep functions
	****************************************************************************/

	void FLMAPI f_yieldCPU( void);

	void FLMAPI f_sleep(
		FLMUINT	uiMilliseconds);

	/****************************************************************************
	Desc: Time, date, timestamp functions
	****************************************************************************/

	typedef struct
	{
		FLMUINT16   year;
		FLMBYTE		month;
		FLMBYTE		day;
	} F_DATE;

	typedef struct
	{
		FLMBYTE		hour;
		FLMBYTE		minute;
		FLMBYTE		second;
		FLMBYTE		hundredth;
	} F_TIME;

	typedef struct
	{
		FLMUINT16	year;
		FLMBYTE		month;
		FLMBYTE		day;
		FLMBYTE		hour;
		FLMBYTE		minute;
		FLMBYTE		second;
		FLMBYTE		hundredth;
	} F_TMSTAMP;

	#define f_timeIsLeapYear(year) \
		((((year) & 0x03) == 0) && (((year) % 100) != 0) || (((year) % 400) == 0))

	void f_timeGetSeconds(
		FLMUINT	*		puiSeconds);

	void f_timeGetTimeStamp(
		F_TMSTAMP *		pTimeStamp);

	FLMINT f_timeGetLocalOffset( void);

	void f_timeSecondsToDate(
		FLMUINT			uiSeconds,
		F_TMSTAMP *		pTimeStamp);

	void f_timeDateToSeconds(
		F_TMSTAMP *		pTimeStamp,
		FLMUINT *		puiSeconds);

	FLMINT f_timeCompareTimeStamps(
		F_TMSTAMP *		pTimeStamp1,
		F_TMSTAMP *		pTimeStamp2,
		FLMUINT			flag);

	FINLINE FLMUINT f_localTimeToUTC(
		FLMUINT			uiSeconds)
	{
		return( uiSeconds + f_timeGetLocalOffset());
	}
	
	FLMUINT FLMAPI FLM_GET_TIMER( void);
	
	FLMUINT FLMAPI FLM_ELAPSED_TIME(
		FLMUINT			uiLaterTime,
		FLMUINT			uiEarlierTime);

	FLMUINT FLMAPI FLM_SECS_TO_TIMER_UNITS( 
		FLMUINT			uiSeconds);
	
	FLMUINT FLMAPI FLM_TIMER_UNITS_TO_SECS( 
		FLMUINT			uiTU);
	
	FLMUINT FLM_TIMER_UNITS_TO_MILLI( 
		FLMUINT			uiTU);
		
	FLMUINT FLM_MILLI_TO_TIMER_UNITS( 
		FLMUINT			uiMilliSeconds);
		
	void FLMAPI f_addElapsedTime(
		F_TMSTAMP  *	pStartTime,
		FLMUINT64 *		pui64ElapMilli);
	
	/****************************************************************************
	Desc: Quick sort
	****************************************************************************/
	
	typedef FLMINT (FLMAPI * F_SORT_COMPARE_FUNC)(
		void *		pvBuffer,
		FLMUINT		uiPos1,
		FLMUINT		uiPos2);

	typedef void (FLMAPI * F_SORT_SWAP_FUNC)(
		void *		pvBuffer,
		FLMUINT		uiPos1,
		FLMUINT		uiPos2);

	FLMINT FLMAPI f_qsortUINTCompare(
		void *		pvBuffer,
		FLMUINT		uiPos1,
		FLMUINT		uiPos2);

	void FLMAPI f_qsortUINTSwap(
		void *		pvBuffer,
		FLMUINT		uiPos1,
		FLMUINT		uiPos2);

	void FLMAPI f_qsort(
		void *					pvBuffer,
		FLMUINT					uiLowerBounds,
		FLMUINT					uiUpperBounds,
		F_SORT_COMPARE_FUNC	fnCompare,
		F_SORT_SWAP_FUNC		fnSwap);

	/****************************************************************************
	Desc: Environment
	****************************************************************************/
	
	void FLMAPI f_getenv(
		const char *			pszKey,
		FLMBYTE *				pszBuffer,
		FLMUINT					uiBufferSize,
		FLMUINT *				puiValueLen = NULL);

	/****************************************************************************
	Desc: f_sprintf
	****************************************************************************/
	
	FLMINT FLMAPI f_vsprintf(
		char *					pszDestStr,
		const char *			pszFormat,
		f_va_list *				args);

	FLMINT FLMAPI f_sprintf(
		char *					pszDestStr,
		const char *			pszFormat,
		...);

	FLMINT FLMAPI f_printf(
		const char *			pszFormat,
		...);
		
	/****************************************************************************
	Desc:	Memory copying, moving, setting
	****************************************************************************/
	
	void * FLMAPI f_memcpy(
		void *				pvDest,
		const void *		pvSrc,
		FLMSIZET				uiLength);
		
	void * FLMAPI f_memmove(
		void *				pvDest,
		const void *		pvSrc,
		FLMSIZET				uiLength);
		
	void * FLMAPI f_memset(
		void *				pvDest,
		unsigned char		ucByte,
		FLMSIZET				uiLength);
		
	FLMINT FLMAPI f_memcmp(
		const void *		pvStr1,
		const void *		pvStr2,
		FLMSIZET				uiLength);
		
	char * FLMAPI f_strcat(
		char *				pszDest,
		const char *		pszSrc);
		
	char * FLMAPI f_strncat(
		char *				pszDest,
		const char *		pszSrc,
		FLMSIZET				uiLength);
		
	char * FLMAPI f_strchr(
		const char *		pszStr,
		unsigned char		ucByte);

	char * FLMAPI f_strrchr(
		const char *		pszStr,
		unsigned char		ucByte);
		
	char * FLMAPI f_strstr(
		const char *		pszStr,
		const char *		pszSearch);
		
	char * FLMAPI f_strupr(
		char *				pszStr);
		
	FLMINT FLMAPI f_strcmp(
		const char *		pszStr1,
		const char *		pszStr2);
		
	FLMINT FLMAPI f_strncmp(
		const char *		pszStr1,
		const char *		pszStr2,
		FLMSIZET				uiLength);
		
	FLMINT FLMAPI f_stricmp(
		const char *		pszStr1,
		const char *		pszStr2);
	
	FLMINT FLMAPI f_strnicmp(
		const char *		pszStr1,
		const char *		pszStr2,
		FLMSIZET				uiLength);
		
	char * FLMAPI f_strcpy(
		char *				pszDest,
		const char *		pszSrc);

	char * FLMAPI f_strncpy(
		char *				pszDest,
		const char *		pszSrc,
		FLMSIZET				uiLength);
		
	FLMUINT FLMAPI f_strlen(
		const char *		pszStr);

	RCODE FLMAPI f_strdup(
		const char *		pszSrc,
		char **				ppszDup);
			
	RCODE FLMAPI f_getCharFromUTF8Buf(
		const FLMBYTE **	ppucBuf,
		const FLMBYTE *	pucEnd,
		FLMUNICODE *		puChar);
	
	RCODE FLMAPI f_uni2UTF8(
		FLMUNICODE			uChar,
		FLMBYTE *			pucBuf,
		FLMUINT *			puiBufSize);
	
	RCODE FLMAPI f_getUTF8Length(
		const FLMBYTE *	pucBuf,
		FLMUINT				uiBufLen,
		FLMUINT *			puiBytes,
		FLMUINT *			puiChars);
	
	RCODE FLMAPI f_getUTF8CharFromUTF8Buf(
		FLMBYTE **			ppucBuf,
		FLMBYTE *			pucEnd,
		FLMBYTE *			pucDestBuf,
		FLMUINT *			puiLen);
	
	RCODE	FLMAPI f_unicode2UTF8(
		FLMUNICODE *		puzStr,
		FLMUINT				uiStrLen,
		FLMBYTE *			pucBuf,
		FLMUINT *			puiBufLength);
	
	FLMBYTE FLMAPI f_getBase24DigitChar( 
		FLMBYTE				ucValue);
		
	#define shiftN(data,size,distance) \
			f_memmove((FLMBYTE *)(data) + (FLMINT)(distance), \
			(FLMBYTE *)(data), (unsigned)(size))

	/***************************************************************************
	Desc:
	***************************************************************************/
	class FLMEXP F_Printf : public F_Object
	{
	public:
	
	#define MAX_LOG_BUF_CHARS	255
	
		F_Printf()
		{
		}
		
		virtual ~F_Printf()
		{
		}
	
		FLMINT FLMAPI strvPrintf(
			char *			pszDestStr,
			const char *	pszFormat,
			f_va_list *		args);

		FLMINT FLMAPI strPrintf(
			char *			pszDestStr,
			const char *	pszFormat,
			...);
	
		FLMINT FLMAPI logvPrintf(
			IF_LogMessageClient *	pLogMsg,
			const char *				pszFormat,
			f_va_list *					args);
			
		FLMINT FLMAPI logPrintf(
			IF_LogMessageClient *	pLogMsg,
			const char *				pszFormat,
			...);
	
	private:
	
		void processFieldInfo(
			const char **	ppszFormat,
			FLMUINT *		puiWidth,
			FLMUINT *		puiPrecision,
			FLMUINT *		puiFlags,
			f_va_list *		args);
	
		void stringFormatter(
			char				cFormatChar,
			FLMUINT			uiWidth,
			FLMUINT			uiPrecision,
			FLMUINT			uiFlags,
			f_va_list *		args);
	
		void colorFormatter(
			char				cFormatChar,
			eColorType		eColor,
			FLMUINT			uiFlags);
			
		void charFormatter(
			char				cFormatChar,
			f_va_list *		args);
	
		void errorFormatter(
			f_va_list *		args);
	
		void notHandledFormatter( void);
	
		void numberFormatter(
			char				cFormatChar,
			FLMUINT			uiWidth,
			FLMUINT			uiPrecision,
			FLMUINT			uiFlags,
			f_va_list *		args);
		
		void parseArgs(
			const char *	pszFormat,
			f_va_list *		args);
		
		void processFormatString(
			FLMUINT			uiLen,
			...);
			
		FLMUINT printNumber(
			FLMUINT64		ui64Val,
			FLMUINT			uiBase,
			FLMBOOL			bUpperCase,
			FLMBOOL			bCommas,
			char *			pszBuf);
			
		void outputLogBuffer( void);
		
		FINLINE void outputChar(
			char				cChar)
		{
			if (!m_pLogMsg)
			{
				*m_pszDestStr++ = cChar;
			}
			else
			{
				m_szLogBuf [m_uiCharOffset++] = cChar;
				m_uiNumLogChars++;
				if (m_uiCharOffset == MAX_LOG_BUF_CHARS)
				{
					outputLogBuffer();
				}
			}
		}
		
		FINLINE void memsetChar(
			char				cChar,
			FLMUINT			uiCount)
		{
			if (!m_pLogMsg)
			{
				f_memset( m_pszDestStr, cChar, uiCount);
				m_pszDestStr += uiCount;
			}
			else
			{
				FLMUINT	uiTmpCount;
				
				while (uiCount)
				{
					uiTmpCount = uiCount;
					if (m_uiCharOffset + uiTmpCount > MAX_LOG_BUF_CHARS)
					{
						uiTmpCount = MAX_LOG_BUF_CHARS - m_uiCharOffset;
					}
					f_memset( &m_szLogBuf [m_uiCharOffset], cChar, uiTmpCount);
					m_uiCharOffset += uiTmpCount;
					m_uiNumLogChars += uiTmpCount;
					uiCount -= uiTmpCount;
					if (m_uiCharOffset == MAX_LOG_BUF_CHARS)
					{
						outputLogBuffer();
					}
				}
			}
		}

		FINLINE void outputStr(
			const char *	pszStr,
			FLMUINT			uiLen)
		{
			if (!m_pLogMsg)
			{
				f_memcpy( m_pszDestStr, pszStr, uiLen);
				m_pszDestStr += uiLen;
			}
			else
			{
				FLMUINT	uiTmpLen;
				
				while (uiLen)
				{
					uiTmpLen = uiLen;
					if (m_uiCharOffset + uiTmpLen > MAX_LOG_BUF_CHARS)
					{
						uiTmpLen = MAX_LOG_BUF_CHARS - m_uiCharOffset;
					}
					f_memcpy( &m_szLogBuf [m_uiCharOffset], pszStr, uiTmpLen);
					m_uiCharOffset += uiTmpLen;
					m_uiNumLogChars += uiTmpLen;
					uiLen -= uiTmpLen;
					pszStr += uiTmpLen;
					if (m_uiCharOffset == MAX_LOG_BUF_CHARS)
					{
						outputLogBuffer();
					}
				}
			}
		}
		
		// Variables used to do the printf stuff
	
		char							m_szLogBuf [MAX_LOG_BUF_CHARS + 1];
		FLMUINT						m_uiNumLogChars;
		FLMUINT						m_uiCharOffset;
		char *						m_pszDestStr;
		IF_LogMessageClient *	m_pLogMsg;
		eColorType					m_eCurrentForeColor;
		eColorType					m_eCurrentBackColor;
	};
	
	/****************************************************************************
	Desc: XML
	****************************************************************************/
	flminterface FLMEXP IF_XML : public F_Object
	{
	public:
	
		virtual FLMBOOL FLMAPI isPubidChar(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isQuoteChar(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isWhitespace(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isExtender(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isCombiningChar(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isNameChar(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isNCNameChar(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isIdeographic(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isBaseChar(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isDigit(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isLetter(
			FLMUNICODE				uChar) = 0;
	
		virtual FLMBOOL FLMAPI isNameValid(
			FLMUNICODE *			puzName,
			FLMBYTE *				pszName) = 0;
	};
	
	RCODE FLMAPI FlmGetXMLObject(
		IF_XML **					ppXmlObject);

	/****************************************************************************
	Desc: Name table
	****************************************************************************/
	flminterface FLMEXP IF_NameTable : public F_Object
	{
		virtual void FLMAPI clearTable(
			FLMUINT					uiPoolBlockSize) = 0;
	
		virtual RCODE FLMAPI getNextTagTypeAndNumOrder(
			FLMUINT					uiType,
			FLMUINT *				puiNextPos,
			FLMUNICODE *			puzTagName = NULL,
			char *					pszTagName = NULL,
			FLMUINT					uiNameBufSize = 0,
			FLMUINT *				puiTagNum = NULL,
			FLMUINT *				puiDataType = NULL,
			FLMUNICODE *			puzNamespace = NULL,
			FLMUINT					uiNamespaceBufSize = 0,
			FLMBOOL					bTruncatedNamesOk = TRUE) = 0;
	
		virtual RCODE FLMAPI getNextTagTypeAndNameOrder(
			FLMUINT					uiType,
			FLMUINT *				puiNextPos,
			FLMUNICODE *			puzTagName = NULL,
			char *					pszTagName = NULL,
			FLMUINT					uiNameBufSize = 0,
			FLMUINT *				puiTagNum = NULL,
			FLMUINT *				puiDataType = NULL,
			FLMUNICODE *			puzNamespace = NULL,
			FLMUINT					uiNamespaceBufSize = 0,
			FLMBOOL					bTruncatedNamesOk = TRUE) = 0;
	
		virtual RCODE FLMAPI getFromTagTypeAndName(
			FLMUINT					uiType,
			const FLMUNICODE *	puzTagName,
			const char *			pszTagName,
			FLMBOOL					bMatchNamespace,
			const FLMUNICODE *	puzNamespace = NULL,
			FLMUINT *				puiTagNum = NULL,
			FLMUINT *				puiDataType = NULL) = 0;
	
		virtual RCODE FLMAPI getFromTagTypeAndNum(
			FLMUINT					uiType,
			FLMUINT					uiTagNum,
			FLMUNICODE *			puzTagName = NULL,
			char *					pszTagName = NULL,
			FLMUINT *				puiNameBufSize = NULL,
			FLMUINT *				puiDataType = NULL,
			FLMUNICODE *			puzNamespace = NULL,
			char *					pszNamespace = NULL,
			FLMUINT *				puiNamespaceBufSize = NULL,
			FLMBOOL					bTruncatedNamesOk = TRUE) = 0;
	
		virtual RCODE FLMAPI addTag(
			FLMUINT					uiType,
			FLMUNICODE *			puzTagName,
			const char *			pszTagName,
			FLMUINT					uiTagNum,
			FLMUINT					uiDataType = 0,
			FLMUNICODE *			puzNamespace = NULL,
			FLMBOOL					bCheckDuplicates = TRUE) = 0;
	
		virtual void FLMAPI removeTag(
			FLMUINT					uiType,
			FLMUINT					uiTagNum) = 0;
	
		virtual RCODE FLMAPI cloneNameTable(
			IF_NameTable **		ppNewNameTable) = 0;
	};

	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_DeleteStatus : public F_Object
	{
		virtual RCODE FLMAPI reportDelete(
			FLMUINT					uiBlocksDeleted,
			FLMUINT					uiBlockSize) = 0;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_Relocator : public F_Object
	{
		virtual void FLMAPI relocate(
			void *					pvOldAlloc,
			void *					pvNewAlloc) = 0;
	
		virtual FLMBOOL FLMAPI canRelocate(
			void *					pvOldAlloc) = 0;
	};

	/****************************************************************************
	Desc:
	****************************************************************************/
	typedef void (FLMAPI * F_ALLOC_INIT_FUNC)(
		void *				pvAlloc,
		FLMUINT				uiSize);
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_SlabManager : public F_Object
	{
		virtual RCODE FLMAPI setup(
			FLMUINT 					uiPreallocSize) = 0;
			
		virtual RCODE FLMAPI allocSlab(
			void **					ppSlab) = 0;
			
		virtual void FLMAPI freeSlab(
			void **					ppSlab) = 0;
			
		virtual RCODE FLMAPI resize(
			FLMUINT 					uiNumBytes,
			FLMBOOL					bPreallocate,
			FLMUINT *				puiActualSize = NULL) = 0;
	
		virtual void FLMAPI incrementTotalBytesAllocated(
			FLMUINT					uiCount) = 0;
	
		virtual void FLMAPI decrementTotalBytesAllocated(
			FLMUINT					uiCount) = 0;
	
		virtual FLMUINT FLMAPI getSlabSize( void) = 0;
	
		virtual FLMUINT FLMAPI getTotalSlabs( void) = 0;
		
		virtual FLMUINT FLMAPI totalBytesAllocated( void) = 0;

		virtual FLMUINT FLMAPI getTotalSlabBytesAllocated( void) = 0;
	
		virtual FLMUINT FLMAPI availSlabs( void) = 0;
	};
	
	RCODE FLMAPI FlmAllocSlabManager(
		IF_SlabManager **			ppSlabManager);

	/****************************************************************************
	Desc:	Class to provide an efficient means of providing many allocations
			of a fixed size.
	****************************************************************************/
	flminterface FLMEXP IF_FixedAlloc : public F_Object
	{
		virtual RCODE FLMAPI setup(
			FLMBOOL					bMultiThreaded,
			IF_SlabManager *		pSlabManager,
			IF_Relocator *			pDefaultRelocator,
			FLMUINT					uiCellSize,
			FLM_SLAB_USAGE *		pUsageStats,
			FLMUINT *				puiTotalBytesAllocated) = 0;
	
		virtual void * FLMAPI allocCell(
			IF_Relocator *			pRelocator,
			void *					pvInitialData,
			FLMUINT					uiDataSize) = 0;
	
		virtual void * FLMAPI allocCell(
			IF_Relocator *			pRelocator,
			F_ALLOC_INIT_FUNC		fnAllocInit) = 0;
	
		virtual void FLMAPI freeCell( 
			void *					ptr) = 0;
	
		virtual void FLMAPI freeUnused( void) = 0;
	
		virtual void FLMAPI freeAll( void) = 0;
	
		virtual FLMUINT FLMAPI getCellSize( void) = 0;
		
		virtual void FLMAPI defragmentMemory( void) = 0;
	};

	RCODE FLMAPI FlmAllocFixedAllocator(
		IF_FixedAlloc **			ppFixedAllocator);
		
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface IF_BlockAlloc : public F_Object
	{
		virtual RCODE FLMAPI setup(
			FLMBOOL					bMultiThreaded,
			IF_SlabManager *		pSlabManager,
			IF_Relocator *			pRelocator,
			FLMUINT					uiBlockSize,
			FLM_SLAB_USAGE *		pUsageStats,
			FLMUINT *				puiTotalBytesAllocated) = 0;
	
		virtual RCODE FLMAPI allocBlock(
			void **					ppvBlock) = 0;
	
		virtual void FLMAPI freeBlock(
			void **					ppvBlock) = 0;
	
		virtual void FLMAPI freeUnused( void) = 0;
	
		virtual void FLMAPI freeAll( void) = 0;
	
		virtual void FLMAPI defragmentMemory( void) = 0;
	};

	RCODE FLMAPI FlmAllocBlockAllocator(
		IF_BlockAlloc **			ppBlockAllocator);
		
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_BufferAlloc : public F_Object
	{
		virtual RCODE FLMAPI setup(
			FLMBOOL					bMultiThreaded,
			IF_SlabManager *		pSlabManager,
			IF_Relocator *			pDefaultRelocator,
			FLM_SLAB_USAGE *		pUsageStats,
			FLMUINT *				puiTotalBytesAllocated) = 0;
	
		virtual RCODE FLMAPI allocBuf(
			IF_Relocator *			pRelocator,
			FLMUINT					uiSize,
			void *					pvInitialData,
			FLMUINT					uiDataSize,
			FLMBYTE **				ppucBuffer,
			FLMBOOL *				pbAllocatedOnHeap = NULL) = 0;
	
		virtual RCODE FLMAPI allocBuf(
			IF_Relocator *			pRelocator,
			FLMUINT					uiSize,
			F_ALLOC_INIT_FUNC		fnAllocInit,
			FLMBYTE **				ppucBuffer,
			FLMBOOL *				pbAllocatedOnHeap = NULL) = 0;
			
		virtual RCODE FLMAPI reallocBuf(
			IF_Relocator *			pRelocator,
			FLMUINT					uiOldSize,
			FLMUINT					uiNewSize,
			void *					pvInitialData,
			FLMUINT					uiDataSize,
			FLMBYTE **				ppucBuffer,
			FLMBOOL *				pbAllocatedOnHeap = NULL) = 0;
	
		virtual void FLMAPI freeBuf(
			FLMUINT					uiSize,
			FLMBYTE **				ppucBuffer) = 0;
	
		virtual FLMUINT FLMAPI getTrueSize(
			FLMUINT					uiSize,
			FLMBYTE *				pucBuffer) = 0;
	
		virtual FLMUINT FLMAPI getMaxCellSize( void) = 0;
		
		virtual void FLMAPI defragmentMemory( void) = 0;
	};

	RCODE FLMAPI FlmAllocBufferAllocator(
		IF_BufferAlloc **			ppBufferAllocator);
		
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface FLMEXP IF_MultiAlloc : public F_Object
	{
		virtual RCODE FLMAPI setup(
			FLMBOOL					bMultiThreaded,
			IF_SlabManager *		pSlabManager,
			IF_Relocator *			pDefaultRelocator,
			FLMUINT *				puiCellSizes,
			FLM_SLAB_USAGE *		pUsageStats,
			FLMUINT *				puiTotalBytesAllocated) = 0;
	
		virtual RCODE FLMAPI allocBuf(
			IF_Relocator *			pRelocator,
			FLMUINT					uiSize,
			FLMBYTE **				ppucBuffer) = 0;
	
		virtual RCODE FLMAPI allocBuf(
			IF_Relocator *			pRelocator,
			FLMUINT					uiSize,
			F_ALLOC_INIT_FUNC		fnAllocInit,
			FLMBYTE **				ppucBuffer) = 0;

		virtual RCODE FLMAPI reallocBuf(
			IF_Relocator *			pRelocator,
			FLMUINT					uiNewSize,
			FLMBYTE **				ppucBuffer) = 0;
	
		virtual void FLMAPI freeBuf(
			FLMBYTE **				ppucBuffer) = 0;
	
		virtual void FLMAPI defragmentMemory( void) = 0;
	
		virtual FLMUINT FLMAPI getTrueSize(
			FLMBYTE *				pucBuffer) = 0;
	};
	
	RCODE FLMAPI FlmAllocMultiAllocator(
		IF_MultiAlloc **			ppMultiAllocator);
		
	/****************************************************************************
	Desc:	Block
	****************************************************************************/
	flminterface FLMEXP IF_Block : public F_Object
	{
	};

	/****************************************************************************
	Desc:	Block manager
	****************************************************************************/
	flminterface FLMEXP IF_BlockMgr : public F_Object
	{
		virtual FLMUINT FLMAPI getBlockSize( void) = 0;
		
		virtual RCODE FLMAPI getBlock(
			FLMUINT32				ui32BlockAddr,
			IF_Block **				ppBlock,
			FLMBYTE **				ppucBlock = NULL) = 0;
			
		virtual RCODE FLMAPI createBlock(
			IF_Block **				ppBlock,
			FLMBYTE **				ppucBlock = NULL,
			FLMUINT32 *				pui32BlockAddr = NULL) = 0;
		
		virtual RCODE FLMAPI freeBlock(
			IF_Block **				ppBlock,
			FLMBYTE **				ppucBlock = NULL) = 0;
		
		virtual RCODE FLMAPI prepareForUpdate(
			IF_Block **				ppBlock,
			FLMBYTE **				ppucBlock = NULL) = 0;
	};
	
	RCODE FLMAPI FlmAllocBlockMgr(
		FLMUINT						uiBlockSize,
		IF_BlockMgr **				ppBlockMgr);
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	enum BTREE_ERR_TYPE
	{
		NO_ERR = 0,
		BT_HEADER,
		KEY_ORDER,
		DUPLICATE_KEYS,
		INFINITY_MARKER,
		CHILD_BLOCK_ADDRESS,
		GET_BLOCK_FAILED,
		MISSING_OVERALL_DATA_LENGTH,
		NOT_DATA_ONLY_BLOCK,
		BAD_DO_BLOCK_LENGTHS,
		BAD_COUNTS,
		CATASTROPHIC_FAILURE = 999
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	typedef struct
	{
		FLMUINT				uiKeyCnt;
		FLMUINT				uiFirstKeyCnt;
		FLMUINT				uiBlockCnt;
		FLMUINT				uiBytesUsed;
		FLMUINT				uiDOBlockCnt;
		FLMUINT				uiDOBytesUsed;
	} BTREE_LEVEL_STATS;
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	typedef struct
	{
		FLMUINT				uiBlockAddr;
		FLMUINT				uiBlockSize;
		FLMUINT				uiBlocksChecked;
		FLMUINT				uiAvgFreeSpace;
		FLMUINT				uiLevels;
		FLMUINT				uiNumKeys;
		FLMUINT64			ui64FreeSpace;
	#define F_BTREE_MAX_LEVELS			8
		BTREE_LEVEL_STATS	LevelStats[ F_BTREE_MAX_LEVELS];
		char					szMsg[ 64];
		BTREE_ERR_TYPE		type;
	} BTREE_ERR_INFO;

	/****************************************************************************
	Desc:	B-Tree
	****************************************************************************/
	flminterface FLMEXP IF_BTree : public F_Object
	{
		virtual RCODE FLMAPI btCreate(
			FLMUINT16					ui16BtreeId,
			FLMBOOL						bCounts,
			FLMBOOL						bData,
			FLMUINT32 *					pui32RootBlockAddr) = 0;
	
		virtual RCODE FLMAPI btOpen(
			FLMUINT32					ui32RootBlockAddr,
			FLMBOOL						bCounts,
			FLMBOOL						bData,
			IF_ResultSetCompare *	pCompare = NULL) = 0;
	
		virtual void FLMAPI btClose( void) = 0;
	
		virtual RCODE FLMAPI btDeleteTree(
			IF_DeleteStatus *			ifpDeleteStatus = NULL) = 0;
	
		virtual RCODE FLMAPI btGetBlockChains(
			FLMUINT *					puiBlockChains,
			FLMUINT *					puiNumLevels) = 0;
	
		virtual RCODE FLMAPI btRemoveEntry(
			const FLMBYTE *			pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT						uiKeyLen) = 0;
	
		virtual RCODE FLMAPI btInsertEntry(
			const FLMBYTE *			pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT						uiKeyLen,
			const FLMBYTE *			pucData,
			FLMUINT						uiDataLen,
			FLMBOOL						bFirst,
			FLMBOOL						bLast,
			FLMUINT32 *					pui32BlockAddr = NULL,
			FLMUINT *					puiOffsetIndex = NULL) = 0;
	
		virtual RCODE FLMAPI btReplaceEntry(
			const FLMBYTE *			pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT						uiKeyLen,
			const FLMBYTE *			pucData,
			FLMUINT						uiDataLen,
			FLMBOOL						bFirst,
			FLMBOOL						bLast,
			FLMBOOL						bTruncate = TRUE,
			FLMUINT32 *					pui32BlockAddr = NULL,
			FLMUINT *					puiOffsetIndex = NULL) = 0;
	
		virtual RCODE FLMAPI btLocateEntry(
			FLMBYTE *					pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT *					puiKeyLen,
			FLMUINT						uiMatch,
			FLMUINT *					puiPosition = NULL,
			FLMUINT *					puiDataLength = NULL,
			FLMUINT32 *					pui32BlockAddr = NULL,
			FLMUINT *					puiOffsetIndex = NULL) = 0;
	
		virtual RCODE FLMAPI btGetEntry(
			FLMBYTE *					pucKey,
			FLMUINT						uiKeyLen,
			FLMBYTE *					pucData,
			FLMUINT						uiDataBufSize,
			FLMUINT *					puiDataLen) = 0;
	
		virtual RCODE FLMAPI btNextEntry(
			FLMBYTE *					pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT *					puiKeyLen,
			FLMUINT *					puiDataLength = NULL,
			FLMUINT32 *					pui32BlockAddr = NULL,
			FLMUINT *					puiOffsetIndex = NULL) = 0;
	
		virtual RCODE FLMAPI btPrevEntry(
			FLMBYTE *					pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT *					puiKeyLen,
			FLMUINT *					puiDataLength = NULL,
			FLMUINT32 *					pui32BlockAddr = NULL,
			FLMUINT *					puiOffsetIndex = NULL) = 0;
	
		virtual RCODE FLMAPI btFirstEntry(
			FLMBYTE *					pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT *					puiKeyLen,
			FLMUINT *					puiDataLength = NULL,
			FLMUINT32 *					pui32BlockAddr = NULL,
			FLMUINT *					puiOffsetIndex = NULL) = 0;
	
		virtual RCODE FLMAPI btLastEntry(
			FLMBYTE *					pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT *					puiKeyLen,
			FLMUINT *					puiDataLength = NULL,
			FLMUINT32 *					pui32BlockAddr = NULL,
			FLMUINT *					puiOffsetIndex = NULL) = 0;
	
		virtual RCODE FLMAPI btSetReadPosition(
			FLMBYTE *					pucKey,
			FLMUINT						uiKeyLen,
			FLMUINT						uiPosition) = 0;
	
		virtual RCODE FLMAPI btGetReadPosition(
			FLMUINT *					puiPosition) = 0;
	
		virtual RCODE FLMAPI btPositionTo(
			FLMUINT						uiPosition,
			FLMBYTE *					pucKey,
			FLMUINT						uiKeyBufSize,
			FLMUINT *					puiKeyLen) = 0;
	
		virtual RCODE FLMAPI btGetPosition(
			FLMUINT *					puiPosition) = 0;
	
		virtual RCODE FLMAPI btRewind( void) = 0;
	
//		virtual RCODE FLMAPI btComputeCounts(
//			IF_BTree *					pUntilBtree,
//			FLMUINT *					puiBlockCount,
//			FLMUINT *					puiKeyCount,
//			FLMBOOL *					pbTotalsEstimated,
//			FLMUINT						uiAvgBlockFullness) = 0;
	
		virtual FLMBOOL FLMAPI btHasCounts( void) = 0;
	
		virtual FLMBOOL FLMAPI btHasData( void) = 0;
		
		virtual void FLMAPI btResetBtree( void) = 0;
		
		virtual FLMUINT32 FLMAPI getRootBlockAddr( void) = 0;
		
		virtual RCODE btCheck(
			BTREE_ERR_INFO *			pErrInfo) = 0;
	};
	
	RCODE FLMAPI FlmAllocBTree(
		IF_BlockMgr *					pBlockMgr,
		IF_BTree **						ppBtree);

	/****************************************************************************
	Desc:	This class is used to do pool memory allocations.
	****************************************************************************/
	
	/// Header for blocks in a memory pool.  This structure is at the head of each block that belongs to a pool of
	/// memory.
	typedef struct PoolMemoryBlock
	{
		PoolMemoryBlock *	pPrevBlock;		///< Points to the previous memory block in the memory pool.
		FLMUINT				uiBlockSize;	///< Total size of the memory block.
		FLMUINT				uiFreeOffset;	///< Offset in block where next allocation should be made.
		FLMUINT				uiFreeSize;		///< Amount of free memory left in block - from uiFreeOfs.
	} PoolMemoryBlock;

	/// Pool memory manager.  This structure is used to keep track of a pool
	/// of memory blocks that are used for pool memory allocation.
	typedef struct
	{
	FLMUINT			uiAllocBytes;			///< Total number of bytes requested from
													///< GedPoolAlloc and GedPoolCalloc calls
	FLMUINT			uiCount;					///< Number of frees and resets performed on 
													///< the pool
	} POOL_STATS;

	class FLMEXP F_Pool : public F_Object
	{
	public:
	
		F_Pool()
		{
			m_uiBytesAllocated = 0;
			m_pLastBlock = NULL;
			m_pPoolStats = NULL;
			m_uiBlockSize = 0;
		}
	
		virtual ~F_Pool();
	
		/// Initialize memory pool.
		/// \ingroup pool
		FINLINE void FLMAPI poolInit(
			FLMUINT			uiBlockSize			///< Default block size for the memory pool.
			)
		{
			m_uiBlockSize = uiBlockSize;
		}
	
		void smartPoolInit(
			POOL_STATS *	pPoolStats);
	
		/// Allocate memory from a memory pool.
		/// \ingroup pool
		RCODE FLMAPI poolAlloc(
			FLMUINT			uiSize,				///< Requested allocation size (in bytes).
			void **			ppvPtr				///< Pointer to the allocation
			);
	
		/// Allocate memory from a memory pool and initialize memory to zeroes.
		/// \ingroup pool
		RCODE FLMAPI poolCalloc(
			FLMUINT			uiSize,				///< Requested allocation size (in bytes).
			void **			ppvPtr);				///< Pointer to the allocation
	
		/// Free all memory blocks in a memory pool.
		/// \ingroup pool
		void FLMAPI poolFree( void);
	
		/// Reset a memory pool back to a mark.\   Free all memory blocks allocated after the mark.
		/// \ingroup pool
		void FLMAPI poolReset(
			void *			pvMark = NULL,		///< Mark that was obtained from GedPoolMark().
			FLMBOOL			bReduceFirstBlock = FALSE);
	
		/// Obtain a mark in a memory pool.\   Returned mark remembers a location in the
		/// pool which can later be passed to poolReset() to free all memory that was
		/// allocated after the mark.
		/// \ingroup pool
		FINLINE void * FLMAPI poolMark( void)
		{
			return (void *)(m_pLastBlock
								 ? (FLMBYTE *)m_pLastBlock + m_pLastBlock->uiFreeOffset
								 : NULL);
		}
	
		FINLINE FLMUINT FLMAPI getBlockSize( void)
		{
			return( m_uiBlockSize);
		}
	
		FINLINE FLMUINT FLMAPI getBytesAllocated( void)
		{
			return( m_uiBytesAllocated);
		}
	
	private:
	
		FINLINE void updateSmartPoolStats( void)
		{
			if (m_uiBytesAllocated)
			{
				if( (m_pPoolStats->uiAllocBytes + m_uiBytesAllocated) >= 0xFFFF0000)
				{
					m_pPoolStats->uiAllocBytes =
						(m_pPoolStats->uiAllocBytes / m_pPoolStats->uiCount) * 100;
					m_pPoolStats->uiCount = 100;
				}
				else
				{
					m_pPoolStats->uiAllocBytes += m_uiBytesAllocated;
					m_pPoolStats->uiCount++;
				}
				m_uiBytesAllocated = 0;
			}
		}
	
		FINLINE void setInitialSmartPoolBlockSize( void)
		{
			// Determine starting block size:
			// 1) average of bytes allocated / # of frees/resets (average size needed)
			// 2) add 10% - to minimize extra allocs 
	
			m_uiBlockSize = (m_pPoolStats->uiAllocBytes / m_pPoolStats->uiCount);
			m_uiBlockSize += (m_uiBlockSize / 10);
	
			if (m_uiBlockSize < 512)
			{
				m_uiBlockSize = 512;
			}
		}
	
		void freeToMark(
			void *		pvMark);
	
		PoolMemoryBlock *		m_pLastBlock;
		FLMUINT					m_uiBlockSize;
		FLMUINT					m_uiBytesAllocated;
		POOL_STATS *			m_pPoolStats;
	};

	/****************************************************************************
	Desc:
	*****************************************************************************/
	class FLMEXP F_DynaBuf : public F_Object
	{
	public:
	
		F_DynaBuf(
			FLMBYTE *		pucBuffer = NULL,
			FLMUINT			uiBufferSize = 0)
		{
			m_pucBuffer = pucBuffer;
			m_uiBufferSize = uiBufferSize;
			m_uiOffset = 0;
			m_bAllocatedBuffer = FALSE;
		}
		
		virtual ~F_DynaBuf()
		{
			if( m_bAllocatedBuffer)
			{
				f_free( &m_pucBuffer);
			}
		}
		
		FINLINE void FLMAPI truncateData(
			FLMUINT			uiSize)
		{
			if( uiSize < m_uiOffset)
			{
				m_uiOffset = uiSize;
			}
		}
		
		FINLINE RCODE FLMAPI allocSpace(
			FLMUINT		uiSize,
			void **		ppvPtr)
		{
			RCODE		rc = NE_FLM_OK;
			
			if( m_uiOffset + uiSize >= m_uiBufferSize)
			{
				if( RC_BAD( rc = resizeBuffer( m_uiOffset + uiSize + 512)))
				{
					goto Exit;
				}
			}
			
			*ppvPtr = &m_pucBuffer[ m_uiOffset];
			m_uiOffset += uiSize;
			
		Exit:
		
			return( rc);
		}
		
		FINLINE RCODE FLMAPI appendByte(
			FLMBYTE		ucChar)
		{
			RCODE			rc = NE_FLM_OK;
			FLMBYTE *	pucTmp = NULL;
			
			if( RC_BAD( rc = allocSpace( 1, (void **)&pucTmp)))
			{
				goto Exit;
			}
			
			*pucTmp = ucChar;
			
		Exit:
		
			return( rc);
		}
		
		FINLINE RCODE FLMAPI appendUniChar(
			FLMUNICODE	uChar)
		{
			RCODE				rc = NE_FLM_OK;
			FLMUNICODE *	puTmp = NULL;
			
			if( RC_BAD( rc = allocSpace( sizeof( FLMUNICODE), (void **)&puTmp)))
			{
				goto Exit;
			}
			
			*puTmp = uChar;
			
		Exit:
		
			return( rc);
		}
		
		FINLINE RCODE FLMAPI appendData(
			const void *		pvData,
			FLMUINT				uiSize)
		{
			RCODE		rc = NE_FLM_OK;
			void *	pvTmp = NULL;
			
			if( RC_BAD( rc = allocSpace( uiSize, &pvTmp)))
			{
				goto Exit;
			}
	
			if( uiSize == 1)
			{
				*((FLMBYTE *)pvTmp) = *((FLMBYTE *)pvData);
			}
			else
			{
				f_memcpy( pvTmp, pvData, uiSize);
			}
			
		Exit:
		
			return( rc);
		}
			
		FINLINE RCODE FLMAPI appendString(
			const char *		pszString)
		{
			RCODE			rc = NE_FLM_OK;
			void *		pvTmp = NULL;
			FLMUINT		uiSize = f_strlen( pszString);
			
			if( RC_BAD( rc = allocSpace( uiSize, &pvTmp)))
			{
				goto Exit;
			}
	
			f_memcpy( pvTmp, pszString, uiSize);
			
		Exit:
		
			return( rc);
		}
		
		FINLINE FLMBYTE * FLMAPI getBufferPtr( void)
		{
			return( m_pucBuffer);
		}
		
		FINLINE FLMUNICODE * FLMAPI getUnicodePtr( void)
		{
			if( m_uiOffset >= sizeof( FLMUNICODE))
			{
				return( (FLMUNICODE *)m_pucBuffer);
			}
			
			return( NULL);
		}
		
		FINLINE FLMUINT FLMAPI getUnicodeLength( void)
		{
			if( m_uiOffset <= sizeof( FLMUNICODE))
			{
				return( 0);
			}
			
			return( (m_uiOffset >> 1) - 1);
		}
		
		FINLINE FLMUINT FLMAPI getDataLength( void)
		{
			return( m_uiOffset);
		}
		
		FINLINE RCODE FLMAPI copyFromBuffer(
			F_DynaBuf *		pSource)
		{
			RCODE		rc = NE_FLM_OK;
			
			if( RC_BAD( rc = resizeBuffer( pSource->m_uiBufferSize)))
			{
				goto Exit;
			}
			
			if( (m_uiOffset = pSource->m_uiOffset) != 0)
			{
				f_memcpy( m_pucBuffer, pSource->m_pucBuffer, pSource->m_uiOffset);
			}
			
		Exit:
			
			return( rc);
		}		
		
	private:
	
		FINLINE RCODE resizeBuffer(
			FLMUINT		uiNewSize)
		{
			RCODE	rc = NE_FLM_OK;
			
			if( !m_bAllocatedBuffer)
			{
				if( uiNewSize > m_uiBufferSize)
				{
					FLMBYTE *		pucOriginalBuf = m_pucBuffer;
					
					if( RC_BAD( rc = f_alloc( uiNewSize, &m_pucBuffer)))
					{
						m_pucBuffer = pucOriginalBuf;
						goto Exit;
					}
					
					m_bAllocatedBuffer = TRUE;
					
					if( m_uiOffset)
					{
						f_memcpy( m_pucBuffer, pucOriginalBuf, m_uiOffset);
					}
				}
			}
			else
			{
				if( RC_BAD( rc = f_realloc( uiNewSize, &m_pucBuffer)))
				{
					goto Exit;
				}
				
				if( uiNewSize < m_uiOffset)
				{
					m_uiOffset = uiNewSize;
				}
			}
			
			m_uiBufferSize = uiNewSize;
			
		Exit:
		
			return( rc);
		}
	
		FLMBOOL		m_bAllocatedBuffer;
		FLMBYTE *	m_pucBuffer;
		FLMUINT		m_uiBufferSize;
		FLMUINT		m_uiOffset;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	typedef struct
	{
		F_ListItem *		pPrevItem;
		F_ListItem *		pNextItem;
		FLMUINT				uiListCount;
	} F_ListNode;
	
	#define FLM_ALL_LISTS			0xFFFF
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_ListItem : public F_Object
	{
	public:
	
		F_ListItem()
		{
			m_pListManager = NULL;
			m_pListNodes = NULL;
			m_uiListNodeCnt = 0;
			m_bInList = FALSE;
		}
	
		virtual ~F_ListItem();
	
		void setup(
			F_ListManager *		pListMgr,
			F_ListNode *			pListNodes,
			FLMUINT					uiListNodeCnt);
	
		void removeFromList(
			FLMUINT					uiList = 0);
	
		FINLINE F_ListItem * getNextListItem(
			FLMUINT					uiList = 0)
		{
			return( m_pListNodes[ uiList].pNextItem);
		}
	
		FINLINE F_ListItem * getPrevListItem(
			FLMUINT					uiList = 0)
		{
			return( m_pListNodes[ uiList].pPrevItem);
		}
	
		FINLINE F_ListItem * setNextListItem(
			FLMUINT					uiList,	
			F_ListItem *			pNewNext)
		{
			F_ListNode *			pListNode;
	
			pListNode = &m_pListNodes[ uiList];
			pListNode->pNextItem = pNewNext;
	
			return( pNewNext);
		}
	
		FINLINE F_ListItem * setPrevListItem(
			FLMUINT					uiList,	
			F_ListItem *			pNewPrev)
		{
			F_ListNode *			pListNode;
	
			pListNode = &m_pListNodes[ uiList];
			pListNode->pPrevItem = pNewPrev;
	
			return( pNewPrev);
		}
		
	private:
	
		F_ListManager *			m_pListManager;
		FLMUINT						m_uiListNodeCnt;
		F_ListNode *				m_pListNodes;
		FLMBOOL						m_bInList;
	
		friend class F_ListManager;
	};
		
	/****************************************************************************
	Desc:
	****************************************************************************/
	class F_ListManager : public F_Object
	{
	public:
	
		F_ListManager(
			F_ListNode *	pListNodes,
			FLMUINT			uiListNodeCnt)
		{
			flmAssert( pListNodes && uiListNodeCnt );
		
			m_uiListNodeCnt = uiListNodeCnt;
			m_pListNodes = pListNodes;
			f_memset( pListNodes, 0, sizeof( F_ListNode) * uiListNodeCnt );
		}
	
		virtual ~F_ListManager()
		{
			clearList( FLM_ALL_LISTS);
		}
	
		void insertFirst(
			FLMUINT			uiList,
			F_ListItem *	pNewFirstItem);
	
		void insertLast(
			FLMUINT			uiList,
			F_ListItem *	pNewLastItem);
	
		F_ListItem * getItem(
			FLMUINT			uiList,
			FLMUINT			nth);
	
		void removeItem(
			FLMUINT			uiList,
			F_ListItem *	pItem);
	
		FINLINE FLMUINT getListCount( void)
		{
			return( m_uiListNodeCnt);
		}
	
		FLMUINT getItemCount(
			FLMUINT			uiList);
	
		void clearList(
			FLMUINT			uiList = 0);
	
	private:
	
		FLMUINT				m_uiListNodeCnt;
		F_ListNode *		m_pListNodes;
	};

	// IMPORTANT NOTE: If these are changed, corresonding changes
	// should be made in java and C# code as well.
	/// Types of locks that may be requested.
	typedef enum
	{
		FLM_LOCK_NONE = 0,
		FLM_LOCK_EXCLUSIVE,		///< 1 = Exclusive lock.
		FLM_LOCK_SHARED			///< 2 = Shared lock.
	} eLockType;

	/****************************************************************************
	/// Abstract base class to get lock information.  The application must
	/// implement this class.  A pointer to an object of this class is passed
	/// into IF_LockObject::getLockInfo().
	****************************************************************************/
	flminterface IF_LockInfoClient : public F_Object
	{
		/// Return the lock count.  This method is called by to tell the
		/// application how many lock holders plus lock waiters there are.  This
		/// gives the application an opportunity to allocate memory to hold the
		/// information that will be returned via the 
		/// IF_LockInfoClient::addLockInfo() method.  The application should
		/// return TRUE from this method in order to continue, FALSE if it wants
		/// to stop and return from the IF_LockObject::getLockInfo() function.
		virtual FLMBOOL FLMAPI setLockCount(
			FLMUINT					uiTotalLocks		///< Total number of lock holders plus lock waiters.
			) = 0;

		/// Return lock information for a lock holder or waiter.  This method
		/// is called for each thread that is either holding the lock or waiting
		/// to obtain the lock.  The application should return TRUE from this
		/// method in order to continue, FALSE if it wants to stop and return
		/// from the IF_LockObject::getLockInfo() function.
		virtual FLMBOOL FLMAPI addLockInfo(
			FLMUINT		uiLockNum,			///< Position in queue (0 = lock holder, 1..n = lock waiter).
			FLMUINT		uiThreadID,			///< Thread ID of the lock holder/waiter.
			FLMUINT		uiTime				///< For the lock holder, this is the amount of time the lock has been
													///< held.\   For a lock waiter, this is the amount of time the thread
													///< has been waiting to obtain the lock.\  Both times are milliseconds.
			) = 0;
	};

	// IMPORTANT NOTE: This structure needs to stay in sync with
	// corresponding structures in java and C# code.
	/**************************************************************************
	/// Structure used in gathering statistics to hold an operation count and an elapsed time.
	**************************************************************************/
	typedef struct
	{
		FLMUINT64	ui64Count;							///< Number of times operation was performed
		FLMUINT64	ui64ElapMilli;						///< Total elapsed time (milliseconds) for the operations.
	} F_COUNT_TIME_STAT;
	
	// IMPORTANT NOTE: This structure needs to stay in sync with
	// corresponding structures in java and C# code.
	/**************************************************************************
	/// Structure for returning lock statistics.
	**************************************************************************/
	typedef struct
	{
		F_COUNT_TIME_STAT	NoLocks;						///< Statistics on times when nobody was holding a lock on the database.
		F_COUNT_TIME_STAT	WaitingForLock;			///< Statistics on times threads were waiting to obtain a database lock.
		F_COUNT_TIME_STAT	HeldLock;					///< Statistics on times when a thread was holding a lock on the database.
	} F_LOCK_STATS;
			
	/****************************************************************************
	/// Structure that gives information on threads that are either waiting to
	/// obtain a lock or have obtained a lock.
	****************************************************************************/
	typedef struct
	{
		FLMUINT		uiThreadId;							///< Thread id of thread that is waiting to obtain a lock or holds a lock.
		FLMUINT		uiTime;								///< For lock holder, this is the time the lock was obtained.
																///< For the lock waiter, this is the time he started waiting for the lock.
	} F_LOCK_USER;
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	flminterface IF_LockObject : public F_Object
	{
		virtual RCODE FLMAPI lock(
			F_SEM						hWaitSem,
			FLMBOOL					bExclLock,
			FLMUINT					uiMaxWaitSecs,
			FLMINT					iPriority,
			F_LOCK_STATS *			pLockStats = NULL) = 0;
	
		virtual RCODE FLMAPI unlock(
			F_LOCK_STATS *			pLockStats = NULL) = 0;
			
		virtual FLMUINT FLMAPI getLockCount( void) = 0;
	
		virtual FLMUINT FLMAPI getWaiterCount( void) = 0;
		
		virtual RCODE FLMAPI getLockInfo(
			FLMINT					iPriority,
			eLockType *				peCurrLockType,
			FLMUINT *				puiThreadId,
			FLMUINT *				puiLockHeldTime = NULL,
			FLMUINT *				puiNumExclQueued = NULL,
			FLMUINT *				puiNumSharedQueued = NULL,
			FLMUINT *				puiPriorityCount = NULL) = 0;
			
		virtual RCODE FLMAPI getLockInfo(
			IF_LockInfoClient *	pLockInfo) = 0;
	
		virtual RCODE FLMAPI getLockQueue(
			F_LOCK_USER **			ppLockUsers) = 0;
	
		virtual FLMBOOL FLMAPI haveHigherPriorityWaiter(
			FLMINT					iPriority) = 0;
	
		virtual void FLMAPI timeoutLockWaiter(
			FLMUINT					uiThreadId) = 0;
	
		virtual void FLMAPI timeoutAllWaiters( void) = 0;
	};
	
	RCODE FLMAPI FlmAllocLockObject(
		IF_LockObject **			ppLockObject);
	
	/****************************************************************************
	Desc: Misc.
	****************************************************************************/
	#define F_UNREFERENCED_PARM( parm) \
		(void)parm
		
	#define f_min(a, b) \
		((a) < (b) ? (a) : (b))
		
	#define f_max(a, b) \
		((a) < (b) ? (b) : (a))
		
	#define f_swap( a, b, tmp) \
		((tmp) = (a), (a) = (b), (b) = (tmp))
		
	FINLINE FLMBOOL f_isHexChar(
		FLMBYTE		ucChar)
	{
		if( (ucChar >= '0' && ucChar <= '9') ||
			(ucChar >= 'A' && ucChar <= 'F') ||
			(ucChar >= 'a' && ucChar <= 'f'))
		{
			return( TRUE);
		}

		return( FALSE);
	}

	FINLINE FLMBOOL f_isHexChar(
		FLMUNICODE		uChar)
	{
		if( uChar > 127)
		{
			return( FALSE);
		}

		return( f_isHexChar( f_tonative( (FLMBYTE)uChar)));
	}

	FINLINE FLMBYTE f_getHexVal(
		FLMBYTE		ucChar)
	{
		if( ucChar >= '0' && ucChar <= '9')
		{
			return( (FLMBYTE)(ucChar - '0'));
		}
		else if( ucChar >= 'A' && ucChar <= 'F')
		{
			return( (FLMBYTE)((ucChar - 'A') + 10));
		}
		else if( ucChar >= 'a' && ucChar <= 'f')
		{
			return( (FLMBYTE)((ucChar - 'a') + 10));
		}

		return( 0);
	}

	FINLINE FLMBYTE f_getHexVal(
		FLMUNICODE	uChar)
	{
		return( f_getHexVal( f_tonative( (FLMBYTE)uChar)));
	}

	FINLINE FLMBOOL f_isValidHexNum(
		const FLMBYTE *	pszString)
	{
		if( *pszString == 0)
		{
			return( FALSE);
		}

		while( *pszString)
		{
			if( !f_isHexChar( *pszString))
			{
				return( TRUE);
			}

			pszString++;
		}

		return( TRUE);
	}

	FINLINE FLMUINT64 f_roundUp(
		FLMUINT64		ui64ValueToRound,
		FLMUINT64		ui64Boundary)
	{
		FLMUINT64	ui64RetVal;
		
		ui64RetVal = ((ui64ValueToRound / ui64Boundary) * ui64Boundary);	
		
		if( ui64RetVal < ui64ValueToRound)
		{
			ui64RetVal += ui64Boundary;
		}
		
		return( ui64RetVal);
	}
	
	FINLINE void f_setBit(
		FLMBYTE *		pucBuffer,
		FLMUINT			uiBit)
	{
		pucBuffer[ uiBit >> 3] |= (FLMBYTE)(0x01 << (uiBit & 0x07));
	}
			
	FINLINE void f_clearBit(
		FLMBYTE *		pucBuffer,
		FLMUINT			uiBit)
	{
		pucBuffer[ uiBit >> 3] &= ~((FLMBYTE)(0x01 << (uiBit & 0x07)));
	}
	
	FINLINE FLMBOOL f_isBitSet(
		FLMBYTE *		pucBuffer,
		FLMUINT			uiBit)
	{
		return( (pucBuffer[ uiBit >> 3] & (FLMBYTE)(0x01 << (uiBit & 0x07))) 
							? TRUE 
							: FALSE);
	}
	
	RCODE FLMAPI f_filecpy(
		const char *				pszSourceFile,
		const char *				pszData);
		
	RCODE FLMAPI f_filecat(
		const char *				pszSourceFile,
		const char *				pszData);
		
	RCODE FLMAPI f_filetobuf(
		const char *				pszSourceFile,
		char **						ppszBuffer);
		
	/****************************************************************************
	Desc:	FTX
	****************************************************************************/
	
	#define FKB_ESCAPE      			0xE01B
	#define FKB_ESC         			FKB_ESCAPE
	#define FKB_SPACE       			0x20
	
	#define FKB_HOME        			0xE008
	#define FKB_UP          			0xE017
	#define FKB_PGUP        			0xE059
	#define FKB_LEFT        			0xE019
	#define FKB_RIGHT       			0xE018
	#define FKB_END         			0xE055
	#define FKB_DOWN        			0xE01A
	#define FKB_PGDN        			0xE05A
	#define FKB_PLUS						0x002B
	#define FKB_MINUS						0x002D
	
	#define FKB_INSERT      			0xE05D
	#define FKB_DELETE      			0xE051
	#define FKB_BACKSPACE   			0xE050
	#define FKB_TAB         			0xE009
	
	#define FKB_ENTER       			0xE00A
	#define FKB_F1          			0xE020
	#define FKB_F2          			0xE021
	#define FKB_F3          			0xE022
	#define FKB_F4          			0xE023
	#define FKB_F5          			0xE024
	#define FKB_F6          			0xE025
	#define FKB_F7          			0xE026
	#define FKB_F8          			0xE027
	#define FKB_F9          			0xE028
	#define FKB_F10         			0xE029
	#define FKB_F11         			0xE03A
	#define FKB_F12         			0xE03B
	
	#define FKB_STAB        			0xE05E
	
	#define FKB_SF1         			0xE02C
	#define FKB_SF2         			0xE02D
	#define FKB_SF3         			0xE02E
	#define FKB_SF4         			0xE02F
	#define FKB_SF5         			0xE030
	#define FKB_SF6         			0xE031
	#define FKB_SF7         			0xE032
	#define FKB_SF8         			0xE033
	#define FKB_SF9         			0xE034
	#define FKB_SF10        			0xE035
	#define FKB_SF11        			0xE036
	#define FKB_SF12        			0xE037
	
	#define FKB_ALT_A       			0xFDDC
	#define FKB_ALT_B       			0xFDDD
	#define FKB_ALT_C       			0xFDDE
	#define FKB_ALT_D       			0xFDDF
	#define FKB_ALT_E       			0xFDE0
	#define FKB_ALT_F       			0xFDE1
	#define FKB_ALT_G       			0xFDE2
	#define FKB_ALT_H       			0xFDE3
	#define FKB_ALT_I       			0xFDE4
	#define FKB_ALT_J       			0xFDE5
	#define FKB_ALT_K       			0xFDE6
	#define FKB_ALT_L       			0xFDE7
	#define FKB_ALT_M       			0xFDE8
	#define FKB_ALT_N       			0xFDE9
	#define FKB_ALT_O       			0xFDEA
	#define FKB_ALT_P       			0xFDEB
	#define FKB_ALT_Q       			0xFDEC
	#define FKB_ALT_R       			0xFDED
	#define FKB_ALT_S       			0xFDEE
	#define FKB_ALT_T       			0xFDEF
	#define FKB_ALT_U       			0xFDF0
	#define FKB_ALT_V       			0xFDF1
	#define FKB_ALT_W       			0xFDF2
	#define FKB_ALT_X       			0xFDF3
	#define FKB_ALT_Y       			0xFDF4
	#define FKB_ALT_Z       			0xFDF5
	
	#define FKB_ALT_1       			0xFDF7
	#define FKB_ALT_2       			0xFDF8
	#define FKB_ALT_3       			0xFDF9
	#define FKB_ALT_4       			0xFDFA
	#define FKB_ALT_5       			0xFDFB
	#define FKB_ALT_6       			0xFDFC
	#define FKB_ALT_7       			0xFDFD
	#define FKB_ALT_8       			0xFDFE
	#define FKB_ALT_9       			0xFDFF
	#define FKB_ALT_0       			0xFDF6
	
	#define FKB_ALT_MINUS   			0xE061
	#define FKB_ALT_EQUAL   			0xE06B
	
	#define FKB_ALT_F1      			0xE038
	#define FKB_ALT_F2      			0xE039
	#define FKB_ALT_F3      			0xE03A
	#define FKB_ALT_F4      			0xE03B
	#define FKB_ALT_F5      			0xE03C
	#define FKB_ALT_F6      			0xE03D
	#define FKB_ALT_F7      			0xE03E
	#define FKB_ALT_F8      			0xE03F
	#define FKB_ALT_F9      			0xE040
	#define FKB_ALT_F10     			0xE041
	
	#define FKB_GOTO        			0xE058
	#define FKB_CTRL_HOME   			0xE058
	#define FKB_CTRL_UP     			0xE063
	#define FKB_CTRL_PGUP   			0xE057
	
	#define FKB_CTRL_LEFT   			0xE054
	#define FKB_CTRL_RIGHT  			0xE053
	
	#define FKB_CTRL_END    			0xE00B
	#define FKB_CTRL_DOWN   			0xE064
	#define FKB_CTRL_PGDN   			0xE00C
	#define FKB_CTRL_INSERT 			0xE06E
	#define FKB_CTRL_DELETE 			0xE06D
	
	#define FKB_CTRL_ENTER  			0xE05F
	
	#define FKB_CTRL_A      			0xE07C
	#define FKB_CTRL_B      			0xE07D
	#define FKB_CTRL_C      			0xE07E
	#define FKB_CTRL_D      			0xE07F
	#define FKB_CTRL_E      			0xE080
	#define FKB_CTRL_F      			0xE081
	#define FKB_CTRL_G      			0xE082
	#define FKB_CTRL_H      			0xE083
	#define FKB_CTRL_I      			0xE084
	#define FKB_CTRL_J      			0xE085
	#define FKB_CTRL_K      			0xE086
	#define FKB_CTRL_L      			0xE087
	#define FKB_CTRL_M      			0xE088
	#define FKB_CTRL_N      			0xE089
	#define FKB_CTRL_O      			0xE08A
	#define FKB_CTRL_P      			0xE08B
	#define FKB_CTRL_Q      			0xE08C
	#define FKB_CTRL_R      			0xE08D
	#define FKB_CTRL_S      			0xE08E
	#define FKB_CTRL_T      			0xE08F
	#define FKB_CTRL_U      			0xE090
	#define FKB_CTRL_V      			0xE091
	#define FKB_CTRL_W      			0xE092
	#define FKB_CTRL_X      			0xE093
	#define FKB_CTRL_Y      			0xE094
	#define FKB_CTRL_Z      			0xE095
	
	#define FKB_CTRL_1      			0xE06B
	#define FKB_CTRL_2      			0xE06C
	#define FKB_CTRL_3      			0xE06D
	#define FKB_CTRL_4      			0xE06E
	#define FKB_CTRL_5      			0xE06F
	#define FKB_CTRL_6      			0xE070
	#define FKB_CTRL_7      			0xE071
	#define FKB_CTRL_8      			0xE072
	#define FKB_CTRL_9      			0xE073
	#define FKB_CTRL_0      			0xE074
	
	#define FKB_CTRL_MINUS  			0xE060
	#define FKB_CTRL_EQUAL  			0xE061
	
	#define FKB_CTRL_F1     			0xE038
	#define FKB_CTRL_F2     			0xE039
	#define FKB_CTRL_F3     			0xE03A
	#define FKB_CTRL_F4     			0xE03B
	#define FKB_CTRL_F5     			0xE03C
	#define FKB_CTRL_F6     			0xE03D
	#define FKB_CTRL_F7     			0xE03E
	#define FKB_CTRL_F8     			0xE03F
	#define FKB_CTRL_F9     			0xE040
	#define FKB_CTRL_F10    			0xE041

	#define FLM_CURSOR_BLOCK			0x01
	#define FLM_CURSOR_UNDERLINE		0x02
	#define FLM_CURSOR_INVISIBLE		0x04
	#define FLM_CURSOR_VISIBLE			0x08
	
	typedef struct FTX_SCREEN	FTX_SCREEN;
	
	typedef struct FTX_WINDOW	FTX_WINDOW;
	
	typedef FLMBOOL (FLMAPI * KEY_HANDLER)(
		FLMUINT			uiKeyIn,
		FLMUINT *		puiKeyOut,
		void *			pvAppData);
	
	RCODE FLMAPI FTXInit(
		const char *	pszAppName = NULL,
		FLMUINT			uiCols = 0,
		FLMUINT			uiRows = 0,
		eColorType		backgroundColor = FLM_BLUE,
		eColorType		foregroundColor = FLM_WHITE,
		KEY_HANDLER 	pKeyHandler = NULL,
		void *			pvKeyHandlerData = NULL);
	
	void FLMAPI FTXExit( void);
	
	void FLMAPI FTXCycleScreensNext( void);
	
	void FLMAPI FTXCycleScreensPrev( void);
	
	void FLMAPI FTXRefreshCursor( void);
	
	void FLMAPI FTXInvalidate( void);
	
	void FLMAPI FTXSetShutdownFlag(
		FLMBOOL *		pbShutdownFlag);
	
	RCODE FLMAPI FTXScreenInit(
		const char *	pszName,
		FTX_SCREEN **	ppScreen);
	
	RCODE FLMAPI FTXCaptureScreen(
		FLMBYTE *		pText,
		FLMBYTE *		pForeAttrib,
		FLMBYTE *		pBackAttrib);
	
	void FLMAPI FTXRefresh( void);
	
	void FLMAPI FTXSetRefreshState(
		FLMBOOL			bDisable);
		
	FLMBOOL FLMAPI FTXRefreshDisabled( void);
	
	RCODE FLMAPI FTXAddKey(
		FLMUINT			uiKey);
	
	RCODE FLMAPI FTXWinInit(
		FTX_SCREEN *	pScreen,
		FLMUINT 			uiCols,
		FLMUINT			uiRows,
		FTX_WINDOW **	ppWindow);
	
	void FLMAPI FTXWinFree(
		FTX_WINDOW **	ppWindow);
	
	RCODE FLMAPI FTXWinOpen(
		FTX_WINDOW *	pWindow);
	
	RCODE FLMAPI FTXWinSetName(
		FTX_WINDOW *	pWindow,
		char *			pszName);
	
	void FLMAPI FTXWinClose(
		FTX_WINDOW *	pWindow);
	
	void FLMAPI FTXWinSetFocus(
		FTX_WINDOW *	pWindow);
	
	void FLMAPI FTXWinPrintChar(
		FTX_WINDOW *	pWindow,
		FLMUINT			uiChar);
	
	void FLMAPI FTXWinPrintStr(
		FTX_WINDOW *	pWindow,
		const char *	pszString);
	
	void FLMAPI FTXWinPrintf(
		FTX_WINDOW *	pWindow,
		const char *	pszFormat, ...);
	
	void FLMAPI FTXWinCPrintf(
		FTX_WINDOW *	pWindow,
		eColorType		backgroundColor,
		eColorType		foregroundColor,
		const char *	pszFormat, ...);
	
	void FLMAPI FTXWinPrintStrXY(
		FTX_WINDOW *	pWindow,
		const char *	pszString,
		FLMUINT			uiCol,
		FLMUINT			uiRow);
	
	void FLMAPI FTXWinMove(
		FTX_WINDOW *	pWindow,
		FLMUINT			uiCol,
		FLMUINT			uiRow);
	
	void FLMAPI FTXWinPaintBackground(
		FTX_WINDOW *	pWindow,
		eColorType		backgroundColor);
	
	void FLMAPI FTXWinPaintForeground(
		FTX_WINDOW *	pWindow,
		eColorType		foregroundColor);
	
	void FLMAPI FTXWinPaintRow(
		FTX_WINDOW *	pWindow,
		eColorType *	pBackgroundColor,
		eColorType *	pForegroundColor,
		FLMUINT			uiRow);
	
	void FLMAPI FTXWinSetChar(
		FTX_WINDOW *	pWindow,
		FLMUINT			uiChar);
	
	void FLMAPI FTXWinPaintRowForeground(
		FTX_WINDOW *	pWindow,
		eColorType		foregroundColor,
		FLMUINT			uiRow);
	
	void FLMAPI FTXWinPaintRowBackground(
		FTX_WINDOW *	pWindow,
		eColorType		backgroundColor,
		FLMUINT			uiRow);
	
	void FLMAPI FTXWinSetBackFore(
		FTX_WINDOW *	pWindow,
		eColorType		backgroundColor,
		eColorType		foregroundColor);
	
	void FLMAPI FTXWinGetCanvasSize(
		FTX_WINDOW *	pWindow,
		FLMUINT *		puiNumCols,
		FLMUINT *		puiNumRows);
	
	void FLMAPI FTXWinGetSize(
		FTX_WINDOW *	pWindow,
		FLMUINT *		puiNumCols,
		FLMUINT *		puiNumRows);
	
	FLMUINT FLMAPI FTXWinGetCurrRow(
		FTX_WINDOW *	pWindow);
	
	FLMUINT FLMAPI FTXWinGetCurrCol(
		FTX_WINDOW *	pWindow);
	
	void FLMAPI FTXWinGetBackFore(
		FTX_WINDOW *	pWindow,
		eColorType *	pBackgroundColor,
		eColorType *	pForegroundColor);
	
	void FLMAPI FTXWinDrawBorder(
		FTX_WINDOW *	pWindow);
	
	void FLMAPI FTXWinSetTitle(
		FTX_WINDOW *	pWindow,
		const char *	pszTitle,
		eColorType		backgroundColor,
		eColorType		foregroundColor);
	
	void FLMAPI FTXWinSetHelp(
		FTX_WINDOW *	pWindow,
		const char *	pszHelp,
		eColorType		backgroundColor,
		eColorType		foregroundColor);
	
	RCODE FLMAPI FTXLineEdit(
		FTX_WINDOW *	pWindow,
		char *   		pszBuffer,
		FLMUINT      	uiBufSize,
		FLMUINT      	uiMaxWidth,
		FLMUINT *		puiCharCount,
		FLMUINT *   	puiTermChar);
	
	FLMUINT FLMAPI FTXLineEd(
		FTX_WINDOW *	pWindow,
		char *			pszBuffer,
		FLMUINT			uiBufSize);
	
	void FLMAPI FTXWinSetCursorPos(
		FTX_WINDOW *	pWindow,
		FLMUINT			uiCol,
		FLMUINT			uiRow);
	
	void FLMAPI FTXWinGetCursorPos(
		FTX_WINDOW *	pWindow,
		FLMUINT *		puiCol,
		FLMUINT *		puiRow);
	
	void FLMAPI FTXWinClear(
		FTX_WINDOW *	pWindow);
	
	void FLMAPI FTXWinClearXY(
		FTX_WINDOW *	pWindow,
		FLMUINT 			uiCol,
		FLMUINT			uiRow);
	
	void FLMAPI FTXWinClearLine(
		FTX_WINDOW *	pWindow,
		FLMUINT			uiCol,
		FLMUINT			uiRow);
	
	void FLMAPI FTXWinClearToEOL(
		FTX_WINDOW *	pWindow);
		
	void FLMAPI FTXWinSetCursorType(
		FTX_WINDOW *	pWindow,
		FLMUINT			uiType);
	
	FLMUINT FLMAPI FTXWinGetCursorType(
		FTX_WINDOW *	pWindow);
	
	RCODE FLMAPI FTXWinInputChar(
		FTX_WINDOW *	pWindow,
		FLMUINT *		puiChar);
	
	RCODE FLMAPI FTXWinTestKB(
		FTX_WINDOW *	pWindow);
	
	void FLMAPI FTXWinSetScroll(
		FTX_WINDOW *	pWindow,
		FLMBOOL			bScroll);
	
	void FLMAPI FTXWinSetLineWrap(
		FTX_WINDOW *	pWindow,
		FLMBOOL			bLineWrap);
	
	void FLMAPI FTXWinGetScroll(
		FTX_WINDOW *	pWindow,
		FLMBOOL *		pbScroll);
	
	RCODE FLMAPI FTXWinGetScreen(
		FTX_WINDOW *	pWindow,
		FTX_SCREEN **	ppScreen);
	
	RCODE FLMAPI FTXWinGetPosition(
		FTX_WINDOW *	pWindow,
		FLMUINT *		puiCol,
		FLMUINT *		puiRow);
	
	void FLMAPI FTXScreenFree(
		FTX_SCREEN **	ppScreen);
	
	RCODE FLMAPI FTXScreenInitStandardWindows(
		FTX_SCREEN *	pScreen,
		eColorType		titleBackColor,
		eColorType		titleForeColor,
		eColorType		mainBackColor,
		eColorType		mainForeColor,
		FLMBOOL			bBorder,
		FLMBOOL			bBackFill,
		const char *	pszTitle,
		FTX_WINDOW **	ppTitleWin,
		FTX_WINDOW **	ppMainWin);
	
	void FLMAPI FTXScreenSetShutdownFlag(
		FTX_SCREEN *	pScreen,
		FLMBOOL *		pbShutdownFlag);
	
	RCODE FLMAPI FTXScreenDisplay(
		FTX_SCREEN *	pScreen);
	
	RCODE FLMAPI FTXScreenGetSize(
		FTX_SCREEN *	pScreen,
		FLMUINT *		puiNumCols,
		FLMUINT *		puiNumRows);
	
	RCODE FLMAPI FTXMessageWindow(
		FTX_SCREEN *	pScreen,
		eColorType		backgroundColor,
		eColorType		foregroundColor,
		const char *	pszMessage1,
		const char *	pszMessage2,
		FTX_WINDOW **	ppWindow);
	
	RCODE FLMAPI FTXDisplayMessage(
		FTX_SCREEN *	pScreen,
		eColorType		backgroundColor,
		eColorType		foregroundColor,
		const char *	pszMessage1,
		const char *	pszMessage2,
		FLMUINT *		puiTermChar);
	
	RCODE FLMAPI FTXDisplayScrollWindow(
		FTX_SCREEN *	pScreen,
		const char *	pszTitle,
		const char *	pszMessage,
		FLMUINT			uiCols,
		FLMUINT			uiRows);
	
	RCODE FLMAPI FTXGetInput(
		FTX_SCREEN *	pScreen,
		const char *	pszMessage,
		char *			pszResponse,
		FLMUINT			uiMaxRespLen,
		FLMUINT *		puiTermChar);

	void FLMAPI FTXBeep( void);

	RCODE FLMAPI f_conInit(
		FLMUINT			uiRows,
		FLMUINT			uiCols,
		const char *	pszTitle);
	
	void FLMAPI f_conExit( void);
	
	void FLMAPI f_conGetScreenSize(
		FLMUINT *		puiNumColsRV,
		FLMUINT *		puiNumRowsRV);
	
	void FLMAPI f_conDrawBorder( void);

	void FLMAPI f_conStrOut(
		const char *	pszString);
	
	void FLMAPI f_conStrOutXY(
		const char *	pszString,
		FLMUINT			uiCol,
		FLMUINT			uiRow);
	
	void FLMAPI f_conPrintf(
		const char *	pszFormat, ...);
	
	void FLMAPI f_conCPrintf(
		eColorType		back,
		eColorType		fore,
		const char *	pszFormat, ...);
	
	void FLMAPI f_conClearScreen(
		FLMUINT			uiCol,
		FLMUINT			uiRow);
	
	void FLMAPI f_conClearLine(
		FLMUINT			uiCol,
		FLMUINT			uiRow);
	
	void FLMAPI f_conSetBackFore(
		eColorType		backColor,
		eColorType		foreColor);
	
	FLMUINT FLMAPI f_conGetCursorColumn( void);

	FLMUINT FLMAPI f_conGetCursorRow( void);
	
	void FLMAPI f_conSetCursorType(
		FLMUINT			uiType);
		
	void FLMAPI f_conSetCursorPos(
		FLMUINT			uiCol,
		FLMUINT			uiRow);
	
	FLMUINT FLMAPI f_conGetKey( void);
	
	FLMBOOL FLMAPI f_conHaveKey( void);
	
	FLMUINT FLMAPI f_conLineEdit(
		char *			pszString,
		FLMUINT			uiMaxLen);

	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_BufferIStream : public IF_BufferIStream
	{
	public:
	
		F_BufferIStream()
		{
			m_pucBuffer = NULL;
			m_uiBufferLen = 0;
			m_uiOffset = 0;
			m_bAllocatedBuffer = FALSE;
			m_bIsOpen = FALSE;
		}
	
		virtual ~F_BufferIStream();
	
		RCODE FLMAPI openStream(
			const char *		pucBuffer,
			FLMUINT				uiLength,
			char **				ppucAllocatedBuffer = NULL);
	
		FINLINE FLMUINT64 FLMAPI totalSize( void)
		{
			f_assert( m_bIsOpen);
			return( m_uiBufferLen);
		}
	
		FINLINE FLMUINT64 FLMAPI remainingSize( void)
		{
			f_assert( m_bIsOpen);
			return( m_uiBufferLen - m_uiOffset);
		}
	
		RCODE FLMAPI closeStream( void);
	
		FINLINE RCODE FLMAPI positionTo(
			FLMUINT64		ui64Position)
		{
			f_assert( m_bIsOpen);
	
			if( ui64Position < m_uiBufferLen)
			{
				m_uiOffset = (FLMUINT)ui64Position;
			}
			else
			{
				m_uiOffset = m_uiBufferLen;
			}
	
			return( NE_FLM_OK);
		}
	
		FINLINE FLMUINT64 FLMAPI getCurrPosition( void)
		{
			f_assert( m_bIsOpen);
			return( m_uiOffset);
		}
	
		FINLINE void FLMAPI truncateStream(
			FLMUINT64		ui64Offset = 0)
		{
			f_assert( m_bIsOpen);
			f_assert( ui64Offset >= m_uiOffset);
			f_assert( ui64Offset <= m_uiBufferLen);
			
			m_uiBufferLen = (FLMUINT)ui64Offset;
		}
	
		RCODE FLMAPI read(
			void *			pvBuffer,
			FLMUINT			uiBytesToRead,
			FLMUINT *		puiBytesRead);
			
		FINLINE const FLMBYTE * getBuffer( void)
		{
			f_assert( m_bIsOpen);
			return( m_pucBuffer);
		}
		
		FINLINE const FLMBYTE * FLMAPI getBufferAtCurrentOffset( void)
		{
			f_assert( m_bIsOpen);
			return( m_pucBuffer ? &m_pucBuffer[ m_uiOffset] : NULL);
		}
		
		FINLINE FLMBOOL isOpen( void)
		{
			return( m_bIsOpen);
		}
	
	private:
	
		const FLMBYTE *	m_pucBuffer;
		FLMUINT				m_uiBufferLen;
		FLMUINT				m_uiOffset;
		FLMBOOL				m_bAllocatedBuffer;
		FLMBOOL				m_bIsOpen;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_FileIStream : public IF_PosIStream
	{
	public:
	
		F_FileIStream()
		{
			m_pFileHdl = NULL;
			m_ui64FileOffset = 0;
		}
	
		virtual ~F_FileIStream()
		{
			if( m_pFileHdl)
			{
				m_pFileHdl->Release();
			}
		}
	
		RCODE FLMAPI openStream(
			const char *	pszPath);
	
		RCODE FLMAPI closeStream( void);
	
		RCODE FLMAPI positionTo(
			FLMUINT64		ui64Position);
	
		FLMUINT64 FLMAPI totalSize( void);
	
		FLMUINT64 FLMAPI remainingSize( void);
	
		FLMUINT64 FLMAPI getCurrPosition( void);
	
		RCODE FLMAPI read(
			void *			pvBuffer,
			FLMUINT			uiBytesToRead,
			FLMUINT *		puiBytesRead);
	
	private:
	
		IF_FileHdl *		m_pFileHdl;
		FLMUINT64			m_ui64FileOffset;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_BufferedIStream : public IF_PosIStream
	{
	public:
	
		F_BufferedIStream()
		{
			m_pIStream = NULL;
			m_pucBuffer = NULL;
		}
	
		virtual ~F_BufferedIStream()
		{
			closeStream();
		}
	
		RCODE FLMAPI openStream(
			IF_IStream *		pIStream,
			FLMUINT				uiBufferSize);
	
		RCODE FLMAPI read(
			void *				pvBuffer,
			FLMUINT				uiBytesToRead,
			FLMUINT *			puiBytesRead);
	
		RCODE FLMAPI closeStream( void);
	
		FINLINE FLMUINT64 FLMAPI totalSize( void)
		{
			if (!m_pIStream)
			{
				f_assert( 0);
				return( 0);
			}
	
			return( m_uiBytesAvail);
		}
	
		FINLINE FLMUINT64 FLMAPI remainingSize( void)
		{
			if( !m_pIStream)
			{
				f_assert( 0);
				return( 0);
			}
	
			return( m_uiBytesAvail - m_uiBufferOffset);
		}
	
		FINLINE RCODE FLMAPI positionTo(
			FLMUINT64		ui64Position)
		{
			if( !m_pIStream)
			{
				f_assert( 0);
				return( RC_SET( NE_FLM_ILLEGAL_OP));
			}
	
			if( ui64Position < m_uiBytesAvail)
			{
				m_uiBufferOffset = (FLMUINT)ui64Position;
			}
			else
			{
				m_uiBufferOffset = m_uiBytesAvail;
			}
	
			return( NE_FLM_OK);
		}
	
		FINLINE FLMUINT64 FLMAPI getCurrPosition( void)
		{
			if( !m_pIStream)
			{
				f_assert( 0);
				return( 0);
			}
	
			return( m_uiBufferOffset);
		}
	
	private:
	
		IF_IStream *			m_pIStream;
		FLMBYTE *				m_pucBuffer;
		FLMUINT					m_uiBufferSize;
		FLMUINT					m_uiBufferOffset;
		FLMUINT					m_uiBytesAvail;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_BufferedOStream : public IF_OStream
	{
	public:
	
		F_BufferedOStream()
		{
			m_pOStream = NULL;
			m_pucBuffer = NULL;
		}
	
		virtual ~F_BufferedOStream()
		{
			closeStream();
		}
	
		RCODE FLMAPI openStream(
			IF_OStream *	pOStream,
			FLMUINT			uiBufferSize);
	
		RCODE FLMAPI write(
			const void *	pvBuffer,
			FLMUINT			uiBytesToWrite,
			FLMUINT *		puiBytesWritten);
	
		RCODE FLMAPI closeStream( void);
	
		RCODE FLMAPI flush( void);
	
	private:
	
		IF_OStream *		m_pOStream;
		FLMBYTE *			m_pucBuffer;
		FLMUINT				m_uiBufferSize;
		FLMUINT				m_uiBufferOffset;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_FileOStream : public IF_OStream
	{
	public:
	
		F_FileOStream()
		{
			m_pFileHdl = NULL;
		}
	
		virtual ~F_FileOStream()
		{
			closeStream();
		}
	
		RCODE FLMAPI openStream(
			const char *	pszFilePath,
			FLMBOOL			bTruncateIfExists);
	
		RCODE FLMAPI write(
			const void *	pvBuffer,
			FLMUINT			uiBytesToWrite,
			FLMUINT *		puiBytesWritten);
	
		RCODE FLMAPI closeStream( void);
	
	private:
	
		IF_FileHdl *		m_pFileHdl;
		FLMUINT64			m_ui64FileOffset;
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_MultiFileIStream : public IF_IStream
	{
	public:
	
		F_MultiFileIStream()
		{
			m_pIStream = NULL;
			m_bOpen = FALSE;
		}
	
		virtual ~F_MultiFileIStream()
		{
			closeStream();
		}
	
		RCODE FLMAPI openStream(
			const char *	pszDirectory,
			const char *	pszBaseName);
	
		RCODE FLMAPI read(
			void *			pvBuffer,
			FLMUINT			uiBytesToRead,
			FLMUINT *		puiBytesRead);
	
		RCODE FLMAPI closeStream( void);
	
	private:
	
		RCODE rollToNextFile( void);
	
		IF_IStream *		m_pIStream;
		FLMBOOL				m_bOpen;
		FLMBOOL				m_bEndOfStream;
		FLMUINT				m_uiFileNum;
		FLMUINT64			m_ui64FileOffset;
		char 					m_szDirectory[ F_PATH_MAX_SIZE + 1];
		char	 				m_szBaseName[ F_PATH_MAX_SIZE + 1];
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_MultiFileOStream : public IF_OStream
	{
	public:
	
		F_MultiFileOStream()
		{
			m_pOStream = NULL;
			m_bOpen = FALSE;
		}
	
		virtual ~F_MultiFileOStream()
		{
			closeStream();
		}
	
		RCODE createStream(
			const char *	pszDirectory,
			const char *	pszBaseName,
			FLMUINT			uiMaxFileSize,
			FLMBOOL			bOkToOverwrite);
	
		RCODE FLMAPI write(
			const void *	pvBuffer,
			FLMUINT			uiBytesToWrite,
			FLMUINT *		puiBytesWritten);
	
		RCODE FLMAPI closeStream( void);
	
		RCODE processDirectory(
			const char *	pszDirectory,
			const char *	pszBaseName,
			FLMBOOL			bOkToDelete);
	
	private:
	
		RCODE rollToNextFile( void);
	
		IF_OStream *	m_pOStream;
		FLMBOOL			m_bOpen;
		FLMUINT			m_uiFileNum;
		FLMUINT64		m_ui64MaxFileSize;
		FLMUINT64		m_ui64FileOffset;
		char 				m_szDirectory[ F_PATH_MAX_SIZE + 1];
		char 				m_szBaseName[ F_PATH_MAX_SIZE + 1];
	};
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_CollIStream : public IF_CollIStream
	{
	public:
	
		F_CollIStream()
		{
			m_pIStream = NULL;
			m_uiLanguage = 0;
			m_bMayHaveWildCards = FALSE;
			m_bUnicodeStream = FALSE;
			m_uNextChar = 0;
		}
	
		virtual ~F_CollIStream()
		{
			if( m_pIStream)
			{
				m_pIStream->Release();
			}
		}
	
		RCODE FLMAPI openStream(
			IF_PosIStream *	pIStream,
			FLMBOOL				bUnicodeStream,
			FLMUINT				uiLanguage,
			FLMUINT				uiCompareRules,
			FLMBOOL				bMayHaveWildCards)
		{
			if( m_pIStream)
			{
				m_pIStream->Release();
			}
	
			m_pIStream = pIStream;
			m_pIStream->AddRef();
			m_uiLanguage = uiLanguage;
			m_uiCompareRules = uiCompareRules;
			m_bCaseSensitive = (uiCompareRules & FLM_COMP_CASE_INSENSITIVE)
									  ? FALSE
									  : TRUE;
			m_bMayHaveWildCards = bMayHaveWildCards;
			m_bUnicodeStream = bUnicodeStream;		
			m_ui64EndOfLeadingSpacesPos = 0;
			return( NE_FLM_OK);
		}
	
		RCODE FLMAPI closeStream( void)
		{
			if( m_pIStream)
			{
				m_pIStream->Release();
				m_pIStream = NULL;
			}
			
			return( NE_FLM_OK);
		}
	
		RCODE FLMAPI read(
			void *			pvBuffer,
			FLMUINT			uiBytesToRead,
			FLMUINT *		puiBytesRead)
		{
			RCODE		rc = NE_FLM_OK;
	
			if( RC_BAD( rc = m_pIStream->read( pvBuffer, 
				uiBytesToRead, puiBytesRead)))
			{
				goto Exit;
			}
	
		Exit:
	
			return( rc);
		}
	
		RCODE FLMAPI read(
			FLMBOOL			bAllowTwoIntoOne,
			FLMUNICODE *	puChar,
			FLMBOOL *		pbCharIsWild,
			FLMUINT16 *		pui16Col,
			FLMUINT16 *		pui16SubCol,
			FLMBYTE *		pucCase);
			
		FINLINE FLMUINT64 FLMAPI totalSize( void)
		{
			if( m_pIStream)
			{
				return( m_pIStream->totalSize());
			}
	
			return( 0);
		}
	
		FINLINE FLMUINT64 FLMAPI remainingSize( void)
		{
			if( m_pIStream)
			{
				return( m_pIStream->remainingSize());
			}
	
			return( 0);
		}
	
		FINLINE RCODE FLMAPI positionTo(
			FLMUINT64)
		{
			return( RC_SET_AND_ASSERT( NE_FLM_NOT_IMPLEMENTED));
		}
	
		FINLINE RCODE FLMAPI positionTo(
			F_CollStreamPos *	pPos)
		{
			
			// Should never be able to position back to before the
			// leading spaces.
			
			m_uNextChar = pPos->uNextChar;
			flmAssert( pPos->ui64Position >= m_ui64EndOfLeadingSpacesPos);
			return( m_pIStream->positionTo( pPos->ui64Position));
		}
	
		FINLINE FLMUINT64 FLMAPI getCurrPosition( void)
		{
			flmAssert( 0);
			return( 0);
		}
	
		void FLMAPI getCurrPosition(
			F_CollStreamPos *		pPos);
	
	private:
	
		FINLINE RCODE readCharFromStream(
			FLMUNICODE *		puChar)
		{
			RCODE		rc = NE_FLM_OK;
			
			if( m_bUnicodeStream)
			{
				if( RC_BAD( rc = m_pIStream->read( puChar, sizeof( FLMUNICODE), NULL)))
				{
					goto Exit;
				}
			}
			else
			{
				if( RC_BAD( rc = f_readUTF8CharAsUnicode( 
					m_pIStream, puChar)))
				{
					goto Exit;
				}
			}
			
		Exit:
		
			return( rc);
		}
			
		IF_PosIStream *	m_pIStream;
		FLMUINT				m_uiLanguage;
		FLMBOOL				m_bCaseSensitive;
		FLMUINT				m_uiCompareRules;
		FLMUINT64			m_ui64EndOfLeadingSpacesPos;
		FLMBOOL				m_bMayHaveWildCards;
		FLMBOOL				m_bUnicodeStream;
		FLMUNICODE			m_uNextChar;
	};

	/****************************************************************************
	Desc:	Decodes an ASCII base64 stream to binary
	****************************************************************************/
	class FLMEXP F_Base64DecoderIStream : public IF_IStream
	{
	public:
	
		F_Base64DecoderIStream()
		{
			m_pIStream = NULL;
			m_uiBufOffset = 0;
			m_uiAvailBytes = 0;
		}
	
		virtual ~F_Base64DecoderIStream()
		{
			closeStream();
		}
	
		RCODE FLMAPI openStream(
			IF_IStream *	pIStream);
		
		RCODE FLMAPI read(
			void *			pvBuffer,
			FLMUINT			uiBytesToRead,
			FLMUINT *		puiBytesRead);
			
		FINLINE RCODE FLMAPI closeStream( void)
		{
			RCODE		rc = NE_FLM_OK;
			
			if( m_pIStream)
			{
				if( m_pIStream->getRefCount() == 1)
				{
					rc = m_pIStream->closeStream();
				}
	
				m_pIStream->Release();
				m_pIStream = NULL;
			}
			
			m_uiAvailBytes = 0;
			m_uiBufOffset = 0;
			
			return( rc);
		}
		
	private:
	
		IF_IStream *		m_pIStream;
		FLMUINT				m_uiBufOffset;
		FLMUINT				m_uiAvailBytes;
		FLMBYTE				m_ucBuffer[ 8];
	};

	/****************************************************************************
	Desc:	Encodes a binary input stream into ASCII base64.
	****************************************************************************/
	class FLMEXP F_Base64EncoderIStream : public IF_IStream
	{
	public:
	
		F_Base64EncoderIStream()
		{
			m_pIStream = NULL;
		}
	
		virtual ~F_Base64EncoderIStream()
		{
			closeStream();
		}
	
		RCODE FLMAPI openStream(
			IF_IStream *	pIStream,
			FLMBOOL			bLineBreaks);
		
		RCODE FLMAPI read(
			void *			pvBuffer,
			FLMUINT			uiBytesToRead,
			FLMUINT *		puiBytesRead);
	
		FINLINE RCODE FLMAPI closeStream( void)
		{
			RCODE		rc = NE_FLM_OK;
			
			if( m_pIStream)
			{
				if( m_pIStream->getRefCount() == 1)
				{
					rc = m_pIStream->closeStream();
				}
	
				m_pIStream->Release();
				m_pIStream = NULL;
			}
			
			return( rc);
		}
		
	private:
	
		IF_IStream *		m_pIStream;
		FLMBOOL				m_bInputExhausted;
		FLMBOOL				m_bLineBreaks;
		FLMBOOL				m_bPriorLineEnd;
		FLMUINT				m_uiBase64Count;
		FLMUINT				m_uiBufOffset;
		FLMUINT				m_uiAvailBytes;
		FLMBYTE 				m_ucBuffer[ 8];
	};

	/****************************************************************************
	Desc:
	****************************************************************************/
	typedef struct LZWODictItem
	{
		LZWODictItem *	pNext;
		FLMUINT16		ui16Code;
		FLMUINT16		ui16ParentCode;
		FLMBYTE			ucChar;
	} LZWODictItem;
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_CompressingOStream : public IF_OStream
	{
	public:
	
		F_CompressingOStream()
		{
			m_pool.poolInit( 64 * 1024);
			m_pOStream = NULL;
			m_ppHashTbl = NULL;
		}
	
		virtual ~F_CompressingOStream()
		{
			closeStream();
		}
	
		RCODE FLMAPI openStream(
			IF_OStream *	pOStream);
	
		RCODE FLMAPI write(
			const void *	pvBuffer,
			FLMUINT			uiBytesToWrite,
			FLMUINT *		puiBytesWritten);
	
		RCODE FLMAPI closeStream( void);
	
	private:
	
		FINLINE FLMUINT getHashBucket(
			FLMUINT16	ui16CurrentCode,
			FLMBYTE		ucChar)
		{
			return( ((((FLMUINT)ui16CurrentCode) << 8) | 
				((FLMUINT)ucChar)) % m_uiHashTblSize);
		}
	
		LZWODictItem * findDictEntry( 
			FLMUINT16		ui16CurrentCode,
			FLMBYTE			ucChar);
	
		F_Pool				m_pool;
		IF_OStream *		m_pOStream;
		LZWODictItem **	m_ppHashTbl;
		FLMUINT				m_uiHashTblSize;
		FLMUINT				m_uiLastRatio;
		FLMUINT				m_uiBestRatio;
		FLMUINT				m_uiCurrentBytesIn;
		FLMUINT				m_uiTotalBytesIn;
		FLMUINT				m_uiCurrentBytesOut;
		FLMUINT				m_uiTotalBytesOut;
		FLMBOOL				m_bStopCompression;
		FLMUINT16			m_ui16CurrentCode;
		FLMUINT16			m_ui16FreeCode;
	};
	
	typedef struct LZWIDictItem
	{
		LZWODictItem *	pNext;
		FLMUINT16		ui16ParentCode;
		FLMBYTE			ucChar;
	} LZWIDictItem;
	
	/****************************************************************************
	Desc:
	****************************************************************************/
	class FLMEXP F_UncompressingIStream : public IF_IStream
	{
	public:
	
		F_UncompressingIStream()
		{
			m_pIStream = NULL;
			m_pDict = NULL;
			m_pucDecodeBuffer = NULL;
		}
	
		virtual ~F_UncompressingIStream()
		{
			closeStream();
		}
	
		RCODE FLMAPI openStream(
			IF_IStream *	pIStream);
	
		RCODE FLMAPI read(
			void *			pvBuffer,
			FLMUINT			uiBytesToRead,
			FLMUINT *		puiBytesRead);
	
		RCODE FLMAPI closeStream( void);
		
	private:
	
		RCODE readCode(
			FLMUINT16 *		pui16Code);
	
		RCODE decodeToBuffer(
			FLMUINT16		ui16Code);
	
		IF_IStream *		m_pIStream;
		LZWIDictItem *		m_pDict;
		FLMBYTE *			m_pucDecodeBuffer;
		FLMUINT				m_uiDecodeBufferSize;
		FLMUINT				m_uiDecodeBufferOffset;
		FLMUINT16			m_ui16FreeCode;
		FLMUINT16			m_ui16LastCode;
		FLMBOOL				m_bStopCompression;
		FLMBOOL				m_bEndOfStream;
	};

	/***************************************************************************
	Desc: Dynamic result sets
	***************************************************************************/

	typedef int (* F_DYNSET_COMPARE_FUNC)(
		void *	pvData1,
		void *	pvData2,
		void *	pvUserData);

	typedef enum
	{
		ACCESS_HASH,
		ACCESS_BTREE_LEAF,
		ACCESS_BTREE_ROOT,
		ACCESS_BTREE_NON_LEAF
	} eDynRSetBlkTypes;

	class	F_FixedBlk : public F_Object
	{
	public:

		F_FixedBlk();

		virtual ~F_FixedBlk()
		{
		}

		eDynRSetBlkTypes blkType()
		{
			return m_eBlkType;
		}

		virtual RCODE getCurrent(
			void *	pvEntryBuffer) = 0;

		virtual RCODE getFirst(
			void *	pvEntryBuffer) = 0;

		virtual RCODE getLast(
			void *	pvEntryBuffer) = 0;

		virtual RCODE getNext(
			void *	pvEntryBuffer) = 0;

		virtual FLMUINT getTotalEntries() = 0;

		virtual RCODE insert(
			void *	pvEntry) = 0;

		FINLINE FLMBOOL isDirty( void)
		{
			return( m_bDirty);
		}

		virtual RCODE search(
			void *	pvEntry,
			void *	pvFoundEntry = NULL) = 0;

		void setCompareFunc(
			F_DYNSET_COMPARE_FUNC	fnCompare,
			void *						pvUserData)
		{
			m_fnCompare = fnCompare;
			m_pvUserData = pvUserData;
		}

	protected:

		F_DYNSET_COMPARE_FUNC	m_fnCompare;
		void *						m_pvUserData;
		eDynRSetBlkTypes			m_eBlkType;
		FLMUINT						m_uiEntrySize;
		FLMUINT						m_uiNumSlots;
		FLMUINT						m_uiPosition;
		FLMBOOL						m_bDirty;
		FLMBYTE *					m_pucBlkBuf;
	};

	class FLMEXP F_DynSearchSet : public F_Object
	{

	public:

		F_DynSearchSet()
		{
			m_fnCompare = NULL;
			m_pvUserData = NULL;
			m_uiEntrySize = 0;
			m_pAccess = NULL;
		}

		virtual ~F_DynSearchSet()
		{
			if( m_pAccess)
			{
				m_pAccess->Release();
			}
		}

		RCODE FLMAPI setup(
			char *						pszTmpDir,
			FLMUINT						uiEntrySize);

		FINLINE void FLMAPI setCompareFunc(
			F_DYNSET_COMPARE_FUNC	fnCompare,
			void *						pvUserData)
		{
			m_fnCompare = fnCompare;
			m_pvUserData = pvUserData;
			m_pAccess->setCompareFunc( fnCompare, pvUserData);
		}

		RCODE FLMAPI addEntry(
			void *						pvEntry);

		FINLINE RCODE FLMAPI findMatch(
			void *						pvMatchEntry,
			void *						pvFoundEntry)
		{
			return m_pAccess->search( pvMatchEntry, pvFoundEntry);
		}

		FINLINE FLMUINT FLMAPI getEntrySize( void)
		{
			return m_uiEntrySize;
		}

		FINLINE FLMUINT FLMAPI getTotalEntries( void)
		{
			return( m_pAccess->getTotalEntries());
		}

	private:

		F_DYNSET_COMPARE_FUNC	m_fnCompare;
		void *						m_pvUserData;
		FLMUINT						m_uiEntrySize;
		F_FixedBlk *				m_pAccess;
		char							m_szFileName[ F_PATH_MAX_SIZE];
	};

	/***************************************************************************
	Desc: Hash tables
	***************************************************************************/
	
	typedef struct
	{
		void *		pFirstInBucket;
		FLMUINT		uiHashValue;
	} F_BUCKET;
	
	RCODE FLMAPI f_allocHashTable(
		FLMUINT					uiHashTblSize,
		F_BUCKET **				ppHashTblRV);
		
	FLMUINT FLMAPI f_strHashBucket(
		char *					pszStr,
		F_BUCKET *				pHashTbl,
		FLMUINT					uiNumBuckets);
		
	FLMUINT FLMAPI f_binHashBucket(
		void *					pBuf,
		FLMUINT					uiBufLen,
		F_BUCKET *				pHashTbl,
		FLMUINT					uiNumBuckets);
	
	/***************************************************************************
	Desc:
	***************************************************************************/
	class F_HashObject : virtual public F_Object
	{
	public:
	
		#define F_INVALID_HASH_BUCKET				(~((FLMUINT)0))
	
		F_HashObject()
		{
			m_pNextInBucket = NULL;
			m_pPrevInBucket = NULL;
			m_pNextInGlobal = NULL;
			m_pPrevInGlobal = NULL;
			m_uiHashBucket = F_INVALID_HASH_BUCKET;
			m_ui32KeyCRC = 0;
			m_uiTimeAdded = 0;
		}
	
		virtual ~F_HashObject()
		{
			flmAssert( !m_pNextInBucket);
			flmAssert( !m_pPrevInBucket);
			flmAssert( !m_pNextInGlobal);
			flmAssert( !m_pPrevInGlobal);
			flmAssert( !getRefCount());
		}
	
		virtual const void * FLMAPI getKey( void) = 0;
		
		virtual FLMUINT FLMAPI getKeyLength( void) = 0;
		
		FINLINE FLMUINT FLMAPI getKeyCRC( void)
		{
			return( m_ui32KeyCRC);
		}
	
		FINLINE FLMUINT FLMAPI getHashBucket( void)
		{
			return( m_uiHashBucket);
		}
	
		FINLINE F_HashObject * FLMAPI getNextInGlobal( void)
		{
			return( m_pNextInGlobal);
		}
		
		FINLINE F_HashObject * FLMAPI getNextInBucket( void)
		{
			return( m_pNextInBucket);
		}
		
		virtual FLMUINT FLMAPI getObjectType( void) = 0;
	
	protected:
	
		void setHashBucket(
			FLMUINT		uiHashBucket)
		{
			m_uiHashBucket = uiHashBucket;
		}
	
		F_HashObject *		m_pNextInBucket;
		F_HashObject *		m_pPrevInBucket;
		F_HashObject *		m_pNextInGlobal;
		F_HashObject *		m_pPrevInGlobal;
		FLMUINT				m_uiHashBucket;
		FLMUINT				m_uiTimeAdded;
		FLMUINT32			m_ui32KeyCRC;
	
	friend class F_HashTable;
	};

	/***************************************************************************
	Desc: Hash tables
	***************************************************************************/
	class F_HashTable : public F_Object
	{
	public:
	
		F_HashTable();
	
		virtual ~F_HashTable();
	
		RCODE FLMAPI setupHashTable(
			FLMBOOL				bMultithreaded,
			FLMUINT				uiNumBuckets,
			FLMUINT				uiMaxObjects);
	
		RCODE FLMAPI addObject(
			F_HashObject *		pObject,
			FLMBOOL				bAllowDuplicates = FALSE);
	
		RCODE FLMAPI getNextObjectInGlobal(
			F_HashObject **	ppObject);
	
		RCODE FLMAPI getNextObjectInBucket(
			F_HashObject **	ppObject);
		
		RCODE FLMAPI getObject(
			const void *		pvKey,
			FLMUINT				uiKeyLen,
			F_HashObject **	ppObject,
			FLMBOOL				bRemove = FALSE);
	
		RCODE FLMAPI removeObject(
			void *				pvKey,
			FLMUINT				uiKeyLen);
	
		RCODE FLMAPI removeObject(
			F_HashObject *		pObject);

		void FLMAPI removeAllObjects( void);
		
		void FLMAPI removeAgedObjects(
			FLMUINT				uiMaxAge);
			
		FLMUINT FLMAPI getMaxObjects( void);
			
		RCODE FLMAPI setMaxObjects(
			FLMUINT				uiMaxObjects);
	
	private:
	
		FLMUINT getHashBucket(
			const void *		pvKey,
			FLMUINT				uiLen,
			FLMUINT32 *			pui32KeyCRC = NULL);
	
		void linkObject(
			F_HashObject *		pObject,
			FLMUINT				uiBucket);
	
		void unlinkObject(
			F_HashObject *		pObject);
	
		RCODE findObject(
			const void *		pvKey,
			FLMUINT				uiKeyLen,
			F_HashObject **	ppObject);
	
		F_MUTEX 				m_hMutex;
		F_HashObject *		m_pMRUObject;
		F_HashObject *		m_pLRUObject;
		F_HashObject **	m_ppHashTable;
		FLMUINT				m_uiBuckets;
		FLMUINT				m_uiObjects;
		FLMUINT				m_uiMaxObjects;
	};

	/****************************************************************************
	Desc: Process ID Functions
	****************************************************************************/

	FLMUINT f_getpid( void);

	#ifdef FLM_PACK_STRUCTS
		#pragma pack(pop)
	#endif

#endif // FTK_H
