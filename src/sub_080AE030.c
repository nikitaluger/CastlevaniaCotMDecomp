extern s32 sub_08005910(s32, s32);
extern void sub_080146D0(void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

struct GameState { u8 _pad[0x174C]; u32 targetX; u32 targetY; };
extern struct GameState D_02025FF0;

/* Aiming step: at script step 3, point the work at the tracked target position
 * (the camera target at game state +0x174C/+0x1750) and set its velocity to
 * 1.25 pixels per frame, then clear the step byte and advance the script. */
void sub_080AE030(u8 *self) {
    u8 *work = *(u8 **)(self + 0x3C);
    s32 dy, dx;
    s32 heading;
    s32 *scriptCb;

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 3) {
        dy = D_02025FF0.targetY - *(s32 *)(work + 0xC);
        dx = D_02025FF0.targetX - *(s32 *)(work + 8);
        heading = sub_08005910(dy, dx);
        sub_080146D0(work, heading, 0x14000);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptCb = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
    }
}
