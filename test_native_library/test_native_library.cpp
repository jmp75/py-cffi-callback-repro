// test_native_library.cpp : Defines the exported functions for the DLL application.
//

#include "test_native_library.h"
#include "error_reporting.h"

static moirai::error_handling::error_log error_handler;

void register_exception_callback(const void* callback)
{
    // diagnose https://github.com/csiro-hydroinformatics/moirai/issues/1
    if (callback == nullptr) // Allow the deregistration, at least for unit test purposes.
        error_handler.register_exception_callback(callback);
    else if (!error_handler.has_callback_registered())
        error_handler.register_exception_callback(callback);
}

int has_callback_registered()
{
	if (error_handler.has_callback_registered())
		return 1;
	return 0;
}

void trigger_callback()
{
	if (error_handler.has_callback_registered())
	{
		auto e = std::logic_error("Hello from the C library!");
		error_handler.handle_std_exception(e);
	}
}


