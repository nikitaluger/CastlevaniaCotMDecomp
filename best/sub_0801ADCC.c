extern s32 absXFromFocus(s32);
extern s32 signOf(s32);
extern s32 getSpriteFacingSign(void *);
extern s32 sub_08014EF4(s32);
extern void sub_0801BE80(void *, s32);
extern void sub_0801BE64(void *, s32);
extern void _call_via_r3(void *, void *, s32, u32);
extern void _call_via_r1(void *, void *);
extern void *gScriptStepCallbacks;

void sub_0801ADCC(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *extra = work + 0x48;
    s32 absX = absXFromFocus(*(s32 *)(work + 8));
    s32 sign = signOf(*(s32 *)(work + 8));
    s32 facing = getSpriteFacingSign(sprite);
    s32 idx;
    u8 *child;

    *(u16 *)(extra + 0x14) = 1;
    if (absX <= 0x0037FFFF) {
        if (sub_08014EF4(*(s16 *)(extra + 0x2A)) == 1) {
            void **cbp;
            sub_0801BE80(work + 0x72, 0x2BC);
            idx = *(s16 *)(self + 0x22);
            *(u8 *)(self + idx * 2 + 0x19) = 0;
            cbp = &gScriptStepCallbacks;
            _call_via_r3(self + 0x18, self + 0x22, 7, (u32)*cbp);
            goto dispatch1;
        }
        sub_0801BE64(work + 0x72, 0x578);
        goto procs;
    }
    if (absX > 0x00B3FFFF)
        goto procs;
    if (facing != sign)
        goto procs;
    if (sub_08014EF4(*(s16 *)(extra + 0x2C)) == 1) {
        void **cbp;
        sub_0801BE80(work + 0x74, 0x3E8);
        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) = 0;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 8, (u32)*cbp);
        goto dispatch1;
    }
    sub_0801BE64(work + 0x74, 0x4B0);
    if (absX > 0x005FFFFF)
        goto procs;
    if (sub_08014EF4(*(s16 *)(extra + 0x2E)) == 1) {
        void **cbp;
        sub_0801BE80(work + 0x76, 0x3E8);
        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) = 0;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 5, (u32)*cbp);
dispatch1:
        idx = *(s16 *)(self + 0x22);
        child = self + idx * 2 + 0x19;
        *child = *child + 1;
        child = self + 0x18 + idx * 2;
        _call_via_r1(self, *(void **)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)child * 4));
        goto end;
    }
    {
        void **cbp;
        sub_0801BE80(work + 0x76, 0x3E8);
procs:
        sub_0801BE64(extra + 0x2A, 0x190);
        sub_0801BE64(extra + 0x2C, 0x190);
        sub_0801BE64(extra + 0x2E, 0x190);
        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) = 0;
        cbp = &gScriptStepCallbacks;
        _call_via_r3(self + 0x18, self + 0x22, 6, (u32)*cbp);
        idx = *(s16 *)(self + 0x22);
        child = self + idx * 2 + 0x19;
        *child = *child + 1;
        child = self + 0x18 + idx * 2;
        _call_via_r1(self, *(void **)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)child * 4));
    }
end:
}
