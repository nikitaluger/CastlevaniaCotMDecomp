extern u32 D_0866D0DC[];
extern u32 D_0866D0E0[];
extern u32 D_0866D0F0[];
extern u32 D_0866D0F8[];
extern void sub_080C31E0(void *);

// Runs one step of an object's script: temporarily advances the step index at
// +0x22, bumps that step's counter at +0x19, dispatches the current command
// (the byte at +0x18) through the handler table at +0x14, then restores the index.
void sub_0800D348(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D0DC;
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

// Runs one script step using the D_0866D0E0 handler table.
void sub_0800D60C(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D0E0;
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

// Runs one script step using the D_0866D0F0 handler table.
void sub_0800E06C(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D0F0;
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

// Runs one script step using the D_0866D0F8 handler table.
void sub_0800E384(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D0F8;
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
