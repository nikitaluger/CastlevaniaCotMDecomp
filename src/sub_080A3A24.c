extern void sub_080114A8(s32 arg0, void *arg1, s32 arg2, u8 arg3);
extern void sub_080A55AC(void *arg0);
extern void sub_080A56D8(void);
extern void sub_080A5608(void);
extern void sub_080A5734(s32 arg0, s32 arg1, s32 arg2);
extern void sub_0808D0A4(s32 arg0);
extern void sub_080C31E4(void *arg0, void *arg1, s32 arg2);
extern u8 D_08101C60[];
extern u32 gMainObjTimerCallback[];

/* Boss attack-phase step: play the animation for the current phase from the
 * phase table, wake the boss's three part groups (actor types 0x192, 0x195 and
 * 0x193), move the attached object to the boss position, play the attack cue,
 * then clear the script byte and advance the script. */
void sub_080A3A24(void *entity) {
    u8 *self = (u8 *)entity;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *body = work + 0x48;
    u8 *phaseTable = D_08101C60;
    s32 phase = *(s32 *)(work + 0x48);
    s32 offset = phase * 4;
    u8 *entry = phaseTable + 2;
    s16 animId = *(s16 *)(entry + offset);

    sub_080114A8(sprite, anim, animId, 0);
    sub_080A55AC(self);
    sub_080A56D8();
    sub_080A5608();
    {
        s32 attached = *(s32 *)(body + 0x4C);
        s32 x = *(s32 *)(work + 0x08);
        s32 y = *(s32 *)(work + 0x0C);
        sub_080A5734(attached, x, y);
    }
    sub_0808D0A4(0x0E);
    {
        s16 step = *(s16 *)(self + 0x22);
        *(u8 *)(self + step * 2 + 0x19) = 0;
    }
    {
        u32 *scriptTable = gMainObjTimerCallback;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}
