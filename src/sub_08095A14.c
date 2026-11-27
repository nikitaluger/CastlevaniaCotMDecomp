extern s32 sub_0805F9B4(s32, s32);
extern s32 hitTestEntities(void *);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866FAE0[];
extern s32 gScriptEventCallbacks;

struct TargetState { u8 a; u8 flag; };
struct ObjFlags2 { u8 flag; };
struct AnimFlag { u16 flag; };

/* Updates a projectile/hit entity: manages target hit flags and attack state,
 * advances its callback, and snaps its coordinates to the camera. */
void sub_08095A14(u8 *self) {
    u8 *gfxObj;
    u8 *anim;
    u8 *stateSlot;
    u8 *coordTable;
    u8 *coordXPtr;
    u8 *camTable;
    u32 index;
    u32 coordX;
    u32 coordY;
    u32 stateId;
    u8 *slots;
    s32 stateOffset;
    u8 *p1;
    s32 hitFlag;
    s32 *stateFn;
    u32 tmp;

    gfxObj = *(u8 **)(self + 0x38);
    anim = *(u8 **)(self + 0x3C);
    if (sub_0805F9B4(*(s32 *)(anim + 8), *(s32 *)(anim + 0xC)) == 1) {
        s32 tmp2 = 0xBF & ((struct ObjFlags2 *)(gfxObj + 0x2A))->flag;
        u8 v = 0;
        ((struct ObjFlags2 *)(gfxObj + 0x2A))->flag = tmp2;
        ((struct TargetState *)(*(u8 **)(anim + 0x28)))->flag = v;
    } else {
        ((struct TargetState *)(*(u8 **)(anim + 0x28)))->flag = 4;
        ((struct ObjFlags2 *)(gfxObj + 0x2A))->flag |= 0x40;
        if (hitTestEntities(*(u8 **)(anim + 0x28)) != 0) {
            ((struct AnimFlag *)anim)->flag |= 1;
        }
    }
    hitFlag = *(u16 *)anim & 1;
    slots = self + 0x18;
    if (hitFlag) {
        ((struct TargetState *)(*(u8 **)(anim + 0x28)))->flag = 0;
        stateOffset = *(s16 *)(self + 0x22) * 2;
        p1 = (u8 *)((s32)stateOffset + (s32)self);
        tmp = *(u8 *)(p1 + 0x1A);
        tmp = (tmp - 1) << 24;
        tmp = tmp >> 24;
        if (tmp > 1) {
            *(u8 *)(p1 + 0x1B) = 0;
            stateFn = &gScriptEventCallbacks;
            sub_080C31E8(slots, self + 0x22, 1, *stateFn);
        }
    }
    *(u32 *)(self + 0x14) = (u32)D_0866FAE0;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    stateSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    *(u8 *)(stateSlot + 0x19) = *(u8 *)(stateSlot + 0x19) + 1;
    stateOffset = *(s16 *)(self + 0x22) * 2;
    stateId = *(u8 *)((u32)slots + (u32)stateOffset);
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + stateId * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    if ((*(u16 *)(self + 2) & 0x8000) == 0) {
        coordTable = gCameraState;
        camTable = gMainWorkspace;
        camTable += 0x18A8;
        index = ((u32)*camTable + 1) * 0x40;
        coordXPtr = coordTable + 0x1278;
        coordX = *(u32 *)(coordXPtr + index);
        *(u32 *)(gfxObj + 0x14) = *(u32 *)(anim + 8) - ((coordX + 0x8000) & 0xFFFF0000);
        index = ((u32)*camTable + 1) * 0x40;
        coordTable += 0x127C;
        coordY = *(u32 *)(coordTable + index);
        *(u32 *)(gfxObj + 0x18) = *(u32 *)(anim + 0xC) - ((coordY + 0xFFFF8000) & 0xFFFF0000);
    }
}
