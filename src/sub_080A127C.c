/* External script-step callback: advances a scripted entity's step counter,
 * nudges its companion on every 8th step, and on step 0x5A sets facing, flags
 * the sprite, resets the step and redirects the script. */
extern s32 sub_08011528(s32, s32);
extern s32 sub_080A1744(s32, s32);
extern s32 sub_080A1780(s32, s32, s32);
extern s32 sub_080A2DF4(void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BD0;

void sub_080A127C(void *obj) {
    s32 sprite = *(s32 *)((u8 *)obj + 0x38);
    s32 scriptState = *(s32 *)((u8 *)obj + 0x3C);
    s32 stateArg = scriptState + 0x34;
    s32 control = scriptState + 0x48;
    s32 *handlerAddr;

    /* companion sprite update */
    sub_08011528(sprite, stateArg);

    /* every 8th step: refresh companion positioning */
    if (!(((u8 *)obj)[*(s16 *)((u8 *)obj + 0x22) * 2 + 0x19] & 7)) {
        sub_080A2DF4(obj, scriptState);
    }

    /* step 0x5A: set facing, flag sprite, reset step, redirect script */
    if (((u8 *)obj)[*(s16 *)((u8 *)obj + 0x22) * 2 + 0x19] == 0x5A) {
        sub_080A1780(sprite, stateArg, control);
        sub_080A1744(sprite, scriptState);
        ((u8 *)obj)[*(s16 *)((u8 *)obj + 0x22) * 2 + 0x19] = 0;
        handlerAddr = &D_08671BD0;
        sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 1, *handlerAddr);
    }
}
