struct A_0809F760 {
    u8 pad00[0x18];
    u8 arr18[0xA];
    s16 f22;
    u8 pad24[0x18];
    u32 f3C;
    u8 pad40[0xC];
    u32 f4C;
    u8 pad50[0xC];
    u32 f5C;
    u8 pad60[0xC];
    u8 f6C;
};
struct B_0809F760 {
    u8 pad00[0x48];
    u32 arr48[6];
    u32 arr60[6];
    u32 arr78[6];
    u16 f90;
    u16 f92;
    u8 f94;
    s8 f95;
    u8 f96;
};
struct Data_02025FF0 { u8 pad[0x174C]; u32 f174C; u32 f1750; };

extern u32 sub_08005910(u32, u32);
extern void sub_080A0668(u32, u32, u32, u32);
extern s32 sub_080C31E0(u32, u32);
extern void sub_080C31E4(u32, u32, u32);
extern u32 D_08671BFC;
extern u32 D_08671BB0;
extern struct Data_02025FF0 D_02025FF0;

void sub_0809F760(struct A_0809F760 *a) {
    struct B_0809F760 *b = (struct B_0809F760 *)a->f3C;
    u8 *r8 = (u8 *)b + 0x48;
    u32 idx3, i, endi;
    u32 *p;
    s8 v95;
    s32 res, absres, sign, r10v, v;
    u32 lo, hi, r5, zero;
    u8 *p94;

    if (*((u8 *)a + 0x6C) <= 2) goto end;
    idx3 = (u32)b->f94 * 3;
    v95 = (s8)b->f95;
    if (v95 == 0) goto branch_b;
    b->f96 = b->f96 - 1;
    if ((s8)b->f96 != 0) goto end;

    p94 = (u8 *)b + 0x94;
    i = idx3;
    endi = idx3 + 3;
    p = (u32 *)(r8 + i * 4);
    if (i < endi) {
        if (*p != 0) goto loop_done;
        do {
            p++;
            i++;
            if (i >= endi) goto loop_done;
        } while (*p == 0);
    }
loop_done:
    if (i == 3) {
        *(u8 *)(r8 + 0x4D) = 0;
        *p94 = *p94 + 1;
        goto end;
    }
    sub_080A0668((u32)a, ((u32 *)r8)[i], ((u32 *)(r8 + 0x18))[i], ((u32 *)(r8 + 0x30))[i]);
    zero = 0;
    *(u8 *)(r8 + 0x4E) = 0xF;
    ((u32 *)r8)[i] = zero;
    goto check;

branch_b:
    { u32 *fp = &D_08671BFC; res = sub_080C31E0(b->f92, *fp); }
    absres = res < 0 ? -res : res;
    if ((u32)absres <= 0x4FFF) goto end;
    sign = res > 0 ? 1 : -1;
    r5 = (0x2AAA * idx3 + b->f90) & 0xFFFF;
    r10v = idx3 != 0 ? 1 : -1;
    v = sub_08005910(D_02025FF0.f1750 - a->f5C, D_02025FF0.f174C - a->f4C);
    lo = (v - 0x1800) & 0xFFFF;
    hi = (v + 0x1800) & 0xFFFF;
    if (lo > hi) { hi += 0x10000; r5 += 0x10000; }
    if (r5 > lo && r5 < hi && r10v == sign) {
        sub_080A0668((u32)a, ((u32 *)r8)[idx3], ((u32 *)((u8 *)b + 0x60))[idx3], ((u32 *)((u8 *)b + 0x78))[idx3]);
        ((u32 *)r8)[idx3] = (u32)v95;
        *(u8 *)(r8 + 0x4D) = 1;
        *(u8 *)(r8 + 0x4E) = 0xF;
    }
check:
    p94 = (u8 *)b + 0x94;
    if (*p94 == 2) {
        *((u8 *)a + a->f22 * 2 + 0x19) = 0;
        sub_080C31E4((u32)((u8 *)a + 0x18), (u32)((u8 *)a + 0x22), D_08671BB0);
    }
end:
    ;
}
