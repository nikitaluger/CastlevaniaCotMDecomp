extern u32 D_0866CEA8[];
extern u32 D_0866CEB8[];
extern u32 D_0866CEC4[];
extern u32 D_0866D1A4[];
extern void sub_080C31E0(void *);

void sub_0800ADC4(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866CEA8;
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

void sub_0800B240(void *a)
{
    u8 *r4 = (u8 *)a;
    s16 idx;
    u8 b;

    *(u32 *)(r4 + 0x14) = (u32)D_0866CEB8;
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

void sub_0800BFFC(void *a)
{
    u8 *self = (u8 *)a;
    s16 commandIndex;
    u8 opcode;

    *(u32 *)(self + 0x14) = (u32)D_0866CEC4;
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

void sub_08010B2C(void *a)
{
    u8 *r4 = (u8 *)a;
    s16 idx;
    u8 b;

    *(u32 *)(r4 + 0x14) = (u32)D_0866D1A4;
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
