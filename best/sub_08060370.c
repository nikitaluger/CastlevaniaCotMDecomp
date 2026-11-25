struct S_02021E90_370 {
    u8 pad0[0x143C];
    u8 f143C;
    u8 pad1[7];
    u8 f1444;
    u8 pad2[0xF];
    u32 f1454;
    u8 pad3[4];
    u8 f145C;
};
extern struct S_02021E90_370 D_02021E90;

void sub_08060370(void) {
    u8 t;
    D_02021E90.f1454 += 1;
    t = D_02021E90.f145C | 4;
    D_02021E90.f145C = t;
    if (t & 2) {
        D_02021E90.f145C = t & 0xFD;
        D_02021E90.f143C = D_02021E90.f1444;
    }
}
