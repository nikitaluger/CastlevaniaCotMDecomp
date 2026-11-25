extern s32 sub_08011408(s32, void *, s32, s32, s32);

/* Play animation frame 2 in the work's current playback direction, then
 * decelerate the work's velocity, mirror the new value into the playback
 * direction field, and clamp the velocity at its minimum. */
void sub_0802F298(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    s32 vel;
    sub_08011408(sprite, work + 0x34, 2, *(s32 *)(work + 0x48), 1);
    vel = *(s32 *)(work + 0x10) + (s32)0xFFFFF7C0;
    *(s32 *)(work + 0x10) = vel;
    *(s32 *)(work + 0x48) = -vel;
    if (vel < (s32)0xFFFB8000) {
        *(s32 *)(work + 0x10) = (s32)0xFFFB8000;
    }
}
