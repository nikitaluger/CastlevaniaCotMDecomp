/* Spawn a 0x8F-byte object at the given 16.16 fixed-point x/y position, record
 * its parent at +0x8C, and return it (NULL if the object pool is exhausted). */
void *sub_0805FB24(s32, s32);
struct S_02025FF0 { u8 _0x000[0x1870]; u32 pool; };
extern struct S_02025FF0 gMainWorkspace;

void *sub_0801C454(s32 parent, s32 xFixed, s32 yFixed) {
    void *obj = sub_0805FB24(gMainWorkspace.pool, 0x8F);
    s32 worldX, worldY;
    if (obj == NULL) return NULL;
    worldX = xFixed / 0x10000;
    *(s16 *)((u8 *)obj + 0x4C) = worldX;
    worldY = yFixed / 0x10000;
    *(s16 *)((u8 *)obj + 0x54) = worldY;
    *(s16 *)((u8 *)obj + 0x5C) = 0;
    *(u32 *)((u8 *)obj + 0x8C) = parent;
    return obj;
}
