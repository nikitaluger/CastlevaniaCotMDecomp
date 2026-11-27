struct Segment {
    s32 mode;
    s32 angle;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 step0;
    s32 step1;
};

s32 sub_080121F8(struct Segment *arg0, struct Segment *arg1) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    s32 var_r0;
    s32 var_r4;

    if (sub_080133EC(arg0->x0, arg0->y0) == 1) goto fail;

    temp_r6 = arg0->x0 & 0xFFFF0000;
    temp_r5 = temp_r6 + 0x8000;
    temp_r4 = arg0->y0 & 0xFFFF0000;
    temp_r7 = temp_r4 + 0x8000;
    sp10 = temp_r5;
    sp4 = temp_r5;
    sp14 = temp_r7;
    sp8 = temp_r7;
    if (sub_080133EC(temp_r5, temp_r4 + 0x18000) == 1) {
        var_r0 = 0xC000;
        goto common;
    }
    if (sub_080133EC(temp_r5, temp_r4 + 0xFFFF8000) == 1) {
        var_r0 = 0x4000;
        goto common;
    }
    if (sub_080133EC(temp_r6 + 0xFFFF8000, temp_r7) == 1) {
        var_r0 = 0;
        goto common;
    }
    if (sub_080133EC(temp_r5 + 0x10000, temp_r7) == 1) goto success;
fail:
    return 0;
success:
    var_r0 = 0x8000;
common:
    spC = var_r0;
    sp0 = var_r0;
    var_r4 = 7;
    do {
        sub_0801235C(0x10000, &sp0, &sp4, &sp8);
        sub_0801235C(0xFFFF0000, &spC, &sp10, &sp14);
        var_r4 -= 1;
    } while (var_r4 >= 0);
    arg1->x0 = sp4;
    arg1->y0 = sp8;
    arg1->x1 = sp10;
    arg1->y1 = sp14;
    arg1->step0 = sp0;
    arg1->step1 = spC;
    return 1;
}
