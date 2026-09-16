/*
                        Weak Symbol Checks

            Copyright 1983-2020 Green Hills Software, Inc.

    This program is the property of Green Hills Software, Inc,
    its contents are proprietary information and no part of it
    is to be disclosed to anyone except employees of Green Hills
    Software, Inc., or as agreed in writing signed by the President
    of Green Hills Software, Inc.
*/
#ifndef IND_WEAK_H
#define IND_WEAK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* __ghs_weak_func_exists(fname)
 *
 * fname must be the name of an imported weak function definition or an imported
 * non-weak function definition.  Returns true if the definition exists and
 * may be called or false if the imported references does not exist and should
 * not be called.  (Non-weak references normally exist because the code will
 * not link otherwise.)
 */
#if defined(__ghs_pic) || defined(__ghs_ropi)
extern void  __ghs_undefined_func (void);
#pragma weak __ghs_undefined_func
#define __ghs_weak_func_exists(fname) ((void (*)(void))(fname) != __ghs_undefined_func)
#else
#define __ghs_weak_func_exists(fname) ((void *)(fname) != (void *)0)
#endif /* pic/ropi */

/* __ghs_weak_var_exists(v)
 *
 * v must be the name of an imported weak variable definition or an imported
 * non-weak variable definition.  Returns true if the definition exists and
 * may be accessed or false if the imported references does not exist and should
 * not be accessed.  (Non-weak references normally exist because the code will
 * not link otherwise.)
 */
#if defined(__ghs_pid)
#pragma weak __ghs_undefined_var
extern void *__ghs_undefined_var;
#define __ghs_weak_var_exists(v) (((void**)&(v)) != &__ghs_undefined_var)
#else
#define __ghs_weak_var_exists(v) (&(v) != (void *)0)
#endif

/* This is used in ind_crt0.c to get the address of a linker-defined text
 * label that is declared as an external function.   Normally we can just use
 * the identifier name to get the address, but with indirect-function call
 * checks we have the address of an descriptor, and we must load the
 * descriptor to get the address.
 */
#if defined(__ghs_ifcc)
  #if defined(__ghs_pid)
   #error Indirect function call checks and pid are not compatible
  #endif /* __ghs_pid */
  extern char __ghs_indirect_function_call_checks_level[];
  static inline int __ghsifcc_linked(void) {
    return ((unsigned long)__ghs_indirect_function_call_checks_level) ==
            /* GHS_FEATURE_ENABLED */ 3;
  }
  #if defined(__x86_64__)
    /* On x64, the decriptor is runnable code.  The address is at an offset
     * of two bytes from the beginning.
     */
    static inline void * __get_address(unsigned long x) {
      if (x == 0) return 0;
      if (!__ghsifcc_linked()) return (void *)x;
      return *(void * __packed *)(x+2);
    }
    #define __ghs_funcadjust(x) (__get_address((unsigned long)(x)))
  #elif defined(__aarch64__)
    /* On ARM64, the descriptor is also runnable code.  The pool entry is
     * at an offset of 8 or 16 from the beginning of the descriptor
     * depending on whether the straightline spectre mitigations are
     * being used.  Whether the mitigation is applied on the binary is
     * determined at link time, so get the pool's address from the
     * opcode.
     */
    static inline void * __get_address(unsigned long x) {
      if (x == 0) return 0;
      if (!__ghsifcc_linked()) return (void *)x;
      {
        /* ARM64 instructions are always little endian */
	unsigned long offset = *(__littleendian unsigned int *)x;
	/* >> 3 instead of >> 5 because we want a word offset here */
	offset = (offset & 0xffffe0) >> 3;
	return *(void **)(x + offset);
      }
    }
    #define __ghs_funcadjust(x) (__get_address((unsigned long)(x)))
  #elif defined(__ARM__)
    /* ARM doesn't currently do straightline spectre mitigation, so the
     * pool entry is also at an offset of 8.
     */
    static inline void * __get_address(unsigned long x) {
      if (x == 0) return 0;
      if (!__ghsifcc_linked()) return (void *)x;
      /* Strip off any Thumb bit */
      x &= ~(unsigned long)1;
      x += 8;
      return *(void **)x;
    }
    #define __ghs_funcadjust(x) (__get_address((unsigned long)(x)))
  #elif defined(__V800__)
    /* On RH850 descriptor addresses are offset 8 */
    static inline void * __get_address(unsigned long x) {
      if (x == 0) return 0;
      return *(void **)(x + 8);
    }
    #define __ghs_funcadjust(x) (__get_address((unsigned long)(x)))
  #elif defined(__RISCV__)
    /* On RISCV descriptor addresses are offset 12 (RV32) or 16 (RV64) */
    static inline void * __get_address(unsigned long x) {
      if (x == 0) return 0;
      #if defined(__RISCV64__)
      return *(void **)(x + 16);
      #else
      return *(void **)(x + 12);
      #endif
    }
    #define __ghs_funcadjust(x) (__get_address((unsigned long)(x)))
  #elif defined(__Tricore__)
    /* On Tricore descriptors have the address offset 12 */
    static inline void * __get_address(unsigned long x) {
      if (x == 0) return 0;
      return *(void **)(x + 12);
    }
    #define __ghs_funcadjust(x) (__get_address((unsigned long)(x)))
  #else
   #error Unexpected non-descriptor case
    static inline void * __get_address(unsigned long x) {
      if (x == 0) return 0;
      return *(void **)x;
    }
    #define __ghs_funcadjust(x) (__get_address((unsigned long)(x)))
  #endif /* defined(__x86_64__) vs ... */
#else
#define __ghs_funcadjust(x) (x)
#endif /* FUNCADJUST */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IND_WEAK_H */
