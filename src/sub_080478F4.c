extern u32 D_0866E314[];
extern void sub_08011368(void *, void *, s32, s32);

/* Script command: start the actor's step-0 animation, switch to this script's
 * handler table, run the next step once (temporarily advancing the step index),
 * then restore the index. */
void sub_080478F4(void *actor)
{
    u8 *self = (u8 *)actor;
    s16 idx;
    u8 stepId;

    sub_08011368(*(void **)(self + 0x38), *(u8 **)(self + 0x3C) + 0x34, 0, 1);

    *(u32 *)(self + 0x14) = (u32)D_0866E314;
    *(u16 *)(self + 0x22) += 1;

    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + 0x19 + idx * 2) += 1;

    idx = *(s16 *)(self + 0x22);
    {
        s32 off = idx * 2;
        u8 *addr = self;
        addr += 0x18;
        addr = addr + off;
        stepId = *addr;
    }

    ((void (**)(void *))*(u32 *)(self + 0x14))[stepId](actor);

    *(u16 *)(self + 0x22) -= 1;
}
