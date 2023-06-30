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
	
	;ввод dw в 16-м виде
	call MainIN		;Ввод адреса в ВX
	push BX 			;полученное в BX число в стек
	
	mov DL, '='
	call PUTCH
	
	mov DX, BX 			;вывод dw в 16-м виде
	call PutHexWd
	
	mov DL, ' '
	call PUTCH
	
	pop	BX
	call DEC_conv 		;вывод dw в 10-м виде
	
	call putnl
LOOP MAIN_LOOP

ext proc
	;Завершение программы
	MOV AL, 0
	MOV AH, 4CH
	INT 21H
ext endp

MainIN PROC
	mov	BP, 0			;счетчик введенных символов
	mov BX, 0			;число
		
	InpCyc:
		call GETCH_NE
		mov	DL, AL
		jmp	CHECK
		
	SHIFT: ;занесение правильно введенных символов в BX -> в BX будет число
		call PUTCH 		;если символ правильный, то он выводится
		pop	AX     ;восстановление из стека введенной цифры (из стека помещается в AX)
		mov AH, 0   ;занесение 0 в AH, в AL цифра - избавление от мусора в двух старших разрядах AX: 00AL(?)
		shl	bx, 4   ;побитовый сдвиг на 4 влево (=умножению числа на 2^4=16)
		add	bx, ax  	;добавление введенной цифры к р-ту

		inc	bp	 		;счетчик ввода
		cmp	bp, 4 		;необходимо ввести 4 цифры	
		je	EXIT	
		jmp InpCyc

	CHECK:
		cmp	AL, '*'  	;проверка на *
		je ext			;выход если *
		
		cmp al, '0' 	;если вводят меньше 0, то запрет
		jb InpCyc
		
		jnb	NUMBER 		;если больше 0 то проверка дальше
		jmp	EXIT 		;ни то, ни то = ретурн

	NUMBER: 			;работа с вводом
		;если код введенного символа '9'>, то проверка больших букв
		cmp AL, '9'
		JA UppCh    
	
	;иначе работа с цифрами 0-9
	DIG:
		sub al, 30h  	;AL=число в аски и аски сдвинут на 30
		push ax   		;сохранение числа в стеке (AX помещается в стек)
		jmp	SHIFT 		;переход на накопление результата в BX

	UppCh:
		cmp al, 'A' 	;если вводят меньше 0, то запрет
		jb InpCyc	
		;если ascii введенного символа >'F', то проверка маленьких букв
		cmp al, 'F'
		JA  LowCh

		;преобразование высокой букв в 16-е цифры
		sub AL, 41h-0Ah ;'B'-'A'+10 <=> 42-41+10=11
		push AX 		;сохранение числа в стеке
		jmp	SHIFT
		
	LowCh:
		; запрет ввода символов не из 16й системы между a и f
		cmp AL, 'a'		
		JB InpCyc
		cmp AL, 'f'		
		JA InpCyc
		
		;преобразование низкой букв в 16-е цифры
		sub AL, 61h-0Ah  ;'b'-'a'+10=11
		push AX
		jmp	SHIFT
		
	EXIT: 
		RET
MainIN ENDP

PutHexWd PROC 			; печать двухбайового слова
	; ABCD -> AB - первый байт => разбивается на два символа
	;	   -> CD - второй байт => разбивается на два символа
	;
	;	;===================================
	;	BX=ABCD
	;	DH=AB, DL=CD
	;	----------------------------
	;	1-ый PUTHEX
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
	;	2-ой PUTHEX
	;	аналогично только CDCD
	;===================================
	
	call PUTHEX 		; первый байт
	
	mov dh, dl
	call PUTHEX 		; второй байт
	
	mov dl, 'h'
	int 21h
	
	RET
PutHexWd ENDP

PUTHEX PROC 			; перевод в шестнадцатеричную для печати
	push BX 			; число в стек из BX
	
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
	
	pop DX 				; число из стека в DX
	
	RET
PUTHEX ENDP



PUTCH PROC
	MOV AH, 02
	INT 21H  
	RET
PUTCH ENDP

GETCH_NE PROC ;ввод без эха
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
		
		mov	AX, BX		; число
		;push bx
		mov	DI, 0		; счетчик цикла
		
		DEC_conv_Cycle:
			
			push ax
			mov	DX, 0 			
			mov si, 0
			mov	BX, pwr10[DI]	; вычитаемое в ВХ
			
			sub_cycle:
				sub ax, BX
				cmp ax, BX
				inc si
				ja sub_cycle
				jna cont_dec
			
			cont_dec:
			mov	dx, si
			call PUTCH
			
			pop ax 			; остаток
			add	DI, 2
			cmp	DI, 10 			;5 цифр - 10 байт
			JB	DEC_conv_Cycle 	;пока не переведем все символы
	RET
DEC_conv ENDP
