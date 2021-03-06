#ifndef __ARCH_ARM_FAULT_H
#define __ARCH_ARM_FAULT_H

/*
 * Fault status register encodings.  We steal bit 31 for our own purposes.
 * Set when the FSR value is from an instruction fault.
 */
#define FSR_LNX_PF		(1 << 31)
#define FSR_WRITE		(1 << 11)
#define FSR_FS4			(1 << 10)
#define FSR_FS3_0		(15)
#define FSR_FS5_0		(0x3f)

#ifdef CONFIG_ARM_LPAE
static inline int fsr_fs(unsigned int fsr)
{
	return fsr & FSR_FS5_0;
}
#else
static inline int fsr_fs(unsigned int fsr)
{
	return (fsr & FSR_FS3_0) | (fsr & FSR_FS4) >> 6;
}
#endif

/* valid for LPAE and !LPAE */
static inline int is_xn_fault(unsigned int fsr)
{
	return ((fsr_fs(fsr) & 0x3c) == 0xc);
}

static inline int is_domain_fault(unsigned int fsr)
{
	return ((fsr_fs(fsr) & 0xD) == 0x9);
}

void do_bad_area(unsigned long addr, unsigned int fsr, struct pt_regs *regs);
unsigned long search_exception_table(unsigned long addr);
void early_abt_enable(void);

#endif	/* __ARCH_ARM_FAULT_H */
