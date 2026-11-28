extern void stepAnimationTrack(s32, void *);
extern void copyPoseAttrs(void *, void *);
extern void moveEntityWithCollision(void *, s32);
extern void spawnEffectSprites(s32, void *, void *);
extern void _call_via_r2(void *, void *, s32);
extern void setAnimationFrame(s32, void *, u16, u8);
extern void *terrainHasSolidFlags(s32, s32);
extern u8 gScriptedEffectPartAttrs[];
extern s32 gMainObjTimerCallbacks[];

/* Update one scripted effect part: advance its animation track, choose pose and vertical offset from the parent effect type, copy the pose attributes, spawn effect sprites, move the part with collision, then cancel the effect's timer on solid terrain or refresh its animation frame. */ void updateScriptedEffectPart(u8 *effect) {
    s32 parentSprite = *(s32 *)(effect + 0x38);
    u8 *part = *(u8 **)(effect + 0x3C);
    u8 *animTrack = part + 0x34;
    u8 *partState = part + 0x48;
    s32 heightDelta;

    stepAnimationTrack(parentSprite, animTrack);
    if (*(u8 *)(partState + 5)) {
        heightDelta = 0;
    } else if (*(u16 *)(parentSprite + 2) & 0x10) {
        heightDelta = 0x50000;
    } else {
        heightDelta = -0x50000;
    }
    switch (*(u16 *)(parentSprite + 0x28)) {
    case 0x13:
        *(u8 *)(partState + 4) = 5;
        *(s32 *)(part + 8) = *(s32 *)(partState + 8) + heightDelta * 2;
        break;
    case 0x16:
        *(u8 *)(partState + 4) = 4;
        *(s32 *)(part + 8) = *(s32 *)(partState + 8) + heightDelta;
        break;
    case 0x19:
        *(u8 *)(partState + 4) = 3;
        *(s32 *)(part + 8) = *(s32 *)(partState + 8);
        break;
    }
    copyPoseAttrs(*(void **)(part + 0x28), (void *)(gScriptedEffectPartAttrs + *(u8 *)(partState + 4) * 8));
    spawnEffectSprites(parentSprite, part, partState);
    moveEntityWithCollision(part, 0x16C1);
    if (terrainHasSolidFlags(*(s32 *)(part + 8), *(s32 *)(part + 0xC)) != 0)
        goto fail;
    if (terrainHasSolidFlags(*(s32 *)(part + 8), *(s32 *)(part + 0xC) + 0x40000) != 0)
        goto ok;
fail:
    *(u8 *)(effect + *(s16 *)(effect + 0x22) * 2 + 0x19) = 0;
    {
        s32 *callbacks = gMainObjTimerCallbacks;
        _call_via_r2((u8 *)effect + 0x18, (u8 *)effect + 0x22, *callbacks);
    }
    goto done;
ok:
    if ((*(u8 *)animTrack & 2) == 0)
        goto done;
    if (*(u8 *)(partState + 5) != 0)
        setAnimationFrame(parentSprite, animTrack, 10, 0);
    else
        setAnimationFrame(parentSprite, animTrack, 14, 0);
    *(u8 *)(partState + 5) = (*(u8 *)(partState + 5) + 1) & 1;
    *(s32 *)(partState + 8) = *(s32 *)(part + 8);
done:;
}
