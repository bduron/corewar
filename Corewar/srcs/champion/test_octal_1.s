#by cpoulet, classic imp

.name		"fork_hacking"
.comment	"cheating like a pinson..."

	ld %255, r1
	and	%4294967295, 7561151, r1
	st r1, 50
