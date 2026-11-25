extern u32 D_0866D9B4[];
void sub_08026CF0(void *a)
{
    u8 *r4 = (u8 *)a;
    s16 idx;
    u8 b;

    *(u32 *)(r4 + 0x14) = (u32)D_0866D9B4;
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

extern u32 D_0866D9F0[];
void sub_08027D6C(void *a)
{
    u8 *r4 = (u8 *)a;
    s16 idx;
    u8 b;

    *(u32 *)(r4 + 0x14) = (u32)D_0866D9F0;
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
extern u32 D_0866D9F8[];
void sub_08027DB4(void *entity)
{
    u8 *data = (u8 *)entity;
    s16 slot;
    u8 cmdId;

    *(u32 *)(data + 0x14) = (u32)D_0866D9F8;
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

extern u32 D_0866DA1C[];
void sub_0802853C(void *a)
{
    u8 *r4 = (u8 *)a;
    s16 idx;
    u8 b;

    *(u32 *)(r4 + 0x14) = (u32)D_0866DA1C;
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
