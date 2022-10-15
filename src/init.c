#include <stdint.h>
#define u64 uint64_t
#define s64 int64_t
#include "lv1call.h"

typedef struct function_descriptor 
{
	void	*addr;
	void    *toc;	
} f_desc_t;

#define INLINE inline __attribute__((always_inline))

#define LV2_TOC						0x39D440 //done
#define syscall_table_symbol				0x3B28F8 //done
#define syscall_call_offset				0x285E70 //

#define MAKE_KERNEL_ADDRESS(addr) (0x8000000000000000ULL | ((uint32_t)addr))
#define MKA MAKE_KERNEL_ADDRESS

#define LV2_SYSCALL2(ret, name, args) asm("" \
"	.section \".text\"\n" \
"	.align 2\n" \
"	.p2align 3,,7\n" \
"	.globl "#name"\n" \
"	.section \".opd\",\"aw\"\n" \
"	.align 3\n" \
#name": \n" \
"	.quad .L."#name",.TOC.@tocbase\n" \
"	.previous\n" \
"	.type   "#name", @function\n" \
".L."#name":\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	nop\n" \
"	mflr 0\n" \
"	std 0, 32(1)\n" \
"	std 2, 40(1)\n" \
"	bl +4\n" \
"	li 0, 0\n" \
"	li 2, 0\n" \
"	oris 2, 2, __toc@h\n" \
"	ori 2, 2, __toc@l\n" \
"	oris 0, 0, .L."#name"@h\n" \
"	ori 0, 0, .L."#name"@l\n" \
"	subf 0, 0, 2\n" \
"	mflr 2\n" \
"	addi 2, 2, -32\n" \
"	add  2, 2, 0\n" \
"	bl .L._"#name"\n" \
"	ld 2, 40(1)\n" \
"	ld 0, 32(1)\n" \
"	mtlr 0\n" \
"	blr\n" \
"	.size "#name",.-.L."#name"\n"); \
ret name args; \
ret _##name args


LV2_SYSCALL2(uint64_t, get_secure_rtc, (uint64_t *addr))
{
	int result;
	//u64 rtc_val;
	//u64 tb_val;

	//result = lv1_get_rtc(&rtc_val, &tb_val);   

    *addr = 719136185;


    return result;
}



static INLINE void create_syscall2(int n, void *func)
{
	uint64_t **table = (uint64_t **)MKA(syscall_table_symbol);
	f_desc_t *f = (f_desc_t *)func;	
	uint64_t *opd = f->addr;
	
	opd[0] = ((uint64_t)opd) + 16;
	opd[1] = MKA(LV2_TOC);
	table[n] = opd;
}


uint64_t PayloadEntry(uint64_t TOC, uint64_t payloadTOC)
{
    create_syscall2(119, get_secure_rtc);
}

