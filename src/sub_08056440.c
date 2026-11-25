/* Script-step dispatchers: install the command handler table for one substate,
 * bump the current step counter, then run the handler the step's command byte
 * selects before restoring the step pointer. */
extern u32 D_0866E774[];
void sub_08055D4C(void *obj)
{
    u8 *r4 = (u8 *)obj;
    s16 slot;
    u8 command;

    *(u32 *)(r4 + 0x14) = (u32)D_0866E774;
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

extern u32 D_0866E794[];
void sub_08056384(void *obj)
{
    u8 *r4 = (u8 *)obj;
    s16 slot;
    u8 command;

    *(u32 *)(r4 + 0x14) = (u32)D_0866E794;
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

extern u32 D_0866E7A0[];
void sub_08056440(void *obj)
{
    u8 *r4 = (u8 *)obj;
    s16 slot;
    u8 command;

    *(u32 *)(r4 + 0x14) = (u32)D_0866E7A0;
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

extern u32 D_0866E7AC[];
void sub_080564FC(void *obj)
{
    u8 *r4 = (u8 *)obj;
    s16 slot;
    u8 command;

    *(u32 *)(r4 + 0x14) = (u32)D_0866E7AC;
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
