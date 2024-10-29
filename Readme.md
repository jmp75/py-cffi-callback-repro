# py-cffi-callback-repro

Repro code for # https://github.com/csiro-hydroinformatics/uchronia-time-series/issues/1. 

Will be used in an issue at python-cffi on github

## Related work

This is a repro adapted from unit tests in https://github.com/csiro-hydroinformatics/pyrefcount

## Steps

Starting with Windows since this is where the issue occurs.

### Windows

Install prerequisites

* Installing msbuild tools https://visualstudio.microsoft.com/visual-cpp-build-tools/
* cmake from https://cmake.org/download/
* Install a python virtual environment  e.g. with windows 3.11

start a VS 2022 developer command prompt from the windows start menu.

```bat
where msbuild
set user_name=xxxyyy
cd C:\Users\%user_name%\
: a virtual environment with python 3.11.9 and at least cffi; see annex section
.\.venv\hydrofc\Scripts\activate

cd c:\src\py-cffi-callback-repro\test_native_library\
:: rm -rf CMakeFiles/ Makefile CMakeCache.txt cmake_install.cmake
cmake -DCMAKE_BUILD_TYPE=DEBUG -Bbuild . -G"Visual Studio 17 2022" -DBUILD_SHARED_LIBS:BOOL=ON 
cmake --build build
```

```bat
cd c:\src\py-cffi-callback-repro
python ./native_handle.py 
```

if you have in the environment `cffi==1.17.1`, a crash occurs; last std output is:

```text
before registration
after registration
<crashes>
```

With  `pip install cffi==1.16` however:

`python ./native_handle.py`:

```text
before registration
after registration
after triggering callback
b'Hello from the C library!'
```

### Linux

To compile the native library:

```sh
cd $HOME/src/py-cffi-callback-repro/test_native_library
# rm -rf CMakeFiles/ Makefile CMakeCache.txt cmake_install.cmake
cmake -DCMAKE_BUILD_TYPE=DEBUG -Bbuild .
cmake --build build
```

```sh
cd $HOME/src/py-cffi-callback-repro
python ./native_handle.py 
```

## Appendix

Steps taken to repro my colleague's behavior.

### Windows

Giving a try to the installation via powershell: https://github.com/pyenv-win/pyenv-win

restart a new PS or cmd

setting python 3.11.9 globally

```bat
pyenv --version
pyenv install -l
pyenv install 3.11.9
pyenv global 3.11.9

cd C:\Users\%user_name%\
mkdir .venv
cd .venv
python -m venv hydrofc

.\hydrofc\Scripts\activate
pip install jupyterlab

python -m ipykernel install --user --name hydrofc --display-name "HFC"

cd C:\Users\%user_name%\AppData\Local\Programs\SF\python
pip install refcount-1.2.2-py2.py3-none-any.whl
pip install cinterop-0.14.0-py2.py3-none-any.whl
pip install uchronia-2.4.1-py2.py3-none-any.whl
pip install swift2-2.4.8-py2.py3-none-any.whl
pip install fogss-2.4.2-py2.py3-none-any.whl
```

```py
import uchronia #Boom
```

### Observations

setting LIBRARY_PATH to c:\local\lib and `import uchronia` from the cmd prompt, this time around I do get a prompt to debug and VStudio shows the exception:

Unhandled exception at 0x00000000000AB160 in python.exe: 0xC0000005: Access violation executing location 0x00000000000AB160.
