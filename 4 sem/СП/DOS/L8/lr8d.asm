; ������������ ������ �8
;===============================================================================
prgr segment

assume CS:prgr,DS:data      ; ������������ ���������� ���������

begin: mov AX,data
	   mov DS,AX
; ������� ������
       mov AX,02h
       int 10h
; �������������� �����
	   mov AH,09h
	   mov DX,offset fengsh1
	   int 21h
	   CALL CLRF
	   mov AH,09h
	   mov DX,offset fengsh0
	   int 21h
	   CALL CLRF
; ����� �� ����� �������� CS
	   mov AH,09h
	   mov DX,offset regCS
	   int 21h
	   mov AX,CS
	   CALL hex4hex
	   mov AH,40h
	   mov CX,4
	   mov BX,1
	   mov DX,offset hx
	   int 21h
	   CALL CLRF
; ����� �� ����� �������� DS
	   mov AH,09h
	   mov DX,offset regDS
	   int 21h
	   mov AX,DS
	   CALL hex4hex
	   mov AH,40h
	   mov CX,4
	   mov BX,1
	   mov DX,offset hx
	   int 21h
	   CALL CLRF
; ����� �� ����� �������� SS
	   mov AH,09h
	   mov DX,offset regSS
	   int 21h
	   mov AX,SS
	   CALL hex4hex
	   mov AH,40h
	   mov CX,4
	   mov BX,1
	   mov DX,offset hx
	   int 21h
	   CALL CLRF
; ����� �� ����� �������� ES
	   mov AH,09h
	   mov DX,offset regES
	   int 21h
	   mov AX,ES
	   CALL hex4hex
	   mov AH,40h
	   mov CX,4
	   mov BX,1
	   mov DX,offset hx
	   int 21h
	   CALL CLRF
; ����� �� ����� �������� SP
	   mov AH,09h
	   mov DX,offset regSP
	   int 21h
	   mov AX,SP
	   CALL hex4hex
	   mov AH,40h
	   mov CX,4
	   mov BX,1
	   mov DX,offset hx
	   int 21h
	   CALL CLRF
; ����� �� ����� �������� SI
	   mov AH,09h
	   mov DX,offset regSI
	   int 21h
	   mov AX,SI
	   CALL hex4hex
	   mov AH,40h
	   mov CX,4
	   mov BX,1
	   mov DX,offset hx
	   int 21h
	   CALL CLRF
; ����� �� ����� �������� DI
	   mov AH,09h
	   mov DX,offset regDI
	   int 21h
	   mov AX,DI
	   CALL hex4hex
	   mov AH,40h
	   mov CX,4
	   mov BX,1
	   mov DX,offset hx
	   int 21h
	   CALL CLRF
; ����� �� ����� �������� BP
	   mov AH,09h
	   mov DX,offset regBP
	   int 21h
	   mov AX,BP
	   CALL hex4hex
	   mov AH,40h
	   mov CX,4
	   mov BX,1
	   mov DX,offset hx
	   int 21h
; ������� ������� ��� �����������
	   CALL CLRF
	   CALL CLRF
	   mov AH,09h
	   mov DX,offset msg2
	   int 21h
	   mov AH,08h
	   int 21h
	   xor AX,AX
; �������� �����, ������ ����, ������ �����
       mov AX,02h
       int 10h
	   mov AH,09h
	   mov DX,offset fengsh2
	   int 21h
	   xor BX,BX
	   mov SI,0
	   CALL inpthex         ; ��������� ����� ������
	   cmp AL,27            ; ���� �� ���� ������ ����� ������� ESC
	   je close             ; �� ��������� ���������, ����� � close
	   mov sg,BX            ; ��������� � ���������� �������
	   mov AH,02h
	   mov DL,58
	   int 21h
	   xor BX,BX
	   mov SI,0
	   CALL inpthex
	   cmp AL,27
	   je close
	   mov adr,BX           ; ��������� � ���������� �������� �� ��������
	   CALL CLRF
	   CALL CLRF
	   mov AX,sg            ; ����� ������� ES �� �������� �������
	   mov ES,AX
	   mov BX,adr           ; ��������, ���-�� �� ��� ������,
	   mov AX,adr           ; �� � ��� �� �����, ����� ����
	   push AX

	   pop AX
	   sub AX,strLen        ; ������ ��� ����� � ����� ����� ���������� �� strLen,!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	                        ; ��� ��� ������ � ������ ������ ������ � ������
	   CALL dumping         ; ��������� ������ ����� �� ������

; ��� ���������� ������� ������� ESC
close: ;CALL CLRF
	   mov AH,09h
	   mov DX,offset msg
	   int 21h
       CALL GETCH
	   mov AX,02h
       int 10h
; ���������� ��������� � ����� ������ 0
       mov AX,4C00h
	   int 21h
; ------------------------------------------------------------------------------
hex2hex proc
; ��� ��������� ����� ������ �����
        mov CX,0
        mov BX,strCnt
		xor DX,DX
		cmp AL,10    ; ���� ��� �� ����, �� ���� ����� ������ 16
		jae dvsn     ; �� �� ���������
		mov el[1],48 ; ����� ������ ���� � ����� �� ���������
		div BX
		mov CX,1
		mov SI,1
		jmp z
dvsn:   div BX       ; ����� AX �� BX, ��������� � AX, ������� � DX
	    push DX      ; ������� ������� � ����
	    xor DX,DX    ; �������� DX, ����� �������� �� �������
	    inc CX       ; ��������� ������� ���������� ���� � �����
	    test AX,AX   ; ���� ���� ��� ������� ������,
	    jnz dvsn     ; �� ����� ��� ���
        mov SI,0
ot:     pop DX       ; ������� ������ ����� ����������� �����
z:      cmp DL,10
		jae letter
		add DX,48    ; �������� � ASCII-���
		jmp nx
letter: add DX,55    ; �������� ASCII-��� �����
nx:     mov el[SI],DL
        inc SI
	    loop ot      ; ��������� CX ��� (�� ���������� ����)
        RET
hex2hex endp
; ------------------------------------------------------------------------------
hex4hex proc
; ��� ��������� ����� �����
        push CX
		xor CX,CX
		mov CL,12
		mov SI,0
ipt:    push AX
		sar AX,CL
		and AX,0Fh
		cmp AL,0
		jne no
		mov hx[SI],48
no:     cmp AL,10
		jae lr
		add AL,48
		jmp n
lr:     add AL,55
n:      mov hx[SI],AL
        inc SI
		pop AX
		sub CL,4
	    cmp SI,4
		jb ipt
		pop CX
        RET
hex4hex endp
; ------------------------------------------------------------------------------
inpthex proc
; ���� ������
inpt:   mov AH,08h ; ������� ����� ������� ��� ��� ������
        int 21h
		cmp AL,13  ; ���� ��� ENTER,
		je inpt    ; �� �����������, ������� �� 4 �������, �� �����
		cmp AL,27  ; ���� ����� ESC,
		je fin     ; �� �� ����������
		cmp AL,'0' ; ���� ��� ��������� �������...
		jb inpt    ; ������ ���� 0, �� �� �����
	    cmp AL,'9' ; ���� ��� ��������� �������...
	    jbe ok     ; ������ ��� ����� ���� 9, �� ������
	    cmp AL,'F' ; ���� ��� ��������� �������...
	    ja inpt    ; ������ ���� F, �� �� �����
	    cmp AL,'A' ; ���� ��� ��������� �������...
	    jb inpt    ; ������ ���� A, �� �� �����
ok:     mov AH,02h
        mov DL,AL  ; ��������� �������� � �������
	    int 21h
	    cmp AL,'9' ; ��������, ��� ��� � ���
	    ja lttr    ; ���� ��� ������ ���� 9, �� �����
	    sub AL,'0' ; ������ �� ���� 48, ������� ������� �����
	    and AX,0Fh ; ����� ��������� ���� ��������
	    jmp addd
lttr:   sub AL,55  ; � �� ����� �������� 55
        and AX,0Fh ; ���� ������ ��� ��������� ����
addd:   mov CL,4   ; �������� �� 16,
        sal BX,CL  ; �������� �� 4 ���� �����,
		or BX,AX   ; �������� ����� �����
		inc SI
		cmp SI,4
		jae fin    ; ���� ��� 4 �������, �� ��,
		jmp inpt   ; � ���� ���, �� �� ���������
fin:    RET
inpthex endp
; ------------------------------------------------------------------------------
dumping proc
; ��������� ����� �������� �� ������ � ����� ����� �� �����
        mov CX,strCnt
dump:   push CX			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mov CX, strLen		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	push DS			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	push DS			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pop ES			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mov DI, offset strChr	;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mov SI, AX		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	rep movsb		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pop DS			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pop CX			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	push AX			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	CALL CLRF		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pop AX			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	add AX,strLen		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        push AX
        push BX
        push CX
		CALL hex4hex
		mov AH,40h
		mov CX,4
		mov BX,1
		mov DX,offset hx
		int 21h
		mov AH,09h
		mov DX,offset def
		int 21h
		pop CX
		pop BX
        push CX
	    mov CX,strLen	;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
dmp:    xor AX,AX
        push BX
	    mov AL, [ES:BX]
        push AX
	    push CX
	    CALL hex2hex
	    mov AH,40h
	    mov BX,1
	    mov CX,2
	    mov DX,offset el
	    int 21h
	    mov el[0],48      ; fust for �� ������...
	    mov el[1],48      ; ...������� ����������
	    mov AH,02h
	    mov DL,32
	    int 21h
	    pop CX
	    pop AX
	    inc AX
	    pop BX
	    inc BX
	    loop dmp
	    push AX
	    ;CALL CLRF       !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    pop AX
	    pop CX
		;pop AX		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    mov AH,09h		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    mov DX,offset strChr	;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    int 21h		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    pop AX		;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    loop dump
dumping endp
; ------------------------------------------------------------------------------
CLRF proc                   ; ��������� �������� ������ � �������� �������
     mov AH,02h
     mov DL,10
	 int 21h
     mov DL,13              ; ������ �������� �������
	 int 21h
	 RET
CLRF endp
; ------------------------------------------------------------------------------
GETCH proc                  ; ��������� �������� ����� �������
	  mov AH,08h
	  int 21h
	  RET
GETCH endp
; ------------------------------------------------------------------------------
prgr ends                   ; ����� �������� ������
; -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
data segment                ; ������ �������� ������
	 msg     db 'Press any key to exit... $'
	 msg2    db 'press any key to continue...$'
	 el      db 2 dup ('0')
	 hx      db 4 dup (32)
	 sg      dw 0
	 adr     dw 0
	 def     db ' - $'
	 fengsh0 db '-----------------------------------------------------------------------$'
	 fengsh1 db 'This program makes dump of RAM. Now, it will show contents of registers$'
	 fengsh2 db 'Now, enter the adress (in HEX, type FAR): $'
	 fengsh3 db 'Dump of memory from $'
	 fengsh4 db ' till $'
	 regCS   db 'CS: $'
	 regDS   db 'DS: $'
	 regSS   db 'SS: $'
	 regES   db 'ES: $'
	 regSP   db 'SP: $'
	 regSI   db 'SI: $'
	 regDI   db 'DI: $'
	 regBP   db 'BP: $'
	 strLen  dw 16d				;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 strCnt  dw 24d				;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 strChr	 db 16 dup ('-'), '$'	;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
data ends                   ; ����� �������� ������
; -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
stk segment stack           ; ������ �������� �����
    db 256 dup (0)          ; �������������� 256 ���� ��� �����
stk ends                    ; ����� �������� �����
; -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
end begin                   ; ����� ������ ���������, ��������� ����� �����
;===============================================================================