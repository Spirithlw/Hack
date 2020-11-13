.model tiny
.code
.186
;-------------------------------------------
CR              equ 13
LF              equ 10
buff_size       equ 16
;-------------------------------------------
org 100h
;-------------------------------------------
;ends program
;expects:       no
;-------------------------------------------
.exitprog macro

		mov ax, 4c00h
		int 21h

		endm
;-------------------------------------------
;writes string
;expects:       addres of string
;-------------------------------------------
.write_str      macro ptr

                mov ah, 09h
                mov dx, offset ptr
                int 21h

                endm
;-------------------------------------------
start:          .write_str greeting

                mov bx, offset buffer

input:          mov ah, 01h
                int 21h

                cmp al, CR      ;checks for enter
                je next

                mov ds:[bx], al ;writing in buffer
                inc bx
                jmp input

next:           call check
                .exitprog
;-------------------------------------------
;compare with password and prints result
;expects: none
;destory: bx, es, di, si, cx
;returns: none
;-------------------------------------------
check           proc

                mov bx, es
                mov ds, bx
                mov cx, paslength
                mov di, offset buffer
                mov si, offset password
                jmp cmpr

??continue:     je ??success
                .write_str ban
                jmp ??return

??success:       .write_str access

??return:       ret
                endp
;-------------------------------------------
.data

greeting        db 'Input Password', 0dh, 0ah, '$'
password        db 'blackout'
paslength       equ $ - password
access          db 0dh, 0ah, 'Access allowed$'
ban             db 0dh, 0ah, 'wrong attempt$'
buffer:         db 16 dup (00h)
cmpr:           rep cmpsb
                jmp ??continue

end start
