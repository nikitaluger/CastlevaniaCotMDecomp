/* Project a rotated and scaled point into the target's x/y, advance the
 * animation timer, and set the sprite's facing flag from a second projection. */
extern u32 gTrigFuncPtr;
s32 divideInt(s32 a, s32 b);
s32 sub_080C31E0(u32 a, u32 b);

void sub_080BC73C(void *arg0, void *arg1, void *arg2) {
    u8 *src = (u8 *)arg0;
    u8 *anim = (u8 *)arg1;
    u8 *out = (u8 *)arg2;
    u8 *parent;
    u8 *motion;
    u8 *params;
    s32 offsetByte;
    s32 baseX;
    s32 baseY;
    s32 projX;
    s32 projY;
    s32 checkX;
    s32 scale;
    s32 maxValue;
    s32 checkAngle;
    u8 *outSprite;
    u32 *trigFn;
    u32 *trigFn2;

    parent = *(u8 **)(src + 0x28);
    motion = *(u8 **)(parent + 0x3C);
    params = *(u8 **)(parent + 0x4C);
    offsetByte = *(s8 *)(params + 0x35);
    baseX = *(s32 *)(motion + 0x08) + (offsetByte << 20);
    baseY = *(s32 *)(motion + 0x0C) + (s32)0xFFF10000;
    trigFn = &gTrigFuncPtr;

    projX = sub_080C31E0(*(s32 *)(src + 0x7C) + 0x4000, *trigFn);
    scale = *(s32 *)(src + 0x6C);
    scale >>= 8;
    projX >>= 8;
    projX = projX * scale;
    projX += baseX;
    *(s32 *)(out + 0x08) = projX;

    projY = sub_080C31E0(*(s32 *)(src + 0x7C), *trigFn);
    scale = *(s32 *)(src + 0x6C);
    scale >>= 8;
    projY >>= 8;
    projY = projY * scale;
    baseY += projY;
    *(s32 *)(out + 0x0C) = baseY;

    if (*(s32 *)(src + 0x4C) != 0) {
        s32 tmp = divideInt(0x01000000, *(s32 *)(src + 0x5C));
        *(u16 *)(anim + 0x04) = (u16)tmp;
        *(u16 *)(anim + 0x06) = (u16)tmp;
        if (*(u32 *)(src + 0x5C) > 0xFFFF) {
            maxValue = 0x80 << 1;
            *(u16 *)(anim + 0x04) = (u16)maxValue;
            *(u16 *)(anim + 0x06) = (u16)maxValue;
            *(s32 *)(src + 0x4C) = 0;
            outSprite = *(u8 **)(out + 0x28);
            *(u8 *)(outSprite + 0x01) = 0x05;
        } else {
            outSprite = *(u8 **)(out + 0x28);
            *(u8 *)(outSprite + 0x01) = 0x00;
        }
    }

    checkAngle = *(s32 *)(src + 0x7C) + *(s32 *)(src + 0x8C);
    trigFn2 = &gTrigFuncPtr;
    checkAngle += 0x4000;
    checkX = sub_080C31E0(checkAngle, *trigFn2);
    scale = *(s32 *)(src + 0x6C);
    scale >>= 8;
    checkX >>= 8;
    checkX = checkX * scale;
    checkX += baseX;
    checkX -= *(s32 *)(out + 0x08);
    if (checkX < 0) {
        *(u16 *)(anim + 0x02) &= 0xFFEF;
    } else {
        s32 flags = 0x10 | *(u16 *)(anim + 0x02);
        *(u16 *)(anim + 0x02) = flags;
    }
}
