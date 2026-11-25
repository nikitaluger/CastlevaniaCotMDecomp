struct Comp
{
  u8 _0[8];
  s32 x;
  s32 y;
  s32 _10;
  s32 _14;
  u8 _18[4];
  s16 id;
  u8 _1E[4];
  s16 rotation;
};
struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x10];
  void (*update)(void *);
  u8 _18[0xA];
  s16 state;
  u8 _24[0x38 - 0x24];
  u8 *obj;
  struct Comp *comp;
  u8 _40[0xC];
  s16 spawnX;
  u8 _4E[6];
  s16 spawnY;
  u8 _56[6];
  u16 spriteId;
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 layer;
  u8 _18A9[0x19];
  u16 spriteFlags;
};
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90
{
  u8 _0[0x1278];
  u32 f1278;
  u32 f127C;
};
extern struct S_02021E90 D_02021E90;
extern u8 D_080CD400[];
extern u8 *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_080C31E0(u8 *, s32);
extern void sub_08028B14(void *);

/* Spawn a projectile entity: allocate the object, seed its position and sprite
 * from the spawner, then install sub_08028B14 as its update callback. */
void sub_080289CC(struct Entity *self)
{
  u8 *obj;
  struct Comp *comp;
  u8 *body;
  u8 *coordBase;
  u16 *oamAttr;
  obj = sub_0800355C();
  if (obj == NULL)
  {
    sub_080C31E0((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  self->obj = obj;
  sub_0800168C((u8 *) self, 0, 0x48, 0);
  comp = self->comp;
  if (comp == NULL)
  {
    sub_080C31E0((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  body = ((u8 *) comp) + 0x34;
  comp->id = self->spriteId;
  comp->x = self->spawnX << 16;
  comp->y = self->spawnY << 16;
  comp->rotation = sub_08013C2C((s32) comp->id);
  if (comp->rotation < 0)
  {
    sub_080C31E0((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  oamAttr = (u16 *) obj;
  sub_0801131C(obj, body, ((s32) D_080CD400) + (comp->id * 0xC));

  {
    u16 shape = 0xC00 & (*((u16 *) obj));
    s32 scale = ((s16) (*((s16 *) (((u8 *) comp) + 0x22)))) << 6;
    scale += 0x200;
    scale |= (((u16) (*((u16 *) (((u8 *) comp) + 0x22)))) + 8) << 12;
    *oamAttr = (u16) (shape | scale);
  }
  *oamAttr = (u16) ((*oamAttr) | D_02025FF0.spriteFlags);
  *((u32 *) (obj + 0x1C)) = 0x8000000A;
  coordBase = (u8 *) (&D_02021E90);
  {
    u32 k = 0x1278;
    *((u32 *) (obj + 0x14)) = comp->x - (((*((u32 *) ((coordBase + k) + ((D_02025FF0.layer + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (obj + 0x18)) = comp->y - (((*((u32 *) ((coordBase + k) + ((D_02025FF0.layer + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  sub_08011368(obj, body, 9, 0);
  self->flags |= 0x1000;
  self->flags |= 0x800;
  self->state = 0;
  self->update = sub_08028B14;
}
