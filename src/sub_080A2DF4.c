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

s32 sub_0800583C(s32);                              /* extern */
M2C_UNK sub_080A2DA8(M2C_UNK, s32, s32);            /* extern */

/* Spawn effect 0x18D near a point: scatter x and y by a random signed offset
 * of up to 8.0 units and lift it 72.0 units (fixed-point) above the source. */
void sub_080A2DF4(M2C_UNK parent, void *pos) {
    s32 temp_r4;

    temp_r4 = M2C_FIELD(pos, s32 *, 8) + sub_0800583C(0x80000);
    sub_080A2DA8(parent, temp_r4, M2C_FIELD(pos, s32 *, 0xC) + sub_0800583C(0x80000) + 0xFFB80000);
}
