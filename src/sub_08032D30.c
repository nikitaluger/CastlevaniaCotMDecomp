void sub_08014668(s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Knock-back reaction: copy the launch velocity at self+0x6C into the target's
 * x velocity, set the sprite's animation step left/right from its sign, then
 * advance the object's part script (same tail as the other part updates). */
void sub_08032D30(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 gfx = *(s32 *)(self + 0x38);
    u8 *target = *(u8 **)(self + 0x3C);
    u8 *animState = target + 0x48;
    s32 *stepTable;
    u8 *partState;
    s32 v;
    s32 launchSpeed;
    launchSpeed = *(s32 *)(self + 0x6C);
    *(s32 *)(target + 0x10) = launchSpeed;
    sub_08014668(gfx, launchSpeed);
    v = *(s32 *)(target + 0x10);
    *(s32 *)(animState + 4) = (v < 0) ? 0xC00 : 0xFFFFF400;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    stepTable = (s32 *)0x08671BB0;
    partState = self + 0x18;
    sub_080C31E4(partState, self + 0x22, *stepTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    partState = partState + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)partState * 4));
}
