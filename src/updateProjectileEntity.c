/* Per-frame update for a projectile/hit entity: cull it outside the active
 * camera rect, manage its target's hit flags and the body's hit state, dispatch
 * the current script step, then refresh animation, motion and screen position. */
extern s32 isPointInActiveCameraBounds(s32, s32, s32, s32, s32, s32);
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 hitTestEntities(void *);
extern s32 _call_via_r1(void *, s32);
extern s32 _call_via_r3(void *, void *, s32, s32);
extern s32 stepAnimationTrack(void *, void *);
extern s32 sub_0805D9A4(void *, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gProjectileStateTable[];
extern s32 sScriptStepCallbacks;

struct TargetState { u8 _0; u8 hitFlag; };
struct ObjFlags2 { u8 attr2A; };
struct AnimFlag { u16 flags; };

void updateProjectileEntity(u8 *entity) {
    u8 *sprite;
    u8 *body;
    u8 *gfxInit;
    u8 *parts;
    u8 *stepData;
    u8 *stepSlot;
    u8 *camera;
    u8 *scrollBase;
    u8 *world;
    u32 coordIdx;
    u32 scrollX;
    u32 scrollY;
    u32 command;
    s32 stepOffset;
    u8 *statePtr;
    s32 hitFlag;
    s32 *stateTable;
    u32 nextState;

    sprite = *(u8 **)(entity + 0x38);
    body = *(u8 **)(entity + 0x3C);
    gfxInit = body + 0x34;
    parts = body + 0x48;
    if (isPointInActiveCameraBounds(*(s32 *)(body + 8), *(s32 *)(body + 0xC), -8, 8, -8, 8) == 0) {
        _call_via_r1(entity, *(u32 *)(entity + 0x24));
        return;
    }
    if (isOutsideCameraBounds(*(s32 *)(body + 8), *(s32 *)(body + 0xC)) == 1) {
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
        if (hitTestEntities(*(u8 **)(body + 0x28)) != 0) {
            ((struct AnimFlag *)body)->flags |= 1;
        }
    }
    hitFlag = *(u16 *)body & 1;
    stepData = entity + 0x18;
    if (hitFlag) {
        ((struct TargetState *)(*(u8 **)(body + 0x28)))->hitFlag = 0;
        stepOffset = *(s16 *)(entity + 0x22) * 2;
        statePtr = (u8 *)((s32)stepOffset + (s32)entity);
        nextState = *(u8 *)(statePtr + 0x1A);
        if (nextState != 1) {
            *(u8 *)(statePtr + 0x1B) = 0;
            stateTable = &sScriptStepCallbacks;
            _call_via_r3(stepData, entity + 0x22, 1, *stateTable);
        }
    }
    *(u32 *)(entity + 0x14) = (u32)gProjectileStateTable;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    stepSlot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stepSlot + 0x19) = *(u8 *)(stepSlot + 0x19) + 1;
    stepOffset = *(s16 *)(entity + 0x22) * 2;
    command = *(u8 *)((u32)stepData + (u32)stepOffset);
    _call_via_r1(entity, *(u32 *)(*(u32 *)(entity + 0x14) + command * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if ((*(u16 *)(entity + 2) & 0x8000) != 0) return;
    stepAnimationTrack(sprite, gfxInit);
    sub_0805D9A4(body, *(s32 *)((u8 *)parts + 8));
    camera = gCameraState;
    world = gMainWorkspace;
    world += 0x18A8;
    coordIdx = ((u32)*world + 1) * 0x40;
    scrollBase = camera + 0x1278;
    scrollX = *(u32 *)(scrollBase + coordIdx);
    *(u32 *)(sprite + 0x14) = *(u32 *)(body + 8) - ((scrollX + 0x8000) & 0xFFFF0000);
    coordIdx = ((u32)*world + 1) * 0x40;
    camera += 0x127C;
    scrollY = *(u32 *)(camera + coordIdx);
    *(u32 *)(sprite + 0x18) = *(u32 *)(body + 0xC) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
