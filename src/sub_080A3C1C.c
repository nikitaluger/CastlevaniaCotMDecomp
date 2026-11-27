extern void sub_08005E80(s32);
extern void moveEntityWithCollision(u8 *, s32);
extern void sub_0808DC40(s32, s32, s32);
extern void sub_0808DC88(s32, s32, s32);
extern void sub_0808E670(s32, s32, s32, s32);
extern void sub_080C050C(s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern s32 D_08101C8C[];
extern s32 gScriptStepCallbackTable;

/* Periodic entity update: mark the sprite's graphics, advance its physics,
 * then on the configured timer spawn effects and a sound and dispatch the
 * next script step. */
void sub_080A3C1C(u8 *entity) {
    u32 i;
    u8 *gfx;
    u8 *body;
    u8 *attrByte;
    u8 *stepIndexPtr;
    u8 *scriptPtr;
    s32 *velTable;
    u8 zero;
    u8 maskedByte;

    gfx = *(u8 **)(entity + 0x38);
    body = *(u8 **)(entity + 0x3C);
    if (!(*(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) & 2)) {
        *(u16 *)gfx = (*(u16 *)gfx & 0xFFF) | 0xE000;
    }
    moveEntityWithCollision(body, 0x16C1);
    if (!(*(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) & 3)) {
        sub_0808DC40(*(s32 *)(body + 8), *(s32 *)(body + 0xC), 8);
    }
    if (*(u16 *)(body + 2) != 0) {
        sub_080C050C(0x186);
        sub_08005E80(0x83);
        sub_0808DC88(*(s32 *)(body + 8), *(s32 *)(body + 0xC), 8);
        sub_0808DC88(*(s32 *)(body + 8), *(s32 *)(body + 0xC), 0x18);
        i = 0;
        attrByte = gfx + 0x2A;
        scriptPtr = entity + 0x18;
        stepIndexPtr = entity + 0x22;
        velTable = D_08101C8C;
        for (; i <= 6; velTable += 2, i++) {
            sub_0808E670(*(s32 *)(body + 8), *(s32 *)(body + 0xC), velTable[0], velTable[1]);
        }
        maskedByte = *attrByte & 0xBF;
        zero = 0;
        *attrByte = maskedByte;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
        sub_080C31E4(scriptPtr, stepIndexPtr, gScriptStepCallbackTable);
    }
}
