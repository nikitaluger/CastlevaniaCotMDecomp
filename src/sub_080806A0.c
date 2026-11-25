extern s32 sub_0806D450(void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_0806D330(void *, void *);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_080C31E0(void *, void *);
struct S_02025FF0
{
  u8 _pad0[0x10];
  s32 unk10;
  u8 _pad1[0x14ED - 0x14];
  u8 unk14ED;
  u8 _pad2[0x173A - 0x14EE];
  u8 unk173A;
  u8 _pad3[0x18A8 - 0x173B];
  u8 unk18A8;
  u8 _pad4[0x18C2 - 0x18A9];
  u16 unk18C2;
};
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02021E90[];
inline s32 *inline_fn(u8 *base, int offset, u32 index)
{
  return (s32 *) ((base + offset) + index);
}

/* Updates an effect/projectile entity: advances its position by its velocity,
 * spawns a secondary effect from the coordinate tables when the target flag is
 * set, and releases the owning object when global state says the effect is done. */
void sub_080806A0(u8 *owner)
{
    u8 *state;
    u8 *entity;
    state = (u8 *)(*((u8 **)(owner + 0x6C))) + 4;
    entity = *((u8 **)(owner + 0x38));
    if (sub_0806D450(owner, entity, state) > 0)
    {
        sub_080C31E0(owner, *((void **)(owner + 0x24)));
        return;
    }
    {
        s32 newX;
        s32 newY;
        newX = (*((s32 *)(entity + 0x14))) + (*((s32 *)(state + 0x08)));
        *((s32 *)(entity + 0x14)) = newX;
        newY = (*((s32 *)(entity + 0x18))) + (*((s32 *)(state + 0x0C)));
        *((s32 *)(entity + 0x18)) = newY;
        {
            u8 *target = *((u8 **)(state + 0x2C));
            if (((*((u16 *)(target + 0x14))) & 1) && (!((*((u16 *)(target + 0x14))) & 2)))
            {
                u8 *coordTable = D_02021E90;
                u8 *indexByte = (u8 *)(&D_02025FF0);
                u8 *xCoordTable;
                u32 coordOffset;
                indexByte += 0x18A8;
                coordOffset = (((u32)(*indexByte)) + 1) * 0x40;
                xCoordTable = coordTable + 0x1278;
                sub_0808DBF8(newX + (*((s32 *)(xCoordTable + coordOffset))), newY + (*inline_fn(coordTable, 0x127C, coordOffset)), 0);
                sub_080C31E0(owner, *((void **)(owner + 0x24)));
                return;
            }
        }
        *((u16 *)entity) = D_02025FF0.unk18C2;
        sub_08003740(state + 0x1C, entity);
        if ((D_02025FF0.unk173A == 0x1C) || ((D_02025FF0.unk14ED == 0) && (D_02025FF0.unk10 != 0)))
        {
            sub_080C31E0(owner, *((void **)(owner + 0x24)));
            return;
        }
        sub_0806D330(owner, entity);
    }
}
