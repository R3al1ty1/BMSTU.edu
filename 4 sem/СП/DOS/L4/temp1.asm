MYCODE SEGMENT 'CODE'
    ASSUME CS:MYCODE
sym DB 'A'
hextable DB '0123456789ABCDEF'
START:
; Загрузка сегментного регистра данных DS
     PUSH CS
     POP  DS

	 CALL CLRSCR
	; Начальные условия цикла
	MOV CX , 20 ; Число циклов в CX
	CYCLE:
		mov dl, sym
		call putch
		call putdash
		call puthex
		;call putnl
		add sym, 1
	INC AL
	LOOP CYCLE

	 
; Выход из программы
     MOV AL, 5 ;errorlevel 5
     MOV AH, 4CH
     INT 21H
	 
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
		MOV AL, sym
		SHR AL, 4
		LEA BX, HEXTABLE
		XLAT
		mov dl, al
		call putch
		
		mov al, sym
		AND AL, 0FH
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