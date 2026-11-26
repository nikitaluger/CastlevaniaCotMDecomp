extern void sub_08003740(void *timer, void *gfx);
extern void sub_08005E80(s32 soundId);
extern void sub_0806D588(void *gfx, void *state);
extern void sub_080C31E4(void *scriptData, void *scriptIndex, s32 handler);

struct S_02025FF0 { u8 _0[0x10]; u32 field10; u32 mode; u8 _1[0x1824]; };
extern struct S_02025FF0 gMainWorkspace;

/* Initialises the effect actor for game mode 9: flashes the screen white,
 * resets its animation phase and 0xA0-frame timer, plays sound effect 0x19A,
 * clears the current script byte and advances the script, then refreshes the
 * sprite's camera-relative screen position. */
void sub_08089A94(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x6C);
    u8 *state = work + 4;
    u8 *gfx = *(u8 **)(self + 0x38);
    s32 *handler;
    if (gMainWorkspace.mode == 9) {
        *(vu16 *)0x05000000 = 0x7FFF;
        *(u8 *)(work + 0x34) = 0;
        *(s32 *)(state + 0x2C) = 0xA0;
        sub_08005E80(0x19A);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        handler = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *handler);
    }
    sub_0806D588(gfx, state);
}
