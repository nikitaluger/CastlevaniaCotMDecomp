extern u32 D_0866E0A0[]; /* command handler table */
extern u32 D_0866E0CC[];
extern u32 D_0866E0E4[];
extern u32 D_0866E0FC[];

/* Enter one command step of an entity's command script: install the
   script's jump table, descend one nesting level, bump the repeat counter
   of the current command slot, then call the handler named by that slot. */
void sub_0803F890(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E0A0;
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

void sub_08040024(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E0CC;
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

void sub_0804047C(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E0E4;
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

void sub_08040B88(void *entity)
{
    u8 *e = (u8 *)entity;
    s16 level;
    u8 cmd;

    *(u32 *)(e + 0x14) = (u32)D_0866E0FC;
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
