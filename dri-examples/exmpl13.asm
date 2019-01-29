calcdpb macro ?spt0,?spb0,?dsm0,?drm0,?off0,?pss0,?flg

?bsm	set	?spb0-1 
?exm	set	?bsm shr 3
	if ?dsm0 gt 256
?exm	set	?exm shr 1
	endif
	
	if not NUL ?flg
?exm	set	?exm shr 1
	endif
	
?cks	set	?drm0/4 
	
?bsh	set	0
?@	set	?spb0	
	rept 8
?@	set	?@ shr 1
	if ?@ eq 0 
	exitm
	endif

?bsh	set	?bsh+1	
	endm
?al0	set	0
	rept (?cks+?bsm)/?spb0
?al0	set	(?al0 shr 1) or 10000000$00000000b
	endm
?al1	set	low ?al0
?al0	set	high ?al0

?psh	set	0
?psm	set	0
?@	set	high ?pss0
	rept 8
	if ?@ eq 0 
	exitm
	endif
?psh	set	?psh+1	
?psm	set	(?psm shl 1) or 1 
?@	set	?@ shr 1
	endm

	dw	?spt0	
	db	?bsh,?bsm,?exm
	dw	?dsm0-1,?drm0-1
	db	?al0,?al1
	dw	?cks,?off0
	db	?psh,?psm

	endm


	cseg
	org	0
STD8:	calcdpb 26, 8,243, 64,2,128
	end
