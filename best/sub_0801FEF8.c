extern void setAnimationFrame(s32, void *, u16, u8);
extern void _call_via_r1(void *, void *);
extern void *spawnBudgetedEffect(s32, s32);
extern s32 sub_0800583C(s32);
extern s32 scaleByRandom(s32);

void sub_0801FEF8(void *self) {
    void *obj;
    void *work;
    u8 *anim;
    s32 *timer;
    void *r4obj;
    s32 v;
    s32 t;

    obj = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    anim = (u8 *)work + 0x34;
    timer = (s32 *)((u8 *)work + 0x48);
    *(s32 *)((u8 *)work + 0x14) = 0;
    *(s32 *)((u8 *)work + 0x10) = 0;
    setAnimationFrame((s32)obj, anim, 0x19, 0);
    if (*(u8 *)anim & 2) {
        _call_via_r1(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    if (--timer[2] < 0) {
        timer[2] = 0;
        return;
    }
    r4obj = spawnBudgetedEffect(*(s32 *)0x02027860, 0x9A);
    if (r4obj == 0) {
        return;
    }
    v = *(s32 *)((u8 *)work + 8);
    if (v < 0) {
        v += 0xFFFF;
    }
    *(u16 *)((u8 *)r4obj + 0x4C) = (s16)(sub_0800583C(10) + (v >> 16));
    v = *(s32 *)((u8 *)work + 0xC);
    if (v < 0) {
        v += 0xFFFF;
    }
    *(u16 *)((u8 *)r4obj + 0x54) = (s16)(sub_0800583C(10) + (v >> 16));

    t = timer[2];
    if (*(u16 *)((u8 *)self + 0x5C) & 2) {
        t -= 1;
    } else {
        t -= 2;
    }
    *(s32 *)((u8 *)r4obj + 0x6C) = t << 15;
    *(s32 *)((u8 *)r4obj + 0x7C) = 0x8000 - scaleByRandom(0x20000);

    v = timer[2] % 2;
    if (v == 0) {
        *(u16 *)((u8 *)r4obj + 0x5C) = 0x100;
    } else if (v == 1) {
        *(u16 *)((u8 *)r4obj + 0x5C) = 0x200;
    }
}
