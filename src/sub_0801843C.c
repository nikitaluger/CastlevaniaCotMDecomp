extern u16 getSpriteFacingSign(s32);
extern void *spawnBudgetedEffect(void *, s32);

/* Three parallel 5-entry u16 arrays in the entity's data block: x at +0, y at
 * +10, direction at +20. Advancing the pointer by 2 fills one column of all
 * three arrays per iteration. */
struct Fill {
  u16 x;
  u8 pad1[8];
  u16 y;
  u8 pad2[8];
  u16 direction;
};
/* Fixed-point position of a child object plus its direction word. */
struct ObjFields {
  u8 pad0[0x4C];
  s16 x;
  u8 pad1[6];
  s16 y;
  u8 pad2[6];
  u16 direction;
};

/* Fills the entity's direction tables and creates one or two child objects at
 * the entity's 16.16 fixed-point coordinates. */
void sub_0801843C(u8 *self)
{
  u8 *base;
  s32 param = *((s32 *) (self + 0x38));
  u16 dir;
  s32 i;
  struct Fill *p;
  s32 new_var;
  u8 *obj;
  u8 *obj2;
  s32 x;
  s32 y;
  int new_var2;
  s32 t;
  base = *((u8 **) (self + 0x3C));
  dir = getSpriteFacingSign(param);
  p = (struct Fill *) (base + 0xA8);
  i = 4;
  do
  {
    p->x = *((s32 *) (base + 8));
    p->y = *((s32 *) (base + 0xC));
    p->direction = dir;
    p = (struct Fill *) (((u8 *) p) + 2);
    i--;
  }
  while (i >= 0);
  obj = spawnBudgetedEffect(self, 0x87);
  if (obj != 0)
  {
    x = *((s32 *) (base + 8));
    if (x < 0)
    {
      x += 0xFFFF;
    }
    t = x >> 16;
    ((struct ObjFields *) obj)->x = t;
    new_var = *((s32 *) (base + 0xC));
    y = new_var;
    if (y < 0)
    {
      y += 0xFFFF;
    }
    t = y;
    ;
    ((struct ObjFields *) obj)->y = t >> 16;
    ((struct ObjFields *) obj)->direction = dir;
    obj2 = spawnBudgetedEffect(obj, 0x87);
    if (obj2 != 0)
    {
      new_var2 = 16;
      x = *((s32 *) (base + 8));
      if (x < 0)
      {
        x += 0xFFFF;
      }
      ;
      ((struct ObjFields *) obj2)->x = x >> new_var2;
      y = *((s32 *) (base + 0xC));
      if (y < 0)
      {
        y += 0xFFFF;
      }
      ;
      ((struct ObjFields *) obj2)->y = y >> 16;
      ((struct ObjFields *) obj2)->direction = dir;
    }
  }
}
