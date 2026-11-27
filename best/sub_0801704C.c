extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_080C364C(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern s32 sub_08014900(s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 sub_08005820(s32);
extern s32 sub_08014EF4(s32);

struct W34 { u8 p0; u8 f1; u8 p2[2]; s32 f4; };
struct W48 { s32 f0; u8 pad[0x10]; s16 f14; u8 pad2[6]; u16 f1c; u8 pad3[2]; s32 f20; u16 f24; };

void sub_0801704C(u8 *self)
{
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    struct W34 *w34 = (struct W34 *)(work + 0x34);
    struct W48 *w48 = (struct W48 *)(work + 0x48);
    s32 *trig;
    s32 *dispatch;
    s32 idx;
    s32 val;
    s32 zero;
    u16 t;

    sub_08011368(sprite, w34, 0, 1);
    if (w34->f1 == 1 && w34->f4 == 1)
        w48->f24 = 0;
    trig = (s32 *)0x08671BFC;
    w48->f20 = sub_080C31E0(sub_080C364C((s32)*(s16 *)((u8 *)w48 + 0x24) << 16, 0x3C), *trig) << 1;
    t = w48->f24 + 1;
    zero = 0;
    w48->f24 = t;
    idx = sub_08014900(*(s32 *)(work + 8));
    val = sub_08014900(w48->f0);
    if (val > 0x1000000) {
        u8 *p = (u8 *)((s16 *)self + *(s16 *)(self + 0x22));
        p[0x19] = zero;
        dispatch = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 2, *dispatch);
        return;
    }
    w48->f1c = w48->f1c - 1;
    if ((s16)w48->f1c >= 0)
        goto cold15c;
    w48->f1c = sub_08005820(0x3D) + 0x3C;
    if (idx > 0x7FFFFF)
        goto tblcheck;
    if (sub_08014EF4(5000) == 1) {
        u8 *p = (u8 *)((s16 *)self + *(s16 *)(self + 0x22));
        p[0x19] = zero;
        dispatch = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 4, *dispatch);
        return;
    } else {
        u8 *p = (u8 *)((s16 *)self + *(s16 *)(self + 0x22));
        p[0x19] = zero;
        dispatch = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, *dispatch, 3);
        return;
    }
tblcheck:
    if (*(s16 *)((u8 *)w48 + 0x14) == 1) {
        u8 *p = (u8 *)((s16 *)self + *(s16 *)(self + 0x22));
        p[0x19] = zero;
        dispatch = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, *dispatch, 3);
        return;
    }
cold15c:
    *(u32 *)(self + 0x14) = (u32)0x0866D548;
    t = *(u16 *)(self + 0x22);
    t = t + 1;
    *(u16 *)(self + 0x22) = t;
    {
        u8 *p = (u8 *)((s16 *)self + *(s16 *)(self + 0x22));
        u8 b = p[0x19];
        p[0x19] = b + 1;
    }
    {
        u8 op = *(u8 *)(self + 0x18 + *(s16 *)(self + 0x22) * 2);
        void (**fn)(u8 *);
        fn = (void (**)(u8 *))(*(u32 *)(self + 0x14));
        fn[op](self);
    }
    t = *(u16 *)(self + 0x22);
    t = t - 1;
    *(u16 *)(self + 0x22) = t;
}
