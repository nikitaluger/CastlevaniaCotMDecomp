void sub_0809C840(void *, void *);
void setAnimationFrame(void *, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Shrinks the actor's sprite by 0x40 (0x100 = 1.0) on each axis per frame;
 * when the horizontal scale reaches 0xC0, marks the shrink transition done in
 * the work state, restores the sprite to full 0x100 scale, switches the
 * animation to frame 2 and advances the script. */
void sub_0809AF80(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    s32 scaleX;
    s32 *scriptTable;
    sub_0809C840(self, sprite);
    scaleX = *(u16 *)(sprite + 4) - 0x40;
    *(u16 *)(sprite + 4) = scaleX;
    *(u16 *)(sprite + 6) = *(u16 *)(sprite + 6) - 0x40;
    if ((s16)scaleX <= 0xC0) {
        u8 *state = *(u8 **)(work + 0x28);
        s32 fullScale = 1;
        state[1] = fullScale;
        fullScale += 0xFF;
        *(u16 *)(sprite + 4) = fullScale;
        *(u16 *)(sprite + 6) = fullScale;
        setAnimationFrame(sprite, (s32)anim, 2, 0);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}
