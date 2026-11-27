extern void sub_08071FDC(void);
extern void sub_08072018(void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gPoseScriptCallbacks;
extern u8 gGameStatus[];
extern u32 gLevelExpTable[];

/* While the level-up check is not busy, compare the current score against the
 * threshold for the next level and either award the level or end the check. */
void sub_08071F3C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *gameState;
    s32 delay;

    gameState = gGameStatus;
    delay = *(s32 *)(self + 0x30);
    if (delay == 0) {
        u32 *score = (u32 *)(gameState + 0x300);
        u32 *levelThresholds = gLevelExpTable;
        s16 level = *(s16 *)(gameState + 0x2FC);
        s32 thresholdIndex = level - 1;
        if (*score < *(levelThresholds + thresholdIndex)) {
            sub_08071FDC();
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            {
                void **fnPtr = &gPoseScriptCallbacks;
                sub_080C31E4(self + 0x18, self + 0x22, *fnPtr);
            }
        } else {
            sub_08072018(arg0);
        }
    }
}
