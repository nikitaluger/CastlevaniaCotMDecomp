extern s32 sub_08005910(s32 a, s32 b);
extern void sub_0801468C(void *a);
extern s32 sub_080C31E4(void *a, void *b, s32 c);
extern s32 sub_080C31E0(void *a, u32 b);

extern u8 D_02025FF0[];

struct S_3C
{
    u8 _0[8];
    s32 unk8;
    s32 unkC;
};
struct S_48
{
    u8 _0[0x14];
    s32 unk14;
    s32 unk18;
};

void sub_080AB368(u8 *self)
{
    u8 *r8;
    struct S_3C *ptr;
    struct S_48 *r7;
    volatile s32 *d;
    s32 f174C;
    s32 v0;
    s32 v1;
    s32 res;

    r8 = *(u8 **)(self + 0x38);
    ptr = *(struct S_3C **)(self + 0x3C);
    r7 = (struct S_48 *)((u8 *)ptr + 0x48);

    d = (volatile s32 *)D_02025FF0;
    (void)d[0x1750 / 4];
    v0 = 0x380000;
    f174C = *(s32 *)(D_02025FF0 + 0x174C);

    if (f174C > ptr->unk8)
        v1 = f174C + 0x200000;
    else
        v1 = f174C + 0xFFE00000;

    if (ptr->unk8 <= 0x7FFFFF)
        v1 = 0xA00000;
    if (ptr->unk8 > 0x1800000)
        v1 = 0x1600000;

    v0 = v0 - ptr->unkC;
    v1 = v1 - ptr->unk8;

    res = sub_08005910(v0, v1);
    r7->unk14 = res;
    r7->unk18 = 0;

    sub_0801468C(r8);

    *((u8 *)(self + ((s16)(*(u16 *)(self + 0x22)) * 2) + 0x19)) = 0;
    {
        s32 *g = (s32 *)0x08671BB0;
        u8 *base18 = self + 0x18;
        sub_080C31E4(base18, self + 0x22, *g);
    }
    *((u8 *)(self + ((s16)(*(u16 *)(self + 0x22)) * 2) + 0x19)) += 1;
    {
        u8 *base18 = self + 0x18;
        s32 off;
        u8 *base;
        u8 byte;
        u32 val;

        off = (s16)(*(u16 *)(self + 0x22));
        off *= 2;
        base = base18 + off;
        byte = *base;
        val = *(u32 *)(self + 0x14);
        sub_080C31E0(self, *(u32 *)((u8 *)val + (byte * 4)));
    }
}
