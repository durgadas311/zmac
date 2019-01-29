	org	0
	jmp	0

rdrc	equ	00$00$11$00b	;RDR: iobyte field
is	equ	2 SHL 2		;input status code

rdrst:	lxi	d,rdrc SHL 8 + is
	end
