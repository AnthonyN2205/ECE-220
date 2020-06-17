; Alnguyn2 - MP1
; 
; Description:
;
; This program will take a string and create a histogram based on the character counts of the string.
; The histogram will then be processed and output to the screen based on non-alphabetic characters and
; alphabetic characters. To print the histogram, the program uses two loops as described below in the PRINT_HIST
; function. Each character count consist of 16-bit values. Each bit is broken into 4-bit chunks that
; are processed and converted to a hex value.
;
;



; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming video lecture, we will discuss 
;  how to prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** Submit a working version to Gradescope  **



	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments


; Description is at the very top
;
; R0 - Will be used to load values for output and hold 4-bit digit
; R1 - Contains NUM_BINS(27)
; R2 - Contain ASCII Char starting at @ and used for iterating through @ABC...WXYZ
; R3 - Contains digit count
; R4 - Histogram address
; R5 - temp
; R6 - bit counter

; @ABC...WXYZ
; Output format:  ASCII_Char h3h2h1h0
; 
; PSEUDOCODE:
;
; for every NUM_BIN/ASCII char:
;	print ascii character + space
;
; 	for every digit(4):
;		for 0 to 3:
;			if (MSB == 1)
;				add 1 to new digit
;			else
;				shift both digit and histogram count left
;
;		check if the digit belongs in [0:9] or [A:F] hex values
;		print digit
;
; 	print newline
;


	; initialize Registers
	AND R0, R0, #0		; Clear R0
	LD R1, NUM_BINS		; R1 <- 27
	LD R2, AT_ASCII		; R2 <- '@'
	AND R3, R3, #0		; Clear R3
	ADD R3, R3, #4		; R3 <- 4
	LD R4, HIST_ADDR	; R4 <- Start of Histogram
	AND R5, R5, #0		; Clear R5
	AND R6, R6, #0
	ADD R6, R6, #4		; R6 <- 4

; Start outter loop
FOR_EVERY_CHAR
	ADD R1, R1, #0		; if (R1 == 0) done
	BRz DONE
	ADD R0, R0, R2		; R0 <- R2
	OUT					
	LD R0, SPACE		; load space character to print
	OUT
	LDR R5, R4, #0		; Load Histogram count into R5

; Start inner loop
FOR_EVERY_DIGIT
	AND R0, R0, #0		; Clear R0
	ADD R3, R3, #0		; if (R3 == 0) done with character
	BRz	NEXT_CHAR
	BRnzp GET_DIGIT

; Now R0 has a 4-bit digit in least sig 4-bits
CHECK_DIGIT			
	AND R6, R6, #0		; Clear R7
	ADD R6, R0, #-9		; if R6 < 0 [0:9], else [A:F]
	BRnz NUM

LETTER
	LD R6, A_ASCII		; Load 'A' offset
	ADD R0, R0, R6		; Letters are [10:15] so you have to offset from ('A' - 10) + digit where ('A' - #10) = 0x37
	BRnzp PRINT_DIGIT

NUM
	LD R6, O_ASCII		; Load '0' offset
	ADD R0, R0, R6		; digit + '0'


; End of inner loop
PRINT_DIGIT
	OUT					; print the digit

	LD R6, FOUR			; Reset 4-bit count
	ADD R3, R3, #-1		; decrement R3 and go to next digit
	BRnzp FOR_EVERY_DIGIT 


; End of outter loop
NEXT_CHAR
	LD 	R0, NEWLINE		; load newline character to print
	OUT

	ADD R1, R1, #-1		; decrement R1
	ADD R2, R2, #1		; move to next ascii value
	ADD R4, R4, #1		; increment histogram pointer to next ascii count
	AND R0, R0, #0		; Clear R0
	LD R3, FOUR			; Reset Digit counter
	BRnzp FOR_EVERY_CHAR	; keep going until all characters are done


; Helper function to get 4-bit digits
GET_DIGIT
	ADD R6, R6, #0		; if R6 == 0, done
	BRz CHECK_DIGIT

	ADD R0, R0, R0		; Left shift R0
	ADD R5, R5, #0		; check MSB
	BRzp #1				; if MSB == 0, skip adding 1 to R0
	ADD R0, R0, #1		; Add 1 to LSB
	ADD R5, R5, R5		; Left shift R5
	ADD R6, R6, #-1		; decrement R6
	BRnzp GET_DIGIT


DONE	HALT			; done




; data for printing hist
NEWLINE		.FILL x000A ; newline char
SPACE		.FILL x0020 ; space char
AT_ASCII	.FILL x0040 ; '@'
A_ASCII		.FILL x0037 ; Offset for hex letters
O_ASCII		.FILL x0030 ; '0'
GET_MSB		.FILL xF000 ; 1111 00...
FOUR		.FILL #4


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
