	.file	"mult.cpp"
	.section	.text.unlikely,"x"
LCOLDB0:
	.text
LHOTB0:
	.p2align 4,,15
	.globl	__Z4multv
	.def	__Z4multv;	.scl	2;	.type	32;	.endef
__Z4multv:
LFB0:
	.cfi_startproc
	rep ret
	.cfi_endproc
LFE0:
	.section	.text.unlikely,"x"
LCOLDE0:
	.text
LHOTE0:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section	.text.unlikely,"x"
LCOLDB1:
	.section	.text.startup,"x"
LHOTB1:
	.p2align 4,,15
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	call	___main
	xorl	%eax, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE1:
	.section	.text.unlikely,"x"
LCOLDE1:
	.section	.text.startup,"x"
LHOTE1:
	.ident	"GCC: (i686-posix-dwarf-rev1, Built by MinGW-W64 project) 4.9.2"
