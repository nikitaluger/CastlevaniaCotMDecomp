extern u32 D_0866D130[];
extern u32 D_0866D154[];
extern u32 D_0866D164[];
extern void sub_080C31E0(void *);

s32 sub_08001626(u16 *arg0, u32 arg1) {
    s32 v;
    s16 *pv;
    s32 mask;
    s32 r;
    v = arg1;
    mask = *arg0 & 0x3FFF;
    pv = (s16 *)&v;
    r = 0;
    if (pv[0] <= mask && mask <= pv[1]) r = 1;
    return r;
}

// Runs one step of an object's script: temporarily advances the step index at
// +0x22, bumps that step's counter at +0x19, dispatches the current command
// (the byte at +0x18) through the handler table at +0x14, then restores the index.
void sub_080104C0(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D130;
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

// Runs one script step using the D_0866D154 handler table.
void sub_08010508(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D154;
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

// Runs one script step using the D_0866D164 handler table.
void sub_08010648(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s16 step;
    u8 command;

    *(u32 *)(objBytes + 0x14) = (u32)D_0866D164;
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
