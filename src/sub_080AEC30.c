extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 findKindIndex(void);
extern s32 sub_080057F8(void);
extern s64 sub_08005820(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallback;
struct SpawnObj { u8 _00[0x14]; u32 stepHandlerTable; };

/*
 * Spawns and initializes an entity's child sprite: allocates the object, sets
 * up its motion/animation, assigns a pseudo-random timer and seed, then starts
 * its step script.
 */
void sub_080AEC30(void *entity)
{
  void *sprite;
  void *motion;
  void *status;
  s32 spriteBase;
  u32 stepByte;
  s16 stepIndex;
  u16 *stepArray;
  u16 *stepEntry;
  u8 *stepBase;
  u32 fn;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  *((void **)(((char *) entity) + 0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if (*((vu32 *)(((char *) entity) + 0x3C)) == 0)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  *((s32 *)(((char *) sprite) + 0x1C)) = 0xB3;
  motion = *((void **)(((char *) entity) + 0x3C));
  status = ((char *) motion) + 0x34;
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
  initSpriteGraphics(sprite, status, (void *) (((s32)(*((s16 *)(((char *) motion) + 0x1C))) * 0xC) + 0x080CD400));
  setAnimationFrame(sprite, status, 0x0F, 0);
  *((void **)(((char *) entity) + 0x6C)) = (void *)((s32)sub_08005820(0x80 << 14) + (0xC0 << 14));
  *((s32 *)(((char *) entity) + 0x7C)) = sub_080057F8() & 0xFFFF;
  *((u16 *)(((char *) entity) + 0x02)) |= (0x80 << 5);
  stepIndex = *((s16 *)(((char *) entity) + 0x22));
  stepArray = (u16 *)entity;
  ((u8 *)(&stepArray[stepIndex]))[0x19] = 0;
  {
    u32 *pbb0 = &gMainObjTimerCallback;
    stepBase = ((u8 *) entity) + 0x18;
    sub_080C31E4(stepBase, ((u8 *) entity) + 0x22, *pbb0);
  }
  stepIndex = *((s16 *)(((char *) entity) + 0x22));
  stepArray = (u16 *)entity;
  ((u8 *)(&stepArray[stepIndex]))[0x19] = ((u8 *)(&stepArray[stepIndex]))[0x19] + 1;
  stepIndex = *((s16 *)(((char *) entity) + 0x22));
  stepArray = (u16 *)stepBase;
  stepEntry = &stepArray[stepIndex];
  stepByte = ((u8 *)stepEntry)[0];
  fn = *((u32 *)(((u8 *)((struct SpawnObj *)entity)->stepHandlerTable) + (stepByte * 4)));
  sub_080C31E0(entity, fn);
}
