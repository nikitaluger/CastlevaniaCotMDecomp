extern s32 signOf(u32);
extern u32 scaleByRandom(u32);
extern s32 absXFromFocus(u32);
extern s32 getSpriteFacingSign(u32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 gScriptStepCallbacks;

struct ObjA { u8 _0[0x38]; u32 f38; u32 f3C; };
struct TimerA { u8 _0[0x16]; u16 f16; u8 _1[2]; u16 f1A; };

void sub_0801A98C(struct ObjA *obj)
{
    u8 *work;
    u8 *actor;
    struct TimerA *timer;
    s32 count;
    u16 flags;
    u32 value;
    u32 *cmdTable;

    actor = (u8 *)obj->f38;
    work = (u8 *)obj->f3C;
    timer = (struct TimerA *)(work + 0x48);
    count = timer->f16 - 1;
    timer->f16 = count;
    if ((s32)((u16)count << 16) >= 0)
        return;

    if (signOf(*(u32 *)(work + 8)) > 0)
        flags = *(u16 *)(actor + 2) | 0x10;
    else
        flags = *(u16 *)(actor + 2) & 0xFFEF;
    *(u16 *)(actor + 2) = flags;

    timer->f1A = scaleByRandom(0x29) + 0x64;

    if (absXFromFocus(*(u32 *)(work + 8)) > 0x300000) {
        if (getSpriteFacingSign(actor) > 0)
            value = 0x4000;
        else
            value = (u32)-0x4000;
    } else {
        if (absXFromFocus(actor) > 0)
            value = (u32)-0x4000;
        else
            value = 0x4000;
    }
    *(u32 *)(work + 0x10) = value;

    *(u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2 + 0x19) = 0;
    cmdTable = &gScriptStepCallbacks;
    sub_080C31E8(actor + 0x18, actor + 0x22, 0, *cmdTable);
}
