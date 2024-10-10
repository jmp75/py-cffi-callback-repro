import os
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
    if not os.path.exists(os.path.join(dir_path, fname)):
        # fallback on AppVeyor output location
        dir_path = pkg_dir / "test_native_library" / "build" / "x64" / "Debug"
else:
    dir_path = pkg_dir / "test_native_library" / "build"

native_lib_path = dir_path / fname
assert native_lib_path.exists()

ut_ffi = FFI()

ut_ffi.cdef("extern void register_exception_callback(const void* callback);")
ut_ffi.cdef("extern void trigger_callback();")

ut_dll = ut_ffi.dlopen(str(native_lib_path), 1)  # Lazy loading

_message_from_c: str | bytes = "<none>"


@ut_ffi.callback("void(char *)")
def called_back_from_c(some_string: str):
    """
    This function is called when uchronia raises an exception.
    It sets the global variable ``_exception_txt_raised_uchronia``

    :param cdata exception_string: Exception string.
    """
    global _message_from_c
    _message_from_c = ut_ffi.string(some_string)


# https://github.com/csiro-hydroinformatics/uchronia-time-series/issues/1
print("before registration")
ut_dll.register_exception_callback(called_back_from_c)
print("after registration")
ut_dll.trigger_callback()
print("after triggering callback")
assert _message_from_c != "<none>"
print(str(_message_from_c))
