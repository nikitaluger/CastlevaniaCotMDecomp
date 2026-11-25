extern u32 D_0866DB60[];

/* Dispatch the entity's current script command: step the command cursor past
   its slot, run that command's handler, then step the cursor back. */
void sub_0802CC50(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866DB60;
    *(u16 *)(self + 0x22) += 1;

    commandIndex = *(s16 *)(self + 0x22);
    *(u8 *)(self + 0x19 + commandIndex * 2) += 1;

    commandIndex = *(s16 *)(self + 0x22);
    {
        s32 offset = commandIndex * 2;
        u8 *commands = self;
        commands += 0x18;
        commands = commands + offset;
        opcode = *commands;
    }

    ((void (**)(void *))*(u32 *)(self + 0x14))[opcode](a);

    *(u16 *)(self + 0x22) -= 1;
}

extern u32 D_0866DBD8[];

/* Same command dispatch, with this entity's command-handler table. */
void sub_0802EBD0(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866DBD8;
    *(u16 *)(self + 0x22) += 1;

    commandIndex = *(s16 *)(self + 0x22);
    *(u8 *)(self + 0x19 + commandIndex * 2) += 1;

    commandIndex = *(s16 *)(self + 0x22);
    {
        s32 offset = commandIndex * 2;
        u8 *commands = self;
        commands += 0x18;
        commands = commands + offset;
        opcode = *commands;
    }

    ((void (**)(void *))*(u32 *)(self + 0x14))[opcode](a);

    *(u16 *)(self + 0x22) -= 1;
}

extern u32 D_0866DBE0[];

/* Same command dispatch, with this entity's command-handler table. */
void sub_0802EE4C(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866DBE0;
    *(u16 *)(self + 0x22) += 1;

    commandIndex = *(s16 *)(self + 0x22);
    *(u8 *)(self + 0x19 + commandIndex * 2) += 1;

    commandIndex = *(s16 *)(self + 0x22);
    {
        s32 offset = commandIndex * 2;
        u8 *commands = self;
        commands += 0x18;
        commands = commands + offset;
        opcode = *commands;
    }

    ((void (**)(void *))*(u32 *)(self + 0x14))[opcode](a);

    *(u16 *)(self + 0x22) -= 1;
}

extern u32 D_0866DBF4[];

/* Same command dispatch, with this entity's command-handler table. */
void sub_0802F3C4(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866DBF4;
    *(u16 *)(self + 0x22) += 1;

    commandIndex = *(s16 *)(self + 0x22);
    *(u8 *)(self + 0x19 + commandIndex * 2) += 1;

    commandIndex = *(s16 *)(self + 0x22);
    {
        s32 offset = commandIndex * 2;
        u8 *commands = self;
        commands += 0x18;
        commands = commands + offset;
        opcode = *commands;
    }

    ((void (**)(void *))*(u32 *)(self + 0x14))[opcode](a);

    *(u16 *)(self + 0x22) -= 1;
}
