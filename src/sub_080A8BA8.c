s32 nextRandomWord(void);
void sub_080AACF8(s32 entity);

/* Ambient-effect timer on the object at arg1+0xDB: counts down each frame;
 * when it expires, with a 1-in-64 chance it is rearmed to 0x3C and an effect
 * (kind 0x1A5) is spawned on the entity. */
void sub_080A8BA8(s32 arg0, void *arg1) {
    u8 timer;

    timer = *(u8 *)((u8 *)arg1 + 0xDB);
    if (timer != 0) {
        *(u8 *)((u8 *)arg1 + 0xDB) = (u8)(timer - 1);
        return;
    }
    if (!(0x3F & nextRandomWord())) {
        *(u8 *)((u8 *)arg1 + 0xDB) = 0x3C;
        sub_080AACF8(arg0);
    }
}
