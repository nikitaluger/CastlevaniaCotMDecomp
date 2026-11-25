s32 sub_0805FDF0(void);
s32 sub_0806111C(void);
s32 sub_080C31DC(u32);
s32 sub_080609B8(void);

s32 sub_0805FEC8(u16 arg0) {
    u16 temp_r5;
    u8 temp_r0;
    u8 temp_r1;
    s32 var_r0;
    u32 var_r1;
    u8 *r7;
    u8 *r4;
    u16 *r6;
    void *r5v;
    void *r4v;

    temp_r5 = arg0;
    r7 = (u8 *)0x02025358;
    r4 = (u8 *)0x02021E90;
    r6 = (u16 *)(r4 + 0x1440);
    if (*r6 == 0) {
        sub_0805FDF0();
        *r6 = 0x7FFF & temp_r5;
        if ((s32)(temp_r5 << 16) < 0) {
            *(u8 *)(r4 + 0x1442) = 1;
            var_r1 = 0x0867084C;
        } else {
            *(u8 *)(r4 + 0x1442) = 0;
            var_r1 = 0x086707D8;
        }
        *(u32 *)(r4 + 0x1454) = *(u32 *)((u8 *)(var_r1 + ((*r6 - 1) << 2)));
    }
    if (*(u8 *)(r4 + 0x145D) != 0) {
        sub_0806111C();
    }
    if ((*(u8 *)(r4 + 0x143C) != 0) && !(*(u8 *)(r4 + 0x145C) & 6)) {
        temp_r1 = r7[0x0C];
        if (!(temp_r1 & 0x80) && (temp_r1 != 0)) {
            if (*(u16 *)(0x02025FF0 + 0x28) & 1) {
                goto doblock;
            }
        } else if (*(u16 *)(r4 + 0x146C) & 1) {
            goto doblock;
        }
        goto skip;
doblock:
        *(u8 *)(r4 + 0x1444) = *(u8 *)(r4 + 0x143C);
        *(s8 *)(r4 + 0x1445) = 1;
        *(u8 *)(r4 + 0x143C) = 1;
        *(u8 *)(r4 + 0x145C) = (u8)(2 | *(u8 *)(r4 + 0x145C));
skip:;
    }
    r5v = (void *)0x020232E4;
    r4v = (void *)0x0866E9E0;
    do {
        temp_r0 = *(u8 *)(*(u32 *)r5v);
        if ((u32)temp_r0 <= 0x25) {
            var_r0 = sub_080C31DC(*(u32 *)(r4v + temp_r0 * 4));
        } else {
            var_r0 = sub_080609B8();
        }
    } while (var_r0 == 0);
    return var_r0 - 1;
}
