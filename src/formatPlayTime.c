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

u32 divideInt(s32, s32);                         /* extern */
s32 moduloInt(u32, s32);                         /* extern */

/* Packs a frame count into (hours << 16) | (minutes << 8) | seconds, saturating at 99:59:59.
 * divideInt is the BIOS Div quotient; moduloInt is its remainder (modulo). */
s32 formatPlayTime(s32 frameCount) {
    s32 minutes;
    s32 seconds;
    u32 hours;

    hours = divideInt(frameCount, 0x34BC0);
    if (hours > 0x63U) {
        hours = 0x63;
        minutes = 0x3B;
        seconds = 0x3B;
    } else {
        seconds = moduloInt(divideInt(frameCount, 0x3C), 0x3C);
        minutes = moduloInt(divideInt(frameCount, 0xE10), 0x3C);
    }
    return (hours << 0x10) | (minutes << 8) | seconds;
}
