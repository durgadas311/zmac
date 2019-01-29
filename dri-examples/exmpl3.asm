TRUE    equ     0FFFFh
FALSE   equ     not TRUE
	org	0
	mvi	a,FALSE
	cpi	TRUE
	end
