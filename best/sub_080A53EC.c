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

M2C_UNK sub_080C31E4();                             /* extern */
extern M2C_UNK sub_080A5418;

typedef struct {
    char pad0[0x2];
    u16 m2;
    char pad4[0x10];
    void *m14;
    char pad18[0xA];
    s16 m22;
    char pad24[0x48];
    s8 m6C;
} Rec_sub_080A53EC_arg0;

void sub_080A53EC(void *arg0) {
    (((Rec_sub_080A53EC_arg0 *) arg0)->m6C) = 0;
    (((Rec_sub_080A53EC_arg0 *) arg0)->m2) = (u16) (0x800 | (((Rec_sub_080A53EC_arg0 *) arg0)->m2));
    (((Rec_sub_080A53EC_arg0 *) arg0)->m14) = &sub_080A5418;
    (((Rec_sub_080A53EC_arg0 *) arg0)->m22) = 1;
    sub_080C31E4();
}
