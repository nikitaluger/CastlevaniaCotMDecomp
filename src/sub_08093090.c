extern void setObjectAnimationFrame(s32, s32, s16, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallbacks[];

struct S_02025FF0_93090 {
    u8 _0x000[0x10];
    u32 scriptValue;
    u8 _0x014[0x28];
    u16 mode;
};
extern struct S_02025FF0_93090 gMainWorkspace;
extern u8 D_08100684[];

/* Starts the animation for the current mode (unless mode 1 or an inactive
 * non-mode-2 state), records the script value and advances to the next step. */
void sub_08093090(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *anim = *(u8 **)(self + 0x3C);
    u8 *animParams = anim + 0x1C;
    u16 mode = gMainWorkspace.mode;

    if (mode == 1) return;
    if (*(s16 *)(anim + 0x14) != 1 && mode != 2) return;

    {
        u8 *animTable = D_08100684;
        u32 offset = *(u32 *)anim << 2;
        animTable += 2;
        setObjectAnimationFrame((s32)sprite, (s32)animParams, *(s16 *)(animTable + offset), 0);
    }
    *(u16 *)(anim + 0x16) = 1;
    if (gMainWorkspace.mode != 2) {
        u32 scriptValue = *(u32 *)(*(u8 **)(anim + 0x18) + 4);
        if (scriptValue != 0) {
            gMainWorkspace.scriptValue = scriptValue;
        }
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *scriptHandlers = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
    }
}
