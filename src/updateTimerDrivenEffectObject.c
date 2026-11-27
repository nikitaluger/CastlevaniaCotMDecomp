void stepAnimationTrack(void *, void *);
void sub_08011EE8(void *, s32, s32);
s32 detectActorHit(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
s32 _call_via_r1(s32, s32);
void _call_via_r3(void *, void *, u32, u32);

extern u32 gScriptEventCallbacks;

/* One tick of a script-driven timer effect: drop out when the camera loses the
 * sprite, apply contact hits and their two scripted actions, then run the
 * display state and dispatch the next opcode from the effect's step table. */
void updateTimerDrivenEffectObject(void *obj) {
    void *sprite;
    void *work;
    void *animTrack;
    u8 *stepOpcodePtr;
    u8 *stepState;
    u8 opcode;
    u32 stepHandlers;
    s32 callback;
    s32 stepOffset;
    u32 *eventCallbacks1, *eventCallbacks2;

    sprite = *(void **)((u8 *)obj + 0x38);
    work = *(void **)((u8 *)obj + 0x3C);
    animTrack = (u8 *)work + 0x34;
    if (checkActorViewBounds(sprite, work) == 1) {
        return;
    }
    applySpritePaletteVariant(obj, sprite);
    if (detectActorHit(sprite, work, *(void **)((u8 *)work + 0x28)) != 0) {
        spawnContactEffectOnHit(obj, *(void **)((u8 *)work + 0x28));
        if (!(*(u16 *)work & 0x0D)) {
            if (*(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1A) != 2) {
                *(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1B) = 0;
                eventCallbacks1 = &gScriptEventCallbacks;
                _call_via_r3((u8 *)obj + 0x18, (u8 *)obj + 0x22, 2, *eventCallbacks1);
            }
        }
    }
    uploadPendingSpriteGraphic(obj, *(void **)((u8 *)work + 0x28));
    if (*(u16 *)work & 1) {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1A) != 3) {
            updateActorWorldPosition(obj);
            *(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1B) = 0;
            eventCallbacks2 = &gScriptEventCallbacks;
            _call_via_r3((u8 *)obj + 0x18, (u8 *)obj + 0x22, 3, *eventCallbacks2);
        }
    }
    if (updateObjectDisplayState(sprite, work) == 0) {
        *(u32 *)((u8 *)obj + 0x14) = 0x0866DA4C;
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) + 1;
        stepState = (u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj);
        *(u8 *)(stepState + 0x19) = *(u8 *)(stepState + 0x19) + 1;
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)obj + 0x22)) * 2;
        stepOpcodePtr = (u8 *)obj;
        stepOpcodePtr += 0x18;
        stepOpcodePtr += stepOffset;
        opcode = *stepOpcodePtr;
        stepHandlers = *(u32 *)((u8 *)obj + 0x14);
        callback = *(s32 *)((u32)(opcode * 4) + stepHandlers);
        _call_via_r1((s32)obj, callback);
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) - 1;
        if (*(u16 *)((u8 *)obj + 2) & 0x8000) {
            return;
        }
        stepAnimationTrack(sprite, animTrack);
        sub_08011EE8(work, 0x16C1, 0);
    }
    syncSpriteToWorldPosition(obj, sprite);
}
