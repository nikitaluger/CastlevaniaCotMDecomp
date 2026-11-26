extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 findKindIndex(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gSpriteAnimDataTable[];

/*
 * Spawns and initializes an entity's child sprite: allocates the object, sets
 * up its motion/animation from a definition object, assigns a sprite flag and
 * clears its step counter, then dispatches its step script.
 */
void sub_080AE860(void *entity)
{
  void *sprite;
  void *motion;
  void *status;
  s32 spriteBase;
  s32 zero;
  u8 *stepBase;
  void **scriptTable;
  s32 *handlerTable;
  u8 *stepData;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  *((void **)(((char *) entity) + 0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if ((*((vu32 *)(((char *) entity) + 0x3C))) == 0)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  *((s32 *)(((char *) sprite) + 0x1C)) = 0x32;
  motion = *((void **)(((char *) entity) + 0x3C));
  status = ((char *) motion) + 0x34;
  zero = 0;
  *((s16 *)(((char *) motion) + 0x1C)) = 0x64;
  spriteBase = findKindIndex();
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
  *((u16 *) sprite) = (u16) (spriteBase | (&gMainWorkspace)->w);
  initSpriteGraphics(sprite, status, (void *) ((((s32) (*((s16 *) (((char *) motion) + 0x1C)))) * 0xC) + 0x080CD400));
  setAnimationFrame(sprite, status, 0x0D, 0);
  *((u16 *)(((char *) sprite) + 2)) |= 0x400;
  *((u8 *)(((char *) entity) + 0x4C)) = (u8) zero;
  *((u16 *)(((char *) entity) + 0x02)) |= 0x1000;
  {
    u8 *p = (u8 *) ((((s16) (*((s16 *) (((char *) entity) + 0x22)))) * 2) + ((u32) entity));
    p[0x19] = (u8) zero;
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
