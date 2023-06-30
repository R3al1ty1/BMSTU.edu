dtseg segment 'data'
	lab_title db 'Lab 6:$'
	no_arguments_error db 'you should provide at least 2 arguments$'
	hex_table db '0123456789ABCDEF'
	let db '_'
	count db 0
	MEM DB 0
dtseg ends

cdseg segment 'code'
	assume cs:cdseg, ds:dtseg

start:
	mov ax, dtseg
	mov ds, ax
	mov dx, offset lab_title
	call putstr
	call clrf

	mov cl, es:80h

	cmp cx, 0
	je no_arguments

	mov bx, 80h
	get_arguments_cycle:
		inc bx
		INC MEM

		mov dl, es:bx

		cmp dl, ' '
		jne jump
		mov dl, ' '
		inc count
		jump:
		call putch
		
	loop get_arguments_cycle
	call clrf
	jmp final

	no_arguments:
	mov dx, offset no_arguments_error
	call putstr
	call clrf
	jmp final
	
	final:
	mov dl, count
	CALL CLRF
	MOV BL, COUNT
	MOV DL, MEM
	SUB DL, BL
	CALL printdigit

	
	mov al, 0
	mov ah, 4CH
	int 21H

putch proc
	push ax
	mov ah, 02
	int 21H
	pop ax
	ret
putch endp

putstr proc
	mov ah, 09
	int 21h
	ret
putstr endp

getch proc
	mov ah, 08h
	int 21h
	ret
getch endp

clrf proc
	mov dl, 10
	call putch
	mov dl, 13
	call putch
	ret
clrf endp

clrscr proc
    call clrf
    mov  ah , 0H
    mov  al , 3H
    int  10H
    ret
clrscr endp

printhex proc
	; first digit
	mov al, let
	shr al, 4
	lea bx, hex_table
	xlat
	mov dl, al
	call putch

	;second digit
	mov al, let
	and al, 0fh
	xlat
	mov dl, al
	call putch

	;final letter h
	mov dl, 'h'
	call putch
	ret
printhex endp

printdigit proc
	cmp dl, 10
	jl jump1
	mov ah, 0
	mov ax, dx
	mov bl, 10
	div bl
	mov dl, al
	add dl, '0'
	call putch
	mov dl, ah
	;add dl, '0'
	;call putch
	jump1:
	add dl, '0'
	call putch
	
	ret
printdigit endp

cdseg ends

end start