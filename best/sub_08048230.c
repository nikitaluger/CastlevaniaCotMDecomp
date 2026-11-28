extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, void *, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void sub_08049160(void *, void *, void *, u32);
extern void *allocEffectPart(void);
extern void registerScriptObject(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void updateScriptedEffectObject(void);
extern u8 gPairedEffectKindTable[];
extern u8 gSpriteAnimDataTable[];
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 gMainObjTimerCallbacks[];
extern struct PairedEffectKindEntry gSpriteKindTable[];

inline s16 getPairedEffectKind(struct PairedEffectWork *work)
{
  return *((s16 *) (((u8 *) work) + 0x1C));
}

/* Create a linked pair of scripted objects and their sprites, initialise the
 * single render part, place it in screen space and dispatch the entry script. */
void sub_08048230(u8 *entity)
{
  void *parent;
  u8 *sprite;
  struct PairedEffectWork *work;
  u8 *kindTable;
  u8 *gfxInit;
  u8 *frameReq;
  struct PairedEffectPart *part;
  s32 zero;
  
  u8 *workspace;
  u8 *scrollY;
  u32 scrollIdx;

  parent = *((void **) (entity + 0xAC));
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  *((void **) (entity + 0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x64, 0);
  if ((*((u32 *) (entity + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (sprite + 0x1C)) = MULTI_PART_SPRITE_GFX_ID;
  work = *((struct PairedEffectWork **) (entity + 0x3C));
  gfxInit = ((u8 *) work) + 0x34;
  frameReq = ((u8 *) work) + 0x48;
  installUpdateHandler(entity, (u8 *) work, (void *) updateScriptedEffectObject);
  kindTable = gPairedEffectKindTable;
  do { do { do { initWorkStateForKind(entity, sprite, (u8 *) work, parent, *((s16 *) (kindTable + ((*(entity + 0x4C)) * 4))));
  initSpriteGraphics(sprite, gfxInit, ((s32) gSpriteAnimDataTable) + ((*((s16 *) (((u8 *) work) + 0x1C))) * 0xC));
  sub_08049160(sprite, gfxInit, frameReq, 0); } while (0); } while (0); } while (0);
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
    zero = 0;
    work->part->gfxIndex = gSpriteKindTable[getPairedEffectKind(work)].gfxIndex;
    work->part->anim0 = *((u16 *) (gfxInit + 0));
    work->part->anim1 = *((u16 *) (gfxInit + 2));
    work->part->anim2 = *((u16 *) (gfxInit + 4));
    work->part->anim3 = *((u16 *) (gfxInit + 6));
    work->part->palette = gSpriteKindTable[getPairedEffectKind(work)].palette;
    work->part->object = (u32) sprite;
    kindTable = gCameraState;
    workspace = gMainWorkspace;
    workspace += 0x18A8;
    scrollIdx = (((u32) (*workspace)) + 1) * 0x40;
    *((u32 *) (sprite + 0x14)) = (*((u32 *) (((u8 *) work) + 0x08))) - (((*((u32 *) ((kindTable + 0x1278) + scrollIdx))) + 0x8000) & 0xFFFF0000);
    scrollIdx = (((u32) (*workspace)) + 1) * 0x40;
    scrollY = kindTable + 0x127C;
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
      do { {
        u8 *scriptBytePtr = (u8 *) ((((u32) ((*((s16 *) (entity + 0x22))) * 2)) + ((u32) entity)) + 0x19);
        *scriptBytePtr = (u8) ((*scriptBytePtr) + 1);
        scriptBytePtr = scriptPtr;
        scriptBytePtr += (*((s16 *) (entity + 0x22))) * 2;
        {
          u8 opcode = *scriptBytePtr;
          void *handler = ((void **) (*((void **) (entity + 0x14))))[opcode];
          sub_080C31E0(entity, handler);
        }
      } } while (0);
    }
  }
}
