void sub_080AC908(void *, void *, void *, void *);
void sub_080114DC(void *, void *, s32, s32);
void sub_080B0828(s32, s32, s32);
void sub_080C31E8(void *, void *, s32, void *);

extern s32 D_081021E4[];
extern void *D_08671BD0;

/* Enemy AI state: mirror two effects around the body mid-attack, then advance state. */
void sub_080AB7B0(u8 *self)
{
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *aim = work + 0x48;
    s16 stateIdx;
    u16 flags;
    u32 timer;

    sub_080AC908(gfx, anim, work, aim);

    stateIdx = *(s16 *)(self + 0x22);
    if (*(u8 *)(self + stateIdx * 2 + 0x19) == 8) {
        sub_080114DC(gfx, anim, 4, 0);
    }

    stateIdx = *(s16 *)(self + 0x22);
    timer = *(u8 *)(self + stateIdx * 2 + 0x19);
    if (timer == 0x10) {
        s32 facing;
        flags = *(u16 *)(gfx + 2);
        timer &= flags;
        facing = -1;
        if (timer) {
            facing = 1;
        }
        sub_080B0828(*(s32 *)(work + 8) + D_081021E4[0] * facing,
                     *(s32 *)(work + 0xC) + D_081021E4[1],
                     0);
        sub_080B0828(*(s32 *)(work + 8) + D_081021E4[2] * facing,
                     *(s32 *)(work + 0xC) + D_081021E4[3],
                     1);
    }

    stateIdx = *(s16 *)(self + 0x22);
    {
        u8 *timerPtr = (u8 *)(stateIdx * 2 + (u32)self) + 0x19;
        if (*timerPtr == 0x5A) {
            s32 *lit;
            *timerPtr = 0;
            lit = (s32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 0, (void *)*lit);
        }
    }
}
