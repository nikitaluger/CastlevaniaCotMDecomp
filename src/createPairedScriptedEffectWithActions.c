extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, void *, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void sub_080415D4(u8, void *, void *, void *);
extern void *spawnBudgetedEffect(void *, s32);
extern void *allocEffectPart(void);
extern void registerScriptObject(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08014290(void);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u8 gEnemyActionKindTable[];
extern u8 gEnemyActionParams[];
extern u32 gMainObjTimerCallbacks[];
extern struct PairedEffectKindEntry gSpriteKindTable[];
inline s16 getPairedEffectKind(struct PairedEffectWork *work)
{
  return *((s16 *) (((u8 *) work) + 0x1C));
}

/* Create a linked pair of scripted enemy objects and their sprites, initialise the render part from the action tables, place it in screen space and dispatch the entry script; failures bail through the state handler. */ void createPairedScriptedEffectWithActions(u8 *entity)
{
  void *parent;
  u8 *sprite;
  struct PairedEffectWork *work;
  u8 *kindTable;
  u8 *gfxInit;
  u8 *variantPtr;
  struct PairedEffectPart *part;
  u8 *layerAttrs;
  u8 *child;
  s32 zeroByte;
  u8 *camera;
  u8 *workspace;
  u8 *scrollX;
  u8 *scrollY;
  u32 scrollIdx;
  parent = *((void **) (entity + 0xAC));
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  *((void **) (entity + 0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x4C, 0);
  if ((*((u32 *) (entity + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (sprite + 0x1C)) = MULTI_PART_SPRITE_GFX_ID;
  work = *((struct PairedEffectWork **) (entity + 0x3C));
  gfxInit = ((u8 *) work) + 0x34;
  installUpdateHandler(entity, (u8 *) work, (void *) sub_08014290);
  kindTable = gEnemyActionKindTable;
  variantPtr = entity + 0x74;
  initWorkStateForKind(entity, sprite, (u8 *) work, parent, *((s16 *) (kindTable + ((*variantPtr) * 4))));
  initSpriteGraphics(sprite, gfxInit, ((s32) gSpriteAnimDataTable) + ((*((s16 *) (((u8 *) work) + 0x1C))) * 0xC));
  sub_080415D4(0, sprite, (u8 *) work, gfxInit);
  child = spawnBudgetedEffect(entity, 0x10B);
  if (child == NULL)
  {
    goto fail;
  }
  {
    u8 variantByte = *variantPtr;
    u8 *dst = ((u8 *) child) + 0x74;
    zeroByte = 0;
    *dst = variantByte;
  }
  child = spawnBudgetedEffect(*((void **) (entity + 0x30)), 0x10B);
  if (child == NULL)
  {
    goto fail;
  }
  {
    u8 variantByte = *variantPtr;
    ((u8 *) child)[0x74] = variantByte;
  }
  *((u8 *) (entity + 0x70)) = (u8) zeroByte;
  *((u8 *) ((*((u8 **) (entity + 0x30))) + 0x70)) = (u8) zeroByte;
  layerAttrs = gEnemyActionParams;
  part = allocEffectPart();
  work->part = part;
  if (part == NULL)
  {
    goto fail;
  }
  goto body;
  fail:
  sub_080C31E0(entity, *((void **) (entity + 0x24)));

  return;
  body:
  part->kind = RENDER_PART_KIND;

  work->part->layer = 8;
  work->part->priority = 1;
  {
    s32 zero = 0;
    work->part->gfxIndex = gSpriteKindTable[getPairedEffectKind(work)].gfxIndex;
    work->part->anim0 = *((u16 *) (layerAttrs + 0));
    work->part->anim1 = *((u16 *) (layerAttrs + 2));
    work->part->anim2 = *((u16 *) (layerAttrs + 4));
    work->part->anim3 = *((u16 *) (layerAttrs + 6));
    work->part->palette = gSpriteKindTable[getPairedEffectKind(work)].palette;
    work->part->object = (u32) sprite;
    camera = gCameraState;
    workspace = gMainWorkspace;
    workspace += 0x18A8;
    scrollIdx = (((u32) (*workspace)) + 1) * 0x40;
    scrollX = camera + 0x1278;
    *((u32 *) (sprite + 0x14)) = (*((u32 *) (((u8 *) work) + 0x08))) - (((*((u32 *) (scrollX + scrollIdx))) + 0x8000) & 0xFFFF0000);
    scrollIdx = (((u32) (*workspace)) + 1) * 0x40;
    scrollY = camera + 0x127C;
    *((u32 *) (sprite + 0x18)) = (*((u32 *) (((u8 *) work) + 0x0C))) - (((*((u32 *) (scrollY + scrollIdx))) + 0xFFFF8000) & 0xFFFF0000);
    registerScriptObject(entity, 0);
    {
      u16 flags = *((u16 *) (entity + 2));
      flags |= THREAD_FLAG_WAIT_SPRITE;
      *((u16 *) (entity + 2)) = flags;
    }
    *((u8 *) ((((u32) ((*((s16 *) (entity + 0x22))) * 2)) + ((u32) entity)) + 0x19)) = (u8) zero;
    {
      u32 *scriptOps = (u32 *) gMainObjTimerCallbacks;
      u8 *scriptPtr = entity + 0x18;
      sub_080C31E4(scriptPtr, entity + 0x22, *scriptOps);
      {
        u8 *scriptBytePtr = (u8 *) ((((u32) ((*((s16 *) (entity + 0x22))) * 2)) + ((u32) entity)) + 0x19);
        *scriptBytePtr = (u8) ((*scriptBytePtr) + 1);
        scriptBytePtr = scriptPtr;
        scriptBytePtr += (*((s16 *) (entity + 0x22))) * 2;
        {
          u8 opcode = *scriptBytePtr;
          void *handler = ((void **) (*((void **) (entity + 0x14))))[opcode];
          do { do { sub_080C31E0(entity, handler); } while (0); } while (0);
        }
      }
    }
  }
}
