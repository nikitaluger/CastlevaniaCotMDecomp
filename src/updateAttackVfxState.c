extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void moveEntityWithCollision(void *, s32);
extern void spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
extern void sub_0808BB54(void);
extern void spawnEffectParticle(s32, s32, s32, s32);
extern void copyBytes(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern u8 gCrossfadeGfxState[];
extern u8 gMainWorkspace[];
inline u16 *flagWord(u8 *p) { return (u16 *) (p + 0x3C); }

/* Updates an entity's attack VFX: moves the work object, sets OAM attributes
 * from step flags, spawns particles/projectiles at scripted steps, runs a
 * countdown and restores the previous handler when it expires. */
void updateAttackVfxState(void *entity)
{
  u8 particleTypeTable[0x11];
  s32 randomOffset;
  u8 *gfxState;
  s32 posX;
  s32 posY;
  u16 *spriteAttr;
  s32 controlWord;
  u8 countdown;
  void *workState;
  void *vfxState;

  spriteAttr = (u16 *) (*((void **) (((u8 *) entity) + 0x38)));
  workState = *((void **) (((u8 *) entity) + 0x3C));
  vfxState = ((u8 *) workState) + 0x48;
  controlWord = 0x3F40;
  copyBytes(particleTypeTable, (void *) 0x081017B4, 0x11);
  moveEntityWithCollision(workState, 0x2D82);
  if (!(2 & (*((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19))))
  {
    *spriteAttr = (0xFFF & (*spriteAttr)) | 0xE000;
  }
  if ((((u32) ((u8 *) workState)[0x6B]) > 2U) && (!(3 & (*((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19)))))
  {
    spawnJitteredParticles(particleTypeTable[((u8 *) workState)[0x6B]], 2, *((s32 *) (((u8 *) workState) + 0x08)), (*((s32 *) (((u8 *) workState) + 0x0C))) + 0xFFE80000, 0x300000, 0x180000);
  }
  if ((((u32) ((u8 *) vfxState)[0x23]) > 8U) && ((0x1F & (*((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19))) == 0x10))
  {
    posX = *((s32 *) (((u8 *) workState) + 0x08));
    posY = *((s32 *) (((u8 *) workState) + 0x0C));
    randomOffset = randomSignedOffset(0x20000);
    spawnEffectParticle(posX, posY, randomOffset, 0 - (scaleByRandom(0x30000) + 0x30000));
  }
  gfxState = gCrossfadeGfxState;
  *((u16 *) (gfxState + 0x04)) = controlWord;
  if (!(0x1F & (*((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19))))
  {
    ((u8 *) vfxState)[0x23] = ((u8 *) vfxState)[0x23] - 1;
  }
  countdown = ((u8 *) vfxState)[0x23];
  *((u16 *) (gfxState + 0x06)) = (u16) (countdown | ((0x10 - countdown) << 8));
  if (((u8 *) vfxState)[0x23] == 0)
  {
    *flagWord(gMainWorkspace) = 2;
    sub_0808BB54();
    sub_080C31E0(entity, *((s32 *) (((u8 *) entity) + 0x24)));
  }
}
