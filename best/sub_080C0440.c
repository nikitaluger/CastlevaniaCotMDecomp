extern u8 D_08106DCC[];
extern u8 D_08106E38[];
extern void sub_080C0ABC(s32, s32);

inline u8 *inline_fn(u8 **arg0, u32 arg1) { return (*arg0) + arg1; }

void sub_080C0440(u32 arg0) {
    u32 off;
    u8 *t;
    u8 *e;
    u8 **ep;
    s32 nv;
    off = arg0 << 16;
    t = D_08106DCC;
    e = D_08106E38;
    off >>= 13;
    nv = *(u16 *)((off + e) + 4);
    nv = *(s32 *)(t + nv * 12);
    ep = &e;
    sub_080C0ABC(nv, *(s32 *)inline_fn(ep, off));
}
