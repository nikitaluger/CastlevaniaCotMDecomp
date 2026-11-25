extern void sub_08005E80(s32);
extern void sub_080113A8(s32, void *);
extern void sub_0801165C(void *, s32);
extern s32 sub_08013B5C(s32, void *);
extern s32 sub_08016238(void *);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_08020498(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct StateFlags { u16 flags; };
struct LayerFlags { u8 _0; u8 flags; };
struct LayerTimer { u8 _0[0x14]; u16 flags; };
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

/* Updates an entity's sprite animation and action state, handles a finished
 * action, and refreshes the sprite's screen position from the coord table. */
void sub_0801FC98(u8 *entity)
{
  s32 sprite = *((s32 *) (entity + 0x38));
  u8 *state = *((u8 **) (entity + 0x3C));
  u8 *anim = state + 0x34;
  u8 *extra = state + 0x48;
  u8 *layer;
  layer = *((u8 **) (state + 0x28));
  ((struct LayerFlags *) layer)->flags |= 5;
  if (*((s32 *)extra) <= 0)
  {
    if (sub_0805F9B4(*((s32 *) (state + 8)), *((s32 *) (state + 0xC))) == 1)
    {
      sub_080C31E0(entity, *((void **) (entity + 0x24)));
      return;
    }
  }
  if (sub_08016238(*((void **) (state + 0x28))) != 0)
    ((struct StateFlags *) state)->flags |= 1;
  if ((1 & ((struct LayerTimer *) (*((u8 **) (state + 0x28))))->flags) || (*((u16 *) (entity + 0x5C)) & 2))
    ((struct StateFlags *) state)->flags |= 1;
  if (1 & (*((u16 *) state)))
  {
    s32 *lit;
    ((struct LayerFlags *) (*((u8 **) (state + 0x28))))->flags &= 0xFB;
    if ((*((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x1A))) != 2)
    {
      *((s32 *) (extra + 8)) = 5;
      if (*((u16 *) (entity + 0x5C)) & 2)
        *((s32 *) (extra + 8)) = 3;
      sub_08005E80(0x189);
      *((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x1B)) = 0;
      lit = (s32 *) 0x08671BDC;
      sub_080C31E8(entity + 0x18, entity + 0x22, 2, *lit);
    }
  }
  if (sub_08013B5C(sprite, state) == 0)
  {
    s32 index; u8 *bytes; u8 value; void **tbl; void *callback; u8 *child;
    *((void **) (entity + 0x14)) = (void *) 0x0866D7D0;
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) + 1);
    child = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    *((u8 *) (child + 0x19)) = (u8) ((*((u8 *) (child + 0x19))) + 1);
    index = (*((s16 *) (entity + 0x22))) * 2;
    bytes = entity + 0x18;
    value = *(bytes + index);
    tbl = *((void **) (entity + 0x14));
    callback = tbl[value];
    sub_080C31E0(entity, callback);
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) - 1);
    if (((*((u16 *) (entity + 2))) & 0x8000) == 0)
    {
      sub_080113A8(sprite, anim);
      sub_0801165C(state, 0);
    }
    else goto done;
  }
  sub_08020498(sprite, state);
  ((struct LayerTimer *) (*((u8 **) (state + 0x28))))->flags = 0;
  {
    u8 *coordBase = D_02021E90;
    u8 *layerBase = D_02025FF0;
    u8 *base1; u8 *base2; u32 idx;
    layerBase += 0x18A8;
    idx = ((u32)*layerBase + 1) * 0x40;
    base1 = coordBase + 0x1278;
    *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)state + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*layerBase + 1) * 0x40;
    base2 = coordBase + 0x127C;
    *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)state + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
  }
done:
  ;
}
