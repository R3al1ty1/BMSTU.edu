MYCODE SEGMENT 'CODE'
ASSUME CS:MYCODE, DS:MYCODE
org 100H
LET DB '�'
BUF DB 1000 DUP('_')
TABLHEX DB '0123456789ABCDEF'
STRING_AMOUNT DB 0
TITEL DB '������ �㪢�: $'
start:

;����� backspace, enter, � �. 
; ����㧪� ॣ���� ᥣ���� ������
	PUSH CS
	POP DS
	
	MOV DX, OFFSET TITEL
	CALL PUTSTR
	CALL CRLF
	
INPUT:
	MOV CX, 1000
	MOV SI, 0
	LABEL2:
			;get char
	CALL GETCH
	MOV DL, AL
	CMP AL, '$'
	JE PRINT_STRING
	CMP AL, 08h
	JE SKIP
	CALL PUTCH
	SKIP:		
			; check if input ended
	CMP BUF[0], '*'
	JE EXIT	
	MOV BUF[SI], AL
	INC SI
	LOOP LABEL2
PRINT_STRING: 
	CMP SI, 0
	JE EXIT
	MOV CX, SI
	MOV SI, 0
	LABEL1:
	MOV DL, BUF[SI] 
	;CALL PUTCH
	INC SI
	LOOP LABEL1
	MOV DL, ' '
	CALL PUTCH
	MOV DL, '='
	CALL PUTCH
	MOV DL, ' '
	CALL PUTCH
	
	MOV cx, SI
	MOV SI, 0
	
	LABEL_HEX:
	MOV DL, BUF[SI]
	MOV LET, DL
	CALL HEX
			
	MOV DL, ' '
	CALL PUTCH
			
	INC SI
			
	loop LABEL_HEX
	CALL CRLF
		
	MOV DL, 0AH
	CALL PUTCH
		
	INC STRING_AMOUNT
	CMP STRING_AMOUNT, 10
	JNE INPUT

; ��室 �� �ணࠬ��
EXIT:
	MOV AL, 0 ;��室 �� �p��p���� � ����p�饭��� errorlevel 0
	MOV AH, 4CH
; ��⨢����� ��⥬��� �㭪樨 ��� �����襭�� �ணࠬ��
	INT 21H
;�����⮢�� �������� ����



; ---�㭪樨--- - ����祭�� ��ப� � ����������
GETCH PROC
	MOV AH, 08H
	INT 21H
	RET
GETCH ENDP
; ��楤�� ��ॢ��� ��ப�
CRLF PROC
	MOV DL , 10
	CALL PUTCH
	MOV DL , 13
	CALL PUTCH
	RET
CRLF ENDP
; ��楤�� �뢮� ᨬ����
PUTCH PROC NEAR
	MOV AH , 02H
	INT 021H
	RETN
PUTCH ENDP

PUTSTR PROC
	MOV AH, 09
	INT 21H
	RET
PUTSTR ENDP

; ��楤�� ��� ���쭥�� �맮��
TESTP PROC FAR
	MOV BP , SP
	MOV DX , 4 + [BP]
	MOV AH , 02H
	INT 021H
	RETF
TESTP ENDP
;��楤�� ��ॢ��� � ���� ���. �।�⠢����� DL-ᨬ����
HEX PROC
	PUSH DX
;�뤥����� � ����� 1-� ���� DL
	MOV AL,DL
	SHR AL,4
	LEA BX, TABLHEX
	XLAT ;��४���஢��
	MOV DL,AL
	CALL PUTCH
	POP DX
; 2-� ���
	MOV AL,DL
	AND AL,0FH ;��᪨஢�� AND
	XLAT
	MOV DL,AL
	CALL PUTCH
	MOV DL, 'h' ;�����塞 h � �����
	CALL PUTCH
	RET
HEX ENDP
;��楤�� ���⪨ �࠭�
CLSSCR PROC
	MOV AH, 00H ; ��४��祭�� ����� ०���
	MOV AL, 3 ; ���� ०��
	INT 10H ; ���뢠��� � BIOS
	RET
CLSSCR ENDP


; ����� ᥣ����
mycode ENDS
	END start