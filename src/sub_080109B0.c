extern u32 D_0866D170[];
extern u32 D_0866D17C[];
extern u32 D_0866D188[];
extern u32 D_0866D194[];

/* Run the handler of the script command under the object's command pointer,
   counting the command first and restoring the pointer's position after. */
void sub_08010718(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866D170;
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

void sub_080107EC(void *a)
{
    u8 *r4 = (u8 *)a;
    s16 idx;
    u8 b;

    *(u32 *)(r4 + 0x14) = (u32)D_0866D17C;
    *(u16 *)(r4 + 0x22) += 1;

    idx = *(s16 *)(r4 + 0x22);
    *(u8 *)(r4 + 0x19 + idx * 2) += 1;

    idx = *(s16 *)(r4 + 0x22);
    {
        s32 off = idx * 2;
        u8 *addr = r4;
        addr += 0x18;
        addr = addr + off;
        b = *addr;
    }

    ((void (**)(void *))*(u32 *)(r4 + 0x14))[b](a);

    *(u16 *)(r4 + 0x22) -= 1;
}

/* Run the handler of the script command under the object's command pointer,
   counting the command first and restoring the pointer's position after. */
void sub_080108B4(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866D188;
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

/* Run the handler of the script command under the object's command pointer,
   counting the command first and restoring the pointer's position after. */
void sub_080109B0(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866D194;
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
