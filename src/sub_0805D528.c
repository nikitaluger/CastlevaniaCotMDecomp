/* Movement/impact update for the object: despawns it when it leaves the active
 * area, applies the view/hit flags to its target, runs the body state handler,
 * then advances to the next state and refreshes its animation and screen
 * position. */
extern s32 sub_08015850(s32, s32, s32, s32, s32, s32); /* inside world rect? */
extern s32 sub_0805F9B4(s32, s32);                     /* outside camera view? */
extern s32 sub_08016238(void *);                       /* find the hit target */
extern s32 sub_080C31E0(void *, s32);                  /* indirect call */
extern s32 sub_080C31E8(void *, void *, s32, s32);     /* state machine dispatch */
extern s32 sub_080113A8(void *, void *);               /* step animation */
extern s32 sub_0805D9A4(void *, s32);                  /* body terrain collision */
extern u8 D_02021E90[];   /* shared video state (BG scroll buffers) */
extern u8 D_02025FF0[];   /* scene state (camera index at +0x18A8) */
extern u8 D_0866E978[];   /* movement state handler table */
extern s32 D_08671BDC;

struct TargetState { u8 _0; u8 hitFlag; };   /* hit target's byte at +1 */
struct ObjFlags2 { u8 attr2A; };             /* sprite palette/attribute byte */
struct AnimFlag { u16 flags; };              /* body flags word */

void sub_0805D528(u8 *entity) {
    u8 *sprite;
    u8 *body;
    u8 *gfxInit;
    u8 *parts;
    u8 *stateData;
    u8 *stateSlot;
    u8 *video;
    u8 *xBase;
    u8 *globalBase;
    u32 coordIdx;
    u32 coordX;
    u32 coordY;
    u32 stateId;
    s32 stateOffset;
    u8 *statePtr;
    s32 hitFlag;
    s32 *stateTable;
    u32 nextState;

    sprite = *(u8 **)(entity + 0x38);
    body = *(u8 **)(entity + 0x3C);
    gfxInit = body + 0x34;
    parts = body + 0x48;
    if (sub_08015850(*(s32 *)(body + 8), *(s32 *)(body + 0xC), -8, 8, -8, 8) == 0) {
        sub_080C31E0(entity, *(u32 *)(entity + 0x24));
        return;
    }
    if (sub_0805F9B4(*(s32 *)(body + 8), *(s32 *)(body + 0xC)) == 1) {
        s32 palByte = 0xBF & ((struct ObjFlags2 *)(sprite + 0x2A))->attr2A;
        u8 zero = 0;
        ((struct ObjFlags2 *)(sprite + 0x2A))->attr2A = palByte;
        ((struct TargetState *)(*(u8 **)(body + 0x28)))->hitFlag = zero;
    } else {
        ((struct ObjFlags2 *)(sprite + 0x2A))->attr2A |= 0x40;
        if (*(u16 *)(body + 2) & 4) {
            ((struct TargetState *)(*(u8 **)(body + 0x28)))->hitFlag = 4;
        } else {
            ((struct TargetState *)(*(u8 **)(body + 0x28)))->hitFlag = 0;
        }
        if (sub_08016238(*(u8 **)(body + 0x28)) != 0) {
            ((struct AnimFlag *)body)->flags |= 1;
        }
    }
    hitFlag = *(u16 *)body & 1;
    stateData = entity + 0x18;
    if (hitFlag) {
        ((struct TargetState *)(*(u8 **)(body + 0x28)))->hitFlag = 0;
        stateOffset = *(s16 *)(entity + 0x22) * 2;
        statePtr = (u8 *)((s32)stateOffset + (s32)entity);
        nextState = *(u8 *)(statePtr + 0x1A);
        if (nextState != 1) {
            *(u8 *)(statePtr + 0x1B) = 0;
            stateTable = &D_08671BDC;
            sub_080C31E8(stateData, entity + 0x22, 1, *stateTable);
        }
    }
    *(u32 *)(entity + 0x14) = (u32)D_0866E978;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    stateSlot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stateSlot + 0x19) = *(u8 *)(stateSlot + 0x19) + 1;
    stateOffset = *(s16 *)(entity + 0x22) * 2;
    stateId = *(u8 *)((u32)stateData + (u32)stateOffset);
    sub_080C31E0(entity, *(u32 *)(*(u32 *)(entity + 0x14) + stateId * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if ((*(u16 *)(entity + 2) & 0x8000) != 0) return;
    sub_080113A8(sprite, gfxInit);
    sub_0805D9A4(body, *(s32 *)((u8 *)parts + 8));
    video = D_02021E90;
    globalBase = D_02025FF0;
    globalBase += 0x18A8;
    coordIdx = ((u32)*globalBase + 1) * 0x40;
    xBase = video + 0x1278;
    coordX = *(u32 *)(xBase + coordIdx);
    *(u32 *)(sprite + 0x14) = *(u32 *)(body + 8) - ((coordX + 0x8000) & 0xFFFF0000);
    coordIdx = ((u32)*globalBase + 1) * 0x40;
    video += 0x127C;
    coordY = *(u32 *)(video + coordIdx);
    *(u32 *)(sprite + 0x18) = *(u32 *)(body + 0xC) - ((coordY + 0xFFFF8000) & 0xFFFF0000);
}
