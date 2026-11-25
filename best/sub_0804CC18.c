extern u16 D_080CF9A8[];

struct Inner_CC18 { u8 pad[6]; u16 a, b, c, d; };
struct Outer_CC18 { u8 pad[0x28]; struct Inner_CC18 * volatile ptr; };

void sub_0804CC18(void *arg0, void *arg1) {
    u8 *p;
    struct Inner_CC18 *d;
    struct Outer_CC18 *outer;
    outer = (struct Outer_CC18 *)*(void **)((u8 *)arg0 + 0x3C);
    p = (u8 *)D_080CF9A8;
    switch (*(u16 *)((u8 *)arg1 + 0x28)) {
    case 0x15:
    case 0x16:
    case 0x1B:
        outer->ptr->pad[1] = 0;
        break;
    }
    d = outer->ptr; d->a = *(u16 *)(p + 0);
    d = outer->ptr; d->b = *(u16 *)(p + 2);
    d = outer->ptr; d->c = *(u16 *)(p + 4);
    d = outer->ptr; d->d = *(u16 *)(p + 6);
}
