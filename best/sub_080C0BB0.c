extern void sub_080C0020(void *, u8 *);

struct Entry {
    u8 flags;
    u8 pad[0x12];
    u8 b13;
    u8 pad2[0x3C];
};
struct S {
    u8 pad0[8];
    u8 count;
    u8 pad9[0x1B];
    u16 f24;
    u16 f26;
    u16 f28;
    struct Entry *ptr;
};

void sub_080C0BB0(struct S *self)
{
    u16 mask;
    u16 f24;
    u16 c;
    u32 v;
    u32 w;
    s32 count;
    struct Entry *p;
    u8 fl;

    f24 = self->f24;
    if (f24 == 0) {
        return;
    }
    mask = 0xFFFF;
    c = --self->f26;
    if ((c << 16) != 0) {
        return;
    }
    v = self->f28 - 0x10;
    self->f28 = (u16)v;
    w = v & mask;
    if (((s32)w << 16) <= 0) {
        count = self->count;
        p = self->ptr;
        if (count > 0) {
            do {
                sub_080C0020(self, (u8 *)p);
                p->flags = 0;
                count--;
                p += 1;
            } while (count > 0);
        }
    } else {
        self->f26 = f24;
        count = self->count;
        p = self->ptr;
        if (count > 0) {
            do {
                fl = p->flags;
                if (fl & 0x80) {
                    p->b13 = self->f28 >> 2;
                    p->flags = fl | 3;
                }
                count--;
                p += 1;
            } while (count > 0);
        }
    }
}
