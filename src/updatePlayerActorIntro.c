/* Per-frame update for the player's intro actor: view-cull it when its timer
 * expires, sync animation/spawn flags, dispatch the current step of
 * sPlayerIntroScriptStepTable, then place the sprite at its camera-relative
 * screen position. */
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern void sub_0801EF8C(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 gScriptEventCallbacks[];
extern u32 sPlayerIntroScriptStepTable[];
extern struct PlayerActorCameraScroll gCameraState;
extern struct PlayerActorWorkspace gMainWorkspace;

void updatePlayerActorIntro(u8 *self) {
    u8 *sprite;
    u8 *state;
    u8 *animState;
    u8 *viewTimer;
    u8 *scriptState;
    s32 stepOffset;
    u8 *scriptBase;
    u8 command;
    u8 *cameraBase;
    u32 scrollOffset;
    u32 *callback;
    s16 stepIndex;
    u16 *stepWords;

    sprite = *(u8 **)(self + 0x38);
    state = *(u8 **)(self + 0x3C);
    animState = state + 0x34;
    viewTimer = state + 0x48;
    ((struct PlayerActorSpawnFlags *)*(u32 *)(state + 0x28))->flags |= 1;

    if (*(s16 *)viewTimer <= 0) {
        if (isOutsideCameraBounds(*(s32 *)(state + 0x08), *(s32 *)(state + 0x0C)) == 1) {
            sub_080C31E0((s32)self, *(u32 *)(self + 0x24));
            return;
        }
    }

    if (*(u16 *)(self + 0x5C) & 0x02)
        ((struct PlayerActorAnimFlags *)state)->flags |= 0x01;

    if (*(u16 *)state & 0x01) {
        ((struct PlayerActorSpawnFlags *)*(u32 *)(state + 0x28))->flags &= 0xFB;
        scriptState = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (scriptState[0x1A] != 2) {
            scriptState[0x1B] = 0;
            callback = gScriptEventCallbacks;
            sub_080C31E8(self + 0x18, self + 0x22, 2, *callback);
        }
    }

    if (updateObjectDisplayState(sprite, state) != 0)
        goto common;

    *(u32 *)(self + 0x14) = (u32)sPlayerIntroScriptStepTable;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    stepIndex = *(s16 *)(self + 0x22);
    stepWords = (u16 *)self;
    ((u8 *)(&stepWords[stepIndex]))[0x19] = ((u8 *)(&stepWords[stepIndex]))[0x19] + 1;
    stepOffset = *(s16 *)(self + 0x22) * 2;
    scriptBase = self + 0x18;
    command = scriptBase[stepOffset];
    sub_080C31E0((s32)self, *(u32 *)(*(u32 *)(self + 0x14) + command * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    if ((*(u16 *)(self + 2) & 0x8000) != 0)
        goto end;
    stepAnimationTrack(sprite, animState);
    advanceMotion(state, 0);

common:
    sub_0801EF8C(sprite, state);
    cameraBase = (u8 *)&gCameraState;
    scrollOffset = 0x1278;
    *(u32 *)(sprite + 0x14) = *(u32 *)(state + 8) - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000);
    scrollOffset = 0x127C;
    *(u32 *)(sprite + 0x18) = *(u32 *)(state + 0x0C) - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
end:
    ;
}
