extern u8 D_0866D7B4[];
void sub_080C31E0(void *, void *);
void sub_08011368(void *, void *, s32, s32);

void sub_0801F5F8(void *arg0)
{
    u32 *p3c = *(u32 **)((u8 *)arg0 + 0x3C);
    u8 *p;
    s16 idx;

    p3c[5] = 0;
    p3c[4] = 0;
    *(u32 *)((u8 *)arg0 + 0x14) = (u32)D_0866D7B4;
    *(s16 *)((u8 *)arg0 + 0x22) += 1;
    *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) += 1;
    idx = *(s16 *)((u8 *)arg0 + 0x22);
    p = (u8 *)arg0 + 0x18;
    sub_080C31E0(arg0, *(void **)(((u32)p[idx * 2] * 4) + *(u32 *)((u8 *)arg0 + 0x14)));
    *(s16 *)((u8 *)arg0 + 0x22) -= 1;
}

void sub_0801F02C(void *arg0)
{
    if ((*(u16 *)((u8 *)arg0 + 0x5C) & 2) == 0)
    {
        u32 *p = (u32 *)(*(u8 **)((u8 *)*(void **)((u8 *)arg0 + 0x6C) + 0x3C) + 0x58);
        s32 i;
        for (i = 5; i >= 0; i--)
        {
            if (*p == (u32)arg0)
                *p = 0;
            p++;
        }
    }
}

void sub_0801EF2C(void *arg0)
{
    u16 *p = (u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x48);
    *p -= 1;
    if ((s16)*p < 0)
        *p = 0;
}

void sub_0801FED0(void *arg0)
{
    void *r4 = *(void **)((u8 *)arg0 + 0x3C);
    void *r2 = *(void **)((u8 *)arg0 + 0x38);
    sub_08011368(r2, (u8 *)r4 + 0x34, 0x11, 1);
    *(s32 *)((u8 *)r4 + 0x48) -= 1;
    if (*(s32 *)((u8 *)r4 + 0x48) < 0)
        *(s32 *)((u8 *)r4 + 0x48) = 0;
}
