typedef void (*StepFunc)(void *);

extern StepFunc D_0866DB58[];
/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth, bumps that step's
 * repeat counter), calls the step's handler, then leaves the step again. */
void sub_0802CC08(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DB58;
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

    ((StepFunc *)*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern StepFunc D_0866DB7C[];
void sub_0802D31C(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DB7C;
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

    ((StepFunc *)*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern StepFunc D_0866DB88[];
void sub_0802D758(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DB88;
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

    ((StepFunc *)*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern StepFunc D_0866DB90[];
void sub_0802D7A0(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DB90;
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

    ((StepFunc *)*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern StepFunc D_0866DBAC[];
void sub_0802DEDC(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DBAC;
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

    ((StepFunc *)*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern StepFunc D_0866DBB8[];
void sub_0802E234(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DBB8;
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

    ((StepFunc *)*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}

extern StepFunc D_0866DBD0[];
void sub_0802E91C(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DBD0;
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

    ((StepFunc *)*(u32 *)(entity + 0x14))[step](a);

    *(u16 *)(entity + 0x22) -= 1;
}
