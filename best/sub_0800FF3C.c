extern void sub_0806D7F4(unsigned int);
extern unsigned int sub_0806D81C(unsigned int);
extern unsigned int sub_0806D860(unsigned int);
extern void sub_0806D894(unsigned int);
extern void sub_0806D8C0(unsigned int);
extern void sub_080C2F20(void);
extern unsigned int D_02025368[];

int sub_0800FF3C(int arg0)
{
    unsigned int *base = D_02025368;
    int ret = 1;
    unsigned int idx = (unsigned int)arg0 - 0x29;
    unsigned int r;
    unsigned int tmp;

    if (idx < 0x0E) {
        switch (idx) {
        case 0:
            if (base[0xB1] != base[0xB2])
                sub_0806D7F4(0x140000);
            break;
        case 1:
            if (base[0xB1] != base[0xB2])
                sub_0806D7F4(0x320000);
            break;
        case 2:
            if (base[0xB1] != base[0xB2])
                sub_0806D7F4(0x640000);
            break;
        case 3:
            if (base[0xB1] != base[0xB2])
                sub_0806D7F4(0xFA0000);
            break;
        case 4:
            if (base[0xB1] != base[0xB2])
                sub_0806D7F4(0);
            break;
        case 5:
            if ((unsigned char)sub_0806D81C(0xF) == 2)
                sub_080C2F20();
            break;
        case 6:
            r = sub_0806D860(1);
            if ((unsigned char)r == 4)
                sub_0806D894((unsigned char)r);
            break;
        case 7:
            if (base[0xB3] != base[0xB4]) {
                tmp = base[0xB4] << 1;
                goto call894;
            }
            break;
        case 8:
            if (base[0xB3] != base[0xB4]) {
                tmp = base[0xB4] * 5 * 10;
                goto call894;
            }
            break;
        case 9:
            if (base[0xB3] != base[0xB4])
                sub_0806D8C0(0);
            break;
        case 10:
            if (*(short *)((char *)base + 0x2D4) != *(short *)((char *)base + 0x2D6))
                sub_0806D8C0(0x0A);
            break;
        case 11:
            if (*(short *)((char *)base + 0x2D4) != *(short *)((char *)base + 0x2D6))
                sub_0806D8C0(0x19);
            break;
        case 12:
            if (*(short *)((char *)base + 0x2D4) != *(short *)((char *)base + 0x2D6))
                sub_0806D8C0(0x32);
            break;
        case 13:
            if (*(short *)((char *)base + 0x2D4) != *(short *)((char *)base + 0x2D6))
                sub_0806D8C0(0x64);
            else
                ret = 0;
            break;
        call894:
            sub_0806D894(tmp);
            break;
        }
    }

    return ret;
}
