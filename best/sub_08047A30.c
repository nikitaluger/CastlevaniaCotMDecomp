extern u16 D_080CF8B0[];

struct Inner_A30 { u8 pad[6]; u16 a, b, c, d; };
struct Outer_A30 { u8 pad[0x28]; struct Inner_A30 * volatile ptr; };

void sub_08047A30(void *arg0, void *arg1) {
    u8 *p;
    struct Inner_A30 *d;
    p = (u8 *)D_080CF8B0;
    switch (*(u16 *)((u8 *)arg0 + 0x28)) {
    case 0x23: p += 8; break;
    case 0x2A: p += 0x10; break;
    }
    d = ((struct Outer_A30 *)arg1)->ptr;
    d->a = *(u16 *)(p + 0);
    d = ((struct Outer_A30 *)arg1)->ptr;
    d->b = *(u16 *)(p + 2);
    d = ((struct Outer_A30 *)arg1)->ptr;
    d->c = *(u16 *)(p + 4);
    d = ((struct Outer_A30 *)arg1)->ptr;
    d->d = *(u16 *)(p + 6);
}
