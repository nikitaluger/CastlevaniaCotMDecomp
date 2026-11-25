extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script command: clear the actor's flag at +0x40 and the current step's
 * progress byte, let the step runner advance the step index, mark the new step
 * as started and dispatch its command handler from the table at +0x14. */
void sub_08049360(void *actor)
{
    void *steps;
    const u32 *stepFnTable;
    *(u8 *)(actor + 0x40) = 0;
    *(u8 *)(actor + (s32)*(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
    stepFnTable = (const u32 *)0x08671BB0;
    steps = actor + 0x18;
    sub_080C31E4(steps, actor + 0x22, *stepFnTable);
    *(u8 *)(actor + (s32)*(s16 *)(actor + 0x22) * 2 + 0x19) += 1;
    steps += (s32)*(s16 *)(actor + 0x22) * 2;
    sub_080C31E0(actor, *(u32 *)((u8 *)*(u32 *)((u8 *)actor + 0x14) + *(u8 *)steps * 4));
}
