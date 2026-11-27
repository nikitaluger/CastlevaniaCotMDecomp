extern void sub_08011EE8(void *, u32, u32);
extern void stepAnimationTrack(void *, void *);
extern void sub_08042130(void *, void *);
extern s32 setAnimationFrame(s32, s32, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 signOf(s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_08041F84(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *state = 0x34 + work;
    u8 *anim = work + 0x48;
    u8 *slot;
u8 *__repair_phase_slot;
    s32 sign;

    sub_08011EE8(work, 0x16C1, 0);
    stepAnimationTrack(sprite, state);
    sub_08042130(anim, sprite);

    if (*state & 2) {
        *(u32 *)(work + 0x10) = (*(u16 *)(sprite + 2) & 0x10) ? 0x34000 : 0xFFFCC000;
        setAnimationFrame((s32)sprite, (s32)state, 10, 1);
    }
    if (*(u32 *)(work + 0x10) == 0)
        return;
    if (absXFromFocus(*(s32 *)(work + 8)) <= 0xFFFFF)
        goto doAnim;
    sign = signOf(*(s32 *)(work + 8));
    if (sign != ((*(u16 *)(sprite + 2) & 0x10) ? 1 : -1)) {
        if (absXFromFocus(*(s32 *)(work + 8)) > 0x600000)
            goto doAnim;
    }
    slot = (u8 *)((u32)(*(s16 *)(self + 0x22) * 2) + (u32)self);
    if (slot[0x19] > 0x3C)
        goto doAnim;
    if ((*(u16 *)(work + 2) & 3) == 0)
        return;
doAnim:
    setAnimationFrame((s32)sprite, (s32)state, 7, 0);
    __repair_phase_slot = (u8 *)((u32)(*(s16 *)(self + 0x22) * 2) + (u32)self);
    __repair_phase_slot[0x19] = 0;
    {
        s32 *handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
    }
}
