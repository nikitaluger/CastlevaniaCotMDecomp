extern u32 D_0866D8D8[];
extern u32 D_0866D8E0[];
extern u32 D_0866D8E8[];
extern void sub_080C31E0(void *);

void sub_08017AD6(void)
{
}

void sub_08023F98(void *a)
{
    u8 *r4 = (u8 *)a;
    s16 idx;
    u8 b;

    *(u32 *)(r4 + 0x14) = (u32)D_0866D8D8;
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

/* Runs one step of an entity's command script: install this script's handler
 * table at +0x14, advance the current slot (+0x22), bump that slot's counter
 * (low byte at +0x19), dispatch the slot's command (high byte at +0x18) through
 * the handler table, then restore the slot index. */
void sub_08023FE0(void *entity)
{
    u8 *data = (u8 *)entity;
    s16 slot;
    u8 cmdId;

    *(u32 *)(data + 0x14) = (u32)D_0866D8E0;
    *(u16 *)(data + 0x22) += 1;

    slot = *(s16 *)(data + 0x22);
    *(u8 *)(data + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(data + 0x22);
    {
        s32 off = slot * 2;
        u8 *cmdPtr = data;
        cmdPtr += 0x18;
        cmdPtr = cmdPtr + off;
        cmdId = *cmdPtr;
    }

    ((void (**)(void *))*(u32 *)(data + 0x14))[cmdId](entity);

    *(u16 *)(data + 0x22) -= 1;
}

void sub_08024028(void *a)
{
    u8 *r4 = (u8 *)a;
    s16 idx;
    u8 b;

    *(u32 *)(r4 + 0x14) = (u32)D_0866D8E8;
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
