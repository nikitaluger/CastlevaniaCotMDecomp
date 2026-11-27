/* Runs one step of an effect: picks a left/right direction from a target position,
 * stores a speed and its half, then dispatches the routine named by a per-step byte. */
s32 signOf(s32);
void setSpriteFlipForDirection(s32, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);

void sub_0803BED0(void *obj)
{
    s32 owner = *(s32 *)((u8 *)obj + 0x38);
    void *work = *(void **)((u8 *)obj + 0x3C);
    void *effect = (u8 *)work + 0x48;
    s32 speed;
    u8 zero;

    if (signOf(*(s32 *)((u8 *)work + 0x08)) > 0) {
        *(s32 *)((u8 *)work + 0x10) = 0x2000;
    } else {
        *(s32 *)((u8 *)work + 0x10) = (s32)0xFFFFE000;
    }
    setSpriteFlipForDirection(owner, *(s32 *)((u8 *)work + 0x10));

    speed = *(s32 *)((u8 *)work + 0x18);
    zero = 0;
    *(u16 *)effect = (u16)speed;
    *(u16 *)((u8 *)effect + 2) = (u16)(*(volatile s32 *)((u8 *)work + 0x18) >> 1);

    *(u8 *)((u8 *)obj + (*(s16 *)((u8 *)obj + 0x22)) * 2 + 0x19) = zero;
    {
        s32 *endFuncs = (s32 *)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, *endFuncs);
    }
    {
        u8 *counterPtr = (u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj);
        counterPtr[0x19] = (u8)(counterPtr[0x19] + 1);
    }
    {
        s32 index2 = (*(s16 *)((u8 *)obj + 0x22)) * 2;
        u8 *stateBytes = (u8 *)obj + 0x18;
        u8 stepIndex = *(stateBytes + index2);
        u8 **stepFuncs = *(u8 **)((u8 *)obj + 0x14);
        sub_080C31E0(obj, (s32)stepFuncs[stepIndex]);
    }
}
