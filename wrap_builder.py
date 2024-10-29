from cffi import FFI

ffibuilder = FFI()

ffibuilder.cdef("""
    extern "Python" void my_callback(char*);

    void library_function(void(*callback)(char*));
""")

ffibuilder.set_source(
    "_my_callback",
    r"""
    //#include <some_library.h>
""",
)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
