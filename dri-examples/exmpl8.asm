	maclib	z80
	org	0
BUFFER:	db	0
DDPB:	db	0
DPBL:	db	0
	LXIX	BUFFER+DDPB-DPBL; DPB TABLE
	end
