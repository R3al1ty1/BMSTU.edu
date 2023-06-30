; program to convert 8-character hex string into binary and decimal
dtseg segment 'data'
	value_error db 'Error!', 0ah, 'Allowed chars: 0123456789ABCDEF', 0ah, 'Aborting$'
	greet_hint db 'Enter hex number in HHHHHHHH format:>$'
	dec_output_hint db 'Dec: $'
	hex_output_hint db 'Hex: $'
	msg DB 'HEX num = ','$'

	string db 9 dup('_') 
	hex_string db 9 dup('_') 
	dec_string db 11 dup('0') 
	num dd 0 
	div_result db 0
	dw_buf dw 0
	powers_of_10 dd 1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1
dtseg ends

sseg segment 'stack'
	db 400h dup(0)
sseg ends


cdseg segment 'code'
	assume cs:cdseg, ds:dtseg, ss:sseg

start:
	call clrscr
	; load data segment
	mov ax, dtseg
	mov ds, ax
	
	; input string
	mov dx, offset msg
	call putstr
	call input_string
	
	; write to memory from string
	call fill_first_dw
	call fill_second_dw
	
	; make hex string
	mov si, 3
	mov ax, word ptr num + 2
	mov dw_buf, ax
	call make_hex
	mov si, 7
	mov ax, word ptr num
	mov dw_buf, ax
	call make_hex
	mov hex_string[8], '$'
	mov dx, offset hex_string
	call putstr
	call clrf
	
	;make dec string
	mov cx, 9
	mov si, 0
	mov di, 0
	make_dec:
		call div_dd
		mov al, div_result
		add dec_string[si], al
		inc si
		add di, 4
	loop make_dec
	mov dec_string[10], '$'
	mov dx, offset dec_output_hint
	call putstr
	mov dx, offset dec_string
	call putstr
	call clrf
	
	call exit
	
input_string proc
	mov si, 0
	mov cx, 8 ; 8 - hex number length
	string_check:
		call getch
		mov string[si], al
		mov dl, string[si]
		call isdigitalpha
		jne show_value_error
		jmp string_check_end
		show_value_error:
			call clrf
			mov dx, offset value_error
			call putstr
			call clrf
			call exit
		string_check_end:
			inc si
	loop string_check
	call clrf
	ret
input_string endp
	
fill_first_dw proc
	mov si, 3
	mov cx, 4
	fill_dw1:
		mov dl, string[si]
		call isdigit
		je process_digit1
		jne process_alpha1
		process_digit1:
			sub string[si], '0'
			jmp add_to_dw1
		process_alpha1:
			sub string[si], 'A'
			add string[si], 10
			jmp add_to_dw1
		add_to_dw1:
			; di = power of 16
			mov di, 3
			sub di, si
			
			;load 16^0 to ax
			mov ax, 1
			
			; if power of 16 is 0, skip the rest
			cmp di, 0
			je fill_dw_cycle_end1
			
			; multiply ax (di) times
			mov bx, cx
			mov cx, di
			move_16_power_to_ax1:
				shl ax, 4
			loop move_16_power_to_ax1
			mov cx, bx
		fill_dw_cycle_end1:
			cmp string[si], 0
			je fill_dw_cycle_end_skip_adding1
			mov bx, 0
			mov bl, string[si]
			mov dx, 0
			mul bx
			add word ptr num + 2, ax
			
			fill_dw_cycle_end_skip_adding1:
				dec si
	loop fill_dw1
	ret
fill_first_dw endp

fill_second_dw proc
	mov si, 3
	mov cx, 4
	fill_dw2:
		mov dl, string[si + 4]
		call isdigit
		je process_digit2
		jne process_alpha2
		process_digit2:
			sub string[si + 4], '0'
			jmp add_to_dw2
		process_alpha2:
			sub string[si + 4], 'A'
			add string[si + 4], 10
			jmp add_to_dw2
		add_to_dw2:
			; di = power of 16
			mov di, 3
			sub di, si
			
			;load 16^0 to ax
			mov ax, 1
			
			; if power of 16 is 0, skip the rest
			cmp di, 0
			je fill_dw_cycle_end2
			
			; multiply ax (di) times
			mov bx, cx
			mov cx, di
			move_16_power_to_ax2:
				shl ax, 4
			loop move_16_power_to_ax2
			mov cx, bx
		fill_dw_cycle_end2:
			cmp string[si + 4], 0
			je fill_dw_cycle_end_skip_adding2
			mov bx, 0
			mov bl, string[si + 4]
			mov dx, 0
			mul bx
			add word ptr num, ax
			
			fill_dw_cycle_end_skip_adding2:
				dec si
	loop fill_dw2
	ret
fill_second_dw endp

; [si:si+4]
; dw_buf = processed dw
make_hex proc
	push cx
	push bx
	mov cx, 4
	make_hex_loop:
		mov bx, dw_buf
		and bx, 0Fh
		cmp bx, 09h
		jle make_hex_process_digit
		jg make_hex_process_alpha
		jmp make_hex_cycle_end
		make_hex_process_alpha:
			mov hex_string[si], 'A'
			add hex_string[si], bl
			sub hex_string[si], 0Ah
			jmp make_hex_cycle_end
		make_hex_process_digit:
			mov hex_string[si], '0'
			add hex_string[si], bl
			jmp make_hex_cycle_end
		make_hex_cycle_end:
			shr dw_buf, 4
			dec si
	loop make_hex_loop
	pop cx
	pop bx
	ret
make_hex endp

; ax - first 
; bx - second
; num - remainder
; div_result - div_result
; делим num на powers_of_10[di]
div_dd proc
	push ax
	push bx
	mov div_result, 0
	div_loop:
		mov ax, word ptr num + 2
		mov bx, word ptr powers_of_10[di] + 2
		cmp ax, bx ; ja = jg and jb = jl
		jb div_dd_end
		ja div_loop_sub
		mov ax, word ptr num
		mov bx, word ptr powers_of_10[di]
		cmp ax, bx
		jb div_dd_end
		
		; substract
		div_loop_sub:
			call sub_dd
			inc div_result
			jmp div_loop
	div_dd_end:
	pop ax
	pop bx
	ret
	
div_dd endp

;sub powers_of_10[di] from num
;assuming num is bigger
sub_dd proc
	push ax
	push bx
	push dx
	push cx
	mov ax, word ptr num + 2 ; num - ax : bx
	mov bx, word ptr num
	mov dx, word ptr powers_of_10[di] + 2 ; powers_of_10[di] = dx:cx
	mov cx, word ptr powers_of_10[di]
	; we can firstly substract cx, and that substract only from dx
	cmp bx, cx
	jb sub_second_part_with_roll
	sub bx, cx
	mov cx, 0
	jmp sub_higher
	sub_second_part_with_roll:
		sub cx, bx	
		mov bx, 0FFFFh
		sub ax, 1
		sub bx, cx
		add bx, 1
		mov cx, 0
	; higher pair
	sub_higher:
		sub ax, dx
	sub_dd_end:	
		mov word ptr num + 2, ax
		mov word ptr num, bx
		pop ax
		pop bx
		pop dx
		pop cx
	ret

sub_dd endp


exit proc
	mov al, 0
	mov ah, 4CH
	int 21H
exit endp

isdigitalpha proc
	call isdigit
	jne check_isaplha
	je digitalpha
	check_isaplha:
		call isalpha
		jne not_digitalpha
		je digitalpha
	not_digitalpha:
		cmp dl, '0'
		ret
	digitalpha:
		cmp dl, dl
		ret
isdigitalpha endp

isdigit proc
	cmp dl, '0'
	jl not_digit

	cmp dl, '9'
	jg not_digit

	jmp digit
	not_digit:
		cmp dl, '0'
		ret
	digit:
		cmp dl, dl
		ret
isdigit endp

isalpha proc
	cmp dl, 'A'
	jl not_alpha

	cmp dl, 'F'
	jg not_alpha

	jmp alpha
	not_alpha:
		cmp dl, 'A'
		ret
	alpha:
		cmp dl, dl
		ret
isalpha endp

putch proc
	mov ah, 02
	int 21H
	ret
putch endp

putstr proc
	mov ah, 09
	int 21h
	ret
putstr endp

getch proc
	mov ah, 01h
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
cdseg ends

end start