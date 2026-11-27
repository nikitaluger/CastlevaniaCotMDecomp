/* Update an entity's view flags and accumulate the body's x/y deltas; when the
 * animation frame reaches its end marker, reset the accumulators and frame and
 * run the next animation command. */
extern void refreshMotionTrail(void *, void *);
extern void _call_via_r2(void *, void *, s32);
extern s32 gMainObjTimerCallbacks;

void sub_080A7BE4(void *arg0) {
    u16 *viewFlags = *(u16 **)((u8 *)arg0 + 0x38);
    void *body = *(void **)((u8 *)arg0 + 0x3C);
    u8 *bodyData = (u8 *)body + 0x48;
    s16 *animIndex = (s16 *)arg0;
    if (!(*(u8 *)((u8 *)arg0 + animIndex[0x11] * 2 + 0x19) & 2)) {
        *viewFlags = (*viewFlags & 0xFFF) | 0xE000;
    }
    {
        u8 *accumX = (u8 *)body + 0xFC;
        *(s32 *)accumX += *(s32 *)((u8 *)body + 0x14C);
        *(s32 *)((u8 *)body + 0x100) += *(s32 *)((u8 *)body + 0x150);
        if (*(u8 *)((u8 *)arg0 + animIndex[0x11] * 2 + 0x19) == 0xC) {
            *(s32 *)((u8 *)body + 0x100) = 0;
            *(s32 *)accumX = 0;
            *(u8 *)((u8 *)arg0 + animIndex[0x11] * 2 + 0x19) = 0;
            {
                s32 *animScript = &gMainObjTimerCallbacks;
                _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *animScript);
            }
        }
    }
    refreshMotionTrail(arg0, bodyData);
}
