extern void sub_08005E80(s32);
extern void sub_0800B9A8(s32, s32, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct S_02021E90_b8c4 { u8 _0[0x146C]; u16 f146C; u8 _1[2]; u16 f1470; };
extern struct S_02021E90_b8c4 gCameraState;
extern void *gMenuScriptCallback;

/* Menu cursor handler: adjusts the wrapped 0..7 selection from directional
 * input, plays a sound and redraws the menu when it changes, and confirms the
 * current entry (resetting state and dispatching a message) on the confirm flag. */
s32 sub_0800B8C4(void *arg0, u8 arg1) {
    u8 *cursor;
    s8 *cursorSigned;
    s8 *cursorCheck;
    s32 oldCursor;
    void *target;
    u8 mode;

    mode = arg1;
    target = *(void **)((u8 *)arg0 + 0x3C);
    cursor = (u8 *)arg0 + 0x50;
    cursorSigned = (s8 *)cursor;
    oldCursor = cursorSigned[0];
    if ((gCameraState.f1470 & 0x30) != 0x30) {
        if (gCameraState.f1470 & 0x20) {
            cursor[0] = cursor[0] - 1;
        }
        if (gCameraState.f1470 & 0x10) {
            cursor[0] = cursor[0] + 1;
        }
        if (cursorSigned[0] < 0) {
            cursor[0] = 7;
        }
        if (cursorSigned[0] == 8) {
            cursor[0] = 0;
        }
    }
    cursorCheck = (s8 *)arg0;
    cursorCheck += 0x50;
    if (oldCursor != cursorCheck[0]) {
        sub_08005E80(0xAA << 1);
        sub_0800B9A8(cursorCheck[0], mode, target);
    }
    if (gCameraState.f146C & 2) {
        *(u8 *)((u8 *)target + 0x635) = 0;
        sub_08005E80(0x159);
        *(s8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x17) = 0;
        {
            void **msgFunc = &gMenuScriptCallback;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0x10, (s32)*msgFunc);
        }
        return 1;
    }
    return 0;
}
