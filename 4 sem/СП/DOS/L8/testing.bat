REM CMD.EXE E:/ON
REM �⪫�祭�� �뢮�� �㦥���� ������
@echo OFF
set par1=%1
set par2=%2
set par3=%3
set par4=%4
set par5=%5
:menu
cls
echo.
echo 1. �஢�ઠ par2
echo 2. ��ࠢ��
echo 3. �������� 䠩��
echo 4. �뢮� par1, par2
echo 5. ��ࠢ�� �� ������� ��ࠬ��ࠬ
echo 6. ��室

REM ������ ������� �������
CHOICE /C 123456 /M "������ ����� �㭪� ����"
REM ��⠭���� ��६����� met ࠢ��� p+���������� ���祭��
set met=p%errorlevel%

REM ��⢫���� � �������� if goto
goto %met%

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
echo par1=%1
echo par2=%2
pause
goto menu

:p5
%3 /?
pause
shift
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
call %2
) else (
echo %2 �� 䠩� �ࠢ��
)
pause 
goto menu
