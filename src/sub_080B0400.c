/* Spawn an effect actor: allocate its graphics object and work state, install
 * the cleanup callback, seed a parameter sub-object from the spawn tables and
 * advance the actor's script. */
#define PARAM_STRIDE(i) ((((u32)((i) << 2)) + (u32)(i)) << 3) /* i * 0x28 */

struct EffectWork {
  u8 _0[8]; u32 f8; u32 fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22;
  u8 _24[4]; struct EffectChild *f28; u8 _2C[0x1C]; u32 f48;
};
struct EffectChild {
  u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10;
};
struct ParamRecord { u8 _0[0x14]; u16 f14; u16 f16; u8 _18[0x10]; };
extern u8 gEffectGfxTable[];     /* per-type spawn parameters, 0x28-byte records */
extern u16 D_081026A4[];    /* parameter word defaults for the sub-object */
extern void *gMainObjTimerCallbacks;    /* script step table */
void *allocSpriteObject(void);
void allocWorkSlot(void *, s32, s32, s32);
void installUpdateHandler(void *, void *, void *);
void *allocEffectPart(void);
void sub_080B05CC(void);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);
void sub_080B0400(u8 *actor)
{
  struct EffectWork *work;
  void *gfx;
  u8 zero;
  u16 *defaults;
  u8 *scriptPtr;
  void **scriptTable;
  u8 *scriptEntry;
  u8 *fieldPtr;
  u8 *params;

  gfx = allocSpriteObject();
  if (gfx == NULL) goto fail;
  *((u32 *) (actor + 0x38)) = (u32) gfx;
  allocWorkSlot(actor, 0, 0x48, 0);
  if ((*((u32 *) (actor + 0x3C))) == 0) goto fail;
  {
    u32 mask = 0xBF & (*((u8 *) (((u8 *) gfx) + 0x2A)));
    zero = 0;
    *((u8 *) (((u8 *) gfx) + 0x2A)) = (u8) mask;
  }
  work = (struct EffectWork *) (*((u8 **) (actor + 0x3C)));
  installUpdateHandler(actor, (u8 *) work, sub_080B05CC);
  zero = 0;
  work->f1C = 0x64;
  *((u32 *) (((u8 *) work) + 0x08)) = zero;
  *((u32 *) (((u8 *) work) + 0x0C)) = zero;
  defaults = D_081026A4;
  work->f28 = allocEffectPart();
  if (work->f28 != NULL) goto cont;
  fail:
  sub_080C31E0(actor, *((void **) (actor + 0x24)));
  return;
  cont:
  work->f28->f1 = zero;
  work->f28->f2 = 8;
  work->f28->f3 = 1;
  work->f28->f4 = ((struct ParamRecord *) ((params = gEffectGfxTable) + PARAM_STRIDE(*((s16 *) (((u8 *) work) + 0x1C)))))->f14;
  work->f28->f6 = defaults[0];
  work->f28->f8 = defaults[1];
  work->f28->fA = defaults[2];
  work->f28->fC = defaults[3];
  work->f28->fE = ((struct ParamRecord *) (params + PARAM_STRIDE(*((s16 *) (((u8 *) work) + 0x1C)))))->f16;
  work->f28->f10 = (u32) gfx;
  fieldPtr = actor + 0x4C;
  *fieldPtr = zero;
  fieldPtr += 4;
  *fieldPtr = zero;
  *((u16 *) (actor + 2)) |= 0x1000;
  *((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x19)) = zero;
  scriptTable = &gMainObjTimerCallbacks;
  scriptPtr = actor;
  scriptPtr += 0x18;
  sub_080C31E4(scriptPtr, actor + 0x22, (s32) (*scriptTable));
  *((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x19)) += 1;
  scriptEntry = scriptPtr + (((u32) (*((s16 *) (actor + 0x22)))) * 2);
  sub_080C31E0(actor, *((void **) ((*((u8 **) (actor + 0x14))) + ((*((u8 *) scriptEntry)) * 4))));
}
