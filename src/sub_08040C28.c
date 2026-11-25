extern u32 D_0866E108[]; /* command handler table */
extern u32 D_0866E134[];
extern u32 D_0866E144[];
extern u32 D_0866E154[];

/* Enter one command step of an entity's command script: install the
   script's jump table, descend one nesting level, bump the repeat counter
   of the current command slot, then call the handler named by that slot. */
void sub_08040C28(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E108;
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

void sub_0804163C(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E134;
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

void sub_080416DC(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E144;
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

void sub_08041780(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E154;
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
