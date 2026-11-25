/* Script command: show the record screen. Loads all graphics banks, draws and
 * updates the record panel, loads the full graphic set, then advances the
 * script and dispatches the next command's handler. */
extern void sub_0800ECF8(void);
extern void sub_0800EDAC(s32);
extern void sub_0800EF3C(s32);
extern void sub_0800F104(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_0800D654(void *actor)
{
    s16 step;
    u8 *stepSlot;
    s32 *scriptTable;

    sub_0800F104(actor);
    sub_0800ECF8();
    sub_0800EDAC(1);
    sub_0800EF3C(0xFF);

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
