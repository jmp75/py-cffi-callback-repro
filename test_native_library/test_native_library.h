/**
 * \file	test_native_library.h
 *
 * \brief	A C API to test and document how one can use dynamic interop from .NET.
 * 			This test library has two concepts, a dog and its owner. Both have a (simplistic) mechanism for 
 * 			reference counting within C API, something you might encounter in real situations, 
 * 			in which case your .NET wrapper may use these instead of doing it at the .NET level.
 */

#pragma once

#ifdef _WIN32
  #define STRDUP _strdup
#else
  #define STRDUP strdup
#endif

// Using patterns in https://msdn.microsoft.com/en-us/library/as6wyhwt(v=vs.100).aspx to mark 
// C interop function as being exported or imported, something necessary with MS cpp tooling.
#ifdef _WIN32
#ifdef USING_TESTLIB_CORE
#define TESTLIB_CORE_DLL_LIB __declspec(dllimport)
#else
#define TESTLIB_CORE_DLL_LIB __declspec(dllexport)
// To prevent warnings such as:
// Warning	C4251	'blah::MyClass' : class 'std::basic_string<char,std::char_traits<char>,std::allocator<char>>' needs to have dll - interface to be used by clients of class 'something'
#pragma warning (disable : 4251)
#endif
#else
#define TESTLIB_CORE_DLL_LIB // nothing
#endif

#define TESTLIB_API  TESTLIB_CORE_DLL_LIB 

#ifdef USING_TESTLIB_CORE
#else
#endif

#ifdef __cplusplus
extern "C" {
#endif

	TESTLIB_API void register_exception_callback(const void* callback);
	TESTLIB_API void trigger_callback();
  TESTLIB_API int has_callback_registered();

#ifdef __cplusplus
}
#endif
