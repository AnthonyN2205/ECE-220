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
;
;
;
;R3 - operand
	AND R3, R3, #0
;R4 - operand
	AND R4, R4, #0
;
;

READ_INPUT
	IN								; Store and echo input
	LD	R2, SPACE_ASCII				; Load spaces first
	ADD R2, R2, R0					; If R2 == 0, read another input
	BRz	READ_INPUT

PLUS_CHECK
	LD 	R2, PLUS_ASCII				; Check if '+'
	ADD R2, R2, R0
	BRnp	MINUS_CHECK				; check for next possible operator

	; operator is '+' so pop two values into R3 & R4 then call PLUS
	AND R3, R3, #0
	AND R4, R4, #0

	JSR	POP
	ADD R3, R3, R0					; move 1st operand into register
	ADD R5, R5, #0					; Check underflow
	BRp	INVALID_INPUT				; if R5 == 0, failure
	JSR POP
	ADD R4, R4, R0					; move 2nd operand into register
	ADD R5, R5, #0					; Check underflow
	BRp	INVALID_INPUT			

	AND R0, R0, #0					; Clear R0
	JSR PLUS						; R3 & R4 loaded, call subroutine
	JSR PUSH
	BRnzp READ_INPUT				; push result onto stack, read another input

MINUS_CHECK
	LD 	R2, MINUS_ASCII				; Check if '-'
	ADD R2, R2, R0
	BRnp MULTIPLY_CHECK

	; operator is '-' :: Same as PLUS
	AND R3, R3, #0
	AND R4, R4, #0

	JSR	POP
	ADD R4, R4, R0					; POP second operand 
	ADD R5, R5, #0					
	BRp	INVALID_INPUT				
	JSR POP
	ADD R3, R3, R0					; POP first operand
	ADD R5, R5, #0					
	BRp	INVALID_INPUT			

	AND R0, R0, #0					; Clear R0
	JSR MIN							; R3 & R4 loaded, call subroutine
	JSR PUSH
	BRnzp READ_INPUT				; push result onto stack, read another input


MULTIPLY_CHECK
	LD 	R2, MULT_ASCII				; Check if '*'
	ADD R2, R2, R0
	BRnp DIVIDE_CHECK

	; operator is '*' :: Same as PLUS
	AND R3, R3, #0
	AND R4, R4, #0

	JSR	POP
	ADD R3, R3, R0					
	ADD R5, R5, #0					
	BRp	INVALID_INPUT				
	JSR POP
	ADD R4, R4, R0					
	ADD R5, R5, #0					
	BRp	INVALID_INPUT			

	AND R0, R0, #0					; Clear R0
	JSR MUL							; R3 & R4 loaded, call subroutine
	JSR PUSH
	BRnzp READ_INPUT				; push result onto stack, read another input

DIVIDE_CHECK
	LD 	R2, DIV_ASCII				; Check if '/'
	ADD R2, R2, R0
	BRnp EXP_CHECK

	; operator is '/' :: Same as PLUS
	AND R3, R3, #0
	AND R4, R4, #0

	JSR	POP
	ADD R4, R4, R0					; POP second operand
	ADD R5, R5, #0					
	BRp	INVALID_INPUT				
	JSR POP
	ADD R3, R3, R0					; POP first operand
	ADD R5, R5, #0					
	BRp	INVALID_INPUT			

	AND R0, R0, #0					; Clear R0
	JSR DIV							; R3 & R4 loaded, call subroutine
	JSR PUSH
	BRnzp READ_INPUT				; push result onto stack, read another input

EXP_CHECK
	LD 	R2, EXP_ASCII				; Check if '^'
	ADD R2, R2, R0
	BRnp EQUAL_CHECK

	; operator is '^' :: Same as PLUS
	AND R3, R3, #0
	AND R4, R4, #0

	JSR	POP
	ADD R4, R4, R0					; POP second operand
	ADD R5, R5, #0					
	BRp	INVALID_INPUT				
	JSR POP
	ADD R3, R3, R0					; POP first operand
	ADD R5, R5, #0					
	BRp	INVALID_INPUT			

	AND R0, R0, #0					; Clear R0
	JSR EXP							; R3 & R4 loaded, call subroutine
	JSR PUSH
	BRnzp READ_INPUT				; push result onto stack, read another input

EQUAL_CHECK
	LD 	R2, EQUAL_ASCII				; Check if '='
	ADD R2, R2, R0
	BRnp NUM_CHECK
	JSR EVALUATE					; Call evalauate subroutine
									; Should not return here since we're done

; Since we know input must be (0-9) or any of the operations or space, it must be a number if it reached here. We simply push the number
NUM_CHECK
	JSR CONVERT_DEC					; convert R0 to decimal value before pushing
	JSR PUSH						; PUSH value onto stack
	BRnzp READ_INPUT				; read another input after pushing to stack


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Converts hex(R0) to dec(R0)
; 
; Input: hex(R0)
;
; Output: dec(R0)
CONVERT_DEC
	LD R3, DEC_CONST				; load R3 with a const to convert hex->dec
	ADD R0, R0, R3					; convert R0 to dec
	RET	


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
;
;R0- hex-value of R3
PRINT_HEX
	AND R3, R3, #0
	ADD R3, R3, R0
    LD R1, FOUR_COUNT				; R1 = 4 digit counter
	LD R0, X_ASCII					
	OUT								; print 'x' for hex
	AND R0, R0, #0					; clear R0

FOR_EVERY_DIGIT
	LD R2, FOUR_COUNT				; R2 = 4 bit counter

FOR_EVERY_BIT
	ADD R0, R0, R0					; left shift both hex value & value we're generating
	ADD R3, R3, #0					; Check MSB, if 1, add 1 to R0
	BRzp #1						
	ADD R0, R0, #1
	ADD R3, R3, R3
	ADD R2, R2, #-1					; decrement bit counter
	BRz	CHECK_DIGIT					; if done with 4 bits, output the digit
	BRnzp FOR_EVERY_BIT				; otherwise, keep going

CHECK_DIGIT
	AND R4, R4, #0					; Clear R4
	ADD R4, R0, #-9					; check if it's a number
	BRp	LETTER

NUMBER
	LD R4, O_ASCII					; Load '0' offset
	ADD R0, R0, R4					; Digit + '0'
	BRnzp PRINT_DIGIT

LETTER
	LD R4, A_ASCII					; Load 'A' offset
	ADD R0, R0, R4					; Add [A:F] offset to R0

PRINT_DIGIT
	OUT								; output the digit in R0
	AND R0, R0, #0					; clear R0 for next digit
	ADD R1, R1, #-1					; decrement digit counter
	BRz FINISH
	BRnzp FOR_EVERY_DIGIT


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R5 - current numerical output
;
;
EVALUATE
	JSR	POP							; POP final answer to load into R5
	ST R0, OP_SAVE					; save final answer to get later

	; ; Stack should be empty, if not, invalid expression
	LD	R1, STACK_TOP				
	LD 	R2, STACK_START
	NOT R1, R1						; TOP - Bottom =? 0
	ADD R1, R1, #1
	ADD R2, R2, R1
	BRnp INVALID_INPUT				

	JSR PUSH						; PUSH final answer back to stack to print
	JSR PRINT_HEX


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
	ADD	R0, R3, R4		; R0 = R3 + R4
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
	NOT R4, R4			; NOT(R4) + 1 to get negative of R4 
	ADD R4, R4, #1		;
	ADD R0, R3, R4		; R0 = R3 - R4
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
	ADD R0, R0, R3		; R0 += R3
	ADD R4, R4, #-1		; decrement R4
	BRp MUL		; if R4 == 0, done
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
	NOT R4, R4					; Complment of second operand
	ADD R4, R4, #1
DIV_START
	ADD R3, R3, R4				; R3 -= R4
	BRn DIV_END					; Keep R0 >= 0
	ADD R0, R0, #1				; increment quotient
	BRnzp DIV_START

DIV_END
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 :: Multipling R3 by R3, R4 times
;out R0
;
;		****R6 is modified****
EXP
	ST R7, SAVE_R7		; Save R7 to return to first caller
	ST R3, OP_SAVE		; Save operand to restore
	AND R6, R6, #0		
	ADD R6, R6, R4		; Use R4 as a counter since it is modified in MUL
	ADD R6, R6, #-1		; Off-by-1 error
	AND R4, R4, #0
	ADD R4, R4, R3		; Move first operand into second operand

EXP_START
	ADD R6, R6, #0		; if R4 == 0 done
	BRz	EXP_DONE

	JSR	MUL				; Multiply R3*R3
	LD R4, OP_SAVE		; Restore second operand
	ADD R6, R6, #-1		; decrement counter
	BRnzp EXP_START	

EXP_DONE
	LD R7, SAVE_R7		; Restore R7
	RET					; return from first call

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Prints "Invalid Expression"
;
INVALID_INPUT
	; If it is none of the above, it's an invalid input
	LEA R0, INVALID_STRING
	PUTS
	LD 	R0, NEWLINE_CHAR
	OUT
	HALT
	BRnzp READ_INPUT	


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
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


FINISH
	LD R5, OP_SAVE					; Place final answer into R5
	HALT


;ASCII Values
;
EQUAL_ASCII		.FILL	#-61		; '='
MULT_ASCII		.FILL	#-42		; '*'
PLUS_ASCII		.FILL	#-43		; '+'
MINUS_ASCII		.FILL	#-45		; '-'
DIV_ASCII		.FILL	#-47		; '/'
SPACE_ASCII		.FILL	#-32		; ' '
EXP_ASCII		.FILL	#-94		; '^'
X_ASCII			.FILL	x0078		; 'x'

A_ASCII			.FILL	x0037		; Hex letter offset
O_ASCII			.FILL   x0030		; '0' offset
NINE_ASCII		.FILL	#-57		; '9'
DEC_CONST		.FILL	#-48		; value for 0 to convert to decimal
FOUR_COUNT		.FILL 	#4			; value 4 for counters

SAVE_R7			.BLKW	#1			; Save R7 for calling nested subroutines
OP_SAVE			.BLKW	#1			; Save value for EXP/DIV

INVALID_STRING	.STRINGZ "Invalid Expression"
NEWLINE_CHAR	.FILL	x000A		; '\n'


.END