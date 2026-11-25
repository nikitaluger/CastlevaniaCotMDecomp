extern void sub_080C31E4(void *, void *, s32);

/* Turn the actor around: flip the horizontal-flip bit (0x10) of its sprite's
 * attribute word, set the step's 60-frame timer, clear the step counter and
 * advance the command script. */
void sub_0803DD18(void *arg0) {
    u8 *actor = (u8 *)arg0;
    u16 *sprite = *(u16 **)(actor + 0x38);
    u8 *sub = *(u8 **)(actor + 0x3C) + 0x48;
    s32 *advanceCb;
    {
        s32 attr = sprite[1] ^ 0x10;
        u32 zero = 0;
        sprite[1] = attr;
        *(u16 *)(sub + 0x04) = 0x3C;
        *(u8 *)((u32)(*(s16 *)(actor + 0x22) << 1) + (u32)actor + 0x19) = zero;
    }
    advanceCb = (s32 *)0x08671BB0;
    sub_080C31E4(actor + 0x18, actor + 0x22, *advanceCb);
}
