extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
extern s32 gMainObjTimerCallbacks[];

/* Test whether the enemy's box at +0xA8 reaches its own 16.16 position (within
 * 0x0C0000); on contact, restart the action script, otherwise slide the box
 * toward the target, clamped by the wall/floor data at enemy+0xDC. */
void sub_08026780(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *enemy = *(u8 **)(self + 0x3C);
    u8 *box = enemy + 0xA8;
    s32 *eventPtr;

    if (sub_08014A04(box, *(s32 *)(enemy + 8), *(s32 *)(enemy + 0xC), 0xC0000, 0xC0000) == 1) {
        s16 stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) = 0;
        eventPtr = gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *eventPtr);
        return;
    }
    sub_08014B1C(box, enemy + 0xDC, *(s32 *)(enemy + 8), *(s32 *)(enemy + 0xC));
}
