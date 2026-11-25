extern u32 D_0866DC3C[];
/* Runs one step of an entity's command script: installs the given script step
 * table, enters the current step (bumps the script depth and that step's repeat
 * counter), calls the step's handler, then leaves the step again. */
void sub_08030830(void *a)
{
    u8 *entity = (u8 *)a;
    s16 depth;
    u8 step;

    *(u32 *)(entity + 0x14) = (u32)D_0866DC3C;
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
