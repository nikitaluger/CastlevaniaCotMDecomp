extern s32 sub_0805F9B4(s32, s32);
extern s32 hitTestEntities(void *);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
extern s32 sub_080113A8(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866E988[];
extern s32 gScriptEventCallbacks;

/* target object at motion+0x28: state byte at +1 */
struct MotionTarget { u8 unused; u8 state; };
/* sprite attribute byte at sprite+0x2A */
struct SpriteAttr { u8 bits; };
/* motion flag word */
struct MotionFlags { u16 bits; };

/*
 * Updates an entity's animation state: clears or sets visibility/collision
 * flags according to whether it is inside the active area, dispatches the
 * handler for the current animation step, and positions the sprite relative
 * to the camera.
 */
void sub_0805DFE0(u8 *entity) {
    u8 *sprite;
    u8 *motion;
    void *status;
    u8 *stepPtr;
    u8 *coordBase;
    u8 *coordXBase;
    u8 *camIndex;
    u32 coordOff;
    u32 camX;
    u32 camY;
    u32 stateId;
    u8 *sequence;
    s32 stepOff;
    u8 *stepPtr2;
    s32 visible;
    s32 *fxFn;

    sprite = *(u8 **)(entity + 0x38);
    motion = *(u8 **)(entity + 0x3C);
    status = motion + 0x34;
    if (sub_0805F9B4(*(s32 *)(motion + 8), *(s32 *)(motion + 0xC)) == 1) {
        s32 maskedBits = 0xBF & ((struct SpriteAttr *)(sprite + 0x2A))->bits;
        u8 zero = 0;
        ((struct SpriteAttr *)(sprite + 0x2A))->bits = maskedBits;
        ((struct MotionTarget *)(*(u8 **)(motion + 0x28)))->state = zero;
    } else {
        ((struct MotionTarget *)(*(u8 **)(motion + 0x28)))->state = 4;
        ((struct SpriteAttr *)(sprite + 0x2A))->bits |= 0x40;
        if (hitTestEntities(*(u8 **)(motion + 0x28)) != 0) {
            ((struct MotionFlags *)motion)->bits |= 1;
        }
    }
    visible = *(u16 *)motion & 1;
    sequence = entity + 0x18;
    if (visible) {
        ((struct MotionTarget *)(*(u8 **)(motion + 0x28)))->state = 0;
        stepOff = *(s16 *)(entity + 0x22) * 2;
        stepPtr2 = (u8 *)((s32)stepOff + (s32)entity);
        if (*(u8 *)(stepPtr2 + 0x1A) != 1) {
            *(u8 *)(stepPtr2 + 0x1B) = 0;
            fxFn = &gScriptEventCallbacks;
            sub_080C31E8(sequence, entity + 0x22, 1, *fxFn);
        }
    }
    *(u32 *)(entity + 0x14) = (u32)D_0866E988;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    stepPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stepPtr + 0x19) = *(u8 *)(stepPtr + 0x19) + 1;
    stepOff = *(s16 *)(entity + 0x22) * 2;
    stateId = *(u8 *)((u32)sequence + (u32)stepOff);
    sub_080C31E0(entity, *(u32 *)(*(u32 *)(entity + 0x14) + stateId * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if ((*(u16 *)(entity + 2) & 0x8000) != 0) return;
    sub_080113A8(sprite, status);
    coordBase = gCameraState;
    camIndex = gMainWorkspace;
    camIndex += 0x18A8;
    coordOff = ((u32)*camIndex + 1) * 0x40;
    coordXBase = coordBase + 0x1278;
    camX = *(u32 *)(coordXBase + coordOff);
    *(u32 *)(sprite + 0x14) = *(u32 *)(motion + 8) - ((camX + 0x8000) & 0xFFFF0000);
    coordOff = ((u32)*camIndex + 1) * 0x40;
    coordBase += 0x127C;
    camY = *(u32 *)(coordBase + coordOff);
    *(u32 *)(sprite + 0x18) = *(u32 *)(motion + 0xC) - ((camY + 0xFFFF8000) & 0xFFFF0000);
}
