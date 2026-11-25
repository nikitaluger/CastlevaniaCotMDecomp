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

M2C_UNK sub_080BFB88();                             /* extern */
M2C_UNK sub_080BFBF8();                             /* extern */

void sub_080BFC18(void *arg1) {
    u8 temp_r2;

    temp_r2 = M2C_FIELD(arg1, u8 *, 2);
    if ((u32) temp_r2 < 3U) {
        M2C_FIELD((arg1 + (temp_r2 * 4)), s32 *, 0x44) = (s32) (M2C_FIELD(arg1, s32 *, 0x40) + 4);
        M2C_FIELD(arg1, u8 *, 2) = (u8) (M2C_FIELD(arg1, u8 *, 2) + 1);
        sub_080BFBF8();
        return;
    }
    sub_080BFB88();
}
