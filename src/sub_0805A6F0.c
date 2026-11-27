/* Enemy script step: start animation 0x10, tick the timer at moveState+8 and
 * steer at speed 0x20000 along the heading at moveState+0x18; once the timer
 * underflows and the animation has ended, clear the action and advance the script. */
extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void setPolarOffset(void *, s32, s32);
extern s32 gScriptStepCallbacks[];

void sub_0805A6F0(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x34;
    u8 *moveState = work + 0x48;
    s32 *scriptTable;
    s32 countdown;

    setAnimationFrame(sprite, animState, 0x10, 0);
    countdown = *(u16 *)(moveState + 8) - 1;
    *(u16 *)(moveState + 8) = countdown;
    if ((countdown << 16) < 0 && (*(u8 *)animState & 2)) {
        s16 scriptIndex;
        scriptIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + scriptIndex * 2 + 0x19) = 0;
        scriptTable = gScriptStepCallbacks;
        sub_080C31E8(self + 0x18, self + 0x22, 0, *scriptTable);
    } else {
        setPolarOffset(work, (*(u32 *)(moveState + 0x18) + 0x8000) & 0xFFFF, 0x20000);
    }
}
