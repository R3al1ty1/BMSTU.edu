REM CMD.EXE E:/ON
REM Отключение вывода служебных команд
@echo OFF
set par1=%1
set par2=%2
set par3=%3
set par4=%4
set par5=%5
:menu
cls
echo.
echo 1. Проверка par2
echo 2. Справка
echo 3. Название файла
echo 4. Вывод par1, par2
echo 5. Справка по заданным параметрам
echo 6. Выход

REM ЗАПРОС НАЖАТИЯ КЛАВИШИ
CHOICE /C 123456 /M "Введите номер пункта меню"
REM установка переменной met равной p+введенному значению
set met=p%errorlevel%

REM ветвление и навигация if goto
goto %met%

REM goto %met%

:p1
if defined par2 (
goto show
) else (
echo par2 пустой
)
pause
goto menu

:p2
echo Справка:
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
REM очистка экрана в зависимости от параметра %1 (Да/Нет)
ECHO Завершение программы
pause
if defined par1 (
if %par1%==Да cls
if %par1%==да cls
)
EXIT /B

:show
if %par2%==My_help.bat (
call %2
) else (
echo %2 не файл справки
)
pause 
goto menu
