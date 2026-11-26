struct S_08002C94 {
    u16 f00;
    u16 f02;
    u8 pad_04[0x24];
    void *f28;
    struct S_08002C94 *f2C;
    struct S_08002C94 *f30;
    u8 pad_34[2];
    u16 f36;
    void *f38;
    struct { void *p; u8 pad[12]; } f3C[8];
};
struct S_base { u8 pad[0x554]; u16 val; };
extern struct S_base gCameraState;
s32 sub_080035AC(void *);
void sub_080035DC(void *);
void sub_08002DB4(void *, u16);

static inline u32 mask_f00(void) { u32 m = 0xFFFF8000; return m; }

void sub_08002C94(struct S_08002C94 *arg0)
{
    struct S_08002C94 *p, *q, *r;
    void *saved, *f38;
    s32 i, mask;
    u32 m0, t0;
    vu16 *temp;

    temp = (vu16 *)&arg0->f00;
    t0 = *temp;
    m0 = mask_f00();
    arg0->f00 = m0 | t0;
    arg0->f02 = 0x8000 | arg0->f02;

    saved = arg0->f28;
    p = saved;
    if (p) {
        if (p->f30 == arg0) {
            q = arg0->f30;
            if (!q) q = arg0->f2C;
            p->f30 = q;
        } else {
            struct S_08002C94 *w = p->f30;
            while (arg0 != w->f2C) w = w->f2C;
            r = arg0->f30;
            q = w;
            if (!r) r = arg0->f2C;
            q->f2C = r;
        }
    }
    q = arg0->f30;
    f38 = arg0->f38;
    if (q) {
        struct S_08002C94 *w = q;
        while (w->f2C) {
            if (w->f28) w->f28 = saved;
            w = w->f2C;
        }
        w->f2C = arg0->f2C;
    }
    if (sub_080035AC(f38)) sub_080035DC(arg0->f38);
    mask = 1;
    i = 0;
    do {
        if (arg0->f36 & mask) sub_080035DC(arg0->f3C[i].p);
        mask <<= 1;
        i++;
    } while (i <= 7);
    sub_08002DB4(arg0, gCameraState.val);
}
