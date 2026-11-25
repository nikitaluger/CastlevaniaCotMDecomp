extern u8 D_02025FF0[];
extern u32 D_080DEA88[];

void sub_08086240(u32 *arg0, u32 arg1)
{
    u32 idx;
    u32 *p;

    idx = (u32)(D_02025FF0[0x14EE] - 0x11);
    if (idx > 0x49) {
        return;
    }
    switch (idx) {
    default:
        break;
    }
    if (arg1 == 9) {
        p = (u32 *)((u8 *)D_080DEA88 + 0x164);
        arg0[0x30 / 4] = *p;
    } else if (arg1 == 0xB) {
        p = (u32 *)((u8 *)D_080DEA88 + 0x18C);
        arg0[0x30 / 4] = *p;
    }
}
