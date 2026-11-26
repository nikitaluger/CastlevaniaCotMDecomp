/*
 * Actor script step: pick an animation frame (0x37 or 0x39) from the script's
 * action byte, tick the animation, then when the byte passes its upper
 * threshold and the anim-state flag is set, publish two work pointers plus a
 * state code to the global game state, clear the byte and run the next step.
 */
extern s32 setObjectAnimation(void *, void *, s32, s32);
extern s32 sub_08011528(void *, void *);
extern s32 sub_080C31E4(void *, void *, u32);

/* Global game state in IWRAM; only the fields this step writes are named. */
struct GameState {
    u8 _pad0[0x10];
    u32 f10;  /* action code published by this step */
    u8 _pad1[0x48 - 0x14];
    u32 f48;  /* work+8 pointer */
    u32 f4C;  /* work+0xC pointer */
};
extern struct GameState gMainWorkspace;

#define ACTION_LOW_MAX   0x1D
#define ACTION_HIGH_MIN  0x1E
#define FRAME_LOW        0x37
#define FRAME_HIGH       0x39
#define ACTION_STATE     0xA
#define ANIM_FLAG_BUSY   2

void sub_080B4A1C(void *arg0) {
    void *sprite;
    void *work;
    u8 *animState;
    u32 *callbackTable;
    u8 actionByte;
    sprite = *(void **)((u8 *)arg0 + 0x38);
    work = *(void **)((u8 *)arg0 + 0x3C);
    animState = (u8 *)work + 0x34;
    actionByte = *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19);
    if (actionByte <= ACTION_LOW_MAX) {
        setObjectAnimation(sprite, animState, FRAME_LOW, 0);
    } else {
        setObjectAnimation(sprite, animState, FRAME_HIGH, 0);
    }
    sub_08011528(sprite, animState);
    actionByte = *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19);
    if (actionByte > ACTION_HIGH_MIN && (*animState & ANIM_FLAG_BUSY)) {
        gMainWorkspace.f48 = *(u32 *)((u8 *)work + 8);
        gMainWorkspace.f4C = *(u32 *)((u8 *)work + 0xC);
        gMainWorkspace.f10 = ACTION_STATE;
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
        callbackTable = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *callbackTable);
    }
}
