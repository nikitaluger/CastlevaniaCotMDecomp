extern s32 checkGlobalStateChange(void *, void *, void *);
extern s32 getTileTerrainB(u32, s32, s32);
extern void startEffectTimer(void *, s32, u32);
extern void stepDelayTimer(void *, void *);
extern void releaseEntityIfOffscreen(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void playSound(u16);
extern struct MotionObjectWorkspace gMainWorkspace;
extern u32 gMainObjTimerCallbacks;

static inline u32 bitOne(u16 v) {
    u32 m = 1;
    m &= v;
    return m;
}

/* Advance an entity's scripted motion, spawn and announce a collision effect
 * when the phase or terrain test fires, refresh its sprite, then dispatch the
 * next callback or release the entity. */
void updateScriptedMotionObject(u8 *entity) {
    void *self;
    void *motionBlock;
    void *stateBase;
    void *sprite;
    void *motion;
    u32 *callbacks;
    s32 phase;
    u8 zeroByte;
    self = entity;
    motionBlock = *(void **)((u8 *)self + 0x6C);
    stateBase = (u8 *)motionBlock + 4;
    sprite = *(void **)((u8 *)self + 0x38);
    motion = stateBase;
    if (checkGlobalStateChange(self, sprite, motion) != 0) return;
    *(s32 *)((u8 *)motion + 0x0C) += MOTION_OBJ_PHASE_STEP;
    if (*(s32 *)((u8 *)motion + 0x0C) > MOTION_OBJ_PHASE_MAX) *(s32 *)((u8 *)motion + 0x0C) = MOTION_OBJ_PHASE_MAX;
    *(s32 *)((u8 *)motionBlock + 4) += *(s32 *)((u8 *)motion + 8);
    phase = *(s32 *)((u8 *)motion + 4) + *(s32 *)((u8 *)motion + 0x0C);
    *(s32 *)((u8 *)motion + 4) = phase;
    if (bitOne(*(u16 *)(*(void **)((u8 *)motion + 0x2C) + 0x14)) != 0 ||
        (getTileTerrainB(((u32)gMainWorkspace.frameCounter << 6) + MOTION_OBJ_TILEMAP_BASE, *(s32 *)((u8 *)motionBlock + 4), phase) << 16) != 0) {
        if (gMainWorkspace.formIndex <= MOTION_OBJ_HIT_FORM_BASE) gMainWorkspace.formIndex = MOTION_OBJ_HIT_FORM_MIN;
        startEffectTimer((u8 *)motionBlock + 0x20, 0, MOTION_OBJ_HIT_EFFECT_DATA);
        *(u16 *)(*(void **)((u8 *)motion + 0x2C) + 0x06) = (zeroByte = 0, MOTION_OBJ_HIT_ANIM);
        *(u16 *)(*(void **)((u8 *)motion + 0x2C) + 0x08) = MOTION_OBJ_HIT_ANIM;
        playSound(MOTION_OBJ_HIT_SFX);
        *(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22) * 2) + 0x19) = zeroByte;
        callbacks = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *callbacks);
    }
    *(u16 *)sprite = gMainWorkspace.gfxFlags;
    stepDelayTimer((u8 *)stateBase + 0x1C, sprite);
    sub_0806D588(sprite, motion);
    if (gMainWorkspace.sceneState == MOTION_OBJ_CLEANUP_SCENE || (gMainWorkspace.actionState == 0 && gMainWorkspace.activeForm != 0)) {
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
        return;
    }
    releaseEntityIfOffscreen(self, sprite);
}
