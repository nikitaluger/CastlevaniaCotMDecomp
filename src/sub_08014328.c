struct SpriteState
{
  u8 flags0;
  u8 flags1;
};
struct Motion
{
  u16 flags;
  u8 pad2[0x1A];
  s16 timer;
  s16 age;
  u8 pad20[8];
  struct SpriteState *sprite;
};
struct S_02025FF0
{
  u8 _0[0x1870];
  void *currentEntity;
  u8 _1[0x189C - 0x1874];
  u32 globalFlags;
};
extern struct S_02025FF0 D_02025FF0;
s32 sub_08014090(s16);
void sub_08013FAC(struct Motion *);
void sub_08014060(struct Motion *);

/* Applies a motion state's sprite-attribute overrides and advances its timer,
 * then folds the state's mode bits into the motion flags. */
s32 sub_08014328(void *entity, u16 *attrFlags, struct Motion *motion)
{
  struct Motion *p = *((struct Motion **) (((u8 *) entity) + 0x3C));
  if (entity == D_02025FF0.currentEntity)
  {
    return 0;
  }
  {
    u16 flags;
    if (p->flags & 0xC)
    {
      if (p->flags & 4)
      {
        if ((p->age > 0x3C) || (!(D_02025FF0.globalFlags & 2)))
        {
          *attrFlags = ((*attrFlags) & 0x0FFF) | 0xD000;
        }
      }
      else
        if ((p->age > 0x3C) || (!(D_02025FF0.globalFlags & 2)))
      {
        *attrFlags = ((*attrFlags) & 0x0FFF) | 0xC000;
      }
      if (motion->sprite != NULL)
      {
        motion->sprite->flags1 &= 0xFE;
      }
    }
 do { do { if (!(p->flags & 1)) { if (sub_08014090(p->timer) == 1) { goto final; } if (!(p->flags & 0xC)) { return 0; } if (p->flags & 4) { sub_08013FAC(motion); } else { sub_08014060(motion); } final: { int x = motion->flags & 0xFFF3; motion->flags = x; motion->flags = (p->flags & 0xC) | x; } return 1; } } while (0); } while (0);
  }
  return 0;
}
