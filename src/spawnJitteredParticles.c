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

s32 randomSignedOffset(s32);                              /* extern */
M2C_UNK sub_0808DBB4(s32, s32, s32);                /* extern */
M2C_UNK sub_0808DBF8(s32, s32, s32);                /* extern */
M2C_UNK sub_0808DC40(s32, s32, s32);                /* extern */

/* Spawns `count` objects of the selected kind at positions jittered around
 * (baseX, baseY) by a signed random offset within the given ranges. */
void spawnJitteredParticles(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 y;
    s32 x;
    s32 remaining;

    if (arg1 > 0) {
        remaining = arg1;
        do {
            x = randomSignedOffset(arg4) + arg2;
            y = randomSignedOffset(arg5) + arg3;
            switch (arg0) {
            case 0:
                sub_0808DBB4(x, y, 8);
                break;
            case 1:
                sub_0808DBF8(x, y, 8);
                break;
            case 2:
                sub_0808DC40(x, y, 8);
                break;
            }
            remaining -= 1;
        } while (remaining != 0);
    }
}
