extern s32 sub_08007EA8(s32);
extern void sub_080014D0(s32, s32);
extern u8 D_02025358[];
extern u8 gMainWorkspace[];

void selectSceneMode(void)
{
    u8 *q = D_02025358;
    u8 *p = gMainWorkspace;
    u8 *p2;
    s32 k;
    u8 t;

    k = (p[0x50] << 8) + p[0x51];
    p2 = p;
    switch (k) {
    case 0x0715:
        if (sub_08007EA8(0xB6) != 0 && sub_08007EA8(0xBD) == 0) {
            *(u32 *)&p[0x10] = 6;
            sub_080014D0(*(s32 *)&p[0x1864], 0x7B);
        }
        break;
    case 3:
        *(u32 *)&p[0x10] = 0x0F;
        break;
    case 0:
        if (q[0x0C] == 0 && sub_08007EA8(0x31) == 0)
            *(u32 *)&p[0x10] = 1;
        break;
    case 0x0E01:
    case 0x0E02:
    case 0x0E03:
    case 0x0E07:
    case 0x0E09:
    case 0x0E11:
    case 0x0E13:
    case 0x0E16:
        *(u32 *)&p2[0x10] = 0x12;
        break;
    case 0x0E0B:
    case 0x0E0E:
    case 0x0E0F:
    case 0x0E12:
    case 0x0E05:
    case 0x0E08:
    case 0x0E14:
    case 0x0E17:
        *(u32 *)&p2[0x10] = 0x14;
        break;
    case 0x0E04:
        t = p[0x53];
        if (t == 3 || t == 7)
            *(u32 *)&p[0x10] = 0x11;
        break;
    case 0x0E0A:
        t = p[0x53];
        if (t == 9 || t == 0x0D)
            *(u32 *)&p[0x10] = 0x11;
        break;
    case 0x0E10:
        t = p[0x53];
        if (t == 0x0F || t == 0x12)
            *(u32 *)&p[0x10] = 0x13;
        break;
    case 0x0E15:
        if (p[0x53] == 0x14)
            *(u32 *)&p[0x10] = 0x13;
        break;
    case 0x0E06:
        t = p[0x53];
        if (t == 5 || t == 8)
            *(u32 *)&p[0x10] = 0x13;
        t = p2[0x53];
        if (t == 0x13 || t == 0x16)
            *(u32 *)&p2[0x10] = 0x11;
        break;
    case 0x0E0C:
        t = p[0x53];
        if (t == 0x0B || t == 0x0E)
            *(u32 *)&p[0x10] = 0x13;
        t = p2[0x53];
        if (t == 0x11)
            *(u32 *)&p2[0x10] = t;
        break;
    case 0x0E18:
        *(u32 *)&p[0x10] = 0x13;
        break;
    }
}
