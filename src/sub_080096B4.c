/* Script command: waits until this step's counter byte passes 59, then clears
 * the actor's flag at +0x5C, advances the script and dispatches the next
 * command's handler from the actor's handler table. */
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_080096B4(void *actor)
{
    s16 step;
    u8 *stepSlot;
    s32 *scriptTable;

    step = *(s16 *)((u8 *)actor + 0x22);
    if (*(u8 *)((u8 *)actor + step * 2 + 0x19) <= 0x3B) {
        return;
    }

    *((u8 *)actor + 0x5C) = 0;

    step = *(s16 *)((u8 *)actor + 0x22);
    *(u8 *)((u8 *)actor + step * 2 + 0x19) = 0;

    scriptTable = (s32 *)0x08671BB0;
    stepSlot = (u8 *)actor + 0x18;
    sub_080C31E4(stepSlot, (u8 *)actor + 0x22, *scriptTable);

    step = *(s16 *)((u8 *)actor + 0x22);
    *(u8 *)((u8 *)actor + step * 2 + 0x19) += 1;

    step = *(s16 *)((u8 *)actor + 0x22);
    stepSlot += step * 2;
    {
        u8 cmd = *stepSlot;
        s32 *handlers = *(s32 **)((u8 *)actor + 0x14);
        sub_080C31E0(actor, handlers[cmd]);
    }
}
