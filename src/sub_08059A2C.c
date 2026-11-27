void setAnimationFrame(void *, void *, s32, s32);
s32 scaleByRandom(s32);

/* Each frame set the sprite to animation frame 7 and decrement a counter;
 * when it expires, flip the velocity at +0x10 based on a position comparison
 * and restart the counter with a bounded random delay. */
void sub_08059A2C(void *entity) {
    void *sprite = *(void **)((u8 *)entity + 0x38);
    u8 *work = *(u8 **)((u8 *)entity + 0x3C);
    u8 *anim = work + 0x34;
    u8 *state = work + 0x48;
    s32 velocity;

    setAnimationFrame(sprite, anim, 7, 1);

    if ((s16)(*(u16 *)(state + 4) = *(u16 *)(state + 4) - 1) < 0) {
        if (*(s32 *)(work + 8) > *(s32 *)(work + 0x48)) {
            velocity = 0xFFFFE000;
        } else {
            velocity = 0x2000;
        }
        *(s32 *)(work + 0x10) = velocity;
        *(u16 *)(state + 4) = scaleByRandom(0x65) + 0x78;
    }
}
