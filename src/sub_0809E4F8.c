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

M2C_UNK sub_08097EF4(s32, s32, s32, s32);           /* extern */

/* Pick the object's OBJ-palette variant from bit 1 of its current script-slot
 * state byte and load that palette (16 colours) into palette slot 1. */
void sub_0809E4F8(void *obj) {
    if (2 & M2C_FIELD(((M2C_FIELD(obj, s16 *, 0x22) * 2) + obj), u8 *, 0x19)) {
        sub_08097EF4(1, 0x083CEA6C, 1, 1);
        return;
    }
    sub_08097EF4(1, 0x083CEACC, 1, 1);
}
