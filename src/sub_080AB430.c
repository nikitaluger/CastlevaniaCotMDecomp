extern s32 sub_080AC908(s32, void *, void *, void *);
extern void sub_080146D0(void *, s32, s32);
extern void sub_0801165C(void *, s32);
extern void sub_080AC9B4(u8, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Orbiting projectile update: advances the aim animation, accelerates the orbit
 * speed (capped at 0x30000), turns the angle and speed into velocity, integrates
 * the position and runs its effect; every 60 frames it advances the script. */
void sub_080AB430(void *arg0) {
    u8 *self = arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *aim;
    s32 *handlerTable;
    sub_080AC908(sprite, work + 0x34, work, aim = work + 0x48);
    *(s32 *)(aim + 0x18) = *(s32 *)(aim + 0x18) + (0x80 << 4);
    if (*(s32 *)(aim + 0x18) > (0xC0 << 0x0A)) {
        *(s32 *)(aim + 0x18) = 0xC0 << 0x0A;
    }
    sub_080146D0(work, *(s32 *)(aim + 0x14), *(s32 *)(aim + 0x18));
    sub_0801165C(work, 0);
    sub_080AC9B4(*(u8 *)(work + (0x91 << 2)), work + 0x68);
    if (*(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) == 0x3C) {
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
    }
}
