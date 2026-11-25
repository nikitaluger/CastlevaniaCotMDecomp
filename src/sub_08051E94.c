extern s32 sub_080C31E0(void *, s32);

/* Builds an 8-segment trail by walking two quadrature sine lookups from a base point,
   writing the resulting X and Y coordinate arrays into the output object. */
void sub_08051E94(void *config, void *out, s32 angle, s32 stepScale) {
    s32 stepMul;
    s8 *cfg;
    s32 spread;
    s32 xOffset;
    s32 baseX;
    s32 xAcc;
    s32 baseY;
    s32 yAcc;
    s32 i;
    s32 angleAcc;
    s32 cosVal;
    s32 sinVal;
    s32 yVal;
    u8 *xArray;
    u8 *yArray;
    u8 *xSlot;
    s32 offset;

    stepMul = stepScale;
    cfg = (s8 *)config;
    spread = cfg[0x6C];
    xOffset = spread << 17;
    angleAcc = angle;
    baseX = *(s32 *)out - xOffset;
    *(s32 *)((u8 *)out + 8) = baseX;
    xAcc = baseX;
    baseY = *(s32 *)((u8 *)out + 4) + (s32)0xFFEE0000;
    *(s32 *)((u8 *)out + 0x2C) = baseY;
    yAcc = baseY;
    i = 1;
    while (i <= 8) {
        cosVal = sub_080C31E0((void *)(angleAcc + 0x4000), *(s32 *)0x08671BFC);
        offset = i * 4;
        xArray = (u8 *)out + 8;
        xSlot = xArray + offset;
        *(s32 *)xSlot = xAcc + cosVal * 6;
        sinVal = sub_080C31E0((void *)angleAcc, *(s32 *)0x08671BFC);
        yArray = (u8 *)out + 0x2C;
        yArray += offset;
        yVal = yAcc + sinVal * 6;
        *(s32 *)yArray = yVal;
        xAcc = *(s32 *)xSlot;
        yAcc = yVal;
        angleAcc += (s8)*(u8 *)((u8 *)config + 0x6C) * stepMul;
        i += 1;
    }
}
