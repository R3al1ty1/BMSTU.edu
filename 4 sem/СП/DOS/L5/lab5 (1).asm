MYCODE SEGMENT 'CODE'
ASSUME CS:MYCODE, DS:MYCODE
org 100H
LET DB 'А'
BUF DB 1000 DUP('_')
TABLHEX DB '0123456789ABCDEF'
STRING_AMOUNT DB 0
TITEL DB 'Введите буквы: $'
start:

;игнор backspace, enter, и тд. 
; Загрузка регистра сегмента данных
	PUSH CS
	POP DS
	
	MOV DX, OFFSET TITEL
	CALL PUTSTR
	CALL CRLF
	
INPUT:
	MOV CX, 1000
	MOV SI, 0
	LABEL2:
			;get char
	CALL GETCH
	MOV DL, AL
	CMP AL, '$'
	JE PRINT_STRING
	CMP AL, 08h
	JE SKIP
	CALL PUTCH
	SKIP:		
			; check if input ended
	CMP BUF[0], '*'
	JE EXIT	
	MOV BUF[SI], AL
	INC SI
	LOOP LABEL2
PRINT_STRING: 
	CMP SI, 0
	JE EXIT
	MOV CX, SI
	MOV SI, 0
	LABEL1:
	MOV DL, BUF[SI] 
	;CALL PUTCH
	INC SI
	LOOP LABEL1
	MOV DL, ' '
	CALL PUTCH
	MOV DL, '='
	CALL PUTCH
	MOV DL, ' '
	CALL PUTCH
	
	MOV cx, SI
	MOV SI, 0
	
	LABEL_HEX:
	MOV DL, BUF[SI]
	MOV LET, DL
	CALL HEX
			
	MOV DL, ' '
	CALL PUTCH
			
	INC SI
			
	loop LABEL_HEX
	CALL CRLF
		
	MOV DL, 0AH
	CALL PUTCH
		
	INC STRING_AMOUNT
	CMP STRING_AMOUNT, 10
	JNE INPUT

; Выход из программы
EXIT:
	MOV AL, 0 ;выход из пpогpаммы с возвpащением errorlevel 0
	MOV AH, 4CH
; Активизация системной функции для завершения программы
	INT 21H
;Подготовка длинного адреса



; ---Функции--- - получение строки с клавиатуры
GETCH PROC
	MOV AH, 08H
	INT 21H
	RET
GETCH ENDP
; Процедура перевода строки
CRLF PROC
	MOV DL , 10
	CALL PUTCH
	MOV DL , 13
	CALL PUTCH
	RET
CRLF ENDP
; Процедура вывод символа
PUTCH PROC NEAR
	MOV AH , 02H
	INT 021H
	RETN
PUTCH ENDP

PUTSTR PROC
	MOV AH, 09
	INT 21H
	RET
PUTSTR ENDP

; Процедура для дальнего вызова
TESTP PROC FAR
	MOV BP , SP
	MOV DX , 4 + [BP]
	MOV AH , 02H
	INT 021H
	RETF
TESTP ENDP
;Процедура перевода и печати шест. представления DL-символа
HEX PROC
	PUSH DX
;Выделения и печать 1-й цифры DL
	MOV AL,DL
	SHR AL,4
	LEA BX, TABLHEX
	XLAT ;Перекодировка
	MOV DL,AL
	CALL PUTCH
	POP DX
; 2-й цифра
	MOV AL,DL
	AND AL,0FH ;Маскировка AND
	XLAT
	MOV DL,AL
	CALL PUTCH
	MOV DL, 'h' ;добаляем h в конец
	CALL PUTCH
	RET
HEX ENDP
;Процедура очистки экрана
CLSSCR PROC
	MOV AH, 00H ; Переключения видео режима
	MOV AL, 3 ; Новый режим
	INT 10H ; Прерывание в BIOS
	RET
CLSSCR ENDP


; Конец сегмента
mycode ENDS
	END start