@echo off
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsx86_amd64.bat"

if new==%1 if exist Makefile nmake /nologo clean
if new==%1 del /q build\helper.exe
if not exist build\helper.exe cl /nologo /W4 /EHsc /O2 /MD /std:c++20 helper.cpp /Foobj\helper.obj /Febuild\helper.exe
build\helper.exe assets

nmake /nologo

endlocal
