void setAnimationFrame(void *, void *, s32, s32);
s32 getSpriteFacingSign(void *);
void spawnDefeatParticle(s32, s32, s32, s32, s32);
void randomizeLaunchOffsets(void *, void *);
void _call_via_r3(void *, void *, s32, void *);

extern struct MainWorkspaceDefeatFlag gMainWorkspace;

/* Defeat step: stop the entity's velocity, start its defeat animation, emit
 * three facing-dependent particles, then add launch jitter and knockback and
 * signal step completion. */
void scriptStepDefeatEntity(void *self)
{
    void *sprite = *(void **)((u8 *)self + 0x38);
    u8 *work = *(u8 **)((u8 *)self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *motion = work + 0x48;

    *(s32 *)(work + 0x14) = 0;
    *(s32 *)(work + 0x10) = 0;

    if (*(u8 *)(anim + 1) == DEFEAT_STAGE_VARIANT)
    {
        s32 globalFlag = gMainWorkspace.flag;
        s32 variant = (s32)(globalFlag + ((u32)globalFlag >> 31));
        if ((variant >> 1) & 1)
            *(s32 *)(motion + 0x14) = DEFEAT_VARIANT_VELOCITY;
        else
            *(s32 *)(motion + 0x14) = 0;
    }

    setAnimationFrame(sprite, anim, DEFEAT_ANIM_FRAME, 0);

    if (*(u8 *)(anim + 1) == DEFEAT_STAGE_PARTICLES && *(s32 *)(anim + 4) == DEFEAT_PARTICLE_GATE)
    {
        if (getSpriteFacingSign(sprite) < 0)
        {
            spawnDefeatParticle(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 0x8000, DEFEAT_PARTICLE_SPEED, *(s16 *)(work + 0x1C));
            spawnDefeatParticle(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 0x6000, DEFEAT_PARTICLE_SPEED, *(s16 *)(work + 0x1C));
        }
        else
        {
            spawnDefeatParticle(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 0, DEFEAT_PARTICLE_SPEED, *(s16 *)(work + 0x1C));
            spawnDefeatParticle(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 0x2000, DEFEAT_PARTICLE_SPEED, *(s16 *)(work + 0x1C));
        }
        spawnDefeatParticle(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 0x4000, DEFEAT_PARTICLE_SPEED, *(s16 *)(work + 0x1C));
    }

    if (*(u8 *)anim & DEFEAT_KNOCKBACK_FLAG)
    {
        s32 knockback;
        s32 zero;
        u32 *callbacks;

        randomizeLaunchOffsets(motion + 8, motion + 0xC);
        if (getSpriteFacingSign(sprite) < 0)
            knockback = DEFEAT_KNOCKBACK_LEFT;
        else
            knockback = DEFEAT_KNOCKBACK_RIGHT;
        *(s32 *)(motion + 0x1C) = knockback;
        zero = 0;
        *(u16 *)(motion + 0x12) = 2;
        *(u8 *)((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = zero;
        callbacks = (u32 *)0x08671BD0;
        _call_via_r3((u8 *)self + 0x18, (u8 *)self + 0x22, 1, (void *)*callbacks);
    }
}
