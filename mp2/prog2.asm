; Alnguyn2 - MP2   
;
; Description:
;       This program implements a postfix expression calculator using a stack.
;       The calculator is able to add, subtract, multiply, divide, and do exponents
;       using only positive integers 0-9. The expression should be of the form 
;       ab+, ab-, ab/, etc..., where the expression follows integers 'a' and 'b'.
;       The value of the expression will be printed out in hexidecimal.
;
;
;
.ORIG x3000
;Parse the input until '=' sign
;operands get pushed onto the stack
;any operators will call the respective functions, perform the task then push the results back onto the stack
READ_INPUT
	IN								; Store and echo input
	LD	R2, SPACE_ASCII				; Load spaces first
	ADD R2, R2, R0					; If R2 == 0, read another input
	BRz	READ_INPUT

CHECK_INPUT
	LD 	R2, NINE_ASCII				; Check if it's a number
	ADD R2, R2, R0					
	BRnz OPERAND					; If it's a number, push to stack

	LD 	R2, EQUAL_ASCII				; Check if '='
	ADD R2, R2, R0
	BRz	EVALUATE

	LD 	R2, PLUS_ASCII				; Check if '+'
	ADD R2, R2, R0
	BRz	PLUS

	LD 	R2, MINUS_ASCII				; Check if '-'
	ADD R2, R2, R0
	BRz	MIN	

	LD 	R2, MULT_ASCII				; Check if '*'
	ADD R2, R2, R0
	BRz	MUL

	LD 	R2, DIV_ASCII				; Check if '/'
	ADD R2, R2, R0
	BRz	DIV

	; If it is none of the above, it's an invalid input
	LEA R0, INVALID_STRING
	PUTS
	LD 	R0, NEWLINE_CHAR
	OUT
	BRnzp READ_INPUT	

OPERAND
	HALT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
;
;R0- hex-value of R3
PRINT_HEX
    

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
	AND R0, R0, #0		; Clear R0
	ADD	R0, R3, R4		; R0 = R3 + R4
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	AND R0, R0, #0		; Clear R0
	NOT R4, R4			; NOT(R4) + 1 to get negative of R4 
	ADD R4, R4, #1		;
	ADD R0, R3, R4		; R0 = R3 - R4
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
	AND R0, R0, #0		; Clear R0
	LDR R0, R3, #0		; Move R3 into R0
MUL_START
	ADD R0, R3, #0		; R0 += R3
	ADD R4, R4, #-1		; decrement R4
	BRp MUL_START		; if R4 == 0, done
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


;ASCII Values
;
EQUAL_ASCII		.FILL	#-61		; '='
MULT_ASCII		.FILL	#-42		; '*'
PLUS_ASCII		.FILL	#-43		; '+'
MINUS_ASCII		.FILL	#-45		; '-'
DIV_ASCII		.FILL	#-47		; '/'
SPACE_ASCII		.FILL	#-32		; ' '
X_ASCII			.FILL	#-120		; 'x'
NINE_ASCII		.FILL	#-57		; '9'

INVALID_STRING	.STRINGZ "Invalid Expression"
NEWLINE_CHAR	.FILL	x000A		; '\n'


.END