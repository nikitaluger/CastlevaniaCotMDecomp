struct ActorCmd
{
    u8 _0x00[0x14];
    u32 handlerTable;
    u8 _0x18[0x0A];
    s16 step;
    u8 _0x24[0x14];
    u32 sprite;
    u32 work;
};

s32 updateObjectDisplayState(void *, void *);
void _call_via_r1(void *, void *);

/* Once the sprite check passes, install this actor's command table, advance
 * the script step and dispatch the new step's handler. */
void sub_080AD958(struct ActorCmd *arg0)
{
    u8 *actor = (u8 *)arg0;
    u8 *stepSlot;
    u8 *stepBase;
    u8 command;
    u32 stepOffset1;
    u32 stepOffset2;
    if (updateObjectDisplayState((void *)arg0->sprite, (void *)arg0->work) != 0)
        return;
    *(u32 *)(actor + 0x14) = 0x0867019C;
    *(u16 *)(actor + 0x22) = *(u16 *)(actor + 0x22) + 1;
    stepOffset1 = (u32)*(s16 *)(actor + 0x22) * 2;
    stepSlot = (u8 *)(stepOffset1 + (u32)actor);
    *(u8 *)(stepSlot + 0x19) += 1;
    stepOffset2 = (u32)*(s16 *)(actor + 0x22) * 2;
    stepBase = actor + 0x18;
    stepBase = stepBase + stepOffset2;
    command = *stepBase;
    _call_via_r1(arg0, *(void **)((u8 *)*(u32 *)(actor + 0x14) + (u32)command * 4));
    *(u16 *)(actor + 0x22) = *(u16 *)(actor + 0x22) - 1;
}
