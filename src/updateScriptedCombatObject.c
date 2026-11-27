extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 detectActorHit(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void stepAnimationTrack(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void setAttackHitboxFromAction(s32, void *);
extern void syncSpriteToWorldPosition(void *, s32);
extern void _call_via_r1(void *, void *);
extern void _call_via_r3(void *, void *, s32, void *);
extern void *gScriptEventCallbacks;
extern u8 gCameraState[];
extern struct { u8 _0[0x18A8]; u8 f18A8; } gMainWorkspace;

/* Per-frame update of a scripted combat object: check view bounds and hits,
 * dispatch one step from its command table, advance its animation, then
 * correct the sprite's Y against the camera scroll. */
void updateScriptedCombatObject(u8 *self) {
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animTrack = work + 0x34;
    u8 *stepState = work + 0x48;
    u32 scrollTable;
    u32 scrollYOffset;
    s32 worldY;
    u32 scrollY;

    if (checkActorViewBounds(sprite, work) == 1) return;

    applySpritePaletteVariant(self, sprite);
    if (detectActorHit(sprite, work, *(void **)(work + 0x28)) != 0) {
        spawnContactEffectOnHit(self, *(void **)(work + 0x28));
    }
    uploadPendingSpriteGraphic(self, *(void **)(work + 0x28));
    if (*(u16 *)work & SCRIPT_OBJ_HIT_FLAG) {
        u8 *step = (u8 *)((u32)(*(s16 *)(self + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)self);
        if (*(u8 *)(step + 0x1A) != 3) {
            updateActorWorldPosition(self);
            {
                u8 *stepPtr = (u8 *)((u32)(*(s16 *)(self + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)self);
                *(u8 *)(stepPtr + 0x1B) = 0;
                { void **eventTable = &gScriptEventCallbacks;
                  _call_via_r3(self + SCRIPT_STEP_BASE_OFFSET, self + SCRIPT_STEP_INDEX_OFFSET, COMBAT_SCRIPT_SOUND_EVENT, *eventTable); }
            }
        }
    }
    if (updateObjectDisplayState(sprite, work) != 0) goto cdc;
    *(u32 *)(self + SCRIPT_STEP_TABLE_OFFSET) = COMBAT_SCRIPT_STEP_TABLE;
    *(u16 *)(self + SCRIPT_STEP_INDEX_OFFSET) = (u16)(*(u16 *)(self + SCRIPT_STEP_INDEX_OFFSET) + 1);
    {
        u8 *stepPtr = (u8 *)((u32)(*(s16 *)(self + SCRIPT_STEP_INDEX_OFFSET)) * 2 + (u32)self);
        stepPtr[0x19] = (u8)(stepPtr[0x19] + 1);
    }
    {
        s32 stepOffset = (*(s16 *)(self + SCRIPT_STEP_INDEX_OFFSET)) * 2;
        u8 *stepBase = self + SCRIPT_STEP_BASE_OFFSET;
        u8 opcode = *(stepBase + stepOffset);
        void **handlers = *(void **)(self + SCRIPT_STEP_TABLE_OFFSET);
        void *handler = handlers[opcode];
        _call_via_r1(self, handler);
    }
    *(u16 *)(self + SCRIPT_STEP_INDEX_OFFSET) = (u16)(*(u16 *)(self + SCRIPT_STEP_INDEX_OFFSET) - 1);
    if ((*(u16 *)(self + 2) & SCRIPT_OBJ_FLAG_SKIP_ANIM) != 0) goto done;
    stepAnimationTrack(sprite, animTrack);
    sub_08011EE8(work, *(s32 *)(stepState + 8), 0);
cdc:
    setAttackHitboxFromAction(sprite, work);
    syncSpriteToWorldPosition(self, sprite);
    worldY = *(s32 *)(work + 0xC) + *(s32 *)(stepState + 0xC);
    scrollTable = (u32)gCameraState;
    scrollYOffset = 0x127C;
    scrollY = *(u32 *)(scrollTable + scrollYOffset + ((gMainWorkspace.f18A8 + 1) << 6));
    scrollY = (scrollY + 0xFFFF8000) & 0xFFFF0000;
    *(s32 *)((u8 *)sprite + 0x18) = worldY - scrollY;
done:
    ;
}
