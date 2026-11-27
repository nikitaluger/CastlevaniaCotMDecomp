extern void sub_080148D8(void *, s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern s32 absXFromFocus(s32);
extern s32 sub_080145D8(s32, s32, s32, s32);
extern void setObjectAnimationFrame(s32, void *, u16, u8);

void sub_08041BE0(void *arg0)
{
    s32 flag = 0;
    s32 dir;
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    void *animTrack = work + 0x34;
    u8 *motion = work + 0x48;
    u16 saved = *(u16 *)(motion + 2);
    void **handlers;

    *(u16 *)(motion + 2) = 0;
    sub_080148D8(sprite, *(s32 *)(work + 8));
    motion[0] = motion[0] + 1;
    if ((u8)motion[0] == 5)
    {
        motion[0] = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            void **cbTable = (void **)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 5, *cbTable);
        }
    }
    else
    {
        *(s32 *)(work + 0x14) = 0;
        dir = (*(u16 *)(sprite + 2) & 0x10) ? 0x8000 : (s32)0xFFFF8000;
        *(s32 *)(work + 0x10) = dir;
        if (absXFromFocus(*(s32 *)(work + 8)) <= 0x005FFFFF)
        {
            flag = 1;
            *(s32 *)(work + 0x10) = -*(s32 *)(work + 0x10);
        }
        if (sub_080145D8(*(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0x100000, 0x300000, 0x200000) == 0
            || (flag != 0 && (saved & 1) != 0))
        {
            setObjectAnimationFrame((s32)sprite, animTrack, 0, 0);
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            {
                void **timerTable = (void **)0x08671BB0;
                sub_080C31E4(self + 0x18, self + 0x22, *timerTable);
            }
        }
        else
        {
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            {
                void **cbTable = (void **)0x08671BD0;
                sub_080C31E8(self + 0x18, self + 0x22, 2, *cbTable);
            }
        }
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    handlers = *(void ***) (self + 0x14);
    sub_080C31E0(self, handlers[*(self + 0x18 + *(s16 *)(self + 0x22) * 2)]);
}
