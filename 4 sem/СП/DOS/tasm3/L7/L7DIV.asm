MYCODE 	SEGMENT	'CODE'
ASSUME	CS:MYCODE

msg DB 'HEX num: ','$'
pwr10 DW 10000, 1000, 100, 10, 1
hextable DB '0123456789ABCDEF'

START:

PUSH CS
POP  DS
CALL CLRSCR

MAIN_LOOP:

	lea	DX, msg
	call putstr
	
	;���� dw � 16-� ����
	call MainIN		;���� ���� � �X
	push BX 			;����祭��� � BX �᫮ � �⥪
	
	mov DL, '='
	call PUTCH
	
	mov DX, BX 			;�뢮� dw � 16-� ����
	call PutHexWd
	
	mov DL, ' '
	call PUTCH
	
	pop	BX
	call DEC_conv 		;�뢮� dw � 10-� ����
	
	call putnl
LOOP MAIN_LOOP

ext proc
	;�����襭�� �ணࠬ��
	MOV AL, 0
	MOV AH, 4CH
	INT 21H
ext endp

MainIN PROC
	mov	BP, 0			;���稪 ��������� ᨬ�����
	mov BX, 0			;�᫮
		
	InpCyc:
		call GETCH_NE
		mov	DL, AL
		jmp	CHECK
		
	SHIFT: ;����ᥭ�� �ࠢ��쭮 ��������� ᨬ����� � BX -> � BX �㤥� �᫮
		call PUTCH 		;�᫨ ᨬ��� �ࠢ����, � �� �뢮�����
		pop	AX     ;����⠭������� �� �⥪� ��������� ���� (�� �⥪� ����頥��� � AX)
		mov AH, 0   ;����ᥭ�� 0 � AH, � AL ��� - ���������� �� ���� � ���� ����� ࠧ�鸞� AX: 00AL(?)
		shl	bx, 4   ;����⮢� ᤢ�� �� 4 ����� (=㬭������ �᫠ �� 2^4=16)
		add	bx, ax  	;���������� ��������� ���� � �-��

		inc	bp	 		;���稪 �����
		cmp	bp, 4 		;����室��� ����� 4 ����	
		je	EXIT	
		jmp InpCyc

	CHECK:
		cmp	AL, '*'  	;�஢�ઠ �� *
		je ext			;��室 �᫨ *
		
		cmp al, '0' 	;�᫨ ������ ����� 0, � �����
		jb InpCyc
		
		jnb	NUMBER 		;�᫨ ����� 0 � �஢�ઠ �����
		jmp	EXIT 		;�� �, �� � = ����

	NUMBER: 			;ࠡ�� � ������
		;�᫨ ��� ���������� ᨬ���� '9'>, � �஢�ઠ ������ �㪢
		cmp AL, '9'
		JA UppCh    
	
	;���� ࠡ�� � ��ࠬ� 0-9
	DIG:
		sub al, 30h  	;AL=�᫮ � �᪨ � �᪨ ᤢ���� �� 30
		push ax   		;��࠭���� �᫠ � �⥪� (AX ����頥��� � �⥪)
		jmp	SHIFT 		;���室 �� ���������� १���� � BX

	UppCh:
		cmp al, 'A' 	;�᫨ ������ ����� 0, � �����
		jb InpCyc	
		;�᫨ ascii ���������� ᨬ���� >'F', � �஢�ઠ �����쪨� �㪢
		cmp al, 'F'
		JA  LowCh

		;�८�ࠧ������ ��᮪�� �㪢 � 16-� ����
		sub AL, 41h-0Ah ;'B'-'A'+10 <=> 42-41+10=11
		push AX 		;��࠭���� �᫠ � �⥪�
		jmp	SHIFT
		
	LowCh:
		; ����� ����� ᨬ����� �� �� 16� ��⥬� ����� a � f
		cmp AL, 'a'		
		JB InpCyc
		cmp AL, 'f'		
		JA InpCyc
		
		;�८�ࠧ������ ������ �㪢 � 16-� ����
		sub AL, 61h-0Ah  ;'b'-'a'+10=11
		push AX
		jmp	SHIFT
		
	EXIT: 
		RET
MainIN ENDP

PutHexWd PROC 			; ����� ���塠������ ᫮��
	; ABCD -> AB - ���� ���� => ࠧ�������� �� ��� ᨬ����
	;	   -> CD - ��ன ���� => ࠧ�������� �� ��� ᨬ����
	;
	;	;===================================
	;	BX=ABCD
	;	DH=AB, DL=CD
	;	----------------------------
	;	1-� PUTHEX
	;	PUSH BX		=> STACK=ABCD
	;	MOV AL, DH 	=> AL=AB
	;	SHR 		=> AL=A
	;	XLAT 		=> AL=41
	;	MOV DL, AL 	=> DL=41, DH=AB
	;	PUTCH DL	=> screen:A
	;
	;	MOV AL, DH	=> AL=AB
	;	AND AL		=> AL=B
	;	XLAT		=> AL=42
	;	MOV DL, AL	=> DL=42, DH=AB
	;	PUTCH DL	=> screen:B
	;
	;	POP DX		=> DX=ABCD
	;	----------------------------
	;	MOV DH, DL	=> DH=CD, DL=CD
	;	----------------------------
	;	2-�� PUTHEX
	;	�������筮 ⮫쪮 CDCD
	;===================================
	
	call PUTHEX 		; ���� ����
	
	mov dh, dl
	call PUTHEX 		; ��ன ����
	
	mov dl, 'h'
	int 21h
	
	RET
PutHexWd ENDP

PUTHEX PROC 			; ��ॢ�� � ��⭠������� ��� ����
	push BX 			; �᫮ � �⥪ �� BX
	
	lea BX, hextable
	mov AL, DH
	shr AL, 4
	XLAT
	mov DL, AL
	CALL PUTCH
	
	mov AL, DH
	and AL, 00001111b
	XLAT
	mov DL, AL
	CALL PUTCH
	
	pop DX 				; �᫮ �� �⥪� � DX
	
	RET
PUTHEX ENDP



PUTCH PROC
	MOV AH, 02
	INT 21H  
	RET
PUTCH ENDP

GETCH_NE PROC ;���� ��� ��
	MOV AH, 08
	INT 21H
	RET
GETCH_NE ENDP;

putnl PROC
	MOV DL, 10
	CALL PUTCH
	MOV DL, 13
	CALL PUTCH
	RET
putnl ENDP

CLRSCR PROC
	MOV AX, 03
	INT 10H
	RET
CLRSCR ENDP

putstr proc
	mov ah, 09
	int 21h
	ret
putstr endp

MYCODE ENDS
END	START



DEC_conv PROC
			`	
		;44416 - 10000 = 34416 > 10000 -> 1
		;34416 - 10000 = 24416 > 10000 -> 2
		;24416 - 10000 = 14416 > 10000 -> 3
		;14416 - 10000 = 04416 > 10000 -> 4
		
		mov	AX, BX		; �᫮
		;push bx
		mov	DI, 0		; ���稪 横��
		
		DEC_conv_Cycle:
			
			push ax
			mov	DX, 0 			
			mov si, 0
			mov	BX, pwr10[DI]	; ���⠥��� � ��
			
			sub_cycle:
				sub ax, BX
				cmp ax, BX
				inc si
				ja sub_cycle
				jna cont_dec
			
			cont_dec:
			mov	dx, si
			call PUTCH
			
			pop ax 			; ���⮪
			add	DI, 2
			cmp	DI, 10 			;5 ��� - 10 ����
			JB	DEC_conv_Cycle 	;���� �� ��ॢ���� �� ᨬ����
	RET
DEC_conv ENDP
