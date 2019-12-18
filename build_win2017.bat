@echo off

pushd %~dp0

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

REM Variable used in this script - name is arbitrary
set QTDIR=C:/Qt/Qt5.12.3/5.12.3/msvc2017_64

mkdir build

set PATH=%PATH%;"C:\Program Files\CMake\bin";%QTDIR%\bin
set VTK_DIR=E:/code/bin/VTK

cmake -H%~dp0 -B%~dp0\build -G "Visual Studio 15 2017 Win64"

REM Create solution
cd %~dp0\build

REM Build solution
msbuild QtVtk.sln /p:Configuration=Release

REM  /verbosity:diagnostic
REM cd ..

REM Go to output directory
REM cd %~dp0\build\gui\Release

REM Deploy all necessary DLL's to output directory.
REM set CURRENTDRIVE=%CD:~0,2%
REM %QTDIR%\bin\qtenv2.bat
REM cd /D %CURRENTDRIVE%%~dp0\build\gui\Release
REM %QTDIR%\bin\windeployqt.exe SofusUI.exe

REM cd %~dp0
