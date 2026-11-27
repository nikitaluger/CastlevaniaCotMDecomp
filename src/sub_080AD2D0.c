extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern s32 findKindIndex(void);
extern void installUpdateHandler(void *, void *, void *);
extern void initSpriteFromTemplate(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s16, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);
struct GameState { u8 _0[0x18C2]; u16 flags; };
extern struct GameState gMainWorkspace;
extern u32 gMainObjTimerCallbacks;
extern u32 D_0810225C[];
extern s16 D_08102258[];
extern u8 D_08102264[];

/* Main object that owns the spawned effect. */
struct MainObj {
    u8 _0[2]; u16 flags; u8 _1[0x14 - 4]; u32 stepHandlerTable;
    u8 _2[0x22 - 0x18]; s16 counter; u32 failCb;
    u8 _3[0x38 - 0x28]; u32 sprite; u32 owner;
    u8 _4[0x4C - 0x40]; u8 kind;
};
/* Sprite object allocated for the effect. */
struct EffectSprite { u16 gfxFlags; u16 _02; u8 _0[0x1C - 4]; u32 gfxBase; };
/* Owner effect component stored in the main object at +0x3C. */
struct OwnerEffect { u8 _0[0x1C]; s16 kind; u8 _1[0x22 - 0x1E]; s16 slot; };

/*
 * Spawns a single-layer graphics effect from a main object: allocates a sprite,
 * initializes its motion/animation from per-kind tables, positions it relative
 * to the owner and starts its step script.
 */
void sub_080AD2D0(struct MainObj *arg)
{
  struct EffectSprite *sprite;
  struct OwnerEffect *owner;
  u8 *kindPtr;
  u8 *work;
  s32 slot;
  u8 *stepBase;
  u32 v;
  u32 fn;
  s16 i;
  u16 *arr;
  u16 *new_var;
  u32 *gfxTable;
  sprite = (struct EffectSprite *) allocSpriteObject();
  if (sprite == NULL) goto Lend;
  arg->sprite = (u32) sprite;
  allocWorkSlot(arg, 0, 0x48, 0);
  if (arg->owner == 0) goto Lend;
  gfxTable = D_0810225C;
  kindPtr = (u8 *)arg + 0x4C;
  sprite->gfxBase = gfxTable[*kindPtr];
  owner = (struct OwnerEffect *) arg->owner;
  work = ((u8 *) owner) + 0x34;
  installUpdateHandler(arg, owner, &releaseActorEffectSubObject);
  owner->kind = 0x64;
  slot = findKindIndex();
  owner->slot = slot;
  if ((slot << 16) >= 0) goto Lcont;
Lend:
  sub_080C31E0(arg, arg->failCb);
  return;
Lcont:
  sprite->gfxFlags = sprite->gfxFlags | gMainWorkspace.flags;
  initSpriteFromTemplate(sprite, work, D_08102264[*kindPtr], 6);
  setObjectAnimation(sprite, work, D_08102258[*kindPtr], 0);
  arg->flags = arg->flags | 0x1000;
  i = arg->counter;
  arr = (u16 *)arg;
  ((u8 *)(&arr[i]))[0x19] = 0;
  {
    u32 *pbb0 = &gMainObjTimerCallbacks;
    stepBase = ((u8 *)arg) + 0x18;
    sub_080C31E4(stepBase, ((u8 *)arg) + 0x22, *pbb0);
  }
  i = arg->counter;
  arr = (u16 *)arg;
  ((u8 *)(&arr[i]))[0x19] = ((u8 *)(&arr[i]))[0x19] + 1;
  i = arg->counter;
  arr = (u16 *)stepBase;
  new_var = &arr[i];
  v = ((u8 *)new_var)[0];
  fn = *((u32 *)(((u8 *)arg->stepHandlerTable) + (v * 4)));
  sub_080C31E0(arg, fn);
}
