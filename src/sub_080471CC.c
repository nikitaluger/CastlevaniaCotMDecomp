extern u32 D_0866E2D0[];

/* Command-script step dispatcher: install the handler table at 0x0866E2D0,
 * tick the current command slot's counter, and call the handler registered for
 * that command. */
void sub_080464B8(void *a)
{
    u8 *obj = (u8 *)a;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866E2D0;
    *(u16 *)(obj + 0x22) += 1;

    slot = *(s16 *)(obj + 0x22);
    *(u8 *)(obj + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(obj + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = obj;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }

    ((void (**)(void *))*(u32 *)(obj + 0x14))[command](a);

    *(u16 *)(obj + 0x22) -= 1;
}

extern u32 D_0866E2DC[];

/* Command-script step dispatcher: install the handler table at 0x0866E2DC,
 * tick the current command slot's counter, and call the handler registered for
 * that command. */
void sub_08046A9C(void *a)
{
    u8 *obj = (u8 *)a;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866E2DC;
    *(u16 *)(obj + 0x22) += 1;

    slot = *(s16 *)(obj + 0x22);
    *(u8 *)(obj + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(obj + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = obj;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }

    ((void (**)(void *))*(u32 *)(obj + 0x14))[command](a);

    *(u16 *)(obj + 0x22) -= 1;
}

extern u32 D_0866E2E8[];

/* Command-script step dispatcher: install the handler table at 0x0866E2E8,
 * tick the current command slot's counter, and call the handler registered for
 * that command. */
void sub_08046D7C(void *a)
{
    u8 *obj = (u8 *)a;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866E2E8;
    *(u16 *)(obj + 0x22) += 1;

    slot = *(s16 *)(obj + 0x22);
    *(u8 *)(obj + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(obj + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = obj;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }

    ((void (**)(void *))*(u32 *)(obj + 0x14))[command](a);

    *(u16 *)(obj + 0x22) -= 1;
}

extern u32 D_0866E2F8[];

/* Command-script step dispatcher: install the handler table at 0x0866E2F8,
 * tick the current command slot's counter, and call the handler registered for
 * that command. */
void sub_080471CC(void *a)
{
    u8 *obj = (u8 *)a;
    s16 slot;
    u8 command;

    *(u32 *)(obj + 0x14) = (u32)D_0866E2F8;
    *(u16 *)(obj + 0x22) += 1;

    slot = *(s16 *)(obj + 0x22);
    *(u8 *)(obj + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(obj + 0x22);
    {
        s32 off = slot * 2;
        u8 *addr = obj;
        addr += 0x18;
        addr = addr + off;
        command = *addr;
    }

    ((void (**)(void *))*(u32 *)(obj + 0x14))[command](a);

    *(u16 *)(obj + 0x22) -= 1;
}
