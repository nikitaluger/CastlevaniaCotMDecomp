extern u16 D_080CE6A0[];

struct In1D678 { u8 pad[6]; u16 a, b, c, d; };
struct Out1D678 { u8 pad[0x28]; struct In1D678 * volatile ptr; };

void sub_0801D678(void *arg0, void *arg1) {
    struct Out1D678 *c;
    struct In1D678 *d;
    u8 *p;
    c = *(struct Out1D678 **)((u8 *)arg0 + 0x3C);
    p = (u8 *)D_080CE6A0;
    switch (*(u16 *)((u8 *)arg1 + 0x28)) {
    case 0x2D: p += 0x10; break;
    case 0x2E: p += 8; break;
    }
    d = c->ptr; d->a = *(u16 *)(p + 0);
    d = c->ptr; d->b = *(u16 *)(p + 2);
    d = c->ptr; d->c = *(u16 *)(p + 4);
    d = c->ptr; d->d = *(u16 *)(p + 6);
}
