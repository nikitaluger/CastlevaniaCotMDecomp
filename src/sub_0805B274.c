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

M2C_UNK sub_0808DBB4(s32, s32, s32);                /* extern */
M2C_UNK sub_080C31E0(void *, s32);                  /* extern */

/* Spawn a variant-0 falling effect at the anchor's position shifted down by
 * 0x60000 (fixed point) with initial X velocity 8, then hand the object to
 * the callback stored at +0x24. */
void sub_0805B274(void *obj) {
    void *anchor;

    anchor = M2C_FIELD(obj, void **, 0x3C);
    sub_0808DBB4(M2C_FIELD(anchor, s32 *, 8), M2C_FIELD(anchor, s32 *, 0xC) + 0x60000, 8);
    sub_080C31E0(obj, M2C_FIELD(obj, s32 *, 0x24));
}
