import sys

from cffi import FFI

# from refcount.putils import library_short_filename


def library_short_filename(fname_noext):
    if sys.platform == "win32":
        return f"{fname_noext}.dll"
    # skip macos
    return f"lib{fname_noext}.so"


from pathlib import Path

fname = library_short_filename("test_native_library")

pkg_dir = Path(".")

if sys.platform == "win32":
    dir_path = pkg_dir / "test_native_library" / "build" / "Debug"
else:
    dir_path = pkg_dir / "test_native_library" / "build"

# C:\src\py-cffi-callback-repro\test_native_library\x64\Debug
# if using the solution and vs2022
#  dir_path = pkg_dir / "test_native_library" / "x64" / "Debug"
native_lib_path = dir_path / fname
if not native_lib_path.exists():
    raise FileNotFoundError(native_lib_path)


ut_ffi = FFI()

ut_ffi.cdef("extern void register_exception_callback(const void* callback);")
ut_ffi.cdef("extern void trigger_callback();")
ut_ffi.cdef("extern int has_callback_registered();")


# import os
# flags = int(os.environ.get("RT_CODE", ut_ffi.RTLD_LAZY))
flags = ut_ffi.RTLD_LAZY
# ut_dll = ut_ffi.dlopen(str(native_lib_path), flags)  # Lazy loading

_message_from_c: str | bytes = "<none>"


# using const char * does not make sense in C99 I think and in any case the issue is the same
# @ut_ffi.callback("void(const char *)")
@ut_ffi.callback("void(char *)")
def called_back_from_c(some_string: str):
    """
    This function is called when uchronia raises an exception.
    It sets the global variable ``_exception_txt_raised_uchronia``

    :param cdata exception_string: Exception string.
    """
    global _message_from_c
    _message_from_c = ut_ffi.string(some_string)


print("before registration")
# According to https://github.com/csiro-hydroinformatics/uchronia-time-series/issues/1
# `register_exception_callback` is where it should crash,
# but in this example we seem to go to up the triggering step.
ut_dll.register_exception_callback(called_back_from_c)
print("after registration")

print("before has_callback_registered")
ut_dll.has_callback_registered()
print("after has_callback_registered")

print("before triggering callback")
ut_dll.trigger_callback()
print("after triggering callback")

assert _message_from_c != "<none>"
print(str(_message_from_c))
