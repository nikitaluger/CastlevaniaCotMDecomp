extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_0801165C(void *, s32);
extern void sub_080146D0(void *, s32, s32);
extern void sub_08049180(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, u32);

/* Steering block at motion+0x48: +4 is the speed counter, +8 the travel angle. */
struct HomingSteer { u8 _0[4]; s32 speed; u32 angle; };

/* Runs a returning (boomerang-style) projectile: drains its speed each frame,
 * steering and moving it; when speed hits zero it flips the heading 180 degrees,
 * restarts the flight, plays an animation and fires the end callback. */
void sub_08048B0C(void *entity) {
    void *sprite;
    void *motion;
    void *collision;
    struct HomingSteer *steer;
    u32 *callback;

    sprite = *(void **)((u8 *)entity + 0x38);
    motion = *(void **)((u8 *)entity + 0x3C);
    collision = (u8 *)motion + 0x34;
    steer = (struct HomingSteer *)((u8 *)motion + 0x48);
    steer->speed = steer->speed + 0xFFFFE000;
    sub_080146D0(motion, steer->angle, steer->speed);
    sub_08049180(sprite, collision, motion, steer);
    sub_0801165C(motion, 0);
    if (steer->speed <= 0) {
        steer->angle = (steer->angle + 0x8000) & 0xFFFF;
        steer->speed = 0x20000;
        sub_080146D0(motion, steer->angle, steer->speed);
        setAnimationFrame(sprite, collision, 0xA, 0);
        *(u8 *)((u8 *)entity + ((s32)*(s16 *)((u8 *)entity + 0x22) * 2) + 0x19) = 0;
        callback = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
    }
}
