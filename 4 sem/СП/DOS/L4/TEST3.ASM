MYCODE SEGMENT 'CODE'
ASSUME CS:MYCODE
	
sym DB 'A'
let db 'b'
hextable DB '0123456789ABCDEF'
;hextable DB 'FEDCBA987654321'

START:
    PUSH CS
    POP  DS

	CALL CLRSCR
	
	MAIN:
	MOV ah, 08H;
    INT 21H
	cmp al, '*' ;сравнивает: равно ли ввденное значение звездочке
	je ext ;перемещение в функцию ext
    MOV sym, al
    MOV let, al
	call putnl
	
	MOV CX , 20
	add sym, 2
	CYCLE:
		mov dl, let
		call putch
		call putdash
		
		LEA BX, HEXTABLE
		MOV AL, sym
		and AL, 0fh
		XLAT
		mov dl, al
		call putch
		
		mov al, sym
		shr AL, 4
		xlat
		mov dl, al
		call putch
		
		mov dl, 'h'
		call putch
		
		call putnl
		sub sym, 1
		add let, 1
	;INC AL
	LOOP CYCLE

	mov ah, 01h
	int 21h
	cmp al, '*'
	call putnl
	je ext ; jump equal
	jmp main ; jump abs

	EXT PROC
		MOV AL, 5 ;errorlevel 5
		MOV AH, 4CH
		INT 21H
		ret
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