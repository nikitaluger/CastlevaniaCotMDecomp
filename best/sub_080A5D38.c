extern void sub_08013AC4(void *);
extern s32 sub_08013B5C(void *, void *);
extern void sub_08013C8C(void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08097F88(s32, void *, void *, void *);
extern void sub_080983E8(void *);
extern void sub_080A820C(void *, void *, void *, void *, void *);
extern void sub_080A84AC(void *, void *, void *, void *);
extern void sub_080A8BA8(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_080A5D38(u8 *arg0)
{
    u16 *a = *(u16 **)(arg0 + 0x38);
    u8 *p = *(u8 **)(arg0 + 0x3C);
    u8 *r10 = p + 0x34;
    u8 *r9 = p + 0x48;
    u8 zero;
    u32 t;

    t = (a[0] & 0x0FFF) | ((*(u16 *)(p + 0x22) + 8) << 12);
    zero = 0;
    a[0] = (u16)t;

    sub_08097F88(0, a, p, *(void **)(p + 0x28));
    sub_08097F88(2, a, p, *(void **)(p + 0x15C));
    sub_080142C0(arg0, *(void **)(p + 0x28));
    sub_080142C0(arg0, *(void **)(p + 0x15C));

    if (*(u16 *)p & 1)
    {
        s32 idx2;
        u8 *a18;
        s32 *litp;
        u8 b;

        sub_08013AC4(arg0);
        *(u8 *)(*(u32 *)(p + 0x28) + 1) = zero;
        *(u8 *)(*(u32 *)(p + 0x15C) + 1) = zero;
        idx2 = *(s16 *)(arg0 + 0x22) * 2;
        *(u8 *)((u32)idx2 + (u32)arg0 + 0x19) = zero;
        litp = (s32 *)0x08671BB0;
        a18 = arg0;
        a18 += 0x18;
        sub_080C31E4(a18, arg0 + 0x22, *litp);
        idx2 = *(s16 *)(arg0 + 0x22) * 2;
        *(u8 *)((u32)idx2 + (u32)arg0 + 0x19) = *(u8 *)((u32)idx2 + (u32)arg0 + 0x19) + 1;
        idx2 = *(s16 *)(arg0 + 0x22) * 2;
        a18 += idx2;
        b = *a18;
        sub_080C31E0(arg0, *(void **)(b * 4 + *(u32 *)(arg0 + 0x14)));
        return;
    }

    sub_080A8BA8(arg0, r9);
    if (sub_08013B5C(a, p) == 0)
    {
        s32 idx2;
        u8 *a18;
        u8 b;

        *(u32 *)(arg0 + 0x14) = 0x0866FF78;
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
        idx2 = *(s16 *)(arg0 + 0x22) * 2;
        *(u8 *)((u32)idx2 + (u32)arg0 + 0x19) = *(u8 *)((u32)idx2 + (u32)arg0 + 0x19) + 1;
        idx2 = *(s16 *)(arg0 + 0x22) * 2;
        a18 = arg0;
        a18 += 0x18;
        a18 += idx2;
        b = *a18;
        sub_080C31E0(arg0, *(void **)(b * 4 + *(u32 *)(arg0 + 0x14)));
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
    }
    sub_080A820C(arg0, a, r10, p, r9);
    sub_080A84AC(a, r10, p, r9);
    sub_080983E8(a);
    sub_08013C8C(arg0, a);
    if (*(s32 *)((u8 *)a + 0x18) > 0x00E00000)
    {
        *(s32 *)((u8 *)a + 0x18) = 0x00E00000;
    }
}
