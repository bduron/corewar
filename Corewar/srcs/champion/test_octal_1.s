#by cpoulet, classic imp

.name		"fork_hacking"
.comment	"cheating like a pinson..."

	ld %255, r1
	or	%0, -7, r1
	st r1, 50
