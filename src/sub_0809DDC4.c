extern void sub_08005FC4(s32, s32, s32, s32, void *);
extern void sub_080114DC(u16 *, s32, s32, s32);
extern void sub_08014848(s32, s32, s32, s32, s32, s32);
extern void sub_0809E278(u16 *, s32, u8 *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_080C0384;
extern u32 D_08671BB0;

/* Script-step handler: set and advance the target's sprite animation, then act
 * on the script state bits — clear the graphic's high bits, spawn particles,
 * or on the final step play a sound, reset the state and fire the callback. */
void sub_0809DDC4(u8 *arg0) {
    u16 *gfx;
    u8 *target;
    u8 *sprite;
    u8 *animState;
    u8 flag;
    s32 posX;
    s32 posY;
    s32 *callback;
    gfx = *(u16 **)(arg0 + 0x38);
    target = *(u8 **)(arg0 + 0x3C);
    sprite = target + 0x34;
    animState = target + 0x48;
    sub_080114DC(gfx, (s32)sprite, 5, 0);
    sub_0809E278(gfx, (s32)sprite, target, (s32)animState);
    flag = *((u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0) + 0x19) & 2;
    if (flag == 0) {
        *gfx = (*gfx & 0x0FFF) | 0xE000;
    }
    flag = *((u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0) + 0x19) & 7;
    if (flag == 0) {
        posX = *(s32 *)(target + 8);
        posY = *(s32 *)(target + 0x0C) + 0xFFF00000;
        sub_08014848(2, 2, posX, posY, 0x100000, 0x100000);
    }
    if (*((u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0) + 0x19) == 0xB4) {
        sub_08005FC4(0, 0x186, 3, 0, &sub_080C0384);
        *((u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0) + 0x19) = 0;
        callback = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *callback);
    }
}
