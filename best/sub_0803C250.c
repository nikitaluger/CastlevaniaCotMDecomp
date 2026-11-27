struct C250Entry { s32 a; s32 b; };
extern struct C250Entry D_080CF308[];
extern u8 D_080CF338[];
extern void sub_0808DBF8(s32, s32, u16);
extern void sub_0808DC40(s32, s32, u16);
extern void sub_0803C5F4(u32, u16 *, u8, u8, s32, s32, s32, s32);
extern void sub_08185780(s32);
extern void _call_via_r1(void *, void *);

void sub_0803C250(void *arg0) {
    u8 *p = (u8 *)arg0;
    u16 *spr = *(u16 **)(p + 0x38);
    u8 *state = *(u8 **)(p + 0x3C);
    u8 *emitter = state;
    s32 a, b;
    u8 idx;

    emitter += 0x48;
    if (spr[1] & 0x10) {
        idx = emitter[4];
        a = -D_080CF308[idx].a;
    } else {
        idx = emitter[4];
        a = D_080CF308[idx].a;
    }
    b = D_080CF308[idx].b;

    switch (D_080CF338[idx]) {
    case 0:
        sub_0808DC40(*(s32 *)(p + 8) + a, *(s32 *)(state + 0xC), 8);
        break;
    case 1:
        sub_0808DBF8(*(s32 *)(p + 8) + a, *(s32 *)(state + 0xC), 8);
        break;
    }
    sub_0803C5F4(0xC, spr, 1, 2, *(s32 *)(p + 8) + a, *(s32 *)(state + 0xC) + b, 0xC00, 0x14002800);
    sub_08185780(0x89);
    _call_via_r1(p, *(void **)(p + 0x24));
}
