extern u32 D_0866DD20[];

/* An entity's command-script state: the current step table and the stack of
 * nested command slots being executed.  Slots live at +0x18 (2 bytes each):
 * low byte = step index, high byte = call/repeat counter. */
struct EntityScript {
    u8 _0[0x14];
    u32 stepTable;      /* +0x14: table of step handlers */
    u8 _18[0xA];
    s16 depth;          /* +0x22: current slot index */
};

/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_080334D0(void *a)
{
    struct EntityScript *entity = (struct EntityScript *)a;
    s16 depth;
    u8 step;

    entity->stepTable = (u32)D_0866DD20;
    entity->depth += 1;

    depth = entity->depth;
    *(u8 *)((u8 *)entity + 0x19 + depth * 2) += 1;

    depth = entity->depth;
    {
        s32 stepOffset = depth * 2;
        u8 *stepAddr = (u8 *)entity;
        stepAddr += 0x18;
        stepAddr = stepAddr + stepOffset;
        step = *stepAddr;
    }

    ((void (**)(void *))entity->stepTable)[step](a);

    entity->depth -= 1;
}
