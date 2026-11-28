extern s16 gBossChargeAnimFrames[];
extern void (*D_08671BB0)(void *, void *);
extern void playSound(u16);
extern void setAnimationFrame(void *, void *, s16, s32);
extern void spawnJitteredParticles(s32, s32, s32, s32, s32, s32);

/* Advance one scripted step of a boss's charge attack: play the charge cue on
 * step 1, pick the animation frame from the boss's variant byte, flag the
 * sprite and adjust the work state's vertical motion, emit a particle burst
 * every fourth step, and on the final step (0x3C) reset the charge and call
 * the main-object completion callback. */
void updateBossChargeStep(u8 *boss) {
    u8 *sprite = *(u8 **)(boss + 0x38);
    u8 *work = *(u8 **)(boss + 0x3C);
    u8 *animTrack = work + 0x34;

    if (*(u8 *)(boss + (*(s16 *)(boss + 0x22) * 2) + 0x19) == 1)
        playSound(0x85);

    setAnimationFrame(sprite, animTrack, gBossChargeAnimFrames[*(u8 *)(boss + 0x4C)], 0);

    if ((*(u8 *)(boss + (*(s16 *)(boss + 0x22) * 2) + 0x19) & 2) != 0)
        *(u16 *)sprite = (*(u16 *)sprite & 0xFFF) | 0xE000;

    if ((*(u8 *)(boss + (*(s16 *)(boss + 0x22) * 2) + 0x19) & 2) != 0)
        *(u32 *)(work + 8) += 0x20000;
    else
        *(u32 *)(work + 8) += 0xFFFE0000;

    {
        u8 stepState = *(u8 *)(boss + (*(s16 *)(boss + 0x22) * 2) + 0x19);
        if ((stepState & 3) == 0) {
            if (stepState <= 0x1D)
                spawnJitteredParticles(0, 2, *(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0xFFE80000, 0xC0000, 0x180000);
            else
                spawnJitteredParticles(1, 2, *(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0xFFE80000, 0xC0000, 0x180000);
        }
    }

    if (*(u8 *)(boss + (*(s16 *)(boss + 0x22) * 2) + 0x19) == 0x3C) {
        *(u32 *)(work + 0x10) = 0;
        *(u32 *)(work + 0x14) = 0xFFFB8000;
        *(u8 *)(boss + (*(s16 *)(boss + 0x22) * 2) + 0x19) = 0;
        D_08671BB0(boss + 0x18, boss + 0x22);
    }
}
