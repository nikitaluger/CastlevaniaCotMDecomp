extern void stepAnimationTrack(s32, void *);
extern void advanceMotion(void *, s32);

/* Motion step: refresh the object's sprite from its motion controller, and when
 * the current slot's command byte is 0x10, clear the controller's motion
 * counter; then integrate the controller's position and velocity. */
void sub_080B8BD8(void *arg0) {
    s32 sprite = *(s32 *)((u8 *)arg0 + 0x38);
    void *motion = *(void **)((u8 *)arg0 + 0x3C);
    stepAnimationTrack(sprite, (u8 *)motion + 0x34);
    if (*(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) == 0x10) {
        *(s32 *)((u8 *)motion + 0x14) = 0;
    }
    advanceMotion(motion, 0);
}
