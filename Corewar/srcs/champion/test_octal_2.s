#by cpoulet, classic imp

.name		"fork_hacking"
.comment	"cheating like a pinson..."

		ld	%525552, r1 
		fork %:modif
		add r1, r1, r2
modif:	st r1, -7
