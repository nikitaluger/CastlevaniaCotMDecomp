extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern s32 sub_08005820(s32);
extern void sub_0801131C(void *, void *, void *);
extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 D_02025FF0;
extern u8 D_080CD400[];

/*
 * Spawns and initializes an entity's child sprite: allocates the object, sets
 * up its motion/animation from a sprite table, allocates its work buffer and
 * starts the entity's script at its first step handler.
 */
void sub_0809B2E0(void *entity)
{
  void *sprite;
  void *motion;
  void *status;
  s32 spriteBase;
  u8 *stepBase;
  void **scriptTable;
  s32 *handlerTable;
  u8 *stepData;
  s32 allocSize;

  sprite = sub_0800355C();
  if (sprite == NULL)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  *((void **)(((char *) entity) + 0x38)) = sprite;
  sub_0800168C(entity, 0, 0x48, 0);
  if ((*((vu32 *)(((char *) entity) + 0x3C))) == 0)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  *((s32 *)(((char *) sprite) + 0x1C)) = 0x80000009;
  motion = *((void **)(((char *) entity) + 0x3C));
  status = ((char *) motion) + 0x34;
  *((s16 *)(((char *) motion) + 0x1C)) = 0x44;
  *((s32 *)(((char *) motion) + 0x08)) = *((s32 *)(((char *) entity) + 0x4C));
  *((s32 *)(((char *) motion) + 0x0C)) = *((s32 *)(((char *) entity) + 0x5C));
  spriteBase = sub_08013C2C(0x44);
  *((s16 *)(((char *) motion) + 0x22)) = (s16) spriteBase;
  if (((s32) (((u32) spriteBase) << 16)) < 0)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  spriteBase = *((s16 *)(((char *) motion) + 0x22));
  spriteBase <<= 6;
  spriteBase += 0x200;
  spriteBase &= 0xFC0;
  *((u16 *) sprite) = (u16) spriteBase;
  *((u16 *) sprite) = (u16) (spriteBase | (&D_02025FF0)->w);
  sub_0801131C(sprite, status, (void *) ((((s32) (*((s16 *) (((char *) motion) + 0x1C)))) * 0xC) + 0x080CD400));
  sub_08011368(sprite, status, 7, 0);
  allocSize = 0xB60;
  *((s32 *)(((char *) entity) + 0x6C)) = sub_08005820(allocSize) + allocSize;
  *((u16 *)(((char *) entity) + 0x02)) |= 0x1000;
  {
    u8 *p = (u8 *) ((((s16) (*((s16 *) (((char *) entity) + 0x22)))) * 2) + ((u32) entity));
    p[0x19] = 0;
  }
  scriptTable = (void **) 0x08671BB0;
  stepBase = ((char *) entity) + 0x18;
  sub_080C31E4(stepBase, ((char *) entity) + 0x22, (s32) (*scriptTable));
  {
    u8 *p = (u8 *) ((((s16) (*((s16 *) (((char *) entity) + 0x22)))) * 2) + ((u32) entity));
    p[0x19] = p[0x19] + 1;
  }
  stepData = stepBase + (((s16) (*((s16 *) (((char *) entity) + 0x22)))) * 2);
  {
    u8 stepByte = *stepData;
    handlerTable = *((s32 **) (((char *) entity) + 0x14));
    sub_080C31E0(entity, handlerTable[stepByte]);
  }
}
