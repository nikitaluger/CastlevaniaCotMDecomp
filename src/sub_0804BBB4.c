extern void *sub_0805FAEC(s32, s32);

/* The spawn-object free-list pointer sits at the end of the game-state block. */
struct GameState { u8 _pad[0x1870]; u32 spawnPool; };
extern struct GameState gMainWorkspace;

/* Spawn one type-0x135 effect/entity object from the shared pool at a 16.16
 * fixed-point position, converting it to whole pixels and storing its two
 * setup parameters. */
void *sub_0804BBB4(s32 xFixed, s32 yFixed, u16 param5C, u16 param6C)
{
    u8 *obj;
    s32 xScaled, y;
    s32 pixelX;
    u8 *p;
    obj = (u8 *)sub_0805FAEC(gMainWorkspace.spawnPool, 0x135);
    if (obj == 0) return 0;
    xScaled = xFixed;
    if (xScaled < 0) xScaled += 0xFFFF;
    pixelX = xScaled >> 16;
    *(s16 *)(obj + 0x4C) = pixelX;
    y = yFixed;
    if (y < 0) y += 0xFFFF;
    y = y >> 16;
    p = obj + 0x54;
    *(s16 *)p = y;
    p += 8;
    *(u16 *)p = param5C;
    p += 0x10;
    *(u16 *)p = param6C;
    return obj;
}
