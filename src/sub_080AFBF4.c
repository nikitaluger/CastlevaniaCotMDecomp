struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 gMainWorkspace;
struct E
{
  u8 _0;
  u8 f1;
  u8 f2;
  u8 f3;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  u16 fE;
  u32 f10;
};
struct P
{
  u8 _0[8];
  u32 f8;
  u32 fC;
  u8 _10[0xC];
  u16 f1C;     /* value looked up in the small id table */
  u8 _1E[4];
  u16 f22;     /* index returned by that lookup */
  u8 _24[4];
  struct E *f28;  /* child effect object */
  u8 _2C[0x1C];
  u32 f48;
};
struct TBL
{
  u16 f0;      /* first parameter loaded into the child effect */
  u8 _[2];
  u16 f4;      /* last parameter loaded into the child effect */
  u8 __[14];
};
extern struct TBL gSpriteKindTable[];
extern u16 D_0810269C[];
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void sub_080B05EC(void *, void *, u8, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_08097D90(void);

/* Creates and initializes the effect object for this entity: allocates the
 * child objects, fills their parameters from the effect table, marks the
 * entity's flags and dispatches the effect's callback. */
void sub_080AFBF4(u8 *entity)
{
  s32 objHandle;
  struct P *state;
  u8 *anim;
  int zero;
  u8 one;
  s32 tableIndex;
  u16 *values;
  struct E *effect;
  objHandle = (s32) allocSpriteObject();
  zero = 0;
  if (objHandle == zero)
  {
    goto fail;
  }
  *((u32 *) (entity + 0x38)) = objHandle;
  allocWorkSlot(entity, zero, 0x48, zero);
  if ((*((u32 *) (entity + 0x3C))) == zero)
  {
    goto fail;
  }
  *((u32 *) (objHandle + 0x1C)) = 0x33;
  state = (struct P *) (*((u8 **) (entity + 0x3C)));
  anim = ((u8 *) state) + 0x34;
  installUpdateHandler(entity, (u8 *) state, sub_08097D90);
  state->f1C = 0x64;
  tableIndex = findKindIndex(0x64);
  state->f22 = tableIndex;
  if ((tableIndex << 16) < zero)
  {
    goto fail;
  }
  *((u16 *) objHandle) |= gMainWorkspace.w;
  sub_080B05EC((void *) objHandle, anim, 0x38, 8);
  setObjectAnimation((void *) objHandle, anim, 0x37, zero);
  values = D_0810269C;
  effect = allocEffectPart();
  state->f28 = effect;
  if (effect != NULL)
  {
    goto cont;
  }
  fail:
  sub_080C31E0(entity, *((void **) (entity + 0x24)));

  return;
  cont:
  effect->f1 = 5;

  state->f28->f2 = 8;
  state->f28->f3 = (one = 1);
  state->f28->f4 = gSpriteKindTable[*((s16 *) (((u8 *) state) + 0x1C))].f0;
  state->f28->f6 = values[zero];
  state->f28->f8 = values[1];
  state->f28->fA = values[2];
  state->f28->fC = values[3];
  state->f28->fE = gSpriteKindTable[*((s16 *) (((u8 *) state) + 0x1C))].f4;
  state->f28->f10 = objHandle;
  *((u16 *) (entity + 2)) |= 0x1000;
  *((u16 *) (entity + 2)) |= 0x800;
  *((u32 *) (entity + 0x14)) = 0x080AFD11;
  *((u16 *) (entity + 0x22)) = one;
  sub_080C31E0(entity, 0x080AFD11);
}
