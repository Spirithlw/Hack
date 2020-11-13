.model tiny
.code
.186
;-------------------------------------------
CR              equ 13
LF              equ 10
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

                xor cx, cx      ;cx - length
                xor dx, dx      ;indicator
                mov bx, offset password

input:          mov ah, 01h
                int 21h

                cmp al, CR      ; checks for enter
                je lenanalys

                inc cx
                cmp cx, paslength
                ja input

                cmp al, [bx]    ; checks byte
                jne wrongpas
continue:       inc bx
                jmp input

lenanalys:      cmp cx, paslength; checks length
                jne noacs

                cmp dx, 0       ; checks indicator
                ja noacs

                .write_str access
                .exitprog

wrongpas:       inc dx
                jmp continue

noacs:          .write_str ban
                .exitprog
;-------------------------------------------
.data

greeting        db 'Input Password', 0dh, 0ah, '$'
password        db 'blackout'
paslength       equ $ - password
access          db 0dh, 0ah, 'Access allowed$'
ban             db 0dh, 0ah, 'wrong attempt$'

end start
