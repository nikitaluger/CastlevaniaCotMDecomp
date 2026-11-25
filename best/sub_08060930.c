struct S_02021E90 {
    u8 pad[0x1454];
    u32 v1454;
    u16 pad2;
    u16 v145A;
    u8 v145C;
};
extern struct S_02021E90 D_02021E90;

s32 sub_08060930(void) {
    struct S_02021E90 *p = &D_02021E90;
    if (p->v145C & 2) {
        p->v145A = 0;
        goto block_5;
    }
    if (p->v145A == 0) {
        u8 *q = (u8 *)p->v1454;
        p->v145A = (u16)(q[1] * 6);
    }
    p->v145A--;
    if (p->v145A == 0) {
block_5:
        p->v1454 += 2;
        return 0;
    }
    return 2;
}
