MYCODE 	SEGMENT	'CODE'
ASSUME	CS:MYCODE

msg DB 'HEX num: ','$'
pw10 DW 10000, 1000, 100, 10, 1
hextable DB '0123456789ABCDEF'

START:

PUSH CS
POP  DS
CALL CLRSCR

MAIN_LOOP:

	lea	DX, msg
	call putstr
	
	;���� ���塠�⮢��� ᫮�� � 16-� ����
	call MainOUT	;���� ���� � �X
	push BX ;����祭��� � BX �᫮ � �⥪
	
	mov DL, '='
	call PUTCH
	
	mov DX, BX ;�뢮� ���塠�⮢��� ᫮�� � 16-� ����
	call PutHexW
	
	mov DL, ' '
	call PUTCH
	
	pop	BX
	call HEX2DEC ;�뢮� ���塠�⮢��� ᫮�� � 10-� ����
	
	call putnl
LOOP MAIN_LOOP

ext proc
	;�����襭�� �ணࠬ��
	MOV AL, 0
	MOV AH, 4CH
	INT 21H
ext endp

MainOUT PROC
	mov	BP, 0	;���稪 ��������� ᨬ�����
	mov BX, 0	;�᫮
		
	InpCyc:
		call GETCH_NE ;���� ��� ��
		mov	DL, AL
		jmp	CHECK
		
	SHIFT:
		call PUTCH ;�᫨ ᨬ��� �ࠢ����, � �� �뢮�����
		pop	AX     ;����⠭������� �� �⥪� ��������� ���� (�� �⥪� ����頥��� � AX)
		mov AH, 0   ;����ᥭ�� 0 � AH, � AL ��� - ���������� �� ���� � ���� ����� ࠧ�鸞� (?)
		shl	bx, 4   ;����⮢� ᤢ�� �� 4 ����� (=㬭������ �᫠ �� 2^4=16)
		add	bx, ax  ;���������� ��������� ���� � �-��

		inc	bp	 ;���稪 �����
		cmp	bp, 4 ;����室��� ����� 4 ����	
		je	EXIT	
		jmp InpCyc

	CHECK:
		cmp	AL, '*'  ;�஢�ઠ �� *
		je ext	;��室 �᫨ *
		
		cmp al, '0' ;�᫨ ������ ����� 0, � �����
		jb InpCyc
		
		jnb	NUMBER ;�᫨ ����� 0 � �஢�ઠ �����
		jmp	EXIT ;�� �, �� � = ����

	NUMBER: ;ࠡ�� � ������
		;�᫨ ��� ���������� ᨬ���� '9'>, � �஢�ઠ ������ �㪢
		cmp AL, '9'
		JA UppCh    
	
	;���� ࠡ�� � ��ࠬ� 0-9
	DIG:
		sub  al, 30h  ;AL-�᫮ � �᪨ � �᪨ ᤢ���� �� 30
		push ax   ;��࠭���� �᫠ � �⥪� (AX ����頥��� � �⥪)
		jmp	SHIFT ;���室 �� ���������� १���� � BX

	UppCh:
		cmp al, 'A' ;�᫨ ������ ����� 0, � �����
		jb InpCyc	
		;�᫨ ascii-��� ���������� ᨬ���� >'F', � �஢�ઠ �����쪨� �㪢
		cmp al, 'F'
		JA  LowCh

		;�८�ࠧ������ ��᮪�� �㪢 � 16-� ����
		sub AL, 41h-0Ah ;'B'-'A'+10 <=> 42-41+10=11
		push AX 	;��࠭���� �᫠ � �⥪�
		jmp	SHIFT
		
	LowCh:
		; ����� ����� ᨬ����� �� �� 16� ��⥬�
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
MainOUT ENDP

PutHexW PROC ; ����� ���塠�⭮�� ᫮��

	
	call PUTHEX ; ���� ����
	;DH=AB, DL=CD
	;
	
	mov dh, dl
	call PUTHEX ; ��ன ����
	
	mov dl, 'h'
	int 21h
	
	RET
PutHexW ENDP

PUTHEX PROC ; ��ॢ�� � ��⭠������� ��� ����
	push BX ; �᫮ � �⥪ �� BX
	
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
	
	pop DX ;�᫮ �� �⥪� � DX
	
	RET
PUTHEX ENDP

HEX2DEC	PROC ; ��ॢ�� � ��������
		mov	AX, BX	;�᫮
		mov	DI, 0	;���稪 横��
		
		HEX2DEC_LOOP:
		;===================================
		;div:
		;DX - ������� (���訩 ����) (� �����⨫� �᫮)
		;AX - ������� (����訩 ����) (� �����⨫� �᫮)
		;BX - ����⥫� (� ����頥� 10pow)
		;div BX => DX:AX / BX
		;AX - 楫��, DX - ���⮪
		
		;===============1 横�===============
		;
		;AX: ADAD (44461)
		;DX: 0000
		;BX: 2710 (10000)
		;STACK: XXXX
		;
		;---DIV---
		;push DX
		;
		;AX: 0004
		;DX: 116D (04461)
		;BX: 2710
		;STACK: 116D (DX)
		;
		;(((����⢨⥫쭮: 44416/10000 = 4, 4461)))
		;
		;pop AX
		;
		;AX: 116D (04461)
		;STACK: XXXX
		;
		;============����� 1 横��============
		;��᫥ ���� 1 横�� ��������� �� ����⥫� (� BX ������ 1000)
		;� ���� �����, ����� ⠪�� �� 横� ⮫쪮 ��� 4461 � 1000
		;⠪ ������, ���� �� �ன��� �� ࠧ���
		;�뢮����� �� �࠭ ����।�� 4,4,4,6,1
		;===================================
		
			mov	DX, 0	;���訩 ���� �������� � ��
			mov	BX, pw10[DI] ;����⥫� � ��
			div	 BX ;������� dx: ax / bx = ax(dx), ax - ��⭮�, dx - ���⮪
			push DX ;���⮪ � �⥪, ���⮪ ��⠥��� ���� �᫮�

			;�뢮� १���� �������
			add	AX, 30h ; ������塞 � �᪨, �⮡� ������� ��� ��� �뢮��
			mov	DL, AL
			call PUTCH
			
			pop	AX ;� ax (����訩 ���� ��������) ����頥��� ���⮪
			add	DI, 2
			cmp	DI, 10 ;5 ��� - 10 ����
			JB	HEX2DEC_LOOP	;���� �� ��ॢ���� �� ᨬ����
	RET
HEX2DEC ENDP

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
;------------------------------------

MYCODE ENDS
END	START
