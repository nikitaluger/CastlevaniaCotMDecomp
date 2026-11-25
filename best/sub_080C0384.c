struct S_080C0384 {
    u8 _0[0x24];
    u16 f24;
    u16 f26;
    u16 f28;
    u8 _2A[0x34 - 0x2A];
    u32 f34;
};

void sub_080C0384(struct S_080C0384 *arg, u16 v) {
    if (arg->f34 == 0x68736D53) {
        arg->f26 = v;
        arg->f24 = v;
        arg->f28 = 0x100;
    }
}
