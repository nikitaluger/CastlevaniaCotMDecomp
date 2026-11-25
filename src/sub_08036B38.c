extern u32 D_0866DE14[];

/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08036B38(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DE14;
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

extern u32 D_0866DE38[];

/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08037178(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DE38;
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

extern u32 D_0866DE50[];

/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08037774(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DE50;
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

extern u32 D_0866DEB0[];

/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08038B48(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DEB0;
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

extern u32 D_0866DEC0[];

/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08038BE8(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DEC0;
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

extern u32 D_0866DEE4[];

/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08039214(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DEE4;
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
