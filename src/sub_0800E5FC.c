extern u32 D_0866CED8[];
extern u32 D_0866D0FC[];
extern u32 D_0866D104[];
extern u32 D_0866D108[];

// Runs one step of an object's script: temporarily advances the step index at
// +0x22, bumps that step's counter at +0x19, dispatches the current command
// (the byte at +0x18) through the handler table at +0x14, then restores the index.
void sub_0800C3BC(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866CED8;
    *(u16 *)(objBytes + 0x22) += 1;

    step = *(s16 *)(objBytes + 0x22);
    *(u8 *)(objBytes + 0x19 + step * 2) += 1;

    step = *(s16 *)(objBytes + 0x22);
    {
        s32 stepOffset = step * 2;
        u8 *commandPtr = objBytes;
        commandPtr += 0x18;
        commandPtr = commandPtr + stepOffset;
        command = *commandPtr;
    }

    ((void (**)(void *))*(u32 *)(objBytes + 0x14))[command](obj);

    *(u16 *)(objBytes + 0x22) -= 1;
}

// Runs one script step using the D_0866D0FC handler table.
void sub_0800E5FC(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D0FC;
    *(u16 *)(objBytes + 0x22) += 1;

    step = *(s16 *)(objBytes + 0x22);
    *(u8 *)(objBytes + 0x19 + step * 2) += 1;

    step = *(s16 *)(objBytes + 0x22);
    {
        s32 stepOffset = step * 2;
        u8 *commandPtr = objBytes;
        commandPtr += 0x18;
        commandPtr = commandPtr + stepOffset;
        command = *commandPtr;
    }

    ((void (**)(void *))*(u32 *)(objBytes + 0x14))[command](obj);

    *(u16 *)(objBytes + 0x22) -= 1;
}

// Runs one script step using the D_0866D104 handler table.
void sub_0800E924(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D104;
    *(u16 *)(objBytes + 0x22) += 1;

    step = *(s16 *)(objBytes + 0x22);
    *(u8 *)(objBytes + 0x19 + step * 2) += 1;

    step = *(s16 *)(objBytes + 0x22);
    {
        s32 stepOffset = step * 2;
        u8 *commandPtr = objBytes;
        commandPtr += 0x18;
        commandPtr = commandPtr + stepOffset;
        command = *commandPtr;
    }

    ((void (**)(void *))*(u32 *)(objBytes + 0x14))[command](obj);

    *(u16 *)(objBytes + 0x22) -= 1;
}

// Runs one script step using the D_0866D108 handler table.
void sub_0800F784(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D108;
    *(u16 *)(objBytes + 0x22) += 1;

    step = *(s16 *)(objBytes + 0x22);
    *(u8 *)(objBytes + 0x19 + step * 2) += 1;

    step = *(s16 *)(objBytes + 0x22);
    {
        s32 stepOffset = step * 2;
        u8 *commandPtr = objBytes;
        commandPtr += 0x18;
        commandPtr = commandPtr + stepOffset;
        command = *commandPtr;
    }

    ((void (**)(void *))*(u32 *)(objBytes + 0x14))[command](obj);

    *(u16 *)(objBytes + 0x22) -= 1;
}
