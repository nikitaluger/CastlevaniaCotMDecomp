extern u32 D_0866DDD4[]; /* command handler table */
extern u32 D_0866DDF4[];
extern u32 D_0866E078[];
extern u32 D_0866E090[];

/* Enter one command step of an entity's command script: install the
   script's jump table, descend one nesting level, bump the repeat counter
   of the current command slot, then call the handler named by that slot. */
void sub_08035EC0(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866DDD4;
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

void sub_08036534(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866DDF4;
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

void sub_0803F270(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E078;
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

void sub_0803F7F0(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E090;
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
