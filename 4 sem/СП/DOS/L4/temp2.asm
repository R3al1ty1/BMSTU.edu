MYCODE SEGMENT 'CODE'
	ASSUME CS:MYCODE, DS:MYCODE
HEX_TABLE DB '0123456789ABCDEF'
LET DB '€'
PUTCH PROC
	    MOV AH, 02
	    INT 21H
		ret
PUTCH ENDP

PRINTNL PROC
	MOV AH, 02
	MOV DL, 0ah
	INT 21H
	ret
PRINTNL ENDP

PRINTSEP PROC
	MOV DL, ' '
	CALL PUTCH
	MOV DL, '-'
	CALL PUTCH
	MOV DL, ' '
	CALL PUTCH
	RET
PRINTSEP ENDP

PRINTHEX PROC
	; first digit
	MOV AL, LET
	SHR AL, 4
	LEA BX, HEX_TABLE
	XLAT
	
	;print first digit and replace it with * if its equal to 8
	MOV DL, AL
	CMP AL, '8'
	JE PRINTSTAR
	JMP CONTINUE
	PRINTSTAR:
	MOV DL, '*'
	CONTINUE:
	CALL PUTCH
	
	;second digit
	MOV AL, LET
	AND AL, 0Fh
	XLAT
	MOV DL, AL
	CALL PUTCH
	MOV DL, 'h'
	CALL PUTCH
	RET
PRINTHEX ENDP
START:		 
	;load segment data reg ds
	PUSH CS
	POP DS
	;print 20 chars
	MOV CX, 20 ; number of cycles
	Cycle:
		MOV DL, LET
		CALL PUTCH
		
		CALL PRINTSEP
		CALL PRINTHEX
		CALL PRINTNL
		INC LET
	LOOP Cycle
		
	;print char on screen
	CALL PUTCH	
	;wait for user input
	MOV AH, 01H
	INT 21H
	;quit
	MOV AL, 0
	MOV AH, 4CH
	INT 21H
MYCODE ENDS
END START	