extern u16 D_080CF8D0[];

void sub_08048030(void *arg0, void *arg1)
{
    void *a1 = arg1;
    u16 *base = D_080CF8D0;
    int v = *(u16 *)((u8 *)arg0 + 0x28);

    if (v == 0x35) goto _58;
    if (v > 0x35) goto _48;
    if (v == 0x34) goto _54;
    goto _5A;

_48:
    if (v > 0x37) goto _5A;
    *(u8 *)(*(u8 *volatile *)((u8 *)a1 + 0x28) + 1) = 0;
    goto _5A;
_54:
    base += 4;
    goto _5A;
_58:
    base += 8;

_5A:
    *(u16 *)(*(u8 *volatile *)((u8 *)a1 + 0x28) + 6) = base[0];
    *(u16 *)(*(u8 *volatile *)((u8 *)a1 + 0x28) + 8) = base[1];
    *(u16 *)(*(u8 *volatile *)((u8 *)a1 + 0x28) + 0xA) = base[2];
    *(u16 *)(*(u8 *volatile *)((u8 *)a1 + 0x28) + 0xC) = base[3];
}
