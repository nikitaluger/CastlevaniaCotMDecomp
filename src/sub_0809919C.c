extern s32 scaleByRandom(s32);
extern s32 sub_0800583C(s32);
extern void moveEntityWithCollision(void *, s32);
extern void sub_08014848(s32, s32, s32, s32, s32, s32);
extern void sub_0808BB54(void);
extern void sub_0808E61C(s32, s32, s32, s32);
extern void copyBytes(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern u8 gCrossfadeGfxState[];
extern u8 gMainWorkspace[];
inline u16 *flagWord(u8 *p) { return (u16 *) (p + 0x3C); }

/*
 * Updates an entity's attack VFX state: advances its motion, sets sprite
 * attributes from the current step flags, spawns particles or a projectile at
 * scripted steps, runs a countdown timer, and restores the previous handler
 * when the timer expires.
 */
void sub_0809919C(void *entity)
{
  u8 particleTypes[0x11];
  s32 randOffset;
  u8 *sysState;
  s32 posX;
  s32 posY;
  u16 *spriteAttr;
  s32 controlWord;
  u8 timer;
  void *motion;
  void *motionState;

  spriteAttr = (u16 *) (*((void **) (((u8 *) entity) + 0x38)));
  motion = *((void **) (((u8 *) entity) + 0x3C));
  motionState = ((u8 *) motion) + 0x48;
  controlWord = 0x3F40;
  copyBytes(particleTypes, (void *) 0x081017B4, 0x11);
  moveEntityWithCollision(motion, 0x2D82);
  if (!(2 & (*((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19))))
  {
    *spriteAttr = (0xFFF & (*spriteAttr)) | 0xE000;
  }
  if ((((u32) ((u8 *) motion)[0x6B]) > 2U) && (!(3 & (*((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19)))))
  {
    sub_08014848(particleTypes[((u8 *) motion)[0x6B]], 2, *((s32 *) (((u8 *) motion) + 0x08)), (*((s32 *) (((u8 *) motion) + 0x0C))) + 0xFFE80000, 0x300000, 0x180000);
  }
  if ((((u32) ((u8 *) motionState)[0x23]) > 8U) && ((0x1F & (*((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19))) == 0x10))
  {
    posX = *((s32 *) (((u8 *) motion) + 0x08));
    posY = *((s32 *) (((u8 *) motion) + 0x0C));
    randOffset = sub_0800583C(0x20000);
    sub_0808E61C(posX, posY, randOffset, 0 - (scaleByRandom(0x30000) + 0x30000));
  }
  sysState = gCrossfadeGfxState;
  *((u16 *) (sysState + 0x04)) = controlWord;
  if (!(0x1F & (*((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19))))
  {
    ((u8 *) motionState)[0x23] = ((u8 *) motionState)[0x23] - 1;
  }
  timer = ((u8 *) motionState)[0x23];
  *((u16 *) (sysState + 0x06)) = (u16) (timer | ((0x10 - timer) << 8));
  if (((u8 *) motionState)[0x23] == 0)
  {
    *flagWord(gMainWorkspace) = 2;
    sub_0808BB54();
    sub_080C31E0(entity, *((s32 *) (((u8 *) entity) + 0x24)));
  }
}
