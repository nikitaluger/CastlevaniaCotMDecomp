extern u32 sub_08005820(u32);
extern s32 sub_08011344(s32, s32, s32, s32);
extern s32 sub_08014938(s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *D_08671BD0;
extern s16 D_080CF1D2[];

void sub_0803A344(u8 *arg0) {
    u8 *self = arg0;
    void *a38 = *(void **)(self + 0x38);
    void *p3C = *(void **)(self + 0x3C);
    s32 a34 = (s32)((u8 *)p3C + 0x34);
    u8 *p48 = (u8 *)p3C + 0x48;
    s16 idx;
    u8 val;
    s32 t;
    s16 off;
    s16 v;
    s32 v8;
    s32 newv;
    if (*(s16 *)((u8 *)a38 + 0x20) == 0) {
        *(u8 *)(*(void **)(self + 0x30) + 0x80) = 1;
    }
    idx = *(s16 *)(self + 0x22);
    val = *(u8 *)(self + idx * 2 + 0x19);
    if (val > 9) {
        if (*(s32 *)(*(u8 **)(self + 0x30) + 0x2C) == 0) {
            *(u8 *)(p48 + 0x0C) = sub_08005820(3);
            t = *(u8 *)(p48 + 0x0D) - 1;
            *(u8 *)(p48 + 0x0D) = t;
            if ((u8)t == 0) {
                s16 idx2 = *(s16 *)(self + 0x22);
                s32 *g;
                *(u8 *)(self + idx2 * 2 + 0x19) = 0;
                g = (s32 *)0x08671BD0;
                sub_080C31E8(self + 0x18, self + 0x22, 0, *g);
            } else {
                v8 = *(s32 *)((u8 *)p3C + 8);
                if (sub_08014938(v8) == 1) {
                    newv = 0x10 | *(u16 *)((u8 *)a38 + 2);
                    *(u16 *)((u8 *)a38 + 2) = newv;
                } else {
                    *(u16 *)((u8 *)a38 + 2) &= 0xFFEF;
                }
                off = *(u8 *)(p48 + 0x0C);
                v = D_080CF1D2[off];
                sub_08011344((s32)a38, a34, v, 0);
                {
                    s16 idx2 = *(s16 *)(self + 0x22);
                    *(u8 *)(self + idx2 * 2 + 0x19) = 0;
                }
                {
                    s32 *g = (s32 *)0x08671BD0;
                    sub_080C31E8(self + 0x18, self + 0x22, 2, *g);
                }
            }
        }
    }
}
