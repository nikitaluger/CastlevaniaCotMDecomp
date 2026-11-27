/* Update a scripted companion entity: run the visibility check, mark it when an
 * overlap/search hit is found, perform the one-time start action (facing the
 * owner based on the player's x position), then dispatch the current script step's
 * callback while logic allows. */
s32 checkActorViewBounds(void *, void *);          /* visibility/validity check */
void sub_080C31E0(void *, void *);
void sub_080C31E8(void *, void *, s32, void *);
void *hitTestEntities(void *);                /* find an overlapping entity */
s32 sub_08013B5C(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
void sub_08005E80(s32);
extern void *gScriptEventCallbacks;
extern u8 gMainWorkspace[];
extern u8 D_00001728[];                     /* offset 0x1728 into gMainWorkspace */

void sub_08044E6C(u8 *self) {
    void *owner = *(void **)(self + 0x38);
    u8 *params = *(u8 **)(self + 0x3C);
    if (checkActorViewBounds(owner, params) == 1) {
        sub_080C31E0(self, *(void **)(self + 0x24));
        return;
    }
    if (hitTestEntities(*(void * volatile *)(params + 0x28)) != 0) {
        u16 flags = *(u16 *)params | 1;
        *(u16 *)params = flags;
    }
    if (*(u16 *)((u8 *)*(u8 * volatile *)(params + 0x28) + 0x14) & 1) {
        u16 flags = *(u16 *)params | 1;
        *(u16 *)params = flags;
    }
    if (*(u16 *)params & 1) {
        u8 *stepPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(stepPtr + 0x1A) != 1) {
            if (*(s32 *)((u32)D_00001728 + (u32)gMainWorkspace) < *(s32 *)((u8 *)params + 8)) {
                u16 flags = *(u16 *)((u8 *)owner + 2) & 0xFFEF;
                *(u16 *)((u8 *)owner + 2) = flags;
            } else {
                u16 flags = *(u16 *)((u8 *)owner + 2) | 0x10;
                *(u16 *)((u8 *)owner + 2) = flags;
            }
            *(u8 *)(*(u8 * volatile *)(params + 0x28) + 1) = 0;
            sub_08005E80(0x189);
            {
                u8 *stepPtr2 = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
                stepPtr2[0x1B] = 0;
            }
            { void **actionTable = &gScriptEventCallbacks;
              sub_080C31E8(self + 0x18, self + 0x22, 1, *actionTable); }
        }
    }
    if (sub_08013B5C(owner, params) == 0) {
        *(u32 *)(self + 0x14) = (u32)0x0866E268;
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
        {
            u8 *stepPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            stepPtr[0x19] = (u8)(stepPtr[0x19] + 1);
        }
        {
            s32 stepOffset = (*(s16 *)(self + 0x22)) * 2;
            u8 *stepBase = self + 0x18;
            u8 stepId = *(stepBase + stepOffset);
            void **handlerTable = *(void **)(self + 0x14);
            void *handler = handlerTable[stepId];
            sub_080C31E0(self, handler);
        }
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
    }
    syncSpriteToWorldPosition(self, owner);
}
