# py-cffi-callback-repro

This is a repro adapted from unit tests in https://github.com/csiro-hydroinformatics/pyrefcount

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

## Windows

msbuild tools
git
cmake

developer command prompt :

```bat
where msbuild
set user_name=xxxyyy
cd C:\Users\%user_name%\
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