extern u8 gCrossfadeGfxState[];
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* "Wait 16 frames" script command, counted up faster: adds 3 to the shared
 * frame counter at 0x03000830+8 each frame and, once it passes 15, clears the
 * current step's flag byte (self+0x19 + step*2, step = s16 at self+0x22),
 * advances the script with sub_080C31E4(self+0x18, self+0x22, *0x08671BB0),
 * sets the flag to 1 and dispatches the new command's handler from the actor's
 * command table (self+0x14, indexed by the command byte at self+0x18+step*2). */
void sub_08001C8C(void *actor) {
    struct { u8 _[8]; u16 v; } *counter = (void *)gCrossfadeGfxState;
    u8 *self = actor;
    counter->v += 3;
    if (counter->v > 0x0F) {
        u8 *stepSlot;
        s32 *scriptTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        stepSlot = self + 0x18;
        sub_080C31E4(stepSlot, self + 0x22, *scriptTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        stepSlot = stepSlot + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(actor, *(void **)((u32)*stepSlot * 4 + *(u32 *)(self + 0x14)));
    }
}
