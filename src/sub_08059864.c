extern s32 setAnimationFrame(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallback[];

/* Advances the animation; when its state has bit 2 set, switches animation,
 * resets the work's motion state and fires the script callback. */
void sub_08059864(void *script) {
    s32 *p0 = (s32 *)script;
    void *sprite = (void *)p0[14]; /* 0x38 */
    void *work = (void *)p0[15]; /* 0x3C */
    void *animState = (void *)((u8 *)work + 0x34);
    void *extra = (void *)((u8 *)work + 0x48);
    int zero = 0;
    *(s32 *)((u8 *)work + 0x10) = 0;
    setAnimationFrame((s32)sprite, (s32)animState, 0x0E, 0);
    if (2 & *(u8 *)animState) {
        setAnimationFrame((s32)sprite, (s32)animState, 0x12, 1);
        *(s32 *)((u8 *)work + 0x14) = 0;
        *(s32 *)((u8 *)work + 0x0C) = *(s32 *)((u8 *)work + 0x0C) + 0x1B0000;
        *(s32 *)((u8 *)extra + 0x08) = 0x2221;
        *(s16 *)((u8 *)extra + 0x06) = 0;
        *(s32 *)((u8 *)extra + 0x0C) = 0;
        *(u16 *)((u8 *)work + 0x04) = (u16)(0xFEFF & *(u16 *)((u8 *)work + 0x04));
        *(s8 *)((u8 *)script + 0x19 + *(s16 *)((u8 *)script + 0x22) * 2) = 0;
        {
            void **fn = &gMainObjTimerCallback[0];
            sub_080C31E4((u8 *)script + 0x18, (u8 *)script + 0x22, *fn);
        }
    }
}
