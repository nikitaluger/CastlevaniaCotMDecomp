extern u32 D_08671BB0;
extern u8 D_020279D0[];
extern u8 D_020207C0[];

void sub_080C31E4(void *, void *, u32);
void *sub_08016AB8(void);

void sub_08016B88(void)
{
    u8 *r0 = D_020279D0;
    u8 *r1 = *(u8 **)(r0 + 8);
    u8 *r3 = r0;

    if (r1 != 0)
    {
        u32 r2 = 0;
        do
        {
            u8 *tmp = *(u8 **)(r1 + 4);
            *(u32 *)r1 = r2;
            *(u32 *)(r1 + 4) = r2;
            r1 = tmp;
        } while (r1 != 0);
    }
    *(u32 *)(r3 + 8) = 0;
    *(u8 *)(r3 + 1) = 0;
}

void sub_080171A4(void *arg0)
{
    u8 *r3 = arg0;
    u8 *r2 = *(u8 **)(r3 + 0x3C);
    u8 *r1 = r2 + 0x48;

    *(u16 *)(r1 + 0x1A) = *(u16 *)(r1 + 0x1A) - 1;
    if ((s16)*(u16 *)(r1 + 0x1A) < 0)
    {
        *(u32 *)(r2 + 0x10) = 0;
        *(u16 *)(r1 + 0x16) = 0x1E;
        *(u8 *)(r3 + *(s16 *)(r3 + 0x22) * 2 + 0x19) = 0;
        sub_080C31E4(r3 + 0x18, r3 + 0x22, D_08671BB0);
    }
}

void *sub_08016AD8(void *arg0)
{
    u8 *r4 = arg0;
    u8 *r2 = sub_08016AB8();
    u8 *r1;
    u8 *r3;

    if (r2 == 0)
        return 0;

    r1 = *(u8 **)(D_020279D0 + 8);
    r3 = D_020279D0;
    while (r1 != 0)
    {
        u8 *next = *(u8 **)(r1 + 4);
        if (next == 0)
            break;
        r1 = next;
    }
    if (r1 == 0)
        *(u8 **)(r3 + 8) = r2;
    else
        *(u8 **)(r1 + 4) = r2;

    *(u8 **)r2 = r4;
    *(u32 *)(r2 + 4) = 0;
    *(u8 *)(r3 + 1) = *(u8 *)(r3 + 1) + 1;
    return r2;
}

void *sub_08016AB8(void)
{
    s32 r2 = 0;
    u8 *r1 = D_020207C0;

    while (r2 <= 0x7F)
    {
        if (*(u32 *)r1 == 0)
            return r1;
        r1 += 8;
        r2++;
    }
    return 0;
}
