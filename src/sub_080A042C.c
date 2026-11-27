extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void *spawnBudgetedEffect(s32, s32);
extern s32 sub_080C31E0(s32, s32);

/* Spawn a sound-effect object with a randomized pan phase and volume, seeding
 * its left/right gains from a wave table and the supplied base values. */
void sub_080A042C(s32 kind, u8 *params) {
    u8 *sound = spawnBudgetedEffect(kind, 0x189);
    s32 phase, volume, otherPhase;
    s32 *pWaveFunc;

    if (sound != NULL) {
        phase = randomSignedOffset(0x4000);
        otherPhase = phase + 0xC000;
        volume = scaleByRandom(0x80000) + 0x180000;
        pWaveFunc = (s32 *)0x08671BFC;
        *(s32 *)(sound + 0x4C) = *(s32 *)(params + 0x08) + ((volume >> 8) * (sub_080C31E0(phase + 0x10000, *pWaveFunc) >> 8));
        *(s32 *)(sound + 0x5C) = *(s32 *)(params + 0x0C) + ((volume >> 8) * (sub_080C31E0(otherPhase, *pWaveFunc) >> 8));
        *(s32 *)(sound + 0x6C) = otherPhase;
        *(s32 *)(sound + 0x7C) = volume;
    }
}
