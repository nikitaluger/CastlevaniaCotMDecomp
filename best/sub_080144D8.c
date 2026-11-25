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

void sub_080144D8(void *arg0, u16 *arg1) {
    void *temp_r1;
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 0x3C);
    temp_r1 = M2C_FIELD(temp_r2, void **, 0x28);
    if (temp_r1 != NULL) {
        M2C_FIELD(temp_r1, s8 *, 1) = 0;
    }
    *arg1 = (0xFFF & *arg1) | ((M2C_FIELD(temp_r2, u16 *, 0x22) + 8) << 0xC);
}
