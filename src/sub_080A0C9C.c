extern s32 sub_080057F8(void);
extern void sub_080114DC(s32, s32, s32, s32);
extern s32 sub_0801459C(void *, s32);
extern void sub_080148D8(s32, s32);
extern void sub_080A17B0(s32, s32, void *);
extern s32 sub_080A17DC(s32, void *, s32, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 D_08671BD0[];
extern u32 D_08671BD8[];

/* Actor direction-change handler: tick the cooldown, follow the movement track,
 * and when direction changes (or the facing counter hits 3) issue the matching
 * animation/timed-action command through the shared command table. */
void sub_080A0C9C(void *arg0)
{
    s32 scene;
    void *anim;
    s32 track;
    void *facing;
    s32 timer;
    u8 *self;
    s32 timerNow;
    s32 step;
    s8 randomDir;
    s32 step2;
    s32 step3;

    self = (u8 *)arg0;
    scene = *(s32 *)(self + 0x38);
    anim = *(void **)(self + 0x3C);
    track = (s32)anim + 0x34;
    facing = (void *)((u8 *)anim + 0x48);
    timer = *(s32 *)(self + 0x04);
    if (timer != 0)
    {
        *(s32 *)(self + 0x04) = timer - 1;
    }
    if (sub_080A17DC(scene, anim, track, facing, 0x4000) != 0)
    {
        timerNow = *(s32 *)(self + 0x04);
        if (timerNow == 0)
        {
            s32 *table;
            step = *(s16 *)(self + 0x22);
            self[step * 2 + 0x17] = (s8)timerNow;
            table = (s32 *)D_08671BD8;
            sub_080C31E8(self + 0x18, self + 0x22, 3, *table);
            return;
        }
        if (sub_0801459C(anim, 0x200000) != 0)
        {
            sub_080148D8(scene, *(s32 *)((u8 *)anim + 0x08));
            randomDir = (s8)(sub_080057F8() & 3);
            if (randomDir != 0)
            {
                s32 *table;
                sub_080114DC(scene, track, 0x0E, 0);
                step = *(s16 *)(self + 0x22);
                self[step * 2 + 0x19] = 0;
                table = (s32 *)D_08671BD0;
                sub_080C31E8(self + 0x18, self + 0x22, 2, *table);
                return;
            }
            {
                s32 *table;
                sub_080A17B0(scene, track, facing);
                step2 = *(s16 *)(self + 0x22);
                self[step2 * 2 + 0x19] = randomDir;
                table = (s32 *)D_08671BD0;
                sub_080C31E8(self + 0x18, self + 0x22, 3, *table);
            }
            return;
        }
    }
    if (((u8 *)facing)[0x17] == 3)
    {
        s32 *table;
        sub_080148D8(scene, *(s32 *)((u8 *)anim + 0x08));
        sub_080A17B0(scene, track, facing);
        step3 = *(s16 *)(self + 0x22);
        self[step3 * 2 + 0x19] = 0;
        table = (s32 *)D_08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 3, *table);
    }
}
