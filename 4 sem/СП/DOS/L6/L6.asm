section .data
    prompt db "������ �������� ॣ����: ", 0
    buffer db 64
    nl db 10

section .text
    global _start

_start:
    ; �뢮��� �ਣ��襭�� ��� ����� ��ࢮ�� ॣ����
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, 25
    INT 21h

    ; ���뢠�� �������� ��ࢮ�� ॣ����
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 64
    INT 21h

    ; �뢮��� ���祭�� ��ࢮ�� ॣ����
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    mov edx, eax
    INT 21h

    ; �뢮��� ᨬ��� ��ॢ��� ��ப�
    mov eax, 4
    mov ebx, 1
    mov ecx, nl
    mov edx, 1
    INT 21h

    ; �뢮��� �ਣ��襭�� ��� ����� ��ண� ॣ����
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, 25
    INT 21h

    ; ���뢠�� �������� ��ண� ॣ����
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 64
    INT 21h

    ; �뢮��� ���祭�� ��ண� ॣ����
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    mov edx, eax
    INT 21h

    ; �뢮��� ᨬ��� ��ॢ��� ��ப�
    mov eax, 4
    mov ebx, 1
    mov ecx, nl
    mov edx, 1
    INT 21h

    ; �뢮��� �ਣ��襭�� ��� ����� ���쥣� ॣ����
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt
    mov edx, 25
    INT 21h

    ; ���뢠�� �������� ���쥣� ॣ����
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 64
    INT 21h

    ; �뢮��� ���祭�� ���쥣� ॣ����
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    mov edx, eax
    INT 21h

    ; �����蠥� �ணࠬ��
    mov eax, 1
    xor ebx, ebx
    INT 21h