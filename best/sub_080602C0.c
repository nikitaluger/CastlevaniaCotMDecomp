struct S_02021E90b_2C0 {
    u8 pad[0x1443];
    u8 v1443;
    u8 pad1[4];
    s32 v1448;
    s32 v144C;
    u8 pad2[4];
    s32 v1454;
    u8 pad3[4];
    u8 v145C;
};
extern struct S_02021E90b_2C0 D_02021E90;

void sub_080602C0(void) {
    struct S_02021E90b_2C0 *p = &D_02021E90;
    if (p->v145C & 8) {
        s32 *q = &p->v1448;
        *q = q[1] + 0x2E0;
    } else {
        p->v1448 = p->v144C + 0x2A0;
    }
    p->v144C = p->v1448;
    p->v1443 = 0;
    p->v1454 += 1;
}
