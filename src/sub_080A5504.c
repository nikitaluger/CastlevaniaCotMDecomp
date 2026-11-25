extern s32 sub_08005820(s32);
extern void sub_080A54C0(s32, s32, s32);

/* Shared player/camera coordinate in 16.16 fixed point (see +0x1750 for the other axis). */
struct S_02025FF0 { u8 _0x000[0x174C]; s32 pos; };
extern struct S_02025FF0 D_02025FF0;

/* Pick a pseudo-random spawn X in a band around the shared coordinate, clamped
 * into the visible window, then spawn a child effect there at a fixed Y. */
void sub_080A5504(s32 arg0) {
    s32 pos = D_02025FF0.pos;
    s32 lo = pos + 0xFFE80000;
    s32 hi = pos + 0x180000;
    s32 rnd;
    s32 spawnX;

    if (hi <= 0x007FFFFF || lo > 0x01800000) {
        rnd = sub_08005820(0x01000000);
        spawnX = rnd + 0x00800000;
    } else if (lo <= 0x007FFFFF && hi > 0x00800000) {
        spawnX = sub_08005820(0x01800000 - hi) + hi;
    } else if (lo <= 0x017FFFFF && hi > 0x01800000) {
        rnd = sub_08005820(lo + 0xFF800000);
        spawnX = rnd + 0x00800000;
    } else {
        rnd = sub_08005820(0x00D00000);
        spawnX = rnd + 0x00800000;
        if (spawnX > lo) {
            spawnX = rnd + 0x00B00000;
        }
    }
    sub_080A54C0(arg0, spawnX, 0x01DF0000);
}
