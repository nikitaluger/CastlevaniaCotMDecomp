extern void initCrossfadeGfxState(void);
extern void sub_080C31E0(void *, s32);

/* Runs a 16-frame screen-effect countdown: on every fourth frame updates the
 * effect state colours, and when the counter reaches 16 clears the hidden flag
 * on this sprite and all linked sprites, restores the effect state and ends the
 * script. */
void sub_0809BEE8(u8 *arg0) {
    u8 *self = arg0;
    vu16 *gfx = (vu16 *)0x03000830;
    u16 effectColor = 0x3F40;
    u8 phase;
    u8 *countP;
    u32 count;
    u8 fade;
    u8 *node;

    gfx[2] = effectColor;
    phase = *(u16 *)(self + 0x22) & 3;
    if (phase == 0) {
        countP = self + 0x5C;
        count = *countP + 1;
        *countP = count;
        fade = *(self + 0x60);
        gfx[3] = (fade << 8) | *countP;
        if ((u8)count == 0x10) {
            gfx[2] = phase;
            {
                u8 *linked;
                u16 *flags;
                linked = (u8 *)(*(vu32 *)(self + 0x28));
                flags = (u16 *)(*(u8 **)(linked + 0x38) + 2);
                *flags &= (0xFBFF);
                node = *(u8 **)(*(vu32 *)(self + 0x28) + 0x30);
                while (node != NULL) {
                    u8 *nodeSprite = *(u8 **)(node + 0x38);
                    if (nodeSprite != NULL)
                        *(u16 *)(nodeSprite + 2) &= 0xFBFF;
                    node = *(u8 **)(node + 0x2C);
                }
            }
            initCrossfadeGfxState();
            sub_080C31E0(self, *(s32 *)(self + 0x24));
        }
    }
}
