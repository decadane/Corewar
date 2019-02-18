.name "noob"
.comment "om nom nom"

		ld		%4, r4
		ld		%20, r6
		ld		%64, r14
		st		r1, 13
		ld		%0, r3

cycl:	live	%1
		ldi		%-12, r3, r2
		sti		r2, %384 ,r3
		add		r3, r4, r3
		add		r3, r6, r15
		and		r15, r14, r16
		zjmp	%:cycl

