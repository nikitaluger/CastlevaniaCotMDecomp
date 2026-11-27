void sub_080BB984(void *, void *);
void sub_080BE810(s32, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);
extern s32 gScriptStepCallbackTable;

/* Place an effect's sprite part: let the owner bob, offset the part from the
 * owner's position by the side-dependent entry of the 0x08102EEC offset table
 * (mirrored by the subject's facing), advance the part's animation frame, and
 * when the step's phase byte reaches 0x4B clear it and move to the next step. */
void sub_080BAB54(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *entity = *(u8 **)(self + 0x3C);
    u8 *body = entity + 0x48;
    u8 *subject = *(u8 **)(self + 0x4C);
    s32 side;
    u8 *offsetTable;
    s32 x;
    s32 y;
    s32 *lit;

    sub_080BB984(entity, body);
    side = *(s32 *)(body + 0x4C) & 1;
    offsetTable = (u8 *)0x08102EEC;
    side = side << 3;
    x = *(s32 *)(entity + 0x08) + *(s32 *)(offsetTable + side) * (s32)*(s8 *)(subject + 0x35);
    offsetTable += 4;
    y = *(s32 *)(entity + 0x0C) + *(s32 *)(offsetTable + side);
    sub_080BE810(*(s32 *)(body + 0x2C), x, y, *(s32 *)(body + 0x58));
    *(s32 *)(body + 0x58) += *(s32 *)(body + 0x50);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x4B) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = &gScriptStepCallbackTable;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
