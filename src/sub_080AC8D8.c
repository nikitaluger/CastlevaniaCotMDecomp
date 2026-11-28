void initCrossfadeGfxState(void);
s32 sub_080C31E0(void *, void *);

struct GameState { u8 _0[0x3C]; u16 screenMode; };
extern struct GameState gMainWorkspace;

/* Script step handler: when the current slot's sub-step counter reaches 0x5A,
 * switch the graphics state to mode 2, apply the BG control registers and
 * chain to the saved update handler. */
void sub_080AC8D8(void *arg0) {
    u8 *p = (u8 *)arg0;
    s16 idx = *(s16 *)(p + 0x22);
    if (*(u8 *)(p + 0x19 + (idx << 1)) == 0x5A) {
        gMainWorkspace.screenMode = 2;
        initCrossfadeGfxState();
        sub_080C31E0(arg0, *(void **)(p + 0x24));
    }
}
