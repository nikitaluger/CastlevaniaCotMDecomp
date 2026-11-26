extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void sub_080141F8(void *, void *, void *, void *, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *sub_0805FAEC(void *, s32);
extern void *allocEffectPart(void);
extern void registerScriptObject(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08014290(void);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u8 D_080CFC98[];
extern u8 D_080CFCA0[];
extern u32 gMainObjTimerCallback[];
struct EffectPart
{
  u8 unk0;
  u8 kind;
  u8 layer;
  u8 priority;
  u16 gfxIndex;
  u16 anim0;
  u16 anim1;
  u16 anim2;
  u16 anim3;
  u16 palette;
  u32 object;
};
struct EffectWork
{
  u8 unk0[8];
  u32 worldX;
  u32 worldY;
  u8 unk10[0x0C];
  s16 kind;
  u8 unk1E[0x0A];
  struct EffectPart *gfx;
};
struct EffectStats
{
  u16 gfxIndex;
  u16 unk2;
  u16 palette;
  u8 unk6[0x0E];
};
extern struct EffectStats gSpriteKindTable[];
inline s16 getKind(struct EffectWork *work)
{
  return *((s16 *) (((u8 *) work) + 0x1C));
}

/* Create a linked pair of scripted objects and their sprites, initialise the
 * single render part, place it in screen space and dispatch the entry script. */
void sub_08056F4C(u8 *arg0)
{
  void *parent;
  u8 *sprite;
  struct EffectWork *work;
  u8 *kindTable;
  u8 *animState;
  u8 *variantPtr;
  struct EffectPart *part;
  u8 *animTable;
  u8 *other;
  s32 zero8c;
  u8 *scrollTable;
  u8 *globalPtr;
  u8 *scrollXBase;
  u8 *scrollYBase;
  u32 scrollIdx;
  parent = *((void **) (arg0 + 0xAC));
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  *((void **) (arg0 + 0x38)) = sprite;
  allocWorkSlot(arg0, 0, 0x64, 0);
  if ((*((u32 *) (arg0 + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  work = *((struct EffectWork **) (arg0 + 0x3C));
  animState = ((u8 *) work) + 0x34;
  installUpdateHandler(arg0, (u8 *) work, (void *) sub_08014290);
  kindTable = D_080CFC98;
  variantPtr = arg0 + 0x4C;
  sub_080141F8(arg0, sprite, (u8 *) work, parent, *((s16 *) (kindTable + ((*variantPtr) * 4))));
  initSpriteGraphics(sprite, animState, ((s32) gSpriteAnimDataTable) + ((*((s16 *) (((u8 *) work) + 0x1C))) * 0xC));
  setAnimationFrame(sprite, animState, 0, 0);
  other = sub_0805FAEC(arg0, 0x15E);
  if (other == NULL)
  {
    goto fail;
  }
  {
    u8 variantByte = *variantPtr;
    u8 *dst = ((u8 *) other) + 0x4C;
    zero8c = 0;
    *dst = variantByte;
  }
  other = sub_0805FAEC(*((void **) (arg0 + 0x30)), 0x15E);
  if (other == NULL)
  {
    goto fail;
  }
  {
    u8 variantByte = *variantPtr;
    ((u8 *) other)[0x4C] = variantByte;
  }
  *((u8 *) (arg0 + 0x8C)) = (u8) zero8c;
  *((u8 *) ((*((u8 **) (arg0 + 0x30))) + 0x8C)) = (u8) zero8c;
  animTable = D_080CFCA0;
  part = allocEffectPart();
  work->gfx = part;
  if (part == NULL)
  {
    goto fail;
  }
  goto body;
  fail:
  sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));

  return;
  body:
  part->kind = 5;

  work->gfx->layer = 8;
  work->gfx->priority = 1;
  {
    s32 zero = 0;
    work->gfx->gfxIndex = gSpriteKindTable[getKind(work)].gfxIndex;
    work->gfx->anim0 = *((u16 *) (animTable + 0));
    work->gfx->anim1 = *((u16 *) (animTable + 2));
    work->gfx->anim2 = *((u16 *) (animTable + 4));
    work->gfx->anim3 = *((u16 *) (animTable + 6));
    work->gfx->palette = gSpriteKindTable[getKind(work)].palette;
    work->gfx->object = (u32) sprite;
    scrollTable = gCameraState;
    globalPtr = gMainWorkspace;
    globalPtr += 0x18A8;
    scrollIdx = (((u32) (*globalPtr)) + 1) * 0x40;
    scrollXBase = scrollTable + 0x1278;
    *((u32 *) (sprite + 0x14)) = (*((u32 *) (((u8 *) work) + 0x08))) - (((*((u32 *) (scrollXBase + scrollIdx))) + 0x8000) & 0xFFFF0000);
    scrollIdx = (((u32) (*globalPtr)) + 1) * 0x40;
    scrollYBase = scrollTable + 0x127C;
    *((u32 *) (sprite + 0x18)) = (*((u32 *) (((u8 *) work) + 0x0C))) - (((*((u32 *) (scrollYBase + scrollIdx))) + 0xFFFF8000) & 0xFFFF0000);
    registerScriptObject(arg0, 0);
    {
      u16 flags = *((u16 *) (arg0 + 2));
      flags |= 0x1000;
      *((u16 *) (arg0 + 2)) = flags;
    }
    *((u8 *) ((((u32) ((*((s16 *) (arg0 + 0x22))) * 2)) + ((u32) arg0)) + 0x19)) = (u8) zero;
    {
      u32 *scriptOps = (u32 *) gMainObjTimerCallback;
      u8 *scriptPtr = arg0 + 0x18;
      sub_080C31E4(scriptPtr, arg0 + 0x22, *scriptOps);
      {
        u8 *counterPtr = (u8 *) ((((u32) ((*((s16 *) (arg0 + 0x22))) * 2)) + ((u32) arg0)) + 0x19);
        *counterPtr = (u8) ((*counterPtr) + 1);
        counterPtr = scriptPtr;
        counterPtr += (*((s16 *) (arg0 + 0x22))) * 2;
        {
          u8 opcode = *counterPtr;
          void *handler = ((void **) (*((void **) (arg0 + 0x14))))[opcode];
          sub_080C31E0(arg0, handler);
        }
      }
    }
  }
}
