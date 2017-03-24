#by cpoulet, classic imp
#MOD -400: 1879375472-440
#MOD -300: 1879375572-340
#MOD -200: 1879375672-240
#MOD 050: 1879310386-15
#MOD 070: 1879310406-35
#MOD 100: 1879310436-65
#MOD 200: 1879310536-165
#MOD 300: 1879310636-265
#MOD 350: 1879310686-315
#MOD 400: 1879310736-365
#MOD 425: 1879310761-390
#MOD 450: 1879310786-415

.name		"mychicken"
.comment	"one is good, two is better..."

		sti r1, %:live, %1
		ld	%1, r1
		ld	%0, r2
		ld	%1879310786, r3
		ld	%65540, r16
		ld	60, r4
		ld	59, r5
		ld	58, r6
		ld	57, r7
		ld	56, r8
		ld	55, r9
		ld	54, r10
		ld	53, r11
		ld	52, r12
		ld	51, r13
		ld	50, r14
		ld	49, r15
loop:	add r16, r3, r3
		st r4, 450
		st r3, -4
		and	r3, %1048576, r1
		zjmp %:loop
live:	live %1
		ld	%1879310786, r3
		ld %0, r2
		zjmp %415
