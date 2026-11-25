extern void sub_080BFBEC(void *a, void *b);
extern void sub_080BFBD2(void *a, void *b, s32 *c, s32 d);
extern void sub_080BFB68(void *p);

void sub_080BFCDC(void *a, void *self, u32 b, s32 val) {
    u8 x;
    sub_080BFBEC(a, self);
    ((u8 *)self)[0x12] = (u8)val;
    x = ((u8 *)self)[0x00];
    x |= 0x03;
    ((u8 *)self)[0x00] = x;
}

void sub_080BFCAC(void *arg0, void *arg1) {
    u8 *p;
    s32 idx;
    s32 *base;
    s32 *t;
    p = *(u8 **)((u8 *)arg1 + 0x40);
    *(u8 **)((u8 *)arg1 + 0x40) = p + 1;
    idx = (p[0] * 3) * 4;
    base = *(s32 **)((u8 *)arg0 + 0x30);
    t = (s32 *)((u8 *)base + idx);
    sub_080BFBD2(arg0, arg1, t, t[0]);
    *(s32 *)((u8 *)arg1 + 0x24) = t[0];
    sub_080BFBD2(arg0, arg1, t + 1, t[1]);
    *(s32 *)((u8 *)arg1 + 0x28) = t[1];
    sub_080BFBD2(arg0, arg1, t + 2, t[2]);
    *(s32 *)((u8 *)arg1 + 0x2C) = t[2];
}

void sub_080BFB88(void *arg0, void *arg1) {
    void *r4 = *(void **)((u8 *)arg1 + 0x20);
    while (r4 != NULL) {
        u8 r1 = *(u8 *)r4;
        if (0xC7 & r1) {
            *(u8 *)r4 = r1 | 0x40;
        }
        sub_080BFB68(r4);
        r4 = *(void **)((u8 *)r4 + 0x34);
    }
    ((u8 *)arg1)[0] = 0;
}

void sub_080BFB68(void *arg0) {
    void *r3 = *(void **)((u8 *)arg0 + 0x2C);
    if (r3 != NULL) {
        void *r1 = *(void **)((u8 *)arg0 + 0x34);
        void *r2 = *(void **)((u8 *)arg0 + 0x30);
        if (r2 != NULL) {
            *(void **)((u8 *)r2 + 0x34) = r1;
        } else {
            *(void **)((u8 *)r3 + 0x20) = r1;
        }
        if (r1 != NULL) {
            *(void **)((u8 *)r1 + 0x30) = r2;
        }
        *(void **)((u8 *)arg0 + 0x2C) = NULL;
    }
}
