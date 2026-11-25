extern u32 D_0866DFB0[];
extern u32 D_0866DFB8[];
extern u32 D_0866DFDC[];
extern u32 D_0866DFE8[];

/* Enter one command step of an entity's command script: install the
   script's jump table, descend one nesting level, bump the repeat counter
   of the current command slot, then call the handler named by that slot. */
void sub_0803C7D0(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866DFB0;
    *(u16 *)(e + 0x22) += 1;

    level = *(s16 *)(e + 0x22);
    *(u8 *)(e + 0x19 + level * 2) += 1;

    level = *(s16 *)(e + 0x22);
    {
        s32 off = level * 2;
        u8 *slot = e;
        slot += 0x18;
        slot = slot + off;
        cmd = *slot;
    }

    ((void (**)(void *))*(u32 *)(e + 0x14))[cmd](entity);

    *(u16 *)(e + 0x22) -= 1;
}

void sub_0803C9DC(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866DFB8;
    *(u16 *)(e + 0x22) += 1;

    level = *(s16 *)(e + 0x22);
    *(u8 *)(e + 0x19 + level * 2) += 1;

    level = *(s16 *)(e + 0x22);
    {
        s32 off = level * 2;
        u8 *slot = e;
        slot += 0x18;
        slot = slot + off;
        cmd = *slot;
    }

    ((void (**)(void *))*(u32 *)(e + 0x14))[cmd](entity);

    *(u16 *)(e + 0x22) -= 1;
}

void sub_0803D040(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866DFDC;
    *(u16 *)(e + 0x22) += 1;

    level = *(s16 *)(e + 0x22);
    *(u8 *)(e + 0x19 + level * 2) += 1;

    level = *(s16 *)(e + 0x22);
    {
        s32 off = level * 2;
        u8 *slot = e;
        slot += 0x18;
        slot = slot + off;
        cmd = *slot;
    }

    ((void (**)(void *))*(u32 *)(e + 0x14))[cmd](entity);

    *(u16 *)(e + 0x22) -= 1;
}

void sub_0803D280(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866DFE8;
    *(u16 *)(e + 0x22) += 1;

    level = *(s16 *)(e + 0x22);
    *(u8 *)(e + 0x19 + level * 2) += 1;

    level = *(s16 *)(e + 0x22);
    {
        s32 off = level * 2;
        u8 *slot = e;
        slot += 0x18;
        slot = slot + off;
        cmd = *slot;
    }

    ((void (**)(void *))*(u32 *)(e + 0x14))[cmd](entity);

    *(u16 *)(e + 0x22) -= 1;
}
