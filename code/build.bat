call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"  x86_amd64

@echo off
if not exist ..\build mkdir ..\build
pushd ..\build
del *.pbd > NUL 2> 2
echo WAITING FOR PBD > lock.tmp

pushd ..\build
cl -nologo -Zi -FC ..\code\win32_plat.c /link user32.lib gdi32.lib -incremental:no -opt:ref /OUT:Vuori.exe

del lock.tmp
del *.obj

popd