void sub_080C31E4(void *, void *, s32);

/* Re-seat the entity's steer block on its animation position: steer velocity
 * = position + 0x100000 with damping 0x2800, reset its motion accumulators,
 * clear the current step's timer, then run the next command-script handler. */
void sub_0805A7BC(void *arg0)
{
    u8 *work;
    u8 *steer;
    s32 *handlerTable;

    work = *(u8 **)((u8 *)arg0 + 0x3C);
    steer = work + 0x48;
    *(s32 *)(steer + 0xC) = *(s32 *)(work + 8);
    *(s32 *)(steer + 0x10) = *(s32 *)(work + 0xC) + 0x100000;
    *(s32 *)(work + 0x10) = 0;
    *(s32 *)(work + 0x14) = 0x2800;
    *(u8 *)((u8 *)((*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
    handlerTable = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *handlerTable);
}
