s32 scaleByRandom(s32);
s32 randomSignedOffset(s32);
s32 sub_08005FC4(s32, s32, s32, s32, s32 *);
s32 setObjectAnimation(u16 *, s32, s32, s32);
s32 advanceAnimTrack(u16 *, s32);
s32 spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
s32 spawnEffectParticle(s32, s32, s32, s32);
s32 sub_080C31E4(void *, void *, s32);
extern s32 sub_080C0384;

/* Per-frame update for an entity effect: refresh its animation, then react to
 * the current script step by adjusting sprite flags, emitting particles, or
 * playing a cue and advancing the script. */
void sub_0809DF9C(void *arg0)
{
    s32 anim;
    s32 baseY;
    s32 *scriptData;
    s32 effectArg;
    s32 baseX;
    u16 *spriteAttrs;
    void *actor;

    spriteAttrs = *(u16 **)((u8 *)arg0 + 0x38);
    actor = *(void **)((u8 *)arg0 + 0x3C);
    anim = actor + 0x34;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    setObjectAnimation(spriteAttrs, anim, 0x17, 0);
    advanceAnimTrack(spriteAttrs, anim);
    if (!(2 & *(u8 *)((u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + arg0) + 0x19))) {
        *spriteAttrs = (0xFFF & *spriteAttrs) | 0xE000;
    }
    if (!(7 & *(u8 *)((u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + arg0) + 0x19))) {
        spawnJitteredParticles(2, 1, *(s32 *)((u8 *)actor + 8), *(s32 *)((u8 *)actor + 0xC) + 0xFFF00000, 0x100000, 0x100000);
    }
    if ((7 & *(u8 *)((u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + arg0) + 0x19)) == 4) {
        baseX = *(s32 *)((u8 *)actor + 8);
        baseY = *(s32 *)((u8 *)actor + 0xC) + 0xFFF00000;
        effectArg = randomSignedOffset(0x18000);
        spawnEffectParticle(baseX, baseY, effectArg, 0 - (scaleByRandom(0x20000) + 0x18000));
    }
    if (*(u8 *)((u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + arg0) + 0x19) == 0xB4) {
        sub_08005FC4(0, 0x186, 0xF, 0, &sub_080C0384);
        *(s8 *)((u8 *)(*(s16 *)((u8 *)arg0 + 0x22) * 2 + arg0) + 0x19) = 0;
        scriptData = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptData);
    }
}
