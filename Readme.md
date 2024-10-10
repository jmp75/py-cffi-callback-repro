# py-cffi-callback-repro

Repro code for # https://github.com/csiro-hydroinformatics/uchronia-time-series/issues/1

Status:

* 2024-10-10: The issue is not reproducible on Windows server 2022, compiled with Visual Studio 17 2022. This is a surprise. The only difference I can think is the version of the C++ compiler. The faulty stack was built via ([via AzureDevops image windows-2019](https://github.com/csiro-hydroinformatics/hydro-forecast-windows-pipeline/blob/e2e19c403dc971c7135eb691827d2b892996259d/azure-pipelines.yml#L35), [Windows Server 2019 with Visual Studio 2019](https://learn.microsoft.com/en-us/azure/devops/pipelines/agents/hosted?view=azure-devops&tabs=yaml)).

## Related work

This is a repro adapted from unit tests in https://github.com/csiro-hydroinformatics/pyrefcount

## Steps

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

### Windows

* Installing msbuild tools https://visualstudio.microsoft.com/visual-cpp-build-tools/
* cmake https://cmake.org/download/

starting a developer command prompt :

```bat
where msbuild
set user_name=xxxyyy
cd C:\Users\%user_name%\
: a virtual environment with python 3.11.9 and at least cffi
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