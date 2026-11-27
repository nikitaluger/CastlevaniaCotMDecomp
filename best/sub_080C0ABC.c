typedef struct {
    void *f0;
    u32 f4;
    u8 f8;
    u8 f9;
    u8 padA[2];
    u32 fC;
    u8 pad10[0xC];
    u16 f1C;
    u16 f1E;
    u16 f20;
    u16 f22;
    u16 f24;
    u8 pad26[6];
    void *f2C;
    u32 f30;
    u32 f34;
} A;

typedef struct {
    volatile u8 b0;
    volatile u8 pad1;
    volatile u8 b2;
    volatile u8 b3;
    u32 f4;
    u32 arr[1];
} B;

typedef struct {
    u8 b0;
    u8 pad1[0x1F];
    u32 f20;
    u8 pad24[0x1C];
    u32 f40;
    u8 padEnd[0xC];
} P;

extern void sub_080C0020(A *, P *);
extern void setSoundMode(u8);

void sub_080C0ABC(A *a, B *b) {
    if (a->f34 == 0x68736D53) {
        a->f34 = a->f34 + 1;
        a->f4 = 0;
        a->f0 = b;
        a->f30 = b->f4;
        a->f9 = b->b2;
        a->fC = 0;
        a->f1C = 0x96;
        a->f20 = 0x96;
        a->f1E = 0x100;
        a->f22 = 0;
        a->f24 = 0;
        {
            s32 i = 0;
            P *p = a->f2C;
            while (i < b->b0 && i < a->f8) {
                sub_080C0020(a, p);
                p->b0 = 0xC0;
                p->f20 = 0;
                p->f40 = b->arr[i];
                i++;
                p++;
            }
            while (i < a->f8) {
                sub_080C0020(a, p);
                p->b0 = 0;
                i++;
                p++;
            }
        }
        {
            u8 mask = 0x80;
            if (b->b3 & mask)
                setSoundMode(b->b3);
        }
        a->f34 = 0x68736D53;
    }
}
