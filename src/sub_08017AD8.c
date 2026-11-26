void setAnimationFrame(s32, void *, s32, s32);
void sub_080161F0(void);
void sub_080C31E8(void *, void *, s32, s32);

/* Script-step callback: sets a companion animation and an initial velocity,
 * clamps a motion coordinate to a control limit (zeroing velocity when reached),
 * and when a control flag is set clears a counter/flag and redirects the script. */
void sub_08017AD8(void *arg0) {
    s32 companion = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *scriptState = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *stateArg = scriptState + 0x34;
    u8 *control = scriptState + 0x48;
    s32 zero;
    u8 *targetObj;
    void **pp;

    setAnimationFrame(companion, stateArg, 0xB, 0);
    targetObj = *(u8 **)(control + 0x34);
    zero = 0;
    targetObj[1] = zero;
    *(s32 *)(scriptState + 0x14) = 0xA000;
    if (*(s32 *)(scriptState + 0x0C) >= *(s32 *)(control + 0x0C)) {
        *(s32 *)(scriptState + 0x0C) = *(s32 *)(control + 0x0C);
        *(s32 *)(scriptState + 0x14) = zero;
    }
    if (*stateArg & 2) {
        if (*(s32 *)(scriptState + 0x0C) >= *(s32 *)(control + 0x0C)) {
            *(s32 *)(scriptState + 0x0C) = *(s32 *)(control + 0x0C);
            *(s32 *)(scriptState + 0x14) = zero;
            if (*(u32 *)(control + 0x34) != 0) {
                sub_080161F0();
                *(u32 *)(control + 0x34) = zero;
            }
            ((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2)[0x17] = zero;
            pp = (void **)0x08671BD8;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 1, (s32)*pp);
        }
    }
}
