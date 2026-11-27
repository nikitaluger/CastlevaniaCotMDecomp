extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 findKindIndex(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080AA8A0(void *, void *);
extern s64 scaleByRandom(s32);
struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 gSpriteAnimDataTable[];

/*
 * Spawns and initializes an entity's child sprite: allocates the object, sets
 * up its motion/animation from a definition object, positions it relative to
 * the parent, assigns a pseudo-random lifetime and dispatches its step script.
 */
void sub_080AA650(void *entity)
{
  void *sprite;
  void *motion;
  void *status;
  s32 spriteBase;
  u8 *stepBase;
  u32 *scriptTable;
  s32 *handlerTable;
  u8 *stepData;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    sub_080C31E0(entity, *((s32 *) (((char *) entity) + 0x24)));
    return;
  }
  *((void **) (((char *) entity) + 0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if ((*((vu32 *) (((char *) entity) + 0x3C))) == 0)
  {
    sub_080C31E0(entity, *((s32 *) (((char *) entity) + 0x24)));
    return;
  }
  *((s32 *) (((char *) sprite) + 0x1C)) = 0x80000009;
  motion = *((void **) (((char *) entity) + 0x3C));
  status = ((char *) motion) + 0x34;
  *((s16 *) (((char *) motion) + 0x1C)) = 0x5F;
  sub_080AA8A0(entity, motion);
  spriteBase = findKindIndex(*((s16 *) (((char *) motion) + 0x1C)));
  *((s16 *) (((char *) motion) + 0x22)) = (s16) spriteBase;
  if (((s32) (((u32) spriteBase) << 16)) < 0)
  {
    sub_080C31E0(entity, *((s32 *) (((char *) entity) + 0x24)));
    return;
  }
  spriteBase = *((s16 *) (((char *) motion) + 0x22));
  spriteBase <<= 6;
  spriteBase += 0x200;
  spriteBase &= 0xFC0;
  *((u16 *) sprite) = (u16) spriteBase;
  *((u16 *) sprite) = (u16) (spriteBase | (&gMainWorkspace)->w);
  initSpriteGraphics(sprite, status, (void *) ((((s32) (*((s16 *) (((char *) motion) + 0x1C)))) * 0xC) + 0x080CD400));
  setAnimationFrame(sprite, status, 8, 0);
  *((s32 *) (((char *) entity) + 0x4C)) = (s32) scaleByRandom(0x5B0) + 0xB60;
  *((u16 *) (((char *) entity) + 0x02)) |= 0x1000;
  {
    u8 *p = (u8 *) ((((s16) (*((s16 *) (((char *) entity) + 0x22)))) * 2) + ((u32) entity));
    p[0x19] = 0;
  }
  scriptTable = (u32 *) 0x08671BB0;
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
