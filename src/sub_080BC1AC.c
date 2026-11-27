extern void forceAnimationFrame(void *, void *, u16, u8);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script step: when self+0x5C is active it highlights the sprite, copies the
 * two child pointers (self+0x6C/+0x7C) into the body animator, starts animation
 * 0x0C and advances the script; when inactive it just clears the highlight. */
void sub_080BC1AC(void *arg0) {
    u8 *self = arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *body = *(u8 **)(self + 0x3C);
    u8 *animData = body + 0x34;

    if (*(u32 *)(self + 0x5C) != 0) {
        u8 *highlight = sprite + 0x2A;
        u8 oldHighlight = *highlight;
        u32 newHighlight = 0x40;
        u32 zero = 0;
        newHighlight |= oldHighlight;
        *highlight = (u8)newHighlight;
        *(u32 *)(body + 0x08) = *(u32 *)(self + 0x6C);
        *(u32 *)(body + 0x0C) = *(u32 *)(self + 0x7C);
        forceAnimationFrame(sprite, animData, 0x0C, 0);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = (u8)zero;
        {
            s32 *scriptTable = (s32 *)0x08671BB0;
            u8 *stepData = self + 0x18;
            sub_080C31E4(stepData, self + 0x22, *scriptTable);
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
            stepData += *(s16 *)(self + 0x22) * 2;
            sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *stepData * 4));
        }
    } else {
        sprite += 0x2A;
        *sprite &= 0xBF;
    }
}
