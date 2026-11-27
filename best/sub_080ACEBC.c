/* machine draft (m2c) for agbcc -mthumb-interwork -O2, tried by autopilot */
#ifndef M2C_DEFINES
#define M2C_DEFINES
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_BITS_F32(expr) (m2c_bits = (u32)(expr), *(f32 *)&m2c_bits)
extern u32 m2c_bits;
#define M2C_PTR_FROM_F32(type, expr) ((type)(m2c_fbits = (expr), *(u32 *)&m2c_fbits))
extern f32 m2c_fbits;
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif

s32 getAngleFromDelta(s32, s32);                         /* extern */
s32 fixedPointDistance(s32, s32);                         /* extern */

void sub_080ACEBC(void *arg0, void *arg1) {
  s32 *__repair_entry_var_r10;
    s32 sp0;
    s32 sp4;
    void *sp8;
    u32 spC;
    void *sp10;
    s32 *sp14;
    s32 *sp18;
    
    void *sp20;
    void *sp24;
    void *sp28;
    void *sp2C;
    u32 sp30;
    void *sp34;
    void *sp38;
    void *sp3C;
    void *sp40;
    void *sp44;
    void *sp48;
    
    s32 *sp50;
    s32 *sp54;
s32 *__repair_phase_sp54;
    s32 *var_r10;
    s32 *var_r3;
    s32 *var_r3_2;
    s32 *var_r8;
    s32 *var_r8_2;
    s32 temp_r0_2;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    s32 temp_r2_6;
    
    s8 *var_r5_2;
    s8 *var_r5_3;
    s8 *var_r7;
    s8 *var_r7_entry;
    u32 temp_r0;
    u32 temp_r7_2;
    u32 var_r9;
    u32 var_r9_2;
    void **temp_r4;
    void **var_r4;
    void **var_r4_2;
    void *temp_r0_3;
    void *temp_r1;
    void *temp_r1_2;
    void *temp_r2;
    void *temp_r2_2;
    void *temp_r2_3;
    void *temp_r2_4;
    void *temp_r2_5;
    void *temp_r2_7;
    void *temp_r2_8;
    s32 *temp_r3;
    void *temp_r7;
    void *temp;
    void *temp2;

    sp8 = arg1;
    sp10 = M2C_FIELD(M2C_FIELD(arg1, M2C_UNK **, 0x14), M2C_UNK **, 0x3C);
    temp_r1 = M2C_FIELD(arg1, M2C_UNK **, 0);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(temp_r1, s32 *, 0x6C);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_r1, s32 *, 0x7C);
    spC = 0;
    temp = arg0 + 0x28;
    var_r7_entry = temp;
    sp4 = 0;
    do {
        *var_r7 = 0;
        temp2 = arg0 + 0x18;
        temp_r4 = temp2 + sp4;
        temp_r2 = *temp_r4;
        *(s32 *)(arg0 + 0x1C + sp4) = getAngleFromDelta(M2C_FIELD(temp_r2, s32 *, 0x6C) - M2C_FIELD(arg0, s32 *, 0x170), M2C_FIELD(temp_r2, s32 *, 0x5C) - M2C_FIELD(arg0, s32 *, 0x16C));
        temp_r2_2 = *temp_r4;
        temp_r2_6 = fixedPointDistance(M2C_FIELD(arg0, s32 *, 0x16C) - M2C_FIELD(temp_r2_2, s32 *, 0x5C), M2C_FIELD(arg0, s32 *, 0x170) - M2C_FIELD(temp_r2_2, s32 *, 0x6C));
        *(s32 *)(arg0 + 0x20 + sp4) = temp_r2_6;
        *(s32 *)(arg0 + 0x24 + sp4) = temp_r2_6;
        var_r7 += 0x14;
        sp4 += 0x14;
        temp_r0 = spC + 1;
        spC = temp_r0;
    } while (temp_r0 <= 1U);
    sp0 = M2C_FIELD(M2C_FIELD(sp8, M2C_UNK **, 4), s32 *, 0x8C);
    sp4 = M2C_FIELD(M2C_FIELD(sp8, M2C_UNK **, 8), s32 *, 0x8C);
    spC = 0;
    sp38 = arg0 + 0x40;
    temp_r7 = arg0 + 0x44;
    sp3C = temp_r7;
    temp_r0_3 = arg0 + 0x48;
    sp40 = temp_r0_3;
    temp_r1_2 = arg0 + 0x4C;
    sp44 = temp_r1_2;
    temp_r2_3 = arg0 + 0xE0;
    sp48 = temp_r2_3;
    sp34 = sp8 + 0xC;
    sp2C = temp_r7 + 0xB0;
    sp20 = temp_r0_3 + 0x9C;
    sp24 = temp_r1_2 + 0x9C;
    sp28 = temp_r2_3 + 0xC;
    sp14 = arg0 + 0x170;
    sp18 = arg0 + 0x16C;
    sp4 = 0;
    var_r10 = &sp0;
    do {
        __repair_entry_var_r10 = var_r10;
        var_r9 = 0;
        var_r8 = sp4 + sp44;
        var_r3 = sp4 + sp40;
        var_r4 = sp4 + sp38;
        sp54 = sp4 + sp3C;
        var_r5_2 = sp4 + (arg0 + 0x50);
        do {
            *var_r5_2 = 1;
            temp_r2_4 = *(s32 *)(*__repair_entry_var_r10 + ((var_r9 << 2)));
            *var_r4 = temp_r2_4;
            do { sp50 = var_r3; } while (0);
            *sp54 = getAngleFromDelta(M2C_FIELD(temp_r2_4, s32 *, 0x7C) - *sp14, M2C_FIELD(temp_r2_4, s32 *, 0x6C) - *sp18);
            temp_r2_5 = *var_r4;
            temp_r0_4 = fixedPointDistance(*sp18 - M2C_FIELD(temp_r2_5, s32 *, 0x6C), *sp14 - M2C_FIELD(temp_r2_5, s32 *, 0x7C));
            *var_r3 = temp_r0_4;
            *var_r8 = temp_r0_4;
            var_r8 += 0x14;
            var_r3 += 0x14;
            var_r4 += 0x14;
            sp54 += 0x14;
            var_r5_2 += 0x14;
            var_r9 += 1;
        } while (var_r9 <= 3U);
        sp4 += 0x50;
        var_r10 += 4;
        temp_r7_2 = spC + 1;
        spC = temp_r7_2;
    } while (temp_r7_2 <= 1U);
    spC = 0;
    __repair_entry_var_r10 = arg0 + 0x170;
    do {
        temp_r2_6 = spC * 0x3C;
        var_r4_2 = sp48 + temp_r2_6;
        temp_r3 = *(s32 *)(sp34 + (spC * 4));
        *var_r4_2 = M2C_FIELD(temp_r3, M2C_UNK **, 0x6C);
        *(s32 *)(sp2C + temp_r2_6) = M2C_FIELD(temp_r3, s32 *, 0x7C);
        *(s32 *)(arg0 + 0x108 + temp_r2_6) = M2C_FIELD(temp_r3, s32 *, 0x8C);
        var_r9_2 = 0;
        sp30 = spC + 1;
        var_r8_2 = sp28 + temp_r2_6;
        var_r3_2 = temp_r2_6 + sp24;
        __repair_phase_sp54 = temp_r2_6 + sp20;
        var_r5_3 = temp_r2_6 + (arg0 + 0xF0);
loop_8:
        *var_r5_3 = 2;
        temp_r2_7 = *var_r4_2;
        sp50 = var_r3_2;
        *__repair_phase_sp54 = getAngleFromDelta(M2C_FIELD(temp_r2_7, s32 *, 0x7C) - *__repair_entry_var_r10, M2C_FIELD(temp_r2_7, s32 *, 0x6C) - M2C_FIELD(arg0, s32 *, 0x16C));
        temp_r2_8 = *var_r4_2;
        temp_r0_5 = fixedPointDistance(M2C_FIELD(arg0, s32 *, 0x16C) - M2C_FIELD(temp_r2_8, s32 *, 0x6C), *__repair_entry_var_r10 - M2C_FIELD(temp_r2_8, s32 *, 0x7C));
        *var_r3_2 = temp_r0_5;
        *var_r8_2 = temp_r0_5;
        var_r8_2 += 0x14;
        var_r3_2 += 0x14;
        var_r4_2 += 0x14;
        __repair_phase_sp54 += 0x14;
        var_r5_3 += 0x14;
        var_r9_2 += 1;
        if (var_r9_2 <= 2U) {
            goto loop_8;
        }
        spC = sp30;
    } while (sp30 <= 1U);
    M2C_FIELD(arg0, s32 *, 0x158) = (s32) M2C_FIELD(sp8, s32 *, 0x14);
    M2C_FIELD(arg0, s8 *, 0x168) = 3;
    M2C_FIELD(arg0, s32 *, 0x15C) = getAngleFromDelta(M2C_FIELD(sp10, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 0x170), M2C_FIELD(sp10, s32 *, 8) - M2C_FIELD(arg0, s32 *, 0x16C));
    temp_r0_6 = fixedPointDistance(M2C_FIELD(arg0, s32 *, 0x16C) - M2C_FIELD(sp10, s32 *, 8), M2C_FIELD(arg0, s32 *, 0x170) - M2C_FIELD(sp10, s32 *, 0xC));
    M2C_FIELD(arg0, s32 *, 0x160) = temp_r0_6;
    M2C_FIELD(arg0, s32 *, 0x164) = temp_r0_6;
}
