extern void sub_080C31E4(void *, void *, u32); /* _call_via_r2 */
extern s32 sub_08014114(s32, s32, s32, s32, s32, s32);
extern u32 gMainObjTimerCallbacks;

/* Script command: when the actor's work timer is running and the actor lies
 * inside the visible screen area (±0x30), clear the current script step's
 * counter byte and run the stream handler stored in gMainObjTimerCallbacks. */
void sub_0801F484(u8 *arg0) {
    u8 *work = *(u8 **)(arg0 + 0x3C);
    u8 *timer = work + 0x48;
    if (*(s16 *)(timer + 0x0A) != 0) {
        if (sub_08014114(*(s32 *)(work + 8), *(s32 *)(work + 0xC), -0x30, 0x30, -0x30, 0x30) != 0) {
            s16 step = *(s16 *)(arg0 + 0x22);
            *(u8 *)(arg0 + step * 2 + 0x19) = 0;
            {
                u32 *lit = &gMainObjTimerCallbacks;
                sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *lit);
            }
        }
    }
}
