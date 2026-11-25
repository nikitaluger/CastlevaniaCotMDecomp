extern void sub_08005E80(s32);
extern s32 sub_0800B8C4(void *, s32);
extern s32 sub_080103F0(u8);
extern void sub_080C31E8(void *, void *, s32, s32);
struct S_02021E90 { u8 _0[0x146C]; u16 flags; };
extern struct S_02021E90 D_02021E90;
extern u8 D_02025368[];
extern u32 D_08671BD8;

struct P {
    u8 _0[0x600];
    u8 tab[0x35];
    u8 f635;
    u8 _636[2];
    u8 f638;
};

void sub_0800AB2C(u8 *arg0) {
    u8 *sp0;
    u8 **psp = &sp0;
    u8 *idxp;
    u8 temp0;
    u8 v8;
    u8 *p;
    u8 *base;
    u32 i;
    u8 *src;
    u8 *a018;
    u8 *a022;
    u8 *q;
    s32 *g;
    s32 sv;

    base = D_02025368;
    p = *(u8 **)(arg0 + 0x3C);
    v8 = ((struct P *)p)->f638;
    if (v8 != 0) {
        sv = sub_0800B8C4(arg0, 0);
        if (sv != 0) return;
        if ((D_02021E90.flags & 1) && (sub_080103F0(*(u8 *)(arg0 + 0x50)) != 0)) {
            sub_08005E80(0x157);
            idxp = (u8 *)(arg0 + 0x5C);
            *idxp = (u8)sv;
            idxp -= 4;
            *idxp = (u8)sv;
            i = 0;
            a018 = arg0 + 0x18;
            a022 = arg0 + 0x22;
            *psp = p + 0x600;
            src = base + 1;
            do {
                temp0 = src[i];
                (*psp)[i] = temp0;
                if ((temp0 & 0x80) != 0) *idxp = (u8)i;
                i++;
            } while (i <= 7);
            sv = *(s8 *)idxp;
            if ((*psp)[sv] != 0) {
                *idxp = *idxp + 1;
            }
            if (*(s8 *)idxp == 8) {
                *idxp = *idxp - 1;
            }
            ((struct P *)p)->f635 = 4;
            q = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(q + 0x17) = 0;
            g = (s32 *)0x08671BD8;
            sub_080C31E8(a018, a022, 0x10, *g);
            return;
        }
    } else if (D_02021E90.flags & 3) {
        sub_08005E80(0x159);
        ((struct P *)p)->f635 = v8;
        q = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(q + 0x17) = v8;
        g = (s32 *)0x08671BD8;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x10, *g);
    }
}
