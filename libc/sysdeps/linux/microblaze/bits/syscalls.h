#ifndef _BITS_SYSCALLS_H
#define _BITS_SYSCALLS_H
#ifndef _SYSCALL_H
# error "Never use <bits/syscalls.h> directly; include <sys/syscall.h> instead."
#endif


#ifndef __ASSEMBLER__

#include <errno.h>

#define INTERNAL_SYSCALL_NCS(name, err, nr, args...)			\
(__extension__ \
	({								\
		register int __ret __asm__("r3");			\
		register int _scno __asm__("r12") = name;		\
		LOAD_ARGS_##nr (args);					\
		__asm__ __volatile__("brki	r14, 0x8"		\
			      : "=r" (__ret)				\
			      :  "r"(_scno) ASM_ARGS_##nr		\
			      : __SYSCALL_CLOBBERS );			\
		__ret;							\
	}) \
)
#define INTERNAL_SYSCALL_ERROR_P(val, err)		\
	((unsigned int)(val) >= 0xfffff001U)

#define LOAD_ARGS_0() do { } while(0)
#define ASM_ARGS_0
#define LOAD_ARGS_1(a1)				\
	register int _a1 __asm__("r5") = (int)(a1);	\
	LOAD_ARGS_0()
#define ASM_ARGS_1	ASM_ARGS_0, "r"(_a1)
#define LOAD_ARGS_2(a1, a2)				\
	register int _a2 __asm__("r6") = (int)(a2);	\
	LOAD_ARGS_1(a1)
#define ASM_ARGS_2	ASM_ARGS_1, "r"(_a2)
#define LOAD_ARGS_3(a1, a2, a3)				\
	register int _a3 __asm__("r7") = (int)(a3);	\
	LOAD_ARGS_2(a1, a2)
#define ASM_ARGS_3	ASM_ARGS_2, "r"(_a3)
#define LOAD_ARGS_4(a1, a2, a3, a4)			\
	register int _a4 __asm__("r8") = (int)(a4);	\
	LOAD_ARGS_3(a1, a2, a3)
#define ASM_ARGS_4	ASM_ARGS_3, "r"(_a4)
#define LOAD_ARGS_5(a1, a2, a3, a4, a5)			\
	register int _a5 __asm__("r9") = (int)(a5);	\
	LOAD_ARGS_4(a1, a2, a3, a4)
#define ASM_ARGS_5	ASM_ARGS_4, "r"(_a5)
#define LOAD_ARGS_6(a1, a2, a3, a4, a5, a6)		\
	register int _a6 __asm__("r10") = (int)(a6);	\
	LOAD_ARGS_5(a1, a2, a3, a4, a5)
#define ASM_ARGS_6	ASM_ARGS_5, "r"(_a6)

#define __SYSCALL_CLOBBERS "r4", "r14", "cc", "memory"

#endif /* __ASSEMBLER__ */
#endif /* _BITS_SYSCALLS_H */
