extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern s32 gMainObjTimerCallback[];

struct Blk {
    u8 pad[0xEC];
    u16 xFlip;
    u8 pad2[0x26];
    u32 timer;
};

/* Starts the effect's spin state: sets the phase bytes, copies the sprite's
 * X-flip flag into the work state and sets its duration, then advances the
 * script step and dispatches the new step's handler. */
void sub_080A6BE8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    struct Blk *work = *(struct Blk **)(self + 0x3C);
    u8 *phase = (u8 *)work + 0xEE;
    *phase++ = 0;
    *phase = 2;
    work->xFlip = *(u16 *)(sprite + 2) & 0x10;
    work->timer = 0x60;
    {
        u8 zero = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    }
    {
        s32 *scriptHandlers = gMainObjTimerCallback;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        u8 *stepBase = self + 0x18;
        s16 idx = *(s16 *)(self + 0x22);
        stepBase += idx * 2;
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *stepBase * 4));
    }
}
