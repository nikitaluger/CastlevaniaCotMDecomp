typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s16 f20;
    s16 f22;
} Arg1;

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s32 f8;
    s32 fC;
} Out;

typedef struct {
    s32 sp0;
    Out *sp4;
    s32 sp8;
} Early;

extern s32 sub_08005910(s32, s32);
extern s32 sub_080059DC(s32, s32);
extern s32 sub_080C364C(s32, s32);
extern s32 _call_via_r1(s32, s32);
extern vu32 D_040000D4[];
extern s32 D_08671BFC;
extern s32 D_08671C00;
extern s32 D_08671C04;

void sub_08004A14(s32 arg0, Arg1 *arg1, Out *arg2, s32 arg3, s32 arg4) {
    Early e;
    volatile s32 spC;
    volatile s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    u32 sp40;
    s32 temp_r5_2, mid;
    s32 temp_r4, temp_r5, temp_r6;
    s32 var_r10, var_r7;
    s32 var_r4, var_r5, var_r5_2;
    s32 temp_r0, temp_r0_2;
    s32 var_r1, var_r1_2;
    u32 temp_r10_2;
    u32 var_r10_2, var_r7_2;
    s32 temp_r1_3, temp_r1_4;
    s32 temp_r6_2, temp_r6_3;
    s32 temp_r9, temp_r7;
    u32 var_r10_3;
    s32 var_r8;
    Out *var_r6;
    u32 temp_r5_4;
    s32 temp_r4_4, temp_r1_5, temp_r0_4, temp_r0_5, temp_r0_6, temp_r1_6, temp_r4_5;
    s32 temp_r1_2, temp_r0_5b;
    Arg1 *ent;

    ent = arg1;
    e.sp4 = arg2;
    e.sp8 = arg3;
    e.sp0 = 0;
    D_040000D4[0] = (u32)&e.sp0;
    D_040000D4[1] = ((u32)e.sp4 + ((u32)e.sp8 << 4));
    D_040000D4[2] = 0x85000000u | ((u32)(arg4 - e.sp8 + 1) << 2);
    (void)D_040000D4[2];

    temp_r5 = ent->fC - ent->f0;
    temp_r6 = ent->f10 - ent->f4;
    temp_r4 = ent->f14 - ent->f8;
    sp10 = sub_08005910(temp_r4, temp_r5);
    spC = sub_08005910(sub_080059DC(temp_r5, temp_r4), temp_r6);
    mid = (arg3 + arg4) >> 1;
    temp_r5_2 = ent->f22;
    sp1C = sub_080C364C((temp_r5_2 << 16) + 0x8000, mid - arg3);
    var_r10 = spC - temp_r5_2;
    var_r7 = spC + ((u32)(sp1C * (arg4 - mid)) >> 16);
    if (spC <= 0x4000) {
        var_r5 = sub_08005910(ent->f1C, temp_r6);
        var_r1 = temp_r6;
        if (temp_r6 < 0) var_r1 = -temp_r6;
        temp_r0 = ent->f18;
        if (var_r1 < temp_r0) {
            var_r4 = sub_08005910(temp_r0, temp_r6);
        } else {
            var_r4 = -1;
        }
    } else {
        var_r4 = sub_08005910(ent->f1C, temp_r6);
        var_r1_2 = temp_r6;
        if (temp_r6 < 0) var_r1_2 = -temp_r6;
        temp_r0_2 = ent->f18;
        if (var_r1_2 < temp_r0_2) {
            var_r5_2 = sub_08005910(temp_r0_2, temp_r6);
        } else {
            var_r5_2 = -1;
        }
        var_r5 = var_r5_2;
    }
    sp3C = temp_r6 >> 16;
    if (var_r4 != -1) {
        var_r10_2 = (u32)var_r10 << 16;
        temp_r10_2 = (u32)var_r4 << 16;
        if (var_r10_2 < temp_r10_2) {
            do {
                var_r10_2 += sp1C;
                e.sp8 += 1;
            } while (var_r10_2 < temp_r10_2);
        }
        var_r10 = var_r10_2 >> 16;
    }
    sp40 = (u32)var_r10 << 16;
    sp38 = var_r10 - spC;
    if (var_r5 != -1) {
        var_r7_2 = (u32)var_r7 << 16;
        temp_r10_2 = (u32)var_r5 << 16;
        if (temp_r10_2 < var_r7_2) {
            do {
                var_r7_2 -= sp1C;
                arg4 -= 1;
            } while (temp_r10_2 < var_r7_2);
        }
        var_r7 = var_r7_2 >> 16;
    }

    sp14 = _call_via_r1(sp10 + 0x4000, D_08671BFC);
    sp18 = _call_via_r1(sp10, D_08671BFC);
    sp30 = sp3C * _call_via_r1((s32)ent->f20, D_08671C00);
    sp34 = sp30 >> 11;
    temp_r0_4 = ent->f0;
    sp20 = temp_r0_4;
    temp_r1_2 = ent->f8;
    sp24 = temp_r1_2;
    temp_r6_2 = _call_via_r1(var_r10, D_08671C04);
    temp_r9 = (sp34 * temp_r6_2) >> 16;
    temp_r9 = _call_via_r1(sp38 + 0x4000, D_08671BFC) * temp_r9;
    temp_r9 = temp_r9 >> 16;
    temp_r6_3 = _call_via_r1(var_r7, D_08671C04);
    temp_r1_3 = (sp34 * temp_r6_3) >> 16;
    temp_r1_3 = _call_via_r1((var_r7 - spC) + 0x4000, D_08671BFC) * temp_r1_3;
    temp_r1_3 = temp_r1_3 >> 16;
    sp20 = temp_r0_4 + ((temp_r9 * sp18) >> 5);
    sp24 = temp_r1_2 - ((temp_r9 * sp14) >> 5);
    temp_r9 = (_call_via_r1(var_r10, D_08671C00) * sp3C) >> 16;
    temp_r1_4 = (_call_via_r1(var_r7, D_08671C00) * sp3C) >> 16;
    sp20 += temp_r9 * sp14;
    sp24 += temp_r9 * sp18;
    temp_r4_5 = temp_r0_4 + ((sp18 * temp_r1_3) >> 5) + sp14 * temp_r1_4;
    temp_r1_5 = temp_r1_2 - ((sp14 * temp_r1_3) >> 5) + sp18 * temp_r1_4;
    temp_r7 = temp_r1_4 - temp_r9;
    sp28 = sub_080C364C(temp_r4_5 - sp20, temp_r7);
    sp2C = sub_080C364C(temp_r1_5 - sp24, temp_r7);
    {
        s32 tmp = sp14;
        sp14 = -sp18;
        sp18 = tmp;
    }
    sp30 = sub_080C364C(sp30, 0x78) >> 4;

    var_r10_3 = sp40;
    var_r8 = e.sp8;
    if (var_r8 <= arg4) {
        var_r6 = (Out *)((u32)e.sp4 + ((u32)e.sp8 << 4));
        do {
            temp_r5_4 = var_r10_3 >> 16;
            temp_r4_4 = _call_via_r1((s32)temp_r5_4, D_08671C04);
            temp_r1_6 = ((sp30 * temp_r4_4) >> 16) * _call_via_r1((s32)(temp_r5_4 - spC) + 0x4000, D_08671BFC);
            temp_r1_6 = temp_r1_6 >> 15;
            temp_r0_5 = (temp_r1_6 * sp14) >> 21;
            var_r6->f0 = (s16)temp_r0_5;
            var_r6->f6 = (s16)temp_r0_5;
            temp_r0_6 = (temp_r1_6 * sp18) >> 21;
            var_r6->f4 = (s16)temp_r0_6;
            var_r6->f2 = (s16)-temp_r0_6;
            temp_r1_6 = ((_call_via_r1((s32)temp_r5_4, D_08671C00) * sp3C) >> 16) - temp_r9;
            var_r6->f8 = (sp20 + sp28 * temp_r1_6) >> 8;
            var_r6->fC = (sp24 + sp2C * temp_r1_6) >> 8;
            var_r10_3 += sp1C;
            var_r6 = (Out *)((u32)var_r6 + 16);
            var_r8 += 1;
        } while (var_r8 <= arg4);
    }
}
