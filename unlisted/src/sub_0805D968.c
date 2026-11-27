struct S_02025FF0 { u32 *ptr; u8 pad[0x1C]; };
extern struct S_02025FF0 gMainWorkspace[];

void *sub_0805FAEC(s32, s32);

/* Spawn a small effect object (kind 0x1E3) from the shared effect pool and
 * store its position and parameter block (x, y, type) at obj+0x4C. */
void *sub_0805D968(s32 x, s32 y, u16 type)
{
    void *obj = sub_0805FAEC((s32)gMainWorkspace[0xC4].ptr, 0x1E3);
    if (obj == NULL)
        return NULL;
    {
        u8 *params = (u8 *)obj + 0x4C;
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)(params + 4) = y;
        *(u16 *)(params + 8) = type;
    }
    return obj;
}
