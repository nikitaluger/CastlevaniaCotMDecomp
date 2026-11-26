extern void sub_08003A6C(void *, s32, void *);
extern void playSound(s32);
extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_080722E0(void *, u8);
extern void sub_0808449C(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gGameStatus[];
extern u32 D_084DE7BC;
extern u32 D_084DE884;
extern s32 gMainObjTimerCallback;
struct S_AEC4 { u8 _0[0x2C]; u8 * volatile res; };
struct S_FF0 { u8 _0[0x1510]; u8 b1510; };
extern struct S_FF0 gMainWorkspace;

void sub_08079DF0(u8 *arg0) {
    s32 zero;
    s32 c;
    u8 *p68 = *(u8 **)(arg0 + 0x6C);
    u8 *r4 = p68 + 4;
    u8 *rp = *(u8 **)(arg0 + 0x38);
    u8 *base2 = gGameStatus;
    void *res;
    struct S_AEC4 *s = (struct S_AEC4 *)r4;

    res = allocEffectPart();
    s->res = res;
    if (res == NULL) {
        sub_0806D2D0(arg0);
        return;
    }
    zero = 0;
    *(u32 *)(r4 + 0x30) = zero;
    *(u32 *)(r4 + 0x34) = zero;
    *(u32 *)(r4 + 0x38) = zero;
    *(u32 *)(r4 + 0x3C) = zero;
    *(u8 *)(res + 1) = 1 & gMainWorkspace.b1510;
    *(u8 *)(s->res + 2) = 2;
    {
        u8 eight;
        *(u8 *)(s->res + 3) = (eight = 8);
        *(u16 *)(s->res + 4) = *(u8 *)(base2 + 0x304);
        *(u16 *)(s->res + 6) = 4;
        *(u16 *)(s->res + 8) = eight;
    }
    *(u16 *)(s->res + 0xA) = zero;
    *(u16 *)(s->res + 0xC) = zero;
    *(u16 *)(s->res + 0xE) = sub_0806D62C(*(u16 *)(base2 + 0x2E2), 0x3F);
    *(u16 *)(s->res + 0x16) = 5;
    *(u16 *)(s->res + 0x18) = 0x5B;
    {
        u8 *rr = s->res;
        *(void **)(rr + 0x10) = rp;
    }
    *(u32 *)(r4 + 0x18) = *(u32 *)(arg0 + 0x24);
    *(u32 *)(arg0 + 0x24) = (u32)&sub_0808449C;
    *(u32 *)(rp + 0x24) = (u32)&D_084DE7BC;
    sub_08003A6C(p68 + 0x20, 0, &D_084DE884);
    *(u32 *)(p68 + 4) = *(u32 *)(arg0 + 0x7C);
    *(u32 *)(r4 + 4) = *(u32 *)(arg0 + 0x8C);
    c = 0x80 << 0xC;
    *(s32 *)(r4 + 0x40) = c;
    {
        u32 v = *(u32 *)(arg0 + 0x9C);
        *(u8 *)(p68 + 0x48) = v;
    }
    sub_080722E0(r4, *(u8 *)(p68 + 0x48));
    {
        s32 t = *(s32 *)(r4 + 0x40) >> 8;
        *(s32 *)(r4 + 8) = (*(s32 *)(r4 + 8) * t) / 256;
        *(s32 *)(r4 + 0xC) = (*(s32 *)(r4 + 0xC) * t) / 256;
    }
    playSound(0x14B);
    *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = zero;
    {
        s32 *lit = &gMainObjTimerCallback;
        u8 *a18 = arg0 + 0x18;
        sub_080C31E4(a18, arg0 + 0x22, *lit);
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) + 1;
        a18 += *(s16 *)(arg0 + 0x22) * 2;
        {
            u8 b = *a18;
            sub_080C31E0(arg0, *(s32 *)(b * 4 + *(u32 *)(arg0 + 0x14)));
        }
    }
}
