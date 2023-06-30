section .data
    prompt db "Введите название регистра: ", 0
    buffer db 64
    nl db 10

section .text
    global _start

_start:
    ; выводим приглашение для ввода первого регистра
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, 25
    INT 21h

    ; считываем название первого регистра
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 64
    INT 21h

    ; выводим значение первого регистра
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    mov edx, eax
    INT 21h

    ; выводим символ перевода строки
    mov eax, 4
    mov ebx, 1
    mov ecx, nl
    mov edx, 1
    INT 21h

    ; выводим приглашение для ввода второго регистра
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, 25
    INT 21h

    ; считываем название второго регистра
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 64
    INT 21h

    ; выводим значение второго регистра
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    mov edx, eax
    INT 21h

    ; выводим символ перевода строки
    mov eax, 4
    mov ebx, 1
    mov ecx, nl
    mov edx, 1
    INT 21h

    ; выводим приглашение для ввода третьего регистра
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, 25
    INT 21h

    ; считываем название третьего регистра
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 64
    INT 21h

    ; выводим значение третьего регистра
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    mov edx, eax
    INT 21h

    ; завершаем программу
    mov eax, 1
    xor ebx, ebx
    INT 21h