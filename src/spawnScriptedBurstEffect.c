extern void sub_08011EE8(void *, s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void *spawnBudgetedEffect(s32, s32);
extern s32 randomSignedOffset(s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, void *);

struct S_02025FF0_1870 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;
extern s32 gActiveObjectId;
extern u32 gMainObjTimerCallbacks;

/* Spawns the entity's particle bursts: a directional one keyed to the script
 * counter, and, when state flags 5 are set, a two-particle burst plus a sound. */
/* Script-step handler for a scripted effect: advances the owner's animation, emits a directional particle burst when the current step timer is a multiple of four, and on work-state flags 5 switches animation frame, spawns two angle-swept particles, clears the timer and dispatches the main-object timer callback. */ void spawnScriptedBurstEffect(u8 *script) {
    u8 *animTrack;
    u8 *work;
    u8 *sprite;
    void *particle;
    s32 *spawnParentPtr;
    u8 *scriptSteps;
    u8 *stepIdx;

    sprite = *(u8 **)(script + 0x38);
    work = *(u8 **)(script + 0x3C);
    animTrack = work + 0x34;

    sub_08011EE8(work, 0x16C1, 0);
    stepAnimationTrack(sprite, animTrack);

    if ((*(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) & 3) == 0) {
        particle = spawnBudgetedEffect((s32)gMainWorkspace.v, 0xFD);
        if (particle != 0) {
            s32 worldX = *(s32 *)(work + 8);
            if (*(u16 *)(sprite + 2) & 0x10)
                *(s32 *)((u8 *)particle + 0x4C) = worldX + 0xFFF70000;
            else
                *(s32 *)((u8 *)particle + 0x4C) = worldX + 0x90000;
            *(s32 *)((u8 *)particle + 0x5C) = *(s32 *)(work + 0xC) + randomSignedOffset(0x40000);
            *(s32 *)((u8 *)particle + 0x6C) = randomSignedOffset(0x1000) + 0x7000;
            *(s32 *)((u8 *)particle + 0x7C) = (-(s32)((*(u16 *)(sprite + 2) & 0x10) != 0) >> 31) & 0x8000;
            *(u8 *)((u8 *)particle + 0x8C) = 7;
        }
    }

    if (*(u16 *)(work + 2) & 5) {
        u32 i;
        s32 angle;

        setAnimationFrame(sprite, animTrack, 0x11, 0);
        i = 0;
        scriptSteps = script + 0x18;
        stepIdx = script + 0x22;
        spawnParentPtr = &gActiveObjectId;
        angle = 0xB000;
        for (i = 0; i <= 1; i++) {
            particle = spawnBudgetedEffect(*spawnParentPtr, 0xFD);
            if (particle != 0) {
                *(s32 *)((u8 *)particle + 0x4C) = *(s32 *)(work + 8);
                *(s32 *)((u8 *)particle + 0x5C) = *(s32 *)(work + 0xC);
                *(s32 *)((u8 *)particle + 0x6C) = 0x14000;
                *(s32 *)((u8 *)particle + 0x7C) = angle;
                *(u8 *)((u8 *)particle + 0x8C) = 0x10;
            }
            angle += 0x2000;
        }

        *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) = 0;
        {
            u32 *callback = &gMainObjTimerCallbacks;
            sub_080C31E4(scriptSteps, stepIdx, (void *)*callback);
        }
    }
}
