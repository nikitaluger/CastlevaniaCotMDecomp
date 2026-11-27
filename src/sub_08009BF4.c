/* Script command: point the actor's linked object at the graphics table
 * 0x08636624, set its 0x400 flag, then advance the script and dispatch the
 * next command's handler. */
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern s32 gScriptStepCallbackTable[];

struct GfxTarget { u8 pad[2]; u16 flags; };

void sub_08009BF4(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *target = *(u8 **)(self + 0x38);
    u8 *stepSlot;
    s32 *scriptTable;
    u8 zero;

    *(u32 *)(target + 0x24) = 0x08636624;
    ((struct GfxTarget *)target)->flags |= 0x400;
    zero = 0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    scriptTable = (s32 *)0x08671BB0;
    stepSlot = self + 0x18;
    sub_080C31E4(stepSlot, self + 0x22, *scriptTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepSlot += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)stepSlot * 4));
}
