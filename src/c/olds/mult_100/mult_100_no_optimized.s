	.file	"mult_100.cpp"
	.text
	.globl	__Z8mult_100v
	.def	__Z8mult_100v;	.scl	2;	.type	32;	.endef
__Z8mult_100v:
LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$5, -8(%ebp)
	movl	$10, -12(%ebp)
	movl	$0, -4(%ebp)
	jmp	L2
L3:
	movl	-8(%ebp), %eax
	imull	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
	addl	$1, -4(%ebp)
L2:
	cmpl	$99999, -4(%ebp)
	jbe	L3
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE1:
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	call	___main
	call	__Z8mult_100v
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2:
	.ident	"GCC: (i686-posix-dwarf-rev1, Built by MinGW-W64 project) 4.9.2"
