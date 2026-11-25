/* machine draft (m2c) for agbcc -mthumb-interwork -O2, tried by autopilot */
#ifndef M2C_DEFINES
#define M2C_DEFINES
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif

M2C_UNK sub_0808DC40(s32, s32, s32);                /* extern */
M2C_UNK sub_080C31E0(void *, s32);                  /* extern */

/* Clear the anchor's +0x14/+0x10 motion fields, spawn a variant-2 effect at
 * its (x, y) with param 8, then hand the object to the callback at +0x24. */
void sub_08045774(void *obj) {
    void *anchor;

    anchor = M2C_FIELD(obj, void **, 0x3C);
    M2C_FIELD(anchor, s32 *, 0x14) = 0;
    M2C_FIELD(anchor, s32 *, 0x10) = 0;
    sub_0808DC40(M2C_FIELD(anchor, s32 *, 8), M2C_FIELD(anchor, s32 *, 0xC), 8);
    sub_080C31E0(obj, M2C_FIELD(obj, s32 *, 0x24));
}
