#by cpoulet, classic imp

.name		"fork_hacking"
.comment	"cheating like a pinson..."

		and r1, r2, r3  #54
		and %0, r2, r3	#94
		and 0, r2, r3	#d4
		and r1, %0, r3	#64
		and %0, %0, r3	#a4
		and 0, %0, r3	#e4
		and r1, 0, r3	#74
		and %0, 0, r3	#b4
		and 0, 0, r3	#f4
		st	r3, 25
