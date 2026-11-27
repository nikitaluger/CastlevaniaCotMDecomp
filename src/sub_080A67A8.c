extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern s32 gMainObjTimerCallbacks[];

// Work state at self+0x3C: +0xEC flip flag, +0xEE/+0xEF phase bytes, +0x114 motion.
struct WorkState {
    u8 pad[0xEC];
    u16 flipFlags;
    u8 pad2[0x26];
    u32 motion;
};

// Reset work-state phase/motion from the sprite's flip flag, clear then bump the
// current script-step byte, advance the step and switch to the next AI handler.
void sub_080A67A8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    struct WorkState *work = *(struct WorkState **)(self + 0x3C);
    u8 *phase = (u8 *)work + 0xEE;
    *phase++ = 0;
    *phase = 1;
    work->flipFlags = *(u16 *)(sprite + 2) & 0x10;
    work->motion = 0x180;
    {
        u8 zero = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    }
    {
        s32 *scriptTable = gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        u8 *actionEntry = self + 0x18;
        s16 stepIndex = *(s16 *)(self + 0x22);
        actionEntry += stepIndex * 2;
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *actionEntry * 4));
    }
}
