/* Update a scripted effect's animation: copy its animation index into the
 * sprite, apply a frame-dependent horizontal speed nudge, occasionally spawn
 * a randomized particle, then count down to the next script step. */
s32 scaleByRandom(s32);
s32 randomSignedOffset(s32);
void sub_08091E3C(s32, s32, s32, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);
s16 sub_080C36E4(s32, s32);
extern u8 D_08100B1E[];

void sub_080964CC(void *script) {
    void *scriptCtx = script;
    void *sprite = *((void **)((u8 *)script + 0x38));
    void *fx = *((void **)((u8 *)script + 0x3C));
    void *state = (u8 *)fx + 0x48;
    u8 *animTable;
    s32 x, y, param;
    s32 idx;
    s32 t;
    s32 *p;

    animTable = D_08100B1E;
    *((u16 *)((u8 *)sprite + 0x28)) = *(u16 *)(animTable + *((s32 *)((u8 *)fx + 0x48)) * 4);
    {
        s32 flags = *(u16 *)((u8 *)state + 0x14);
        if (!(flags & 3)) {
            *((s32 *)((u8 *)fx + 0x08)) = *((s32 *)((u8 *)fx + 0x08)) + 0x20000;
        }
    }
    {
        s32 timer = *(s16 *)((u8 *)state + 0x14);
        s32 rounded = timer;
        if (timer < 0) rounded = timer + 3;
        if ((s16)(timer - ((rounded >> 2) << 2)) == 2) {
            *((s32 *)((u8 *)fx + 0x08)) = *((s32 *)((u8 *)fx + 0x08)) + (s32)0xFFFE0000;
        }
    }
    {
        s32 flags = *(u16 *)((u8 *)state + 0x14);
        if (!(flags & 1)) {
            x = *((s32 *)((u8 *)fx + 0x08)) + randomSignedOffset(0xE0000);
            y = *((s32 *)((u8 *)fx + 0x0C)) + 0x40000;
            param = scaleByRandom(0x8000) + 0x2000;
            {
                s32 timer = *(s16 *)((u8 *)state + 0x14);
                s32 bias = (u32)timer >> 31;
                s16 angle = sub_080C36E4((timer + bias) >> 1, 3);
                sub_08091E3C(x, y, 0, param, 0x16C1, (s32)angle << 16 >> 16);
            }
        }
    }
    t = *(u16 *)((u8 *)state + 0x14) - 1;
    *((u16 *)((u8 *)state + 0x14)) = (u16)t;
    if ((s32)(t << 16) < 0) {
        *((u16 *)((u8 *)state + 0x14)) = 8;
        idx = *((s16 *)((u8 *)scriptCtx + 0x22)) * 2;
        *((u8 *)((u8 *)scriptCtx + idx + 0x19)) = 0;
        p = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)scriptCtx + 0x18, (u8 *)scriptCtx + 0x22, *p);
    }
}
