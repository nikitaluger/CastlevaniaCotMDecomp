extern u16 sub_08007D30(s32, s32, s32);
extern void sub_0808D1E4(void);
extern u8 D_02023130[];
extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u8 D_080E068C[];
extern u8 D_0866EB08[];
extern u8 D_0866F840[];

struct PtrAData {
    u8 pad[0x94];
    u8 f94;
    u8 f95;
    u8 f96[5];
};

void sub_0806CD80(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3)
{
    struct PtrAData *ptrA = (struct PtrAData *)D_02025368;
    u8 *ptrB = D_02025FF0;
    s32 temp_r4;
    s32 var_r3;
    u8 *var_r2;
    u8 *temp_r7;
    u8 *temp_r3;
    s32 temp_r4_2;
    u8 *temp_r5;
    u8 *temp_r3_2;
    u8 *var_r0;
    u8 *var_r0_2;
    u8 temp_r4_3;

    if (*(vu32 *)&ptrB[0x20] & 1) return;
    if (arg0[0x18] == 0x2E) return;

    temp_r4 = sub_08007D30(
        (s32)(ptrB[0x18A8] << 6) + (s32)D_02023130,
        (s32)*(u32 *)arg3,
        (s32)*(u32 *)(arg3 + 4) - (s32)*(u32 *)(arg2 + 0x3C));
    if (temp_r4 == 0) return;

    var_r3 = ptrA->f94 * 4;
    temp_r7 = *(u8 **)&D_0866F840[var_r3] + (ptrA->f95 * 0x60);
    temp_r3 = *(u8 **)&D_0866EB08[var_r3] + (ptrA->f95 * 2);
    ptrB[0x14C6] = temp_r3[0];
    ptrB[0x14C7] = temp_r3[1];
    temp_r4_2 = temp_r4 * 8;
    ptrA->f94 = *(u8 *)(*(u32 *)(temp_r7 + 0x5C) + temp_r4_2 - 0xC0);
    ptrA->f95 = *(u8 *)(*(u32 *)(temp_r7 + 0x5C) + temp_r4_2 - 0xC0 + 1);
    *(u16 *)&ptrB[0x14D8] = *(u16 *)(*(u32 *)(temp_r7 + 0x5C) + temp_r4_2 - 0xC0 + 4);
    *(u16 *)&ptrB[0x14DA] = *(u16 *)(*(u32 *)(temp_r7 + 0x5C) + temp_r4_2 - 0xC0 + 6);
    sub_0808D1E4();

    var_r3 = 0;
    var_r2 = D_080E068C;
    do {
        if (ptrA->f94 == var_r2[0] && ptrA->f95 == var_r2[1]) {
            ptrA->f96[var_r3] = 1;
        }
        var_r2 += 4;
        var_r3++;
    } while (var_r3 <= 4);

    var_r3 = ptrA->f94 * 4;
    temp_r5 = *(u8 **)&D_0866F840[var_r3] + (ptrA->f95 * 0x60);
    temp_r3_2 = *(u8 **)&D_0866EB08[var_r3] + (ptrA->f95 * 2);
    ptrB[0x14C4] = temp_r3_2[0];
    ptrB[0x14C5] = temp_r3_2[1];
    if (*(u8 *)(temp_r7 + 0x50) == 0) var_r0 = temp_r7 + 0x34;
    else var_r0 = temp_r7 + 0x44;
    if (*(u8 *)(temp_r5 + 0x50) == 0) var_r0_2 = temp_r5 + 0x34;
    else var_r0_2 = temp_r5 + 0x44;

    temp_r4_3 = *(u8 *)(*(u32 *)(temp_r7 + 0x5C) + temp_r4_2 - 0xC0 + 2);
    switch (temp_r4_3) {
    case 1:
        *(u32 *)&ptrB[0x14D0] = 0x100000;
        *(u32 *)&ptrB[0x14D4] = 0;
        if (!(*var_r0 & temp_r4_3)) *(u32 *)&ptrB[0x14D0] = 0x200000;
        *(u32 *)&ptrB[0x14C8] = *(u32 *)arg3 + *(u32 *)&ptrB[0x14D0];
        var_r3 = *(u32 *)(arg3 + 4);
        goto store_bc;
    case 2:
        *(u32 *)&ptrB[0x14D0] = 0xFFF00000;
        *(u32 *)&ptrB[0x14D4] = 0;
        if (!(*var_r0_2 & 1)) *(u32 *)&ptrB[0x14D0] = 0xFFE00000;
        *(u32 *)&ptrB[0x14C8] = *(u32 *)arg3 + *(u32 *)&ptrB[0x14D0];
        var_r3 = *(u32 *)(arg3 + 4);
        goto store_bc;
    case 3:
        *(u32 *)&ptrB[0x14D0] = 0;
        *(u32 *)&ptrB[0x14D4] = 0xFFF00000;
        *(u32 *)&ptrB[0x14C8] = *(u32 *)arg3;
        var_r3 = 0xFFF00000;
        goto add_bc;
    case 4:
        *(u32 *)&ptrB[0x14D0] = 0;
        *(u32 *)&ptrB[0x14D4] = 0x100000;
        *(u32 *)&ptrB[0x14C8] = *(u32 *)arg3;
        var_r3 = 0x100000;
add_bc:
        var_r3 = *(u32 *)(arg3 + 4) + var_r3;
store_bc:
        *(u32 *)&ptrB[0x14CC] = var_r3;
        break;
    }
    *(u32 *)&ptrB[0x14B4] = 0x111;
    *(vu32 *)&ptrB[0x1844] |= 0x06000000;
}
