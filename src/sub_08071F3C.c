extern void sub_08071FDC(void);
extern void sub_08072018(void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *D_08671BC0;
extern u8 D_02025368[];
extern u32 D_080E0738[];

/* While the level-up check is not busy, compare the current score against the
 * threshold for the next level and either award the level or end the check. */
void sub_08071F3C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *gameState;
    s32 delay;

    gameState = D_02025368;
    delay = *(s32 *)(self + 0x30);
    if (delay == 0) {
        u32 *score = (u32 *)(gameState + 0x300);
        u32 *levelThresholds = D_080E0738;
        s16 level = *(s16 *)(gameState + 0x2FC);
        s32 thresholdIndex = level - 1;
        if (*score < *(levelThresholds + thresholdIndex)) {
            sub_08071FDC();
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            {
                void **fnPtr = &D_08671BC0;
                sub_080C31E4(self + 0x18, self + 0x22, *fnPtr);
            }
        } else {
            sub_08072018(arg0);
        }
    }
}
