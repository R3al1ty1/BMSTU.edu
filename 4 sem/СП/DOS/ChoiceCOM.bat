@echo OFF
:menu
cls
echo A. One
echo B. Two
echo C. Exit
REM ������ ������� �������
CHOICE /C:123 ������ ����� �㭪� ����
IF ERRORLEVEL=1 SET met=1
IF ERRORLEVEL=2 SET met=2
IF ERRORLEVEL=3 SET met=3

goto %met%
:1
echo a
pause
goto menu
:2
echo b
pause
goto menu
:3
echo c
pause
goto fin
:fin
ECHO �����襭�� �ணࠬ��
