/* Spawn a table-driven directional child effect for an actor: take a render
 * part from the pool, seed it from the global config, read the timer payload
 * and direction from the entity's variant record, install the cleanup handler,
 * then run the current script step. */
extern void *allocEffectPart(void);
extern void cleanupFailedEffectSpawn(void *a);
extern s16 scalePercentSaturate16(u16, s32);
extern void startEffectTimer(void *a, s32 b, void *c);
extern void setDirectionVector(void *a, u8 b);
extern void _call_via_r1(void *a, void *b);
extern void _call_via_r2(void *a, void *b, void *c);
extern void releaseActorEffectParts(void);
extern u8 gGameStatus[];
extern struct ChildEffectWorkspace gMainWorkspace;
extern u8 gActorChildEffectVariantTable[];

void spawnActorChildEffectFromTable(u8 *entity)
{
  u8 *header = *((u8 **) (entity + 0x6C));
  u8 *state = header + 4;
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *dataTable = gGameStatus;
  struct TabledChildEffectPart *part = allocEffectPart();
  u8 *variantTable;
  u8 *variant;
  s32 *callbackSlot;
  u8 *ctrlBase;
  *((struct TabledChildEffectPart **) (state + 0x2C)) = part;
  if (part == 0)
  {
    cleanupFailedEffectSpawn(entity);
    return;
  }
  *((u32 *) (state + 0x30)) = 0;
  *((u32 *) (state + 0x34)) = 0;
  *((u32 *) (state + 0x38)) = 0;
  *((u32 *) (state + 0x3C)) = 0;
  part->variant = gMainWorkspace.variantBit & 1;
  (*((struct TabledChildEffectPart **) (state + 0x2C)))->kind = 2;
  (*((struct TabledChildEffectPart **) (state + 0x2C)))->layer = 8;
  {
    u8 v;
    u8 zero = 0;
    (void) zero;
    (*((struct TabledChildEffectPart **) (state + 0x2C)))->gfxIndex = dataTable[0x304];
    (*((struct TabledChildEffectPart **) (state + 0x2C)))->width = 4;
    (*((struct TabledChildEffectPart **) (state + 0x2C)))->height = 4;
    (*((struct TabledChildEffectPart **) (state + 0x2C)))->affine0 = 0;
    (*((struct TabledChildEffectPart **) (state + 0x2C)))->affine1 = 0;
  }
  (*((struct TabledChildEffectPart **) (state + 0x2C)))->palette = scalePercentSaturate16(*((u16 *) (dataTable + 0x2E2)), 0x32);
  (*((struct TabledChildEffectPart **) (state + 0x2C)))->frame = 5;
  (*((struct TabledChildEffectPart **) (state + 0x2C)))->animStep = 0x54;
  (*((struct TabledChildEffectPart **) (state + 0x2C)))->sprite = (u32) sprite;
  *((u32 *) (state + 0x18)) = *((u32 *) (entity + 0x24));
  *((u32 *) (entity + 0x24)) = (u32) releaseActorEffectParts;
  *((u32 *) (sprite + 0x24)) = CHILD_EFFECT_TABLED_ANIM_DATA;
  {
    u8 *dst = header + 0x20;
    variantTable = gActorChildEffectVariantTable;
    variant = entity + 0x9C;
    startEffectTimer(dst, 0, *((void **) (variantTable + ((*((u32 *) variant)) * 8))));
  }
  *((u32 *) (header + 4)) = *((u32 *) (entity + 0x7C));
  *((u32 *) (state + 4)) = *((u32 *) (entity + 0x8C));
  *((u32 *) (state + 0x40)) = CHILD_EFFECT_WORK_DISTANCE;
  {
    u8 direction = *((u8 *) ((variantTable + ((*((u32 *) variant)) * 8)) + 4));
    u8 *directionDst = header + 0x48;
    *directionDst = direction;
    setDirectionVector(state, *directionDst);
  }
  *((u32 *) (state + 0x48)) = CHILD_EFFECT_STATE_TIME;
  *(((u8 *) ((((s16) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity))) + 0x19) = 0;
  callbackSlot = (s32 *) MAIN_OBJ_TIMER_CALLBACK_TABLE;
  ctrlBase = variant - 0x84;
  _call_via_r2(ctrlBase, entity + 0x22, (void *) (*callbackSlot));
  {
    u8 *stepDesc = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
    *(u8 *)(stepDesc + 0x19) = (u8)(*(u8 *)(stepDesc + 0x19) + 1);
  }
  {
    s16 stepIndex = *((s16 *) (entity + 0x22));
    u8 *stepPtr = ctrlBase + (stepIndex * 2);
    _call_via_r1(entity, *((void **) ((*((u32 *) (entity + 0x14))) + ((*stepPtr) * 4))));
  }
}
