extern void sub_080BFBEC(void *a, void *b);
extern void sub_080BFBF8(void *a, void *b);

void sub_080BFC78(void *a, void *self, u32 b, s32 val) {
    sub_080BFBEC(a, self);
    ((u8 *)self)[0x1D] = (u8)val;
}

void sub_080BFC84(void *self, void *b, u32 c, s32 val) {
    s32 t;
    u16 u;
    sub_080BFBEC(self, b);
    t = val * 2;
    *(s16 *)((u8 *)self + 0x1C) = (s16)t;
    u = *(u16 *)((u8 *)self + 0x1E);
    t = (t * u) >> 8;
    *(s16 *)((u8 *)self + 0x20) = (s16)t;
}

void sub_080BFC98(void *a, void *self, u32 b, s32 val) {
    u8 x;
    sub_080BFBEC(a, self);
    ((u8 *)self)[0x0A] = (u8)val;
    x = ((u8 *)self)[0x00];
    x |= 0x0C;
    ((u8 *)self)[0x00] = x;
}

void sub_080BFC48(void *a, void *self) {
    u8 **pp;
    u8 *p;
    u8 c;
    pp = (u8 **)((u8 *)self + 0x40);
    p = *pp;
    if (p[0] == 0) {
        *pp = p + 1;
        sub_080BFBF8(a, self);
        return;
    }
    c = ((u8 *)self)[3] + 1;
    ((u8 *)self)[3] = c;
    sub_080BFBEC(a, self);
    ((u8 *)self)[3] = 0;
    *pp = p + 5;
}
