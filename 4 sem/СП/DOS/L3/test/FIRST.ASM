MYCODE SEGMENT 'CODE'
    ASSUME CS:MYCODE
    PUBLIC symA, symB, symC
symA  DB '�'
symB  DB '�'
symC  DB '�'
START:
; ����㧪� ᥣ���⭮�� ॣ���� ������ DS
     PUSH CS
     POP  DS
; �뢮� ������ ᨬ���� �� ��࠭
	 CALL CLRSCR
	 
     MOV DL, symA
     CALL PUTCH

	 CALL CRLF 
	 
	 MOV DL, symB
     CALL PUTCH
	 
	 CALL CRLF
	 
	 MOV DL, symC
     CALL PUTCH
	 
; ��室 �� �ணࠬ��
     MOV AL, 0
     MOV AH, 4CH
     INT 21H
	 
	PUTCH PROC
		MOV AH, 02H
		INT 021H
		RET
	PUTCH ENDP
	
	CRLF PROC
		MOV DL , 10
		CALL PUTCH
		MOV DL , 13
		CALL PUTCH
		RET
	CRLF ENDP
	
	CLRSCR PROC
		;mov ah, 00h 
		;mov al, 7
		int 10h
		ret
	CLRSCR ENDP
	
MYCODE ENDS
END START


