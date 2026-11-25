extern void sub_080C13E0(void *);

struct Entry {
    u8 flags;
    u8 pad[0x16];
    u8 field_17;
    u8 pad2[0x38];
};
struct S {
    u8 pad0[8];
    u8 count;
    u8 pad9[0x23];
    struct Entry *ptr;
    u8 pad30[4];
    u32 magic;
};

void sub_080C1400(struct S *arg0, u16 arg1, u8 arg2)
{
    if (arg0->magic == 0x68736D53) {
        s32 count;
        struct Entry *p;
        u32 mask;
        arg0->magic++;
        count = arg0->count;
        p = arg0->ptr;
        mask = 1;
        if (count > 0) {
            u8 v = arg2;
            do {
                if (arg1 & mask) {
                    u32 bit = 0x80;
                    bit &= p->flags;
                    if (bit != 0) {
                        p->field_17 = arg2;
                        if (v == 0)
                            sub_080C13E0(p);
                    }
                }
                count--;
                p++;
                mask <<= 1;
            } while (count > 0);
        }
        arg0->magic = 0x68736D53;
    }
}
