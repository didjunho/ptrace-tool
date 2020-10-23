	.file	"read.cpp"
# GNU C++14 (Ubuntu 7.4.0-1ubuntu1~18.04.1) version 7.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 7.4.0, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.19-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu -D_GNU_SOURCE read.cpp
# -mtune=generic -march=x86-64 -O2 -fverbose-asm -fstack-protector-strong
# -Wformat -Wformat-security
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -falign-labels -fasynchronous-unwind-tables -fauto-inc-dec
# -fbranch-count-reg -fcaller-saves -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcode-hoisting -fcombine-stack-adjustments -fcommon
# -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
# -fdefer-pop -fdelete-null-pointer-checks -fdevirtualize
# -fdevirtualize-speculatively -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -fexceptions -fexpensive-optimizations
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse
# -fgcse-lm -fgnu-runtime -fgnu-unique -fguess-branch-probability
# -fhoist-adjacent-loads -fident -fif-conversion -fif-conversion2
# -findirect-inlining -finline -finline-atomics
# -finline-functions-called-once -finline-small-functions -fipa-bit-cp
# -fipa-cp -fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-profile
# -fipa-pure-const -fipa-ra -fipa-reference -fipa-sra -fipa-vrp
# -fira-hoist-pressure -fira-share-save-slots -fira-share-spill-slots
# -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
# -fmath-errno -fmerge-constants -fmerge-debug-strings
# -fmove-loop-invariants -fomit-frame-pointer -foptimize-sibling-calls
# -foptimize-strlen -fpartial-inlining -fpeephole -fpeephole2 -fplt
# -fprefetch-loop-arrays -free -freg-struct-return -freorder-blocks
# -freorder-functions -frerun-cse-after-loop
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fschedule-insns2
# -fsemantic-interposition -fshow-column -fshrink-wrap
# -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
# -fsplit-wide-types -fssa-backprop -fssa-phiopt -fstack-protector-strong
# -fstdarg-opt -fstore-merging -fstrict-aliasing -fstrict-overflow
# -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
# -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
# -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim
# -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
# -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr
# -ftree-sra -ftree-switch-conversion -ftree-tail-merge -ftree-ter
# -ftree-vrp -funit-at-a-time -funwind-tables -fverbose-asm
# -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mfxsr
# -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
# -msse -msse2 -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"reading.txt"
.LC1:
	.string	"SENSOR: "
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB2926:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2926
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx	#
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$552, %rsp	#,
	.cfi_def_cfa_offset 576
# read.cpp:25:     ifstream inFile;
	leaq	16(%rsp), %rbx	#, tmp103
# read.cpp:24: int main(int argc, char** argv) {
	movq	%fs:40, %rax	#, tmp104
	movq	%rax, 536(%rsp)	# tmp104, D.68371
	xorl	%eax, %eax	# tmp104
# read.cpp:25:     ifstream inFile;
	movq	%rbx, %rdi	# tmp103,
.LEHB0:
	call	_ZNSt14basic_ifstreamIcSt11char_traitsIcEEC1Ev@PLT	#
.LEHE0:
# read.cpp:27:     inFile.open("reading.txt");
	leaq	.LC0(%rip), %rsi	#,
	movl	$8, %edx	#,
	movq	%rbx, %rdi	# tmp103,
# read.cpp:26:     long sensor_val = 9999;
	movq	$9999, 8(%rsp)	#, sensor_val
.LEHB1:
# read.cpp:27:     inFile.open("reading.txt");
	call	_ZNSt14basic_ifstreamIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode@PLT	#
# /usr/include/c++/7/istream:187:       { return _M_extract(__n); }
	leaq	8(%rsp), %rsi	#, tmp95
	movq	%rbx, %rdi	# tmp103,
	call	_ZNSi10_M_extractIlEERSiRT_@PLT	#
# read.cpp:29:     inFile.close();
	movq	%rbx, %rdi	# tmp103,
	call	_ZNSt14basic_ifstreamIcSt11char_traitsIcEE5closeEv@PLT	#
# /usr/include/c++/7/ostream:561: 	__ostream_insert(__out, __s,
	leaq	.LC1(%rip), %rsi	#,
	leaq	_ZSt4cout(%rip), %rdi	#,
	movl	$8, %edx	#,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /usr/include/c++/7/ostream:167:       { return _M_insert(__n); }
	movq	8(%rsp), %rsi	# sensor_val,
	leaq	_ZSt4cout(%rip), %rdi	#,
	call	_ZNSo9_M_insertIlEERSoT_@PLT	#
# /usr/include/c++/7/ostream:113: 	return __pf(*this);
	movq	%rax, %rdi	# _12,
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@PLT	#
.LEHE1:
# read.cpp:25:     ifstream inFile;
	movq	%rbx, %rdi	# tmp103,
	call	_ZNSt14basic_ifstreamIcSt11char_traitsIcEED1Ev@PLT	#
# read.cpp:32: }
	xorl	%eax, %eax	#
	movq	536(%rsp), %rcx	# D.68371, tmp105
	xorq	%fs:40, %rcx	#, tmp105
	jne	.L8	#,
	addq	$552, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx	#
	.cfi_def_cfa_offset 16
	popq	%rbp	#
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	call	__stack_chk_fail@PLT	#
.L4:
	movq	%rax, %rbp	#, tmp102
# read.cpp:25:     ifstream inFile;
	movq	%rbx, %rdi	# tmp103,
	call	_ZNSt14basic_ifstreamIcSt11char_traitsIcEED1Ev@PLT	#
	movq	%rbp, %rdi	# tmp102,
.LEHB2:
	call	_Unwind_Resume@PLT	#
.LEHE2:
	.cfi_endproc
.LFE2926:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2926:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2926-.LLSDACSB2926
.LLSDACSB2926:
	.uleb128 .LEHB0-.LFB2926
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB2926
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L4-.LFB2926
	.uleb128 0
	.uleb128 .LEHB2-.LFB2926
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE2926:
	.section	.text.startup
	.size	main, .-main
	.section	.rodata.str1.1
.LC2:
	.string	"BYTES READ: %d\n"
.LC3:
	.string	"\n"
	.text
	.p2align 4,,15
	.globl	_Z5main2iPPc
	.type	_Z5main2iPPc, @function
_Z5main2iPPc:
.LFB2927:
	.cfi_startproc
	pushq	%rbx	#
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
# /usr/include/x86_64-linux-gnu/bits/fcntl2.h:53:       return __open_alias (__path, __oflag, __va_arg_pack ());
	leaq	.LC0(%rip), %rdi	#,
	xorl	%esi, %esi	#
# read.cpp:34: int main2(int argc, char** argv) {
	subq	$8208, %rsp	#,
	.cfi_def_cfa_offset 8224
# read.cpp:34: int main2(int argc, char** argv) {
	movq	%fs:40, %rax	#, tmp95
	movq	%rax, 8200(%rsp)	# tmp95, D.68377
	xorl	%eax, %eax	# tmp95
# /usr/include/x86_64-linux-gnu/bits/unistd.h:44:   return __read_alias (__fd, __buf, __nbytes);
	movq	%rsp, %rbx	#, tmp92
# /usr/include/x86_64-linux-gnu/bits/fcntl2.h:53:       return __open_alias (__path, __oflag, __va_arg_pack ());
	call	open@PLT	#
# /usr/include/x86_64-linux-gnu/bits/unistd.h:44:   return __read_alias (__fd, __buf, __nbytes);
	movl	$8191, %edx	#,
	movq	%rbx, %rsi	# tmp92,
	movl	%eax, %edi	# _5,
	call	read@PLT	#
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:104:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC2(%rip), %rsi	#,
	movq	%rax, %rdx	# _6,
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	call	__printf_chk@PLT	#
# read.cpp:38:   write(0, sensor_val, 4);
	xorl	%edi, %edi	#
	movl	$4, %edx	#,
	movq	%rbx, %rsi	# tmp92,
	call	write@PLT	#
# read.cpp:39:   write(0,"\n",1);
	leaq	.LC3(%rip), %rsi	#,
	xorl	%edi, %edi	#
	movl	$1, %edx	#,
	call	write@PLT	#
# read.cpp:41: }
	movq	8200(%rsp), %rcx	# D.68377, tmp96
	xorq	%fs:40, %rcx	#, tmp96
	jne	.L12	#,
	addq	$8208, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax	#
	popq	%rbx	#
	.cfi_def_cfa_offset 8
	ret
.L12:
	.cfi_restore_state
	call	__stack_chk_fail@PLT	#
	.cfi_endproc
.LFE2927:
	.size	_Z5main2iPPc, .-_Z5main2iPPc
	.section	.text.startup
	.p2align 4,,15
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB3492:
	.cfi_startproc
# /usr/include/c++/7/iostream:74:   static ios_base::Init __ioinit;
	leaq	_ZStL8__ioinit(%rip), %rdi	#,
# read.cpp:41: }
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 16
# /usr/include/c++/7/iostream:74:   static ios_base::Init __ioinit;
	call	_ZNSt8ios_base4InitC1Ev@PLT	#
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi	#,
	leaq	__dso_handle(%rip), %rdx	#,
	leaq	_ZStL8__ioinit(%rip), %rsi	#,
# read.cpp:41: }
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 8
# /usr/include/c++/7/iostream:74:   static ios_base::Init __ioinit;
	jmp	__cxa_atexit@PLT	#
	.cfi_endproc
.LFE3492:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
