#by cpoulet, classic imp

.name		"fork_hacking"
.comment	"cheating like a pinson..."

		ld	%0, r1
		zjmp %-512
		st r1, 40
		st r2, 50
