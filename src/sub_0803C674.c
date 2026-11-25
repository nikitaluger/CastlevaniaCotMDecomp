extern void sub_0803C5F4(u32 count, u16 *spriteAttrs, u8 paramX, u8 paramY, s32 x, s32 y, s32 arg6, s32 arg7);

struct SpawnOffset {
    s32 dx;
    s32 dy;
    s32 param0;
    s32 param1;
};
struct SpawnParam {
    u8 x;
    u8 y;
};

extern struct SpawnOffset D_080CF340[];
extern struct SpawnParam D_080CF3A0[];

/* Spawn a pair of effect objects at a table-defined offset from the source,
 * mirroring the x offset when the sprite is flipped, and note the source's
 * current state on the emitter. */
void sub_0803C674(u16 *spriteAttrs, void *source, void *emitter)
{
    struct SpawnOffset *offset;
    s32 dx;

    if (spriteAttrs[1] & 0x10) {
        dx = -D_080CF340[*(u8 *)((u8 *)emitter + 4)].dx;
        offset = D_080CF340;
    } else {
        dx = D_080CF340[*(u8 *)((u8 *)emitter + 4)].dx;
        offset = D_080CF340;
    }
    if (*(s32 *)((u8 *)source + 0x18) != (s32)*(s16 *)((u8 *)emitter + 0)) {
        u8 tableIndex;
        u8 paramX;
        u8 paramY;
        u8 *paramTable;

        tableIndex = *(u8 *)((u8 *)emitter + 4);
        paramTable = (u8 *)D_080CF3A0;
        paramX = paramTable[tableIndex * 2];
        paramTable = paramTable + 1;
        paramY = paramTable[tableIndex * 2];
        sub_0803C5F4(2, spriteAttrs, paramX, paramY,
            *(s32 *)((u8 *)source + 8) + dx,
            *(s32 *)((u8 *)source + 0xC) + D_080CF340[*(u8 *)((u8 *)emitter + 4)].dy,
            D_080CF340[*(u8 *)((u8 *)emitter + 4)].param0,
            D_080CF340[*(u8 *)((u8 *)emitter + 4)].param1);
        *(u16 *)((u8 *)emitter + 0) = (u16)*(s32 *)((u8 *)source + 0x18);
    }
}
