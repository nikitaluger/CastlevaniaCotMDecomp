typedef s32 (*TrigFn)(s32);
typedef void (*StepFn)(void *);

extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 divInt32(s32, s32);
extern s32 absXFromFocus(s32);
extern s32 sub_08014EF4(s32);
extern s32 scaleByRandom(s32);
extern u32 gTrigFuncTable;
extern void *gScriptStepCallbacks;
extern u32 D_0866D658[];
extern void _call_via_r1(s32, void *);
extern void _call_via_r3(void *, void *, s32, void *);

void sub_0801A7F0(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *track = work + 0x34;
    u8 *anim = work + 0x48;
    s32 absA;
    s32 absB;
    s32 timer;
    s32 q;
    s32 r;
    s32 incVal;
    u32 *trigAddr;
    s32 zero;

    setAnimationFrame(sprite, track, 0, 1);
    if (*(u8 *)(track + 1) == 1 && *(u32 *)(track + 4) == 1)
        *(u16 *)(anim + 0x24) = 0;
    trigAddr = &gTrigFuncTable;
    q = divInt32((s32)(*(s16 *)(anim + 0x24) << 16), 0x3C);
    r = ((TrigFn)*trigAddr)(q);
    *(u32 *)(anim + 0x20) = (u32)(r << 1);
    incVal = *(u16 *)(anim + 0x24) + 1;
    zero = 0;
    *(u16 *)(anim + 0x24) = incVal;
    absA = absXFromFocus(*(s32 *)(work + 8));
    absB = absXFromFocus(*(s32 *)(anim + 0));
    if (absB > 0x1000000) {
        void **cbp;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 2, *cbp);
        goto end;
    }
    timer = *(u16 *)(anim + 0x1C) - 1;
    *(u16 *)(anim + 0x1C) = timer;
    if ((timer << 16) >= 0)
        goto advance;
    *(u16 *)(anim + 0x1C) = scaleByRandom(0x3D) + 0x3C;
    if (absA <= 0x7FFFFF) {
        if (sub_08014EF4(0x1388) == 1) {
            void **cbp;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
            cbp = &gScriptStepCallbacks;
            _call_via_r3(self + 0x18, self + 0x22, 4, *cbp);
            goto end;
        }
    }
    if (*(s16 *)(anim + 0x14) == 1) {
        void **cbp;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 3, *cbp);
        goto end;
    }
advance:
    *(u32 **)(self + 0x14) = D_0866D658;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) =
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) + 1;
    {
        s32 idx2 = *(s16 *)(self + 0x22);
        u8 *script = self + 0x18;
        ((StepFn)(*(u32 **)(self + 0x14))[*(u8 *)(script + idx2 * 2)])(self);
    }
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
end:
}
