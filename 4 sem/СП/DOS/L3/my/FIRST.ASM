MYCODE SEGMENT 'CODE'
    ASSUME CS:MYCODE
    PUBLIC sym
sym DB 'А'
START:
; Загрузка сегментного регистра данных DS
     PUSH CS ;code segment
     POP  DS ;data segment

	 CALL CLRSCR
	 
     MOV DL, sym
     CALL PUTCH ;вывод символа

	 CALL CRLF ;сдвиг строки
	 
	 ADD sym, 1
	 MOV DL, sym
     CALL PUTCH
	 
	 CALL CRLF
	 
	 ADD sym, 1
	 MOV DL, sym
     CALL PUTCH

; Ожидание ввода
    ;MOV AH, 01H
    ;INT 21H
	 
; Выход из программы
     MOV AL, 0 ;выход из программы с возвращением errorlevel = 0
     MOV AH, 4CH ;"EXIT" - TERMINATE WITH RETURN CODE
     INT 21H
	 
	PUTCH PROC
		; 02h: entry - dl=char to write, return - al=last char output
		MOV AH, 02H
		INT 21H
		RET
	PUTCH ENDP
	
	CRLF PROC
		mov dl, 0ah ;0ah - курсор на новую строку
		call putch
		;mov dl, 0dh ;0dh - курсор в начало строки (надо??)
		;call putch
		ret
	CRLF ENDP
	
	CLRSCR PROC
	; AL=режим
	; 2: текст	80x25	16/8 полутона	CGA,EGA  b800  Composite
		mov al, 2
		int 10h
		ret
	CLRSCR ENDP
	
MYCODE ENDS
END START