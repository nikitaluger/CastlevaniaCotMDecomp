#ifndef M2C_DEFINES
#define M2C_DEFINES
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
extern M2C_UNK _0808D0A4(s32);
extern M2C_UNK sub_080B300C(void);
extern M2C_UNK sub_080B307C(void);
extern M2C_UNK sub_080B31AC(void *);
extern M2C_UNK sub_080C31E4(void *, void *, s32);
void sub_080B1734(void *arg0)
{
  int new_var;
  *((s32 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x3C)))) + 0x54)) = 0x10000;
  sub_080B300C();
  sub_080B307C();
  sub_080B31AC(arg0);
  _0808D0A4(0x11);
  *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
  new_var = 0x08671BB0;
  sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) new_var));
}

extern void sub_080C31E8(void *, void *, s32, s32);

/* Script step handler: when the current slot's command byte is 8, clear the
 * slot's flag byte at +0x17 and dispatch the next script command through the
 * command table at 0x08671BD8, using mode 1. */
void sub_080B80D8(void *arg0) {
    u8 *obj = (u8*)arg0;
    if (*(u8*)(obj + *(s16*)(obj + 0x22) * 2 + 0x19) == 8) {
        s32 *lit;
        *(u8*)(obj + *(s16*)(obj + 0x22) * 2 + 0x17) = 0;
        lit = (s32*)0x08671BD8;
        sub_080C31E8(obj + 0x18, obj + 0x22, 1, *lit);
    }
}
