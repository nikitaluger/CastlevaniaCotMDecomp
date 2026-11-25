struct S { u8 b[0x20]; };

extern struct S *sub_080BFBEC(void *a, void *b, void *c, u32 d);

void sub_080BFD2C(void *a, void *b, void *c, u32 d)
{
    struct S *p = sub_080BFBEC(a, b, c, d);
    p->b[0x1B] = (u8)d;
}

void sub_080BFD38(void *a, void *b, void *c, u32 d)
{
    struct S *p = sub_080BFBEC(a, b, c, d);
    if (p->b[0x18] != (u8)d) {
        p->b[0x18] = (u8)d;
        p->b[0] |= 0x0F;
    }
}

void sub_080BFD50(void *a, void *b, void *c, u32 d)
{
    struct S *p = sub_080BFBEC(a, b, c, d);
    p->b[0x0C] = (u8)(d - 0x40);
    p->b[0] |= 0x0C;
}

void sub_080BFD04(void *a, void *b, void *c, u32 d)
{
    struct S *p = sub_080BFBEC(a, b, c, d);
    p->b[0x0E] = (u8)(d - 0x40);
    p->b[0] |= 0x0C;
}
