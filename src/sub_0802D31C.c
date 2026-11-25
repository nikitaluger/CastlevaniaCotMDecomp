extern u32 D_0866DB7C[];

/* Dispatch the entity's current script command: step the command cursor past
   its slot, run that command's handler, then step the cursor back. */
void sub_0802D31C(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866DB7C;
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
