extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 findKindIndex(s32);
extern void sub_080146D0(void *, s32, s32);
extern s32 sub_080057F8(void);
extern s32 scaleByRandom(s32);
extern void sub_080C31E0(void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gSpriteAnimDataTable[];

/* Spawns and initializes a child sprite, gives it a randomized velocity,
 * then switches the entity to its dedicated step handler. */
void sub_080A5268(void *entity)
{
  void *sprite;
  void *motion;
  void *status;
  s32 spriteBase;
  s32 speed;
  s32 angle;

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
  *((s32 *)(((char *) sprite) + 0x1C)) = 0x80000009;
  motion = *((void **)(((char *) entity) + 0x3C));
  status = ((char *) motion) + 0x34;
  *((s16 *)(((char *) motion) + 0x1C)) = 0x59;
  *((s32 *)(((char *) motion) + 0x08)) = *((s32 *)(((char *) entity) + 0x4C));
  *((s32 *)(((char *) motion) + 0x0C)) = *((s32 *)(((char *) entity) + 0x5C));
  spriteBase = findKindIndex(0x59);
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
  setAnimationFrame(sprite, status, 0x2C, 0);
  *((u16 *)(((char *) sprite) + 0x02)) |= 0x400;
  speed = (s32) scaleByRandom(0x80 << 11) + (0x80 << 10);
  angle = sub_080057F8() & (0xFC << 8);
  sub_080146D0(motion, angle, speed);
  *((u16 *)(((char *) entity) + 0x02)) |= (0x80 << 5);
  *((u16 *)(((char *) entity) + 0x02)) |= (0x80 << 4);
  *((s32 *)(((char *) entity) + 0x14)) = 0x080A5369;
  *((u16 *)(((char *) entity) + 0x22)) = 1;
  sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x14)));
}
