; Read symbol from keyboard and print next 3 characters from ascii table
MYCODE SEGMENT 'CODE'
    ASSUME CS:MYCODE
    PUBLIC LET
LET DB 'A'
START:
; Çàãðóçêà ñåãìåíòíîãî ðåãèñòðà äàííûõ DS
     PUSH CS
     POP  DS
; read symbol
    MOV AH, 01H ;ф-я ввода символа
    INT 21H
    MOV LET, AL	;поместим в LET символ из AL
; print new line
    MOV AH, 02
    MOV DL, 0ah
    INT 21H 
; print first
     ADD LET, 1
     MOV AH, 02
     MOV DL, LET
     INT 21H
; print new line
    MOV AH, 02
    MOV DL, 0ah
    INT 21H 
;print second
    ADD LET, 1
    MOV AH, 02
    MOV DL, LET
    INT 21H
;print new line
    MOV AH, 02
    MOV DL, 0ah
    INT 21H
;print third
    ADD LET, 1
    MOV AH, 02
    MOV DL,LET 
    INT 21H
; wait input
    MOV AH, 01H
    INT 21H
; Âûõîä èç ïðîãðàììû
     MOV AL, 0
     MOV AH, 4CH
     INT 21H
MYCODE ENDS
END START
