/* Entity tick: dispatches the current script command, then spawns periodic
 * effects/projectiles around the entity based on its facing direction and a
 * countdown timer; when the timer expires it calls the failure callback.
 * sub_080C36E4 is a remainder helper (a % b), so the two tests fire on timer
 * multiples of 6 and 3. */
extern s32 scaleByRandom(s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void sub_08014848(s32, s32, s32, s32, s32, s32);
extern s32 getSpriteFacingSign(u8 *);
extern void sub_0801A310(s32, s32, s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern s32 sub_080C36E4(s16, s32);

void sub_0801820C(u8 *self) {
    u8 *work;
    u8 *entity;
    u8 *body;
    u8 *anim;
    u8 *scriptSlot;
    u8 *scriptPtr;
    s32 cmdOffset;
    s32 xOffset;
    s32 facing;
    s32 xPos;
    s32 yPos;
    s32 xGrid;
    s32 yGrid;
    s32 timer;
    u32 vv;
    u8 cmdId;

    work = *(u8 **)(self + 0x38);
    entity = *(u8 **)(self + 0x3C);
    anim = entity + 0x34;
    body = entity + 0x48;
    *(u32 *)(entity + 0x14) = 0;
    *(u32 *)(entity + 0x10) = 0;
    setAnimationFrame(work, anim, 0, 0);
    *(u32 *)(self + 0x14) = 0x0866D5AC;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    scriptSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    *(u8 *)(scriptSlot + 0x19) = *(u8 *)(scriptSlot + 0x19) + 1;
    cmdOffset = *(s16 *)(self + 0x22) * 2;
    scriptPtr = self;
    scriptPtr += 0x18;
    cmdId = *(u8 *)((u32)scriptPtr + (u32)cmdOffset);
    sub_080C31E0((s32)self, *(u32 *)(*(u32 *)(self + 0x14) + cmdId * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;

    facing = getSpriteFacingSign(work);
    xOffset = 0xFFFC0000;
    if (facing < 0) {
        xOffset = 0x80 << 11;
    }
    if ((sub_080C36E4(*(s16 *)(body + 0x16), 6) << 16) == 0) {
        sub_08014848(1, 2, *(u32 *)(entity + 0x08) + xOffset, *(u32 *)(entity + 0x0C) + 0xFFEE0000, 0x80 << 13, 0xC0 << 13);
    }
    if ((sub_080C36E4(*(s16 *)(body + 0x16), 3) << 16) == 0) {
        xPos = *(u32 *)(entity + 0x08) + xOffset;
        if (xPos < 0) xPos += 0xFFFF;
        xGrid = xPos >> 16;
        yPos = *(u32 *)(entity + 0x0C);
        if (yPos < 0) yPos += 0xFFFF;
        yGrid = yPos >> 16;
        sub_0801A310(xGrid, yGrid, -scaleByRandom(0x38), scaleByRandom(0x80 << 9));
    }
    timer = *(s16 *)(body + 0x16);
    if (((timer % 2) << 16) == 0) {
        *(u16 *)work = (*(u16 *)work & 0x0FFF) | (0xE0 << 8);
    }
    vv = *(u16 *)(body + 0x16);
    vv -= 1;
    *(u16 *)(body + 0x16) = vv;
    if ((s32)(vv << 16) < 0) {
        sub_080C31E0((s32)self, *(u32 *)(self + 0x24));
    }
}
