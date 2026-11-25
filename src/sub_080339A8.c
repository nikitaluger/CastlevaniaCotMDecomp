extern u32 D_0866DCFC[];
/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08032E88(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DCFC;
    *(u16 *)(entity + 0x22) += 1;

    depth = *(s16 *)(entity + 0x22);
    *(u8 *)(entity + 0x19 + depth * 2) += 1;

    depth = *(s16 *)(entity + 0x22);
    {
        s32 stepOffset = depth * 2;
        u8 *stepAddr = entity;
        stepAddr += 0x18;
        stepAddr = stepAddr + stepOffset;
        step = *stepAddr;
    }

    ((void (**)(void *))*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern u32 D_0866DD20[];
/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_080334D0(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DD20;
    *(u16 *)(entity + 0x22) += 1;

    depth = *(s16 *)(entity + 0x22);
    *(u8 *)(entity + 0x19 + depth * 2) += 1;

    depth = *(s16 *)(entity + 0x22);
    {
        s32 stepOffset = depth * 2;
        u8 *stepAddr = entity;
        stepAddr += 0x18;
        stepAddr = stepAddr + stepOffset;
        step = *stepAddr;
    }

    ((void (**)(void *))*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern u32 D_0866DD30[];
/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_080339A8(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DD30;
    *(u16 *)(entity + 0x22) += 1;

    depth = *(s16 *)(entity + 0x22);
    *(u8 *)(entity + 0x19 + depth * 2) += 1;

    depth = *(s16 *)(entity + 0x22);
    {
        s32 stepOffset = depth * 2;
        u8 *stepAddr = entity;
        stepAddr += 0x18;
        stepAddr = stepAddr + stepOffset;
        step = *stepAddr;
    }

    ((void (**)(void *))*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern u32 D_0866DD58[];
/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08034478(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DD58;
    *(u16 *)(entity + 0x22) += 1;

    depth = *(s16 *)(entity + 0x22);
    *(u8 *)(entity + 0x19 + depth * 2) += 1;

    depth = *(s16 *)(entity + 0x22);
    {
        s32 stepOffset = depth * 2;
        u8 *stepAddr = entity;
        stepAddr += 0x18;
        stepAddr = stepAddr + stepOffset;
        step = *stepAddr;
    }

    ((void (**)(void *))*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}
