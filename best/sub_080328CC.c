void stepAnimationTrack(void *, void *);
void *spawnBudgetedEffect(s32, s32);
void sub_08011344(s32, s32, s32, s32);
void _call_via_r3(void *, void *, s32, s32);
void _call_via_r2(void *, void *, s32);
extern u32 gScriptStepCallbacks;

void sub_080328CC(u8 *self)
{
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x34;
    u8 *stepState = work + 0x48;
    u8 *obj;
    s32 idx;
    u8 flags;

    stepAnimationTrack(sprite, animState);
    flags = stepState[0xD];
    if ((flags & 0xF) == 0)
    {
        if (*(u16 *)((u8 *)sprite + 0x28) == 0x1C || *(u16 *)((u8 *)sprite + 0x28) == 0x28)
        {
            flags |= 1;
            stepState[0xD] = flags;
            obj = (u8 *)spawnBudgetedEffect((s32)self, 0xDF);
            if (obj != 0)
            {
                obj[0x7C] = 0;
                if (*(u16 *)((u8 *)sprite + 2) & 0x10)
                {
                    *(s32 *)(obj + 0x4C) = *(s32 *)((u8 *)work + 8) + 0x80000;
                    *(s32 *)(obj + 0x6C) = 0x30000;
                }
                else
                {
                    *(s32 *)(obj + 0x4C) = *(s32 *)((u8 *)work + 8) + (s32)0xFFFFF800;
                    *(s32 *)(obj + 0x6C) = (s32)0xFFFFFD00;
                }
                if (stepState[0xD] & 0x10)
                    *(s32 *)(obj + 0x5C) = *(s32 *)((u8 *)work + 0xC) + (s32)0xFFFFE500;
                else
                    *(s32 *)(obj + 0x5C) = *(s32 *)((u8 *)work + 0xC) + (s32)0xFFFFF700;
            }
            else
            {
                *(u8 *)((u8 *)self + 0x80) = 1;
            }
        }
    }
    if (*(u8 *)((u8 *)self + 0x80) != 0)
    {
        idx = *(s16 *)((u8 *)self + 0x22) * 2 + (s32)self;
        *(u8 *)(idx + 0x19) = 0;
        {
            u32 *callback = &gScriptStepCallbacks;
            _call_via_r3((u8 *)self + 0x18, (u8 *)self + 0x22, 0, *callback);
        }
    }
    else
    {
        stepState[0xE]++;
        if ((u8)(stepState[0xE]) == 0x80)
        {
            if (stepState[0xD] & 0x10)
                sub_08011344((s32)sprite, (s32)animState, 0xD, 0);
            sub_08011344((s32)sprite, (s32)animState, 0x15, 0);
            idx = *(s16 *)((u8 *)self + 0x22) * 2 + (s32)self;
            *(u8 *)(idx + 0x19) = 0;
            {
                u32 *callbacks = (u32 *)0x08671BB0;
                _call_via_r2((u8 *)self + 0x18, (u8 *)self + 0x22, *callbacks);
            }
        }
    }
}
