extern u32 D_08671BB0;

void sub_080C31E4(void *, void *, u32);

void sub_080171A4(void *arg0)
{
    u8 *p = arg0;
    u8 *r2 = *(u8 **)(p + 0x3C);
    u8 *r1 = r2 + 0x48;

    *(u16 *)(r1 + 0x1A) = *(u16 *)(r1 + 0x1A) - 1;
    if ((s16)*(u16 *)(r1 + 0x1A) < 0)
    {
        *(u32 *)(r2 + 0x10) = 0;
        *(u16 *)(r1 + 0x16) = 0x1E;
        *(u8 *)(p + *(s16 *)(p + 0x22) * 2 + 0x19) = 0;
        sub_080C31E4(p + 0x18, p + 0x22, D_08671BB0);
    }
}

void sub_08016B88(void)
{
    u32 *base = (u32 *)0x020279D0;
    u32 *node = *(u32 **)((u8 *)base + 8);
    u32 *r3 = base;

    if (node != 0)
    {
        do
        {
            u32 *next = *(u32 **)((u8 *)node + 4);
            node[0] = 0;
            node[1] = 0;
            node = next;
        } while (node != 0);
    }
    r3[2] = 0;
    ((u8 *)r3)[1] = 0;
}
