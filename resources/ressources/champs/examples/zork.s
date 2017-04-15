.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live

test:	and r10, r1, r2
		sti r1, %:l2, %1
