extern s32 hitTestEntities(void *);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866E9C0[];
extern s32 sScriptStepCallbacks;

struct HitTarget { u8 pad; u8 hitState; };
struct MotionFlags { u16 bits; };

/* Advance an actor's animation step: mark a collision, dispatch the current
 * sequence entry, then place its screen position relative to the camera. */
void sub_0805EE0C(u8 *self) {
    u8 *sprite;
    u8 *motion;
    u8 *sequence;
    u8 *mapBase;
    u8 *mapX;
    u8 *cameraIndex;
    u32 mapOffset;
    u32 snappedX;
    u32 snappedY;
    u32 animState;
    s32 stepOffset;
    u8 *stepEntry;
    u8 *stepEntry2;
    s32 isVisible;
    s32 *fxValue;

    sprite = *(u8 **)(self + 0x38);
    motion = *(u8 **)(self + 0x3C);
    if (hitTestEntities(*(u8 **)(motion + 0x28)) != 0) {
        ((struct MotionFlags *)motion)->bits |= 1;
    }
    isVisible = *(u16 *)motion & 1;
    sequence = self + 0x18;
    if (isVisible) {
        ((struct HitTarget *)(*(u8 **)(motion + 0x28)))->hitState = 0;
        stepOffset = *(s16 *)(self + 0x22) * 2;
        stepEntry2 = (u8 *)((s32)stepOffset + (s32)self);
        if (*(u8 *)(stepEntry2 + 0x1A) != 1) {
            *(u8 *)(stepEntry2 + 0x1B) = 0;
            fxValue = &sScriptStepCallbacks;
            sub_080C31E8(sequence, self + 0x22, 1, *fxValue);
        }
    }
    *(u32 *)(self + 0x14) = (u32)D_0866E9C0;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    stepEntry = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    *(u8 *)(stepEntry + 0x19) = *(u8 *)(stepEntry + 0x19) + 1;
    stepOffset = *(s16 *)(self + 0x22) * 2;
    animState = *(u8 *)((u32)sequence + (u32)stepOffset);
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + animState * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    if ((*(u16 *)(self + 2) & 0x8000) != 0) return;
    mapBase = gCameraState;
    cameraIndex = gMainWorkspace;
    cameraIndex += 0x18A8;
    mapOffset = ((u32)*cameraIndex + 1) * 0x40;
    mapX = mapBase + 0x1278;
    snappedX = *(u32 *)(mapX + mapOffset);
    *(u32 *)(sprite + 0x14) = *(u32 *)(motion + 8) - ((snappedX + 0x8000) & 0xFFFF0000);
    mapOffset = ((u32)*cameraIndex + 1) * 0x40;
    mapBase += 0x127C;
    snappedY = *(u32 *)(mapBase + mapOffset);
    *(u32 *)(sprite + 0x18) = *(u32 *)(motion + 0xC) - ((snappedY + 0xFFFF8000) & 0xFFFF0000);
}
