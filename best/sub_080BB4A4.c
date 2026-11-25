extern void sub_080988B8(void *a, s32 b);
extern void sub_080BE550(s32 a, s32 b, void *c);
extern void sub_080BE564(s32 a, s32 b);
extern void sub_080BB8AC(void *a);
extern void sub_080BE644(void *a);
extern void sub_080BE7D4(void);
extern void sub_080BE87C(void);
extern void sub_080BE8C0(s32 a);
extern void sub_080BE8C8(s32 a, s32 b);
extern void sub_08098664(void *a, s32 b, s32 c);
extern void sub_0808D0A4(s32 a);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern u16 D_03000830[];

void sub_080BB4A4(u8 *arg0) {
    u8 *ctx = *(u8 **)(arg0 + 0x3C);
    u8 *sub = ctx + 0x48;
    u8 *f4c = *(u8 **)(arg0 + 0x4C);
    s32 v;
    s32 z = 0;

    sub_080988B8(f4c, *(s32 *)(ctx + 8));
    sub_080BE550(*(s32 *)(sub + 0x20), 0, ctx);
    sub_080BE564(*(s32 *)(sub + 0x1C), 0);
    sub_080BB8AC(sub);
    sub_080BE644(arg0);
    sub_080BE7D4();
    sub_080BE87C();

    {
        u8 *q = *(u8 **)(sub + 0x2C);
        if (q != NULL) {
            sub_080C31E0(q, *(s32 *)(q + 0x24));
        }
    }
    {
        u8 *r = *(u8 **)(sub + 0x30);
        if (r != NULL) {
            sub_080C31E0(r, *(s32 *)(r + 0x24));
        }
    }

    {
        u8 *s = *(u8 **)(*(u8 **)(sub + 0x14) + 0x38);
        *(u16 *)(s + 2) = (*(u16 *)(s + 2) | 0x400) | z;
    }
    {
        u8 *t = *(u8 **)(*(u8 **)(sub + 0x18) + 0x38);
        *(u16 *)(t + 2) = (*(u16 *)(t + 2) | 0x400) | z;
    }

    sub_080BE8C0(*(s32 *)(sub + 0x34));
    sub_080BE8C8(*(s32 *)(sub + 0x34), 0);
    sub_08098664(f4c, 1, 1);

    *(u32 *)(ctx + 0xD0) = 0x10;
    D_03000830[2] = 0x3F42;
    v = *(u32 *)(ctx + 0xD0);
    D_03000830[3] = (u16)(v | ((0x10 - v) << 8));
    sub_0808D0A4(0x14);

    if (*(u8 *)(f4c + 0x34) != 0) {
        *(u8 *)(f4c + 0x34) = 0;
        *(u32 *)(sub + 0x40) = 0;
        *(u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0 + 0x19) = z;
        {
            u32 *cb = (u32 *)0x08671BB0;
            u8 *script = arg0 + 0x18;
            sub_080C31E4(script, arg0 + 0x22, *cb);
        }
        {
            u8 *u = (u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0);
            *(u8 *)(u + 0x19) = (u8)(*(u8 *)(u + 0x19) + 1);
        }
        {
            u8 *script = arg0 + 0x18;
            u8 *w = script + (s16)*(s16 *)(arg0 + 0x22) * 2;
            sub_080C31E0(arg0, *(u32 *)((u32)(*w) * 4 + *(u32 *)(arg0 + 0x14)));
        }
    } else {
        *(u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0 + 0x19) = z;
        {
            u32 *cb = (u32 *)0x08671BB0;
            u8 *script = arg0 + 0x18;
            sub_080C31E4(script, arg0 + 0x22, *cb);
        }
        {
            u8 *u = (u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0);
            *(u8 *)(u + 0x19) = (u8)(*(u8 *)(u + 0x19) + 1);
        }
        {
            u8 *script = arg0 + 0x18;
            u8 *w = script + (s16)*(s16 *)(arg0 + 0x22) * 2;
            sub_080C31E0(arg0, *(u32 *)((u32)(*w) * 4 + *(u32 *)(arg0 + 0x14)));
        }
    }
}
