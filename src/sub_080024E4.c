void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct IoState { u8 pad[8]; u16 waitTimer; };
extern struct IoState gCrossfadeGfxState;

/* Script-step dispatcher: run the entity's current command once the gCrossfadeGfxState
 * countdown at +8 has drained, then advance the action byte and install the
 * handler for the next command from the entity's handler table. */
void sub_080024E4(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *cmdPtr;
    s32 *scriptTable;
    u16 timer;

    timer = gCrossfadeGfxState.waitTimer;
    if (timer <= 2) {
        u8 zero;
        gCrossfadeGfxState.waitTimer = 0;
        zero = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        scriptTable = (s32 *)0x08671BB0;
        cmdPtr = self + 0x18;
        sub_080C31E4(cmdPtr, self + 0x22, *scriptTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        cmdPtr += *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(entity, *(void **)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)cmdPtr * 4));
    } else {
        gCrossfadeGfxState.waitTimer = timer - 2;
    }
}
