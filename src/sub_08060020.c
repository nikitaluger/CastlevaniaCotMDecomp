extern u8 gCameraState[];
extern void sub_08061048(void);
extern void sub_08061084(void);
extern void sub_080610D0(void);

/* Per-frame palette update: apply the current brightness, step the fade when
 * the fade-active flag is set, and advance the palette animation timer. */
s32 sub_08060020(void) {
    u8 *gameState;
    sub_08061048();
    gameState = gCameraState;
    if (gameState[0x145C] & 8) {
        sub_080610D0();
        sub_08061084();
    }
    *(u32 *)(gameState + 0x1454) = *(u32 *)(gameState + 0x1454) + 1;
    return 0;
}
