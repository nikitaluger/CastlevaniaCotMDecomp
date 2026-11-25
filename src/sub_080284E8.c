extern s32 sub_0800583C(s32 range); /* random value in [-range, range) */

/* Shake command: flip the direction bit, then set the motion offset to
 * base+72px (or base-72px) plus a random +/-48px jitter on X and a random
 * +/-16px jitter on Y. */
void sub_080284E8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *motion = work + 0x48;
    s32 jitterX;
    s32 jitterY;
    s32 targetX;

    *(u16 *)(motion + 0x10) ^= 1;
    jitterX = sub_0800583C(0x300000);
    jitterY = sub_0800583C(0x100000);

    if (*(s16 *)(motion + 0x10) == 0) {
        targetX = *(s32 *)(work + 0x48) + 0xFFB80000;
        targetX = targetX - jitterX;
    } else {
        targetX = *(s32 *)(work + 0x48) + 0x480000;
        targetX = targetX + jitterX;
    }
    *(s32 *)(motion + 8) = targetX;
    *(s32 *)(motion + 0xC) = *(s32 *)(motion + 4) + jitterY;
}
