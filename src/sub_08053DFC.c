
void sub_08053DFC(u8 *arg0, void *arg1) {
    u16 *r2 = (u16 *)0x080CFAF4;
    u16 v, v2, v3;
    switch (*(u16 *)(arg0 + 0x28) - 6) {
        case 0:
        case 1:
            *(u8 *)(*(u8 **)((u8 *)arg1 + 0x28) + 1) = 0;
            break;
        case 2:
            r2 = (u16 *)0x080CFAFC;
            break;
        case 24:
        case 29:
        case 34:
            r2 = (u16 *)0x080CFB0C;
            break;
        default:
            break;
    }
    v = *(u16 *)(arg0 + 0x28);
    v2 = v - 0x2A;
    if (v2 <= 0x0A) r2 = (u16 *)0x080CFB14;
    v3 = v - 0x0B;
    if (v3 <= 0x0E) r2 = (u16 *)0x080CFB04;
    *(u16 *)(*(u8 **)((u8 *)arg1 + 0x28) + 6) = r2[0];
    *(u16 *)(*(u8 **)((u8 *)arg1 + 0x28) + 8) = r2[1];
    *(u16 *)(*(u8 **)((u8 *)arg1 + 0x28) + 10) = r2[2];
    *(u16 *)(*(u8 **)((u8 *)arg1 + 0x28) + 12) = r2[3];
}
