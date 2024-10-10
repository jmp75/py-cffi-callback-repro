// test_native_library.cpp : Defines the exported functions for the DLL application.
//

#include "test_native_library.h"

// Cheap, cheerful and self-contained registration of a callback.
// A safer way to handle callback function registration is in 
// https://github.com/csiro-hydroinformatics/moirai/blob/master/src/reference_handle.cpp
typedef void(*exception_callback)(const char * str);
exception_callback ptr_callback = nullptr;

void register_exception_callback(const void* callback)
{
	if(ptr_callback == nullptr) // Allow the deregistration, at least for unit test purposes.
		ptr_callback = (exception_callback)callback;
}

void trigger_callback()
{
	if (ptr_callback != nullptr)
	{
		(*ptr_callback)("Hello from the C library!");
	}
}


