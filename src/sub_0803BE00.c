extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void sub_08013C8C(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *sScriptStepCallbacks;

/* Runs an enemy object's AI step: updates its sprite and collision state,
 * handles player interaction and child objects, and fires a slot-indexed
 * callback (with a despawn callback on flag 5) when its action timer ends. */
void sub_0803BE00(u8 *object) {
    s32 sprite = *(s32 *)(object + 0x38);
    u8 *state = *(u8 **)(object + 0x3C);

    applySpritePaletteVariant(object, sprite);
    if (checkActorViewBounds(sprite, state) == 1) return;
    if (sub_08013558(sprite, state, *(void **)(state + 0x28)) != 0) {
        spawnContactEffectOnHit(object, *(void **)(state + 0x28));
    }
    uploadPendingSpriteGraphic(object, *(void **)(state + 0x28));
    if (*(u16 *)state & 1) {
        u8 *slot = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
        if (*(u8 *)(slot + 0x1A) != 5) {
            updateActorWorldPosition(object);
            {
                u8 *slot = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
                u8 zero = 0;
                *(u8 *)(slot + 0x1B) = zero;
                { void **callback = &sScriptStepCallbacks;
                  sub_080C31E8(object + 0x18, object + 0x22, 5, *callback); }
            }
        }
    }
    if (updateObjectDisplayState(sprite, state) == 0) {
        *(u32 *)(object + 0x14) = (u32)0x0866DF88;
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
    sub_08013C8C(object, sprite);
}
