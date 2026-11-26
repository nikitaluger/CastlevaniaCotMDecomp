/* machine draft (m2c) for agbcc -mthumb-interwork -O2 -fno-strength-reduce, tried by autopilot */
#ifndef M2C_DEFINES
#define M2C_DEFINES
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_BITS_F32(expr) (m2c_bits = (u32)(expr), *(f32 *)&m2c_bits)
extern u32 m2c_bits;
#define M2C_PTR_FROM_F32(type, expr) ((type)(m2c_fbits = (expr), *(u32 *)&m2c_fbits))
extern f32 m2c_fbits;
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif

M2C_UNK sub_0808DBF8(s32, s32, s32);                /* extern */
M2C_UNK sub_080C31E0(void *, s32);                  /* extern */

void sub_0804F604(void *arg0) {
    void *temp_r4;

    temp_r4 = M2C_FIELD(arg0, M2C_UNK **, 0x3C);
    sub_0808DBF8(M2C_FIELD(temp_r4, s32 *, 8) + 0xFFFC0000, M2C_FIELD(temp_r4, s32 *, 0xC) + 0xC0000, 8);
    sub_0808DBF8(M2C_FIELD(temp_r4, s32 *, 8) + 0x40000, M2C_FIELD(temp_r4, s32 *, 0xC) + 0xC0000, 8);
    sub_080C31E0(arg0, M2C_FIELD(arg0, s32 *, 0x24));
}
