extern u32 nextRandomWord(void);
extern u32 scaleByRandom(u32);
extern void spawnHitSpark(s32, void *);
extern void advanceAnimTrack(void *, void *);
extern void setTrackAnimFrame(void *, void *, s16, s32, u8);
extern void advanceAnimTrackByDelta(void *, void *, s32);

extern u8 D_08101C60[];
extern u8 D_08101C74[];
extern u16 D_08101C78[];

/* Advance one main-object effect step: run the animation countdown and spawn a
   hit spark when it expires, switch to a specific frame at step 0x5A, update
   the animation track, and branch to a new step after the delayed phase ends. */
void updateMainObjectEffectStep(void *arg0) {
    void *obj = arg0;
    void *sprite = *(void **)((u8 *)obj + 0x38);
    void *state = *(void **)((u8 *)obj + 0x3C);
    u8 *track = (u8 *)state + 0x34;
    u8 *work = (u8 *)state + 0x48;
    s16 stepIndex;
    u8 stepByte;
    u32 countdown;
    u32 randomWord;
    u32 trackIndex;
    s16 frame;
    u32 phase;
    u32 span;
    s32 index;
    u32 spanValue;
    u8 *branchTable;
    u8 *argTable;
    u8 branchByte;
    u32 zeroWord;
    u16 callbackArg;
    void *callback;
    u8 *frameTable;
    u32 frameAddr;
    u32 argIndex, tableOffset;
    u32 *callbackTable;
    volatile u32 *dma;
    u8 *stepBase, *stepIndexPtr;

    stepIndex = *(s16 *)((u8 *)obj + 0x22);
    stepByte = *((u8 *)obj + stepIndex * 2 + 0x19);
    if (stepByte <= 0x59) {
        if (track[0] & 2) {
            countdown = *(u32 *)(work + 0x6C);
            if (countdown != 0) {
                countdown--;
                *(u32 *)(work + 0x6C) = countdown;
            } else {
                randomWord = nextRandomWord();
                if ((randomWord & 0x1F) == 0) {
                    spawnHitSpark(*(u32 *)(state + 0x48), state);
                    *(u32 *)(work + 0x6C) = 0x0C;
                }
            }
        }
    }

    stepIndex = *(s16 *)((u8 *)obj + 0x22);
    stepByte = *((u8 *)obj + stepIndex * 2 + 0x19);
    if (stepByte == 0x5A) {
        frameTable = D_08101C60;
        trackIndex = *(u32 *)(work + 0x00);
        frameAddr = trackIndex * 4;
        frameTable = frameTable + 2;
        frameAddr = frameAddr + (u32)frameTable;
        frame = *(s16 *)frameAddr;
        setTrackAnimFrame(sprite, track, frame, (s32)0xFFFF0000, 0);
    }

    stepIndex = *(s16 *)((u8 *)obj + 0x22);
    stepByte = *((u8 *)obj + stepIndex * 2 + 0x19);
    if (stepByte <= 0x59) {
        advanceAnimTrack(sprite, track);
    } else {
        advanceAnimTrackByDelta(sprite, track, (s32)0xFFFF0000);
    }

    stepIndex = *(s16 *)((u8 *)obj + 0x22);
    stepByte = *((u8 *)obj + stepIndex * 2 + 0x19);
    if (stepByte > 0x5A) {
        if (track[0] & 2) {
            phase = *(u32 *)(work + 0x68);
            if (phase == 0 || phase == 2) {
                span = scaleByRandom(2);
                *(u32 *)(work + 0x64) = span;
                *(u32 *)(work + 0x68) = 0;
            }
            index = *(u32 *)(work + 0x68);
            index = index + 1;
            *(u32 *)(work + 0x68) = index;
            branchTable = D_08101C74;
            spanValue = *(u32 *)(work + 0x64);
            tableOffset = spanValue * 2;
            tableOffset -= 1;
            index = index + tableOffset;
            index = index + (u32)branchTable;
            branchByte = *(u8 *)index;
            zeroWord = 0;
            dma = (volatile u32 *)0x040000D4;
            dma[0] = (u32)&zeroWord;
            dma[1] = (u32)(work + 0x0C);
            dma[2] = 0x8500000F;
            (void)dma[2];
            stepIndex = *(s16 *)((u8 *)obj + 0x22);
            *((u8 *)obj + stepIndex * 2 + 0x19) = 0;
            callbackTable = (u32 *)SCRIPT_STEP_CALLBACK_TABLE;
            stepBase = (u8 *)obj + 0x18;
            stepIndexPtr = (u8 *)obj + 0x22;
            argTable = (u8 *)D_08101C78;
            argIndex = branchByte;
            argIndex = argIndex * 2;
            argIndex = argIndex + (u32)argTable;
            callbackArg = *(u16 *)argIndex;
            callback = (void *)*callbackTable;
            ((void (*)(void *, void *, u16))callback)(stepBase, stepIndexPtr, callbackArg);
        }
    }
}
