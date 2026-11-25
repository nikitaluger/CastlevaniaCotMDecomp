/* Spawns the sprite and sub-actor for one entity, seeds its fixed direction
 * (0x2F), sets up the initial animation and sprite attributes, then registers
 * its script after computing the camera-relative screen position. */
extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);
struct Actor
{
  u8 _0[8];
  s32 posX;
  s32 posY;
  s32 velX;
  s32 velY;
  u8 _18[4];
  s16 angle;
  u8 _1E[4];
  s16 dirIndex;
};
struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x22 - 4];
  s16 dirIndex;
  u8 _24[0x38 - 0x24];
  u8 *sprite;
  struct Actor *actor;
  u8 _40[0x4C - 0x40];
  s16 xPos;
  u8 _4E[6];
  s16 yPos;
  u8 _56[0x5C - 0x56];
  u16 variant;
  u8 _5E[0x6C - 0x5E];
  u32 extra;
};
struct CameraInfo
{
  u8 _0[0x18A8];
  u8 index;
  u8 _18A9[0x19];
  u16 spriteAttrMask;
};
extern struct CameraInfo D_02025FF0;
struct CoordTable
{
  u8 _0[0x1278];
  u32 camX;
  u32 camY;
};
extern struct CoordTable D_02021E90;
extern u8 D_080CD400[];
extern u32 D_08671BB0;
void sub_08059BF8(struct Entity *entity)
{
  u8 *sprite;
  struct Actor *actor;
  u8 *animState;
  s32 dirIndexResult;
  u32 spriteAttr;
  u8 *coordBase;
  s32 *scriptData;
  sprite = sub_0800355C();
  actor = NULL;
  animState = NULL;
  dirIndexResult = 0;
  if (((sprite == NULL) || ((entity->sprite = sprite, sub_0800168C((u8 *) entity, 0, 0x48, 0), actor = entity->actor, actor == NULL))) || ((animState = ((u8 *) actor) + 0x34, actor->angle = 0x2F, actor->posX = entity->xPos << 16, actor->posY = entity->yPos << 16, dirIndexResult = sub_08013C2C(0x2F), actor->dirIndex = dirIndexResult, ((s32) (dirIndexResult << 16)) < 0)))
  {
 do { _call_via_r1((u8 *) entity, *((s32 *) (((u8 *) entity) + 0x24))); } while (0);
    return;
  }
  sub_0801131C(sprite, animState, ((s32) D_080CD400) + (actor->angle * 0xC));
  sub_08011368(sprite, animState, 0x17, 0);
  spriteAttr = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (((u8 *) actor) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) actor) + 0x22))) + 8) << 12));
  *((u16 *) sprite) = spriteAttr;
  *((u16 *) sprite) = spriteAttr | D_02025FF0.spriteAttrMask;
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  if (entity->variant & 1)
  {
    *((u16 *) (sprite + 2)) |= 0x10;
  }
  coordBase = (u8 *) (&D_02021E90);
  {
    u32 coordField = 0x1278;
    *((u32 *) (sprite + 0x14)) = actor->posX - (((*((u32 *) ((coordBase + coordField) + ((D_02025FF0.index + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 coordField = 0x127C;
    *((u32 *) (sprite + 0x18)) = actor->posY - (((*((u32 *) ((coordBase + coordField) + ((D_02025FF0.index + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  entity->flags |= 0x1000;
  *((u8 *) ((((u8 *) entity) + (2 * entity->dirIndex)) + 0x19)) = 0;
  scriptData = (s32 *) 0x08671BB0;
  _call_via_r2(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, *scriptData);
}
