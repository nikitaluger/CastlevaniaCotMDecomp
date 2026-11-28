extern void stepAnimationTrack(s32, void *);
extern void moveEntityWithCollision(void *, s32);
extern s32 sub_0801459C(void *, s32);
extern void setSpriteFlipForDirection(s32, s32);
extern s32 applyFacingSign(s32, s32);
extern void setSpriteFacingToTarget(s32, s32);
extern void sub_080415D4(u8, s32, void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallbacks;

/* Update a falling enemy: integrate gravity, face the player, and when the
 * player is close enough, lunge toward them and play animation 1. */
void sub_08041040(void *arg0) {
    u8 *entity = (u8 *)arg0;
    s32 anim = *(s32 *)(entity + 0x38);
    u8 *motion = *(u8 **)(entity + 0x3C);
    u8 *animDesc = motion + 0x34;
    s32 vx;
    moveEntityWithCollision(motion, 0x16C1);                  /* gravity + tile collision */
    stepAnimationTrack(anim, animDesc);                  /* refresh animation frame */
    setSpriteFacingToTarget(anim, *(s32 *)(motion + 0x08));   /* face the player */
    if (sub_0801459C(motion, 0x600000) != 0) {     /* player within range */
        vx = applyFacingSign(anim, 0xFFFD0000);       /* lunge speed, toward player */
        *(s32 *)(motion + 0x10) = vx;
        setSpriteFlipForDirection(anim, vx);
        sub_080415D4(1, anim, motion, (s32)animDesc);
        *(u8 *)(entity + (*(s16 *)(entity + 0x22) * 2) + 0x19) = 0;
        {
            s32 *litp = (s32 *)&gMainObjTimerCallbacks;
            sub_080C31E4(entity + 0x18, entity + 0x22, *litp);
        }
    }
}
