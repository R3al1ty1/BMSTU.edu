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
	
	;ввод двухбайтового слова в 16-м виде
	call MainOUT	;Ввод адреса в ВX
	push BX ;полученное в BX число в стек
	
	mov DL, '='
	call PUTCH
	
	mov DX, BX ;вывод двухбайтового слова в 16-м виде
	call PutHexW
	
	mov DL, ' '
	call PUTCH
	
	pop	BX
	call HEX2DEC ;вывод двухбайтового слова в 10-м виде
	
	call putnl
LOOP MAIN_LOOP

ext proc
	;Завершение программы
	MOV AL, 0
	MOV AH, 4CH
	INT 21H
ext endp

MainOUT PROC
	mov	BP, 0	;счетчик введенных символов
	mov BX, 0	;число
		
	InpCyc:
		call GETCH_NE ;ввод бех эха
		mov	DL, AL
		jmp	CHECK
		
	SHIFT:
		call PUTCH ;если символ правильный, то он выводится
		pop	AX     ;восстановление из стека введенной цифры (из стека помещается в AX)
		mov AH, 0   ;занесение 0 в AH, в AL цифра - избавление от мусора в двух старших разрядах (?)
		shl	bx, 4   ;побитовый сдвиг на 4 влево (=умножению числа на 2^4=16)
		add	bx, ax  ;добавление введенной цифры к р-ту

		inc	bp	 ;счетчик ввода
		cmp	bp, 4 ;необходимо ввести 4 цифры	
		je	EXIT	
		jmp InpCyc

	CHECK:
		cmp	AL, '*'  ;проверка на *
		je ext	;выход если *
		
		cmp al, '0' ;если вводят меньше 0, то запрет
		jb InpCyc
		
		jnb	NUMBER ;если больше 0 то проверка дальше
		jmp	EXIT ;ни то, ни то = ретурн

	NUMBER: ;работа с вводом
		;если код введенного символа '9'>, то проверка больших букв
		cmp AL, '9'
		JA UppCh    
	
	;иначе работа с цифрами 0-9
	DIG:
		sub  al, 30h  ;AL-число в аски и аски сдвинут на 30
		push ax   ;сохранение числа в стеке (AX помещается в стек)
		jmp	SHIFT ;переход на накопление результата в BX

	UppCh:
		cmp al, 'A' ;если вводят меньше 0, то запрет
		jb InpCyc	
		;если ascii-код введенного символа >'F', то проверка маленьких букв
		cmp al, 'F'
		JA  LowCh

		;преобразование высокой букв в 16-е цифры
		sub AL, 41h-0Ah ;'B'-'A'+10 <=> 42-41+10=11
		push AX 	;сохранение числа в стеке
		jmp	SHIFT
		
	LowCh:
		; запрет ввода символов не из 16й системы
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
MainOUT ENDP

PutHexW PROC ; печать двухбайтного слова

	
	call PUTHEX ; первый байт
	;DH=AB, DL=CD
	;
	
	mov dh, dl
	call PUTHEX ; второй байт
	
	mov dl, 'h'
	int 21h
	
	RET
PutHexW ENDP

PUTHEX PROC ; перевод в шестнадцатеричную для печати
	push BX ; число в стек из BX
	
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
	
	pop DX ;число из стека в DX
	
	RET
PUTHEX ENDP

HEX2DEC	PROC ; перевод в десятичную
		mov	AX, BX	;число
		mov	DI, 0	;счетчик цикла
		
		HEX2DEC_LOOP:
		;===================================
		;div:
		;DX - делимое (старший байт) (сюда поместили число)
		;AX - делимое (младший байт) (сюда поместили число)
		;BX - делитель (сюда помещаем 10pow)
		;div BX => DX:AX / BX
		;AX - целое, DX - остаток
		
		;===============1 цикл===============
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
		;(((Действительно: 44416/10000 = 4, 4461)))
		;
		;pop AX
		;
		;AX: 116D (04461)
		;STACK: XXXX
		;
		;============конец 1 цикла============
		;после конца 1 цикла двигаемся по делителю (в BX кладем 1000)
		;и идем вверх, делая такой же цикл только для 4461 и 1000
		;так делаем, пока не пройдем все разряды
		;выводится на экран поочередно 4,4,4,6,1
		;===================================
		
			mov	DX, 0	;Старший байт делимого в АХ
			mov	BX, pw10[DI] ;делитель в ВХ
			div	 BX ;деление dx: ax / bx = ax(dx), ax - частное, dx - остаток
			push DX ;остаток в стек, остаток считается новым числом

			;вывод результата деления
			add	AX, 30h ; добавляем к аски, чтобы получить вид для вывода
			mov	DL, AL
			call PUTCH
			
			pop	AX ;в ax (младший байт делимого) помещается остаток
			add	DI, 2
			cmp	DI, 10 ;5 цифр - 10 байт
			JB	HEX2DEC_LOOP	;пока не переведем все символы
	RET
HEX2DEC ENDP

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
;------------------------------------

MYCODE ENDS
END	START
