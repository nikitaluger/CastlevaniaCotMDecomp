extern u8 D_0866D550[];

void sub_080184E0(void *);
void sub_080C31E0(void *, void *);

/* Push a script level: install the handler table at D_0866D550, bump the
 * level index, increment that level's repeat counter, dispatch the level's
 * current opcode handler, then pop the level again. */
void sub_0801728C(void *arg0)
{
    u8 *obj = arg0;
    s16 level;

    *(u32 *)(obj + 0x14) = (u32)D_0866D550;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;

    level = *(s16 *)(obj + 0x22);
    *(u8 *)(obj + level * 2 + 0x19) = *(u8 *)(obj + level * 2 + 0x19) + 1;

    level = *(s16 *)(obj + 0x22);
    {
        s32 byteOfs = level * 2;
        u8 *levelBytes = obj + 0x18;
        sub_080C31E0(arg0, *(void **)((u8 *)*(void **)(obj + 0x14) + *(u8 *)(levelBytes + byteOfs) * 4));
    }

    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
    sub_080184E0(arg0);
}
