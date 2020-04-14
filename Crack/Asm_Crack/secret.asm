
STD_IN equ 2  
STD_OUT equ 1
section .data

	greeting: db "Insert the password to get the secret information", 0xa, 0
	greeting_len equ $ - greeting

	password: db "DIHT", 0
	pass_len equ $ - password
	accept: db "Your password is right!", 0xa, 0xa, 0
	acc_len equ $ - accept
	wrong: db  "Your password is wrong! Go away!", 0xa, 0
	wrong_len equ $ - wrong

	secret_info: db "The secret is: DIHT is better than RT!", 0xa, 0
	secret_info_len equ $ - secret_info
	
	buffer: times 10d db 0
	check:  db 0

section .text
global _start

_start:

	mov rcx, greeting
	mov rdx, greeting_len
	call write_str

	call check_password
	
	cmp byte [check], 'k'
	je .right_pas

	call pas_wrong
	jmp .End

.right_pas:

	call pas_access

.End:
	mov rax, 60							; системный вызов "sys_exit"
	xor rdi, rdi						; код ошибки
	syscall

	ret

check_password:

	mov rcx, buffer
	mov rdx, 10
	call read_str

	cld
	mov rsi, password
	mov rdi, buffer
	mov rcx, pass_len
	repe cmpsb

	cmp rcx, 0

	jne .wrong_pas

	cmp byte [rdi], 0
	jne .wrong_pas

	mov byte [check], 'k'

.wrong_pas:

	ret

pas_access:

	mov rcx, accept
    mov rdx, acc_len
	call write_str

	mov rcx, secret_info
	mov rdx, secret_info_len
	call write_str

	ret

pas_wrong:

	mov rcx, wrong
	mov rdx, wrong_len
	call write_str

	ret


; Expects the length of the string in rdx, ptr to the string in rcx.
; Destroys rax, rbx
read_str:

	mov rax, 3                  		; The number of the system call "read".
    mov rbx, STD_IN              	  	; The file descriptor "stdin".
	int 0x80                            ; Call the interruption.
	ret


; Expects the length of the string in rdx, ptr to the string in rcx.
; Destroys rax, rbx
write_str:

	mov rax, 4                  		; The number of the system call "write".
    mov rbx, STD_OUT              	  	; The file descriptor "stdout".
	int 0x80                            ; Call the interruption.
	ret