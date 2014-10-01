;--------------------------------------------------------------
; XTREME OS                                    
; VERSION 0.1                                  
;--------------------------------------------------------------
; ICON.INC
; Decodes the xtreme icon format (.xif) which is an 4 bpp format
; -------------------------------------------------------------

Decode_pixel:
;-----------------------------------------
; FUNCTION = DECODES A TRIAL OF PIXELS
; IN:  SI = Image Buffer
;      WORD [xpos] = X POSITION OF THE ICON IMAGE
;      WORD [ypos] = Y POSITION OF THE ICON IMAGE
;      WORD [transp] = 0 (For full transparency)
;                      1 (For semi-transparency)
; OUT: NOTHING (REGISTERS PRESERVED)
;-------------------------------------------
;NOTE:-
; XTREME IMAGE TYPE
;     B = 000  ; Black
;     N = 001  ; Navy blue
;     G = 002  ; Dark green
;     A = 003  ; Aqua
;     R = 004  ; Dark red
;     P = 005  ; Purple
;     Y = 006  ; Dark yellow
;     w = 007  ; Dull white
;     S = 008  ; silver
;     b = 009  ; light blue
;     g = 010  ; light green
;     a = 011  ; light aqua   
;     r = 012  ; light red
;     p = 013  ; light purple
;     y = 014  ; light yellow
;     W = 015  ; bright white
;     X = ( Transparent)
;     1 = Newline
;     $ = Image End
; ------------------------------------
mov bx, [xpos]
mov word [constant], bx
mov bx, 0




.loop:
lodsb
cmp al, 'B'
je .black
cmp al, 'N'
je .navy
cmp al, 'G'
je .dark_green
cmp al, 'A'
je .aqua
cmp al, 'R'
je .dark_red
cmp al, 'P'
je .purple
cmp al, 'Y'
je .dark_yellow
cmp al, 'w'
je .dull_white
cmp al, 'S'
je .silver
cmp al, 'b'
je .light_blue
cmp al, 'g'
je .light_green
cmp al, 'a'
je .light_aqua
cmp al, 'r'
je .light_red
cmp al, 'p'
je .light_purple
cmp al, 'y'
je .light_yellow
cmp al, 'W'
je .bright_white
cmp al, 1
je .new_line
cmp al, '$'
je .end
cmp al, 'X'
je .ignore
jmp .loop

.plot_pixel:
mov al, [color]
mov cx, [xpos]
mov dx, [ypos]
mov ah, 0x0c
int 10h
jmp .loop

.black:
add word [xpos], 1
mov word [color], 000
jmp .plot_pixel

.navy:
add word [xpos], 1
mov word [color], 001
jmp .plot_pixel

.dark_green:
add word [xpos], 1
mov word [color], 002
jmp .plot_pixel

.aqua:
add word [xpos], 1
mov word [color], 003
jmp .plot_pixel

.dark_red:
add word [xpos], 1
mov word [color], 004
jmp .plot_pixel

.purple:
add word [xpos], 1
mov word [color], 005
jmp .plot_pixel

.dark_yellow:
add word [xpos], 1
mov word [color], 006 
jmp .plot_pixel

.dull_white:
add word [xpos], 1
mov word [color], 007
jmp .plot_pixel

.silver:
add word [xpos], 1
mov word [color], 008
jmp .plot_pixel

.light_blue:
add word [xpos], 1
mov word [color], 009
jmp .plot_pixel

.light_green:
add word [xpos], 1
mov word [color], 010
jmp .plot_pixel

.light_aqua:
add word [xpos], 1
mov word [color], 011
jmp .plot_pixel

.light_red:
add word [xpos], 1
mov word [color], 12
jmp .plot_pixel

.light_purple:
add word [xpos], 1
mov word [color], 13
jmp .plot_pixel

.light_yellow:
add word [xpos], 1
mov word [color], 14
jmp .plot_pixel

.bright_white:
add word [xpos], 1
mov word [color], 15
jmp .plot_pixel

.ignore:
cmp word [transp], 0
je .transp0
cmp word [transp], 1
je .transp1
jmp .transp0

.transp0:
add word [xpos], 1
jmp .loop

.transp1:
mov cx, [xpos]
mov dx, [ypos]
xor ax, ax
mov ah, 0Dh
int 10h
add al, 8
jmp .plot_pixel

.new_line:
mov word [xpos], 0
add word [ypos], 1
mov bx, [constant]
mov word [xpos], bx
mov bx, 0
jmp .loop

.end:
mov word [xpos], 0
mov word [ypos], 0
mov word [constant], 0
mov si, 0
mov ax, 0
ret




