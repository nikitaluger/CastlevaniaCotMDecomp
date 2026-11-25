extern void sub_08004484(void *, s32, s32, s32, s32);

void sub_08004314(void *arg0) {
    s32 temp_r6;
    s32 temp_r5;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s16 temp_r2;
    s16 temp_r3;
    s32 var_r9;
    s32 var_r8;
    s32 var_r10;
    s32 var_r12;
    s32 var_r0;
    s32 var_r2;
    s32 var_r3;
    s32 var_r7;
    s32 var_r1;
    s32 var_r6;
    s32 var_r5;
    s32 t10;
    s32 n1;

    temp_r6 = *(s32 *)((u8 *)arg0 + 0x18) + 0x8000;
    sp4 = temp_r6 >> 0x10;
    temp_r5 = *(s32 *)((u8 *)arg0 + 0x1C) + 0x8000;
    sp8 = temp_r5 >> 0x10;
    if ((sp4 == *(s16 *)((u8 *)arg0 + 0x3C)) && (sp8 == *(s16 *)((u8 *)arg0 + 0x3E))) {
        return;
    }
    temp_r2 = *(s16 *)((u8 *)arg0 + 0x20);
    temp_r3 = *(s16 *)((u8 *)arg0 + 0x22);
    n1 = sp4 + temp_r2 - 1;
    t10 = sp8 + temp_r3 - 1;
    var_r8 = temp_r6 >> 0x13;
    spC = temp_r5 >> 0x13;
    var_r9 = n1 >> 3;
    sp10 = t10 >> 3;
    var_r10 = (*(u16 *)((u8 *)arg0 + 0x3C) << 16) >> 0x13;
    sp14 = (*(u16 *)((u8 *)arg0 + 0x3E) << 16) >> 0x13;
    var_r12 = (temp_r2 + *(s16 *)((u8 *)arg0 + 0x3C) - 1) >> 3;
    sp18 = (*(s16 *)((u8 *)arg0 + 0x3E) + temp_r3 - 1) >> 3;
    if (0x100 & *(u16 *)((u8 *)arg0 + 0)) {
        var_r8 &= ~1;
        var_r12 &= ~1;
        var_r10 &= ~1;
        var_r9 &= ~1;
        var_r0 = 2;
    } else {
        var_r0 = 1;
    }
    if (sp4 != *(s16 *)((u8 *)arg0 + 0x3C)) {
        if (sp4 < *(s16 *)((u8 *)arg0 + 0x3C)) {
            var_r2 = var_r8;
            var_r3 = var_r10 - var_r0;
        } else {
            var_r2 = var_r12 + var_r0;
            var_r3 = var_r9;
        }
        var_r7 = spC;
        var_r1 = sp10;
    } else {
        var_r1 = 0;
        var_r7 = 0;
        var_r3 = 0;
        var_r2 = 0;
    }
    sp1C = var_r8;
    sp20 = var_r9;
    if (sp8 != *(s16 *)((u8 *)arg0 + 0x3E)) {
        if (sp8 < *(s16 *)((u8 *)arg0 + 0x3E)) {
            var_r7 = sp14;
            var_r1 = sp10;
            var_r6 = spC;
            var_r5 = var_r7 - 1;
        } else {
            var_r7 = spC;
            var_r1 = sp18;
            var_r6 = var_r1 + 1;
            var_r5 = sp10;
        }
    } else {
        var_r5 = 0;
        var_r6 = 0;
    }
    if (((var_r8 != var_r10) || (var_r12 != var_r9)) && (var_r2 <= var_r3) && ((var_r3 - var_r2) <= 0x1D)) {
        sub_08004484(arg0, var_r2, var_r7, var_r3, var_r1);
    }
    if (((spC != sp14) || (sp10 != sp18)) && (var_r6 <= var_r5) && ((var_r5 - var_r6) <= 0x13)) {
        sub_08004484(arg0, sp1C, var_r6, sp20, var_r5);
    }
    *(s16 *)((u8 *)arg0 + 0x3C) = (s16)sp4;
    *(s16 *)((u8 *)arg0 + 0x3E) = (s16)sp8;
}
