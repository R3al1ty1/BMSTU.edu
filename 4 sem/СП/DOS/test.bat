echo off
set par1=%1
set par2=%2
:menu
cls
echo 1. FAQ
echo 2. Who is the programm?
echo 3. See the first param
echo 4. Absolute FAQ (my_help file)
echo 5. Exit
choice /C:12345 /M "ENTER: "
Set met=p%ERRORLEVEL%
goto %met%

REM Variable parameters use

:p1
if defined par2 (
call %2
) else (
goto nofile
)
if ERRORLEVEL 0 (
echo printed successfuly
) else (
echo failed to print
)
pause
goto menu

:p2
echo I am %0
pause
goto menu

:p3
if defined par1 echo Will the screen be cleaned after closing? -%par1%
pause
goto menu

:p4
call my_help.bat
pause
goto menu

:p5
echo Closing
goto fin
pause

:p
echo Choice failed
goto menu

:nofile
echo file does not exist!
pause
goto menu

REM fin is final

:fin
echo %par1%
echo %par2%
pause
if Yes==%par1% cls
if yes==%par1% cls
ECHO End