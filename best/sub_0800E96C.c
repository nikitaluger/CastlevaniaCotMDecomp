extern void sub_08005E80(s32);
extern void sub_0800EB44(s32, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

struct S21E90 { u8 _0[0x146C]; u16 f146C; u16 f1470; };
extern struct S21E90 D_02021E90;
struct S278D0 { u8 _0[0x64]; u8 f64; u8 _65[0xFB-0x65]; s8 fFB; };
extern struct S278D0 D_020278D0;
extern u16 D_080CB1D6[];
extern u32 D_08671BD8;

struct Arg0 { u8 _0[0x17]; u8 f17; u8 _18[0x22-0x18]; s16 f22; };

void sub_0800E96C(struct Arg0 *arg0)
{
    u32 *ptrs[4];
    u8 *b;
    struct S21E90 *e2;
    u32 v, v2, i, j, found, idx;
    s32 h;
    s32 r4;
    s32 off1, off2;

    b = (u8 *)0x02025368;
    r4 = 0;
    off1 = 0x3BC;
    ptrs[0] = (u32 *)(b + off1);
    off2 = 0x3BE;
    ptrs[1] = (u32 *)(b + off2);
    off1 += 4;
    ptrs[2] = (u32 *)(b + off1);
    off2 += 4;
    ptrs[3] = (u32 *)(b + off2);

    v = D_02021E90.f1470 & 0xC0;
    e2 = &D_02021E90;
    if (v != 0xC0) {
        if (v != 0) sub_08005E80(0x140);
        if (D_02021E90.f1470 & 0x40) D_020278D0.fFB--;
        if (D_02021E90.f1470 & 0x80) D_020278D0.fFB++;
        if (D_020278D0.fFB < 0) D_020278D0.fFB = 3;
        if (D_020278D0.fFB > 3) D_020278D0.fFB = 0;
    }

    v2 = D_02021E90.f1470 & 0x30;
    if (v2 != 0x30 && v2 != 0) {
        sub_08005E80(0x139);
        idx = D_020278D0.fFB;
        h = *(u16 *)ptrs[idx];
        switch (h) {
        case 2: r4 = 1; break;
        case 0x100: r4 = 2; break;
        case 0x200: r4 = 3; break;
        }
        if (D_02021E90.f1470 & 0x20) r4--;
        if (D_02021E90.f1470 & 0x10) r4++;
        r4 &= 3;
        idx = D_020278D0.fFB;
        *(u16 *)ptrs[idx] = D_080CB1D6[r4];
    }

    if ((e2->f146C & 3) != 0) {
        found = 0;
        for (i = 0; i < 4; i++) {
            u16 h1 = *(u16 *)ptrs[i];
            for (j = i + 1; j < 4; j++) {
                if (h1 == *(u16 *)ptrs[j]) found = 1;
            }
        }
        if (found) {
            sub_08005E80(0x12D);
            sub_0800EB44(0x81E5, 2, 0xFC0);
        } else {
            sub_08005E80(0x14F);
            D_020278D0.f64 = found;
            *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x17) = found;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, D_08671BD8, 0x0E);
        }
    }
}
