extern u16 D_080CE688[];
extern u16 D_080CE690[];
extern u16 D_080CE698[];

struct S_1C9F8 {
    u8 pad[0x28];
    u8 * volatile field28;
};

void sub_0801C9F8(u8 *arg0, u8 *arg1)
{
    u16 *r3;
    struct S_1C9F8 *r2;
    s32 idx;

    r3 = D_080CE688;
    r2 = *(struct S_1C9F8 **)(arg0 + 0x3C);
    idx = *(u16 *)(arg1 + 0x28) - 0x32;

    switch (idx) {
    case 0:
    case 1:
        r2->field28[1] = 0;
        break;
    case 2:
    case 4:
        r3 = D_080CE698;
        break;
    case 9:
        r3 = D_080CE690;
        break;
    default:
        break;
    }

    *(u16 *)(r2->field28 + 6) = r3[0];
    *(u16 *)(r2->field28 + 8) = r3[1];
    *(u16 *)(r2->field28 + 0xA) = r3[2];
    *(u16 *)(r2->field28 + 0xC) = r3[3];
}
