extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *a);
extern s16 scalePercentSaturate16(u16, s32);
extern void startEffectTimer(void *a, s32 b, void *c);
extern void setDirectionVector(void *a, u8 b);
extern void _call_via_r1(void *a, void *b);
extern void _call_via_r2(void *a, void *b, void *c);
extern void releaseActorEffectParts(void);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];

/* Render part handed out by allocEffectPart; the 0x80 flag in `flags` marks
 * the slot as allocated in the shared effect-part pool. */
struct DirectionalEffectPart
{
  u8 flags;
  u8 variant;
  u8 kind;
  u8 layer;
  u16 gfxIndex;
  u16 width;
  u16 height;
  u16 affine0;
  u16 affine1;
  u16 palette;
  u32 sprite;
  u8 _14[2];
  u16 frame;
  u16 animStep;
};

/* The actor's sprite: 8.8 fixed-point scale and its animation data pointer. */
struct DirectionalEffectSprite
{
  u8 _0[4];
  u16 scaleX;
  u16 scaleY;
  u16 rotation;
  u8 _a[0x1A];
  u32 animData;
};

/* Spawn a directional child effect for an actor: take a render part from the
 * pool, fill it from the global game tables (bailing out through
 * cleanupFailedEffectSpawn when the pool is full), save the actor's handler
 * and install releaseActorEffectParts, set the sprite's scale and animation
 * plus the effect's direction, start the script timer, then run the current
 * script step. */
void spawnActorChildEffectDirectional(u8 *entity)
{
  u8 *header = *((u8 **) (entity + 0x6C));
  u8 *state = header + 4;
  struct DirectionalEffectSprite *sprite = *((struct DirectionalEffectSprite **) (entity + 0x38));
  u8 *dataTable = gGameStatus;
  struct DirectionalEffectPart *part = allocEffectPart();
  u8 *workspace;
  u32 zero;
  u8 *ctrlBase;
  s32 *callbackSlot;
  *((struct DirectionalEffectPart **) (state + 0x2C)) = part;
  if (part == 0)
  {
    cleanupFailedEffectSpawn(entity);
    return;
  }
  zero = 0;
  *((u32 *) (state + 0x30)) = zero;
  *((u32 *) (state + 0x34)) = zero;
  *((u32 *) (state + 0x38)) = zero;
  *((u32 *) (state + 0x3C)) = zero;
  workspace = gMainWorkspace;
  part->variant = workspace[0x1510] & 1;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->kind = 2;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->layer = 8;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->gfxIndex = dataTable[0x304];
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->width = 8;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->height = 8;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->affine0 = zero;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->affine1 = zero;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->palette = scalePercentSaturate16(*((u16 *) (dataTable + 0x2E2)), 0x8D);
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->frame = 0x1E;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->animStep = 0x51;
  (*((struct DirectionalEffectPart **) (state + 0x2C)))->sprite = (u32) sprite;
  *((u32 *) (state + 0x18)) = *((u32 *) (entity + 0x24));
  *((u32 *) (entity + 0x24)) = (u32) releaseActorEffectParts;
  sprite->scaleX = 0x100;
  sprite->scaleY = 0x100;
  sprite->rotation = zero;
  sprite->animData = 0x084D7EF4;
  startEffectTimer(header + 0x20, 0, (void *) 0x084D80FC);
  *((u32 *) (header + 4)) = *((u32 *) (workspace + 0x174C));
  *((u32 *) (state + 4)) = *((u32 *) (workspace + 0x1750));
  *((u32 *) (state + 0x40)) = 0x50000;
  {
    u32 direction = *((u32 *) (entity + 0x7C));
    u8 *directionDst = header + 0x48;
    *directionDst = direction;
    setDirectionVector(state, *directionDst);
  }
  *((u32 *) (state + 0x48)) = 0x18;
  *(((u8 *) ((((s16) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity))) + 0x19) = 0;
  callbackSlot = (s32 *) 0x08671BB0;
  ctrlBase = entity + 0x18;
  _call_via_r2(ctrlBase, entity + 0x22, (void *) (*callbackSlot));
  {
    u8 *stepDesc = (u8 *) ((((s16) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    stepDesc[0x19]++;
  }
  {
    u8 *stepPtr = ctrlBase + (((s16) (*((s16 *) (entity + 0x22)))) * 2);
    _call_via_r1(entity, *((void **) ((*((u32 *) (entity + 0x14))) + ((*stepPtr) * 4))));
  }
}
