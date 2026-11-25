extern u8 D_0866D67C[];
extern u8 D_0866D68C[];
extern u8 D_0866D69C[];
void _call_via_r1(void *, void *);

void sub_0801AF90(void *arg0)
{
    u8 *p = (u8 *)arg0;
    u8 *q = *(u8 **)(p + 0x3C);
    s16 idx;

    *(u32 *)(q + 0x68) = 0;
    *(u32 *)(q + 0x14) = 0;
    *(u32 *)(q + 0x10) = 0;
    *(u32 *)(p + 0x14) = (u32)D_0866D67C;
    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x22) + 1;

    idx = *(s16 *)(p + 0x22);
    *(u8 *)(p + idx * 2 + 0x19) = *(u8 *)(p + idx * 2 + 0x19) + 1;

    idx = *(s16 *)(p + 0x22);
    {
        s32 off = idx * 2;
        u8 *base = p + 0x18;
        _call_via_r1(arg0, *(void **)((u8 *)*(void **)(p + 0x14) + *(u8 *)(base + off) * 4));
    }

    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x22) - 1;
}

void sub_0801B300(void *arg0)
{
    u8 *p = (u8 *)arg0;
    u8 *q = *(u8 **)(p + 0x3C);
    s16 idx;

    *(u32 *)(q + 0x14) = 0;
    *(u32 *)(q + 0x10) = 0;
    *(u32 *)(q + 0x68) = 0;
    *(u32 *)(p + 0x14) = (u32)D_0866D68C;
    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x22) + 1;

    idx = *(s16 *)(p + 0x22);
    *(u8 *)(p + idx * 2 + 0x19) = *(u8 *)(p + idx * 2 + 0x19) + 1;

    idx = *(s16 *)(p + 0x22);
    {
        s32 off = idx * 2;
        u8 *base = p + 0x18;
        _call_via_r1(arg0, *(void **)((u8 *)*(void **)(p + 0x14) + *(u8 *)(base + off) * 4));
    }

    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x22) - 1;
}

void sub_0801B55C(void *arg0)
{
    u8 *p = (u8 *)arg0;
    u8 *q = *(u8 **)(p + 0x3C);
    s16 idx;

    *(u32 *)(q + 0x14) = 0;
    *(u32 *)(q + 0x10) = 0;
    *(u32 *)(q + 0x68) = 0;
    *(u32 *)(p + 0x14) = (u32)D_0866D69C;
    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x22) + 1;

    idx = *(s16 *)(p + 0x22);
    *(u8 *)(p + idx * 2 + 0x19) = *(u8 *)(p + idx * 2 + 0x19) + 1;

    idx = *(s16 *)(p + 0x22);
    {
        s32 off = idx * 2;
        u8 *base = p + 0x18;
        _call_via_r1(arg0, *(void **)((u8 *)*(void **)(p + 0x14) + *(u8 *)(base + off) * 4));
    }

    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x22) - 1;
}

void sub_080186DC(u16 *a, s16 b)
{
    s32 v = *a - b;
    *a = (u16)v;
    if ((s32)((u16)v << 16) <= 0x03E70000)
        *a = 1000;
}
