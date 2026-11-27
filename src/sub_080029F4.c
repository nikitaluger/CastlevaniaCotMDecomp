/* "Delay 14 frames" script command: takes 14 frames off the shared frame-delay
 * counter (gCrossfadeGfxState.field). When it is about to run out, the current step's
 * flag byte (self+0x19 + step*2, step = s16 at self+0x22) is cleared, the
 * script advances one command via sub_080C31E4(self+0x18, self+0x22,
 * *scriptTable), the flag is set to 1 and the new command's handler is
 * dispatched from the actor's command table (self+0x14, indexed by the
 * command byte at self+0x18 + step*2). */
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_03000830 { u8 pad[8]; u16 field; };
extern struct S_03000830 gCrossfadeGfxState;

void sub_080029F4(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *stepSlot;
    s32 *scriptTable;
    u16 framesLeft;

    framesLeft = gCrossfadeGfxState.field;
    if (framesLeft <= 14) {
        u8 zero;
        gCrossfadeGfxState.field = 0;
        zero = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        scriptTable = (s32 *)0x08671BB0;
        stepSlot = self + 0x18;
        sub_080C31E4(stepSlot, self + 0x22, *scriptTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        stepSlot += *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(actor, *(void **)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)stepSlot * 4));
    } else {
        gCrossfadeGfxState.field = framesLeft - 14;
    }
}
