;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; unload.asm - ���㦠�� TSR �� �����
;
;  tasm.exe /l unload.asm
;  tlink /t /x unload.obj
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

code segment	'code'
	assume	CS:code, DS:code
	;org	100h
	
	STARTSTR DB 'Do you want to unload?(Y or N) $'
	ENDSTR  DB 'Successfully unloaded$'
	_start:
	push CS
	pop DS
	
	
	MOV DX, OFFSET STARTSTR
	CALL PUTST
	call CLRF

	CALL GETCH
	
	cmp AL, 'Y'
	jne Exit 
	call CLRF
	;PUSH AX
	MOV DX, OFFSET ENDSTR
	CALL PUTST
	call CLRF
	mov AH, 0FFh
	mov AL, 1
	int 2Fh
	

	
Exit:
	MOV AL, 0
	MOV AH, 4CH
	INT 021H

PUTST PROC
	MOV AH, 09H
	INT 021H	
	RET
PUTST ENDP
	
	; ��������� - ����� ������� 
PUTCH PROC
	MOV AH, 02H
	INT 021H
	RET
PUTCH ENDP

; ��������� - ������� ������
CLRF PROC
    MOV AH, 02H
    MOV DL, 13
    INT 21H
    MOV DL, 10
    INT 21H
    RET
CLRF ENDP 

	; ��������� - ���� ������� 
GETCH PROC   
	MOV AH, 01H
	INT 021H
    RET
GETCH ENDP

	; ��������� - ������� ������ 
CLRSCR PROC   
	MOV AH, 00H 
	MOV AL, 02
	INT 10H
	RET
CLRSCR ENDP	
code ends
end _start