MYCODE SEGMENT 'CODE'
    ASSUME CS:MYCODE
    PUBLIC sym
sym DB '�'
START:
; ����㧪� ᥣ���⭮�� ॣ���� ������ DS
     PUSH CS ;code segment
     POP  DS ;data segment

	 CALL CLRSCR
	 
     MOV DL, sym
     CALL PUTCH ;�뢮� ᨬ����

	 CALL CRLF ;ᤢ�� ��ப�
	 
	 ADD sym, 1
	 MOV DL, sym
     CALL PUTCH
	 
	 CALL CRLF
	 
	 ADD sym, 1
	 MOV DL, sym
     CALL PUTCH

; �������� �����
    ;MOV AH, 01H
    ;INT 21H
	 
; ��室 �� �ணࠬ��
     MOV AL, 0 ;��室 �� �ணࠬ�� � �����饭��� errorlevel = 0
     MOV AH, 4CH ;"EXIT" - TERMINATE WITH RETURN CODE
     INT 21H
	 
	PUTCH PROC
		; 02h: entry - dl=char to write, return - al=last char output
		MOV AH, 02H
		INT 21H
		RET
	PUTCH ENDP
	
	CRLF PROC
		mov dl, 0ah ;0ah - ����� �� ����� ��ப�
		call putch
		;mov dl, 0dh ;0dh - ����� � ��砫� ��ப� (����??)
		;call putch
		ret
	CRLF ENDP
	
	CLRSCR PROC
	; AL=०��
	; 2: ⥪��	80x25	16/8 ����⮭�	CGA,EGA  b800  Composite
		mov al, 2
		int 10h
		ret
	CLRSCR ENDP
	
MYCODE ENDS
END START