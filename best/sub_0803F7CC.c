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

void sub_0803F7CC(void *arg0) {
    s32 temp_r3;
    void *temp_r1;

    temp_r3 = 1 & M2C_FIELD(arg0, u16 *, 0x5C);
    if (temp_r3 == 0) {
        temp_r1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x8C), s32 *, 0x3C) + 0x48;
        if (M2C_FIELD(temp_r1, s32 *, 0x14) == arg0) {
            M2C_FIELD(temp_r1, s32 *, 0x14) = temp_r3;
        }
    }
}
