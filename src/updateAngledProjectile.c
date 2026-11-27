extern s32 sub_080C31E0(s32, s32);
extern s32 sub_08026C7C(s32, s32, s16, s16, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Compute an angle-driven world position into the effect's work state; when the
 * entity is flagged to fire, spawn a projectile, notify its owner, mark the
 * script step finished and play the associated sound. */
void updateAngledProjectile(u8 *entity) {
    s32 scaledSin, scaledCos;
    s32 rawSin, rawCos;
    s32 motionAngle;
    s32 baseX, baseY, rotateCos, rotateSin, worldY;
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *motion = work + 0x48;
    s32 *trigFuncs;

    motionAngle = *(u16 *)(motion + 8);
    trigFuncs = (s32 *)0x08671BFC;
    rawSin = sub_080C31E0(motionAngle + ANGLE_PROJECTILE_QUARTER_TURN, *trigFuncs);
    if (rawSin < 0) rawSin += ANGLE_PROJECTILE_SIN_BIAS;
    scaledSin = rawSin >> ANGLE_PROJECTILE_SIN_SHIFT;
    rawCos = sub_080C31E0(motionAngle, *trigFuncs);
    if (rawCos < 0) rawCos += ANGLE_PROJECTILE_COS_BIAS;
    scaledCos = rawCos >> ANGLE_PROJECTILE_COS_SHIFT;

    baseX = (sub_080C31E0(*(u16 *)(*(u8 **)(motion + 0x58) + 4) + ANGLE_PROJECTILE_QUARTER_TURN, *trigFuncs) * ANGLE_PROJECTILE_POS_SCALE) + *(s32 *)(motion + 0x5C);
    baseY = (sub_080C31E0(*(u16 *)(*(u8 **)(motion + 0x58) + 4), *trigFuncs) * ANGLE_PROJECTILE_POS_SCALE) + *(s32 *)(motion + 0x60);
    rotateCos = sub_080C31E0(*(u16 *)(*(u8 **)(motion + 0x58) + 2) + ANGLE_PROJECTILE_QUARTER_TURN, *trigFuncs);
    *(s32 *)(work + 8) = (scaledSin * rotateCos) - (sub_080C31E0(*(u16 *)(*(u8 **)(motion + 0x58) + 2), *trigFuncs) * scaledCos) + baseX;
    rotateSin = sub_080C31E0(*(u16 *)(*(u8 **)(motion + 0x58) + 2), *trigFuncs);
    worldY = (scaledSin * rotateSin) + (sub_080C31E0(*(u16 *)(*(u8 **)(motion + 0x58) + 2) + ANGLE_PROJECTILE_QUARTER_TURN, *trigFuncs) * scaledCos) + baseY;
    *(s32 *)(work + 0xC) = worldY;

    if (ANGLE_PROJECTILE_FIRE_FLAG & *(u16 *)(entity + 0x64)) {
        sub_08026C7C(*(s32 *)(work + 8), worldY, *(s16 *)(motion + 0x18), *(s16 *)(motion + 0x22), *(s16 *)(work + 0x1C));
        {
            void *owner = *(void **)(entity + 0x30);
            if (owner != NULL) {
                sub_080C31E0((s32)owner, *(s32 *)((u8 *)owner + 0x24));
            }
        }
        {
            u8 *stepPtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepPtr + 0x17) = 0;
        }
        {
            s32 *soundCallbackPtr = (s32 *)0x08671BD8;
            sub_080C31E8(entity + 0x18, entity + 0x22, 1, *soundCallbackPtr);
        }
    }
}
