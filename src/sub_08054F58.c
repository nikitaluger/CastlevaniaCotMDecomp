/* Script-step dispatchers: install the command handler table for one substate,
 * bump the current step counter, then run the handler the step's command byte
 * selects before restoring the step pointer. */
extern u32 D_0866E718[];
extern u32 D_0866E720[];
extern u32 D_0866E728[];
extern u32 D_0866E768[];

void sub_08054C4C(void *obj)
{
    u8 *r4 = (u8 *)obj;
    s16 slot;
    u8 command;

    *(u32 *)(r4 + 0x14) = (u32)D_0866E718;
    *(u16 *)(r4 + 0x22) += 1;

    slot = *(s16 *)(r4 + 0x22);
    *(u8 *)(r4 + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(r4 + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = r4;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }

    ((void (**)(void *))*(u32 *)(r4 + 0x14))[command](obj);

    *(u16 *)(r4 + 0x22) -= 1;
}

void sub_08054F10(void *obj)
{
    u8 *r4 = (u8 *)obj;
    s16 slot;
    u8 command;

    *(u32 *)(r4 + 0x14) = (u32)D_0866E720;
    *(u16 *)(r4 + 0x22) += 1;

    slot = *(s16 *)(r4 + 0x22);
    *(u8 *)(r4 + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(r4 + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = r4;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }

    ((void (**)(void *))*(u32 *)(r4 + 0x14))[command](obj);

    *(u16 *)(r4 + 0x22) -= 1;
}

void sub_08054F58(void *obj)
{
    u8 *r4 = (u8 *)obj;
    s16 slot;
    u8 command;

    *(u32 *)(r4 + 0x14) = (u32)D_0866E728;
    *(u16 *)(r4 + 0x22) += 1;

    slot = *(s16 *)(r4 + 0x22);
    *(u8 *)(r4 + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(r4 + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = r4;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }

    ((void (**)(void *))*(u32 *)(r4 + 0x14))[command](obj);

    *(u16 *)(r4 + 0x22) -= 1;
}

void sub_080559C4(void *obj)
{
    u8 *r4 = (u8 *)obj;
    s16 slot;
    u8 command;

    *(u32 *)(r4 + 0x14) = (u32)D_0866E768;
    *(u16 *)(r4 + 0x22) += 1;

    slot = *(s16 *)(r4 + 0x22);
    *(u8 *)(r4 + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(r4 + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = r4;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }

    ((void (**)(void *))*(u32 *)(r4 + 0x14))[command](obj);

    *(u16 *)(r4 + 0x22) -= 1;
}
