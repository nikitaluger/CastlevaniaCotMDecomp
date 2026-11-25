extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_08014938(s32);
extern s32 sub_08014990(void *);
extern void sub_08048074(s32, s32, s32, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Face-and-spawn effect: when the object already faces its target, emit a
 * projectile at a distance-scaled offset; on the animation flag set the
 * horizontal velocity toward the target and return to the script. */
void sub_080477D4(void *self) {
    void *mainObj;
    void *state;
    void *state34;
    void *state48;
    s32 facing;
    s32 distance;
    s32 speed;
    s32 velocity;
    s32 *scriptJump;
    s16 scriptIdx;

    mainObj = *(void **)((u8 *)self + 0x38);
    state = *(void **)((u8 *)self + 0x3C);
    state34 = (u8 *)state + 0x34;
    state48 = (u8 *)state + 0x48;
    *(s32 *)((u8 *)state + 0x10) = 0;
    sub_08011368(mainObj, state34, 8, 0);
    if (*(u8 *)((u8 *)state34 + 1) == 2 && *(s32 *)((u8 *)state34 + 4) == 1) {
        facing = sub_08014990(mainObj);
        if (facing == sub_08014938(*(s32 *)((u8 *)state + 8))) {
            distance = sub_08014900(*(s32 *)((u8 *)state + 8));
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
        if (sub_08014990(mainObj) < 0) {
            sub_08048074(*(s32 *)((u8 *)state + 8) + 0xFFE80000, *(s32 *)((u8 *)state + 0x0C) + 0xFFDC0000, -speed, 0xFFFFE000, *(s16 *)((u8 *)state + 0x1C));
        } else {
            sub_08048074(*(s32 *)((u8 *)state + 8) + 0x180000, *(s32 *)((u8 *)state + 0x0C) + 0xFFDC0000, speed, 0xFFFFE000, *(s16 *)((u8 *)state + 0x1C));
        }
    }
    if (*(u8 *)state34 & 0x02) {
        if (*(s32 *)((u8 *)state + 8) < *(s32 *)((u8 *)state48 + 0)) {
            velocity = 0x4000;
        } else {
            velocity = 0xFFFFC000;
        }
        *(s32 *)((u8 *)state + 0x10) = velocity;
        scriptIdx = *(s16 *)((u8 *)self + 0x22);
        ((u8 *)self)[scriptIdx * 2 + 0x19] = 0;
        scriptJump = (s32 *)0x08671BD0;
        sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 0, *scriptJump);
    }
}
