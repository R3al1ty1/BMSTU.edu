MYCODE SEGMENT 'CODE'
ASSUME CS:MYCODE
	
sym DB 'A'
hextable DB '0123456789ABCDEF'

START:
; Загрузка сегментного регистра данных DS
    PUSH CS
    POP  DS

	CALL CLRSCR
	
	MAIN:
	; Ввод символа с клавиатуры: entry ah=01h return al=char read
	; т.е. настраиваем ah на ввод символа, а записывается он сразу в al?
	MOV ah, 08H;перенос значения из источника в приемник
    INT 21H
	cmp al, '*' ;сравнивает: равно ли ввденное значение звездочке
	je ext ;перемещение в функцию ext
    MOV sym, al
	call putnl ;новая строчка линия
	CALL CLRSCR
	MOV dl, 10
	call putch
	call putnl
	int 21h
	
	; Начальные условия цикла
	MOV CX , 20 ; Число циклов в CX
	CYCLE:
		mov dl, sym
		call putch
		call putdash
		call puthex
		;call putnl
		add sym, 1
	INC AL ;прибавляет 1 к операнду
	LOOP CYCLE

	; Ввод * - запрос на завершение программы
	mov ah, 01h
	int 21h
	cmp al, '*'
	call putnl
	je ext ; jump equal
	jmp main ; команда безусловного перехода в main

	; Выход из программы
	EXT PROC
		MOV AL, 5 ;errorlevel 5
		MOV AH, 4CH
		INT 21H
		ret ;возврат из ближней процедуры
	EXT ENDP
	 
	PUTCH PROC
		MOV AH, 02H
		INT 21H
		RET
	PUTCH ENDP

	PUTDASH PROC
		MOV DL, ' '
		CALL PUTCH
		MOV DL, '-'
		CALL PUTCH
		MOV DL, ' '
		CALL PUTCH
		RET
	PUTDASH ENDP

	PUTHEX PROC
		LEA BX, HEXTABLE ;загружаем адрес hex-таблицы в DS:BX, смещение, работает как оффсет				
		
		;ASCII m: 6D(hex) = 0110 1101(bin)
		;
		;SHR 4:
		; 0: 0110 1101|
		; 1: x0110 110|1
		; 2: xx0110 11|01
		; 3: xxx0110 1|101
		; 4: xxxx 0110|1101 --> 0110(bin) = 6(hex)
		;
		;AND AL(=m) x 0FH:
		; 0110 1101
		;x
		; 0000 1111 
		;----------
		; 0000 1101 = 1101(bin) = D(hex)
		
		;первый символ
		MOV AL, sym
		SHR AL, 4 ; логический сдвиг вправо на 4
		;берет из таблицы (в памяти по адресу DS:BX -- HEXTABLE)
		;элемент по адресу DS:[BX+AL] и помещает его в AL
		XLAT
		mov dl, al
		call putch
		
		;второй символ
		mov al, sym
		AND AL, 0FH ; логическое И между AL и 0FH(=0000 1111)
		xlat
		mov dl, al
		call putch
		
		mov dl, 'h'
		call putch
	PUTHEX ENDP

	PUTNL PROC
		mov dl, 0ah
		call putch
		ret
	PUTNL ENDP

	CLRSCR PROC
		mov al, 2
		int 10h
		ret
	CLRSCR ENDP
	
MYCODE ENDS
END START