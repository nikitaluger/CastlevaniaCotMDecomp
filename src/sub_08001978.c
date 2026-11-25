/* Script command: bumps the shared frame-delay counter at 0x03000830; once it
 * passes 15, clears the current step's flag, advances the actor's script and
 * dispatches the next command's handler from the actor's handler table. */
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_08001978(void *actor)
{
    s16 step;
    void *actorPtr;
    s32 **tablePtr;
    u8 *stepSlot;
    s32 *scriptTable;
    vu16 *counter = (vu16 *) 0x03000830;
    u8 *cmdByte;
    u32 counterValue;

    counterValue = counter[4] + 1;
    counter[4] = counterValue;
    ;
    if (((u16) counterValue) <= 0x0F)
    {
        return;
    }
    step = *((s16 *) (((u8 *) actor) + 0x22));
    *((u8 *) ((((u8 *) actor) + (step * 2)) + 0x19)) = 0;
    scriptTable = (s32 *) 0x08671BB0;
    stepSlot = ((u8 *) actor) + 0x18;
    sub_080C31E4(stepSlot, ((u8 *) actor) + 0x22, *scriptTable);
    actorPtr = actor;
    step = *((s16 *) (((u8 *) actor) + 0x22));
    tablePtr = (s32 **) (((u8 *) actorPtr) + 0x14);
    *((u8 *) ((((u8 *) actorPtr) + (step * 2)) + 0x19)) += 1;
    step = *((s16 *) (((u8 *) actorPtr) + 0x22));
    stepSlot += step * 2;
    cmdByte = stepSlot;
    {
        u8 cmd = *cmdByte;
        s32 *handlers = *tablePtr;
        sub_080C31E0(actor, handlers[cmd]);
    }
}
