extern void startEffectTimer(void *, s32, void *);
extern s32 stepDelayTimer(void *, void *);
extern void spawnEntity(void *, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gMainWorkspace[];
extern s32 gMainObjTimerCallbacks;

void sub_0807F678(u8 *arg0) {
    u32 zero = 0;
    u8 *r7 = *(u8 **)(arg0 + 0x6C);
    u8 *r4 = r7 + 4;
    u8 *rp = *(u8 **)(arg0 + 0x38);

    *(u32 *)(r4 + 0x2C) = zero;
    *(u32 *)(r4 + 0x30) = zero;
    *(u32 *)(r4 + 0x34) = zero;
    *(u32 *)(r4 + 0x38) = zero;
    *(u32 *)(r4 + 0x3C) = zero;
    *(u32 *)(r4 + 0x18) = *(u32 *)(arg0 + 0x24);
    *(u32 *)(arg0 + 0x24) = 0x0808449D;
    *(u32 *)(rp + 0x24) = 0x084EBCCC;
    {
        u8 *p20 = r7;
        p20 += 0x20;
        startEffectTimer(p20, 0, (void *)0x084EBFC4);
        stepDelayTimer(p20, rp);
    }
    {
        u8 *base = gMainWorkspace;
        *(s32 *)(r7 + 4) = *(s32 *)(base + 0x1728);
        *(s32 *)(r4 + 4) = *(s32 *)(base + 0x172C) + 0xFF800000;
    }
    *(u32 *)(r4 + 0x10) = zero;
    *(u32 *)(r4 + 0x54) = zero;
    spawnEntity(arg0, 0x62, 0x0A, 0x12);
    *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = (u8)zero;
    {
        s32 *lit = &gMainObjTimerCallbacks;
        u8 *a18 = arg0;
        a18 += 0x18;
        sub_080C31E4(a18, arg0 + 0x22, *lit);
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) + 1;
        a18 += *(s16 *)(arg0 + 0x22) * 2;
        {
            u8 b = *a18;
            sub_080C31E0(arg0, *(s32 *)(b * 4 + *(u32 *)(arg0 + 0x14)));
        }
    }
}
