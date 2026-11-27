s32 checkActorViewBounds(void *, void *);
void sub_080C31E0(void *, void *);
s32 sub_08013B5C(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
void sub_080C31E8(void *, void *, s32, void *);
void *hitTestEntities(void *);
extern void *sScriptStepCallbacks;

/* Steps an enemy object's AI: releases it on player collision, marks itself
 * when its child or target is flagged, fires a despawn callback on flag 1, and
 * dispatches a slot-indexed callback when its action timer finishes. */
void sub_080441F8(u8 *object) {
    void *sprite = *(void **)(object + 0x38);
    u8 *state = *(u8 **)(object + 0x3C);
    if (checkActorViewBounds(sprite, state) == 1) {
        sub_080C31E0(object, *(void **)(object + 0x24));
        return;
    }
    if (hitTestEntities(*(void **)(state + 0x28)) != 0) {
        u16 flags = *(u16 *)state | 1;
        *(u16 *)state = flags;
    }
    if (*(u16 *)(*(u8 **)(state + 0x28) + 0x14) & 1) {
        u16 flags = *(u16 *)state | 1;
        *(u16 *)state = flags;
    }
    if (*(u16 *)state & 1) {
        u8 *slot = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
        if (*(u8 *)(slot + 0x1A) != 1) {
            *(u8 *)(slot + 0x1B) = 0;
            { void **callback = &sScriptStepCallbacks;
              sub_080C31E8(object + 0x18, object + 0x22, 1, *callback); }
        }
    }
    if (sub_08013B5C(sprite, state) == 0) {
        *(u32 *)(object + 0x14) = (u32)0x0866E21C;
        *(u16 *)(object + 0x22) = (u16)(*(u16 *)(object + 0x22) + 1);
        {
            u8 *slot = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
            slot[0x19] = (u8)(slot[0x19] + 1);
        }
        {
            s32 slotIndex = (*(s16 *)(object + 0x22)) * 2;
            u8 *slotBase = object + 0x18;
            u8 slotByte = *(slotBase + slotIndex);
            void **dispatchTable = *(void **)(object + 0x14);
            void *dispatchFn = dispatchTable[slotByte];
            sub_080C31E0(object, dispatchFn);
        }
        *(u16 *)(object + 0x22) = (u16)(*(u16 *)(object + 0x22) - 1);
    }
    syncSpriteToWorldPosition(object, sprite);
}
