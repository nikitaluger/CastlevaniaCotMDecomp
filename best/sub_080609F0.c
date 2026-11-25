struct S_02021E90_609 {
    u8 pad0[0x143C];
    u8 f143C;
    u8 pad1[5];
    u8 f1442;
    u8 pad2[2];
    u8 f1445;
    u8 pad3[0xE];
    u8 *f1454;
};
extern struct S_02021E90_609 D_02021E90;

s32 sub_080609F0(void) {
    u8 v = D_02021E90.f1445;
    if (v != 0) {
        D_02021E90.f1445 = v - 1;
        return 0;
    }
    D_02021E90.f1445 = D_02021E90.f143C;
    return 2;
}
