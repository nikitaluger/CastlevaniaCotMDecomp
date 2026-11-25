extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void sub_080146D0(void *, s32, s32);
extern void sub_08049160(void *, void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Steering block at motion+0x48: +4 is the speed counter, +8 the travel angle. */
struct HomingSteer { u8 _0[4]; s32 speed; u32 angle; };

/* Updates a homing projectile: ramps its speed up or down from the per-entity
 * state byte, steers and moves it, and fires the end callback at state 0x14. */
void sub_08048BA4(void *entity) {
    void *sprite;
    void *motion;
    void *collision;
    struct HomingSteer *steer;
    u32 *callback;

    sprite = *(void **)((u8 *)entity + 0x38);
    motion = *(void **)((u8 *)entity + 0x3C);
    collision = (u8 *)motion + 0x34;
    steer = (struct HomingSteer *)((u8 *)motion + 0x48);
    if (*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) <= 0x13) {
        steer->speed = steer->speed + 0x2000;
    } else {
        steer->speed = steer->speed + 0xFFFFE000;
    }
    sub_080146D0(motion, steer->angle, steer->speed);
    sub_080113A8(sprite, collision);
    sub_0801165C(motion, 0);
    if (*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) == 0x14) {
        sub_08049160(sprite, collision, steer, 0);
        *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
        callback = (u32 *)0x08671BD0;
        sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 0, *callback);
    }
}
