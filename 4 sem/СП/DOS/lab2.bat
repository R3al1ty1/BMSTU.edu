REM CMD.EXE E:/ON
REM �⪫�祭�� �뢮�� �㦥���� ������
@echo OFF
set par1=%1
set par2=%2
:menu
cls
echo.
echo 1. �஢�ઠ par2
echo 2. ��ࠢ��
echo 3. �������� 䠩��
echo 4. �뢮� par1, par2
echo 5. ��ࠢ�� �� MKDIR
echo 6. ��室

REM ������ ������� �������
CHOICE /C 123456 /M "������ ����� �㭪� ����"
REM ��⠭���� ��६����� met ࠢ��� p+���������� ���祭��
set met=p%errorlevel%

REM ��⢫���� � �������� if goto
if %met%==p1 goto p1
if %met%==p2 goto p2
if %met%==p3 goto p3
if %met%==p4 goto p4
if %met%==p5 goto p5
if %met%==p6 goto p6

REM goto %met%

:p1
if defined par2 (
goto show
) else (
echo par2 ���⮩
)
pause
goto menu

:p2
echo ��ࠢ��:
echo.
call My_help.bat
pause
goto menu

:p3
echo %0%
pause
goto menu

:p4
echo par1=%par1%
echo par2=%par2%
pause
goto menu

:p5
call MKDIR /?
pause
goto menu

:p6
REM ���⪠ �࠭� � ����ᨬ��� �� ��ࠬ��� %1 (��/���)
ECHO �����襭�� �ணࠬ��
pause
if defined par1 (
if %par1%==�� cls
if %par1%==�� cls
)
EXIT /B

:show
if %par2%==My_help.bat (
call %par2%
) else (
echo %par2% �� 䠩� �ࠢ��
)
pause 
goto menu