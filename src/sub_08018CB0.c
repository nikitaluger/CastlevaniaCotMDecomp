void *sub_0805FB24(u32, s32);

struct S_02025FF0_1870
{
    u8 _[0x1870];
    u32 v;
};
extern struct S_02025FF0_1870 D_02025FF0;

inline s16 toS16(s32 value)
{
    return (s16)value;
}

/* Spawn an 0x88-byte object at the given 16.16 fixed-point x/y position and
 * record its parent at +0x8C. Returns NULL if allocation fails. */
void *sub_08018CB0(void *parent, s32 x, s32 y)
{
    u32 parentPtr = (u32)parent;
    s32 sx = x;
    s32 sy = y;
    void *obj = sub_0805FB24(D_02025FF0.v, 0x88);

    if (obj == 0)
    {
        return 0;
    }
    {
        s32 px = sx;
        if (px < 0)
        {
            px += 0xFFFF;
        }
        px >>= 16;
        *((s16 *)(((u8 *)obj) + 0x4C)) = (s16)px;
    }
    {
        s32 py = sy;
        if (py < 0)
        {
            py += 0xFFFF;
        }
        py >>= 16;
        *((s16 *)(((u8 *)obj) + 0x54)) = toS16(py);
    }
    *((s16 *)(((u8 *)obj) + 0x5C)) = 0;
    *((u32 *)(((u8 *)obj) + 0x8C)) = parentPtr;
    return obj;
}
