extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 signOf(s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_08048074(s32, s32, s32, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Script-step handler for a projectile: advance the animation track to frame
 * 8, and once its flag is set launch an effect toward the target with a speed
 * scaled by how far the object already faces it; finally pick the horizontal
 * velocity from the target's X and continue to the next script step. */
void scriptStepSpawnFacingProjectile(void *self) {
    void *sprite;
    void *work;
    void *anim;
    void *stepState;
    s32 facing;
    s32 distance;
    s32 speed;
    s32 velocity;
    s32 *stepCallbacks;
    s16 stepIndex;

    sprite = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    anim = (u8 *)work + 0x34;
    stepState = (u8 *)work + 0x48;
    *(s32 *)((u8 *)work + 0x10) = 0;
    setAnimationFrame(sprite, anim, 8, 0);
    if (*(u8 *)((u8 *)anim + 1) == 2 && *(s32 *)((u8 *)anim + 4) == 1) {
        facing = getSpriteFacingSign(sprite);
        if (facing == signOf(*(s32 *)((u8 *)work + 8))) {
            distance = absXFromFocus(*(s32 *)((u8 *)work + 8));
            if (distance < 0) distance += 0x1F;
            speed = distance >> 5;
            if (speed > 0x5FFF) {
                if (speed > 0x30000) speed = 0x30000;
            } else {
                speed = 0x6000;
            }
        } else {
            speed = 0x6000;
        }
        if (getSpriteFacingSign(sprite) < 0) {
            sub_08048074(*(s32 *)((u8 *)work + 8) + 0xFFE80000, *(s32 *)((u8 *)work + 0x0C) + 0xFFDC0000, -speed, 0xFFFFE000, *(s16 *)((u8 *)work + 0x1C));
        } else {
            sub_08048074(*(s32 *)((u8 *)work + 8) + 0x180000, *(s32 *)((u8 *)work + 0x0C) + 0xFFDC0000, speed, 0xFFFFE000, *(s16 *)((u8 *)work + 0x1C));
        }
    }
    if (*(u8 *)anim & 0x02) {
        if (*(s32 *)((u8 *)work + 8) < *(s32 *)((u8 *)stepState + 0)) {
            velocity = 0x4000;
        } else {
            velocity = 0xFFFFC000;
        }
        *(s32 *)((u8 *)work + 0x10) = velocity;
        stepIndex = *(s16 *)((u8 *)self + 0x22);
        ((u8 *)self)[stepIndex * 2 + 0x19] = 0;
        stepCallbacks = (s32 *)SCRIPT_STEP_CALLBACK_TABLE;
        sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 0, *stepCallbacks);
    }
}
