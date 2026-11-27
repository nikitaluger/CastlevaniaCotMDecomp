void sub_0803B194(void *);
void sub_080113A8(void *, void *);
void sub_0803B140(s32, void *, void *, s32);
void sub_08011EE8(void *, s32, s32);
void sub_0803B1A4(void *);
void _call_via_r3(void *, void *, s32, s32);
extern u32 gScriptStepCallbacks;

void sub_080333D0(void *self)
{
    void *sprite = *(void **)((u8 *)self + 0x38);
    void *work = *(void **)((u8 *)self + 0x3C);
    void *animState = (u8 *)work + 0x34;
    void *moveState = (u8 *)work + 0x48;

    sub_0803B194((u8 *)work + 0x54);
    sub_080113A8(sprite, animState);
    sub_0803B140(7, sprite, (u8 *)work + 0x54, 0x080CED6E);
    if (*(s32 *)((u8 *)work + 0x10) != 0)
    {
        if (*(u16 *)((u8 *)sprite + 2) & 0x10)
            *(s32 *)((u8 *)work + 0x10) += (s32)0xFFFF8000;
        else
            *(s32 *)((u8 *)work + 0x10) += 0x8000;
    }
    sub_08011EE8(work, 0x16C1, 0);
    {
        u8 *stepState = (u8 *)moveState;
        stepState[0x18]++;
        if (stepState[0x18] == 0x26)
        {
            sub_0803B1A4((u8 *)moveState + 0xC);
            {
                s32 idx = *(s16 *)((u8 *)self + 0x22) * 2 + (s32)self;
                *(u8 *)(idx + 0x19) = 0;
            }
            {
                u32 *callback = &gScriptStepCallbacks;
                _call_via_r3((u8 *)self + 0x18, (u8 *)self + 0x22, 0, *callback);
            }
        }
    }
}
