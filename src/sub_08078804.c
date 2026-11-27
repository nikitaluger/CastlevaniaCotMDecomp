/* Spawn/init this entity's AI: allocate a small child record, fill its
 * parameters from global tables, install callbacks and run the first step. */
extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *a);
extern s16 scalePercentSaturate16(u16, s32);
extern void sub_08003A6C(void *a, s32 b, void *c);
extern void setDirectionVector(void *a, u8 b);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);
extern void sub_0808449C(void);
extern u8 gGameStatus[];
struct S25FF0 { u8 pad[0x1510]; u8 b1510; };
extern struct S25FF0 gMainWorkspace;
extern u8 D_080E4D44[];
struct AIChild
{
  u8 f0; u8 f1; u8 f2; u8 f3;
  u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE;
  u32 f10; u8 _14[2]; u16 f16; u16 f18;
};
void sub_08078804(u8 *entity)
{
  u8 *work = *((u8 **) (entity + 0x6C));
  u8 *state = work + 4;
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *paramTable = gGameStatus;
  struct AIChild *child = allocEffectPart();
  u8 *tbl;
  u8 *variantPtr;
  s32 *g;
  u8 *framePtr;
  *((struct AIChild **) (state + 0x2C)) = child;
  if (child == 0)
  {
    sub_0806D2D0(entity);
    return;
  }
  *((u32 *) (state + 0x30)) = 0;
  *((u32 *) (state + 0x34)) = 0;
  *((u32 *) (state + 0x38)) = 0;
  *((u32 *) (state + 0x3C)) = 0;
  child->f1 = gMainWorkspace.b1510 & 1;
  (*((struct AIChild **) (state + 0x2C)))->f2 = 2;
  (*((struct AIChild **) (state + 0x2C)))->f3 = 8;
  {
    u8 v;
    u8 zero = 0;
    (void) zero;
    (*((struct AIChild **) (state + 0x2C)))->f4 = paramTable[0x304];
    (*((struct AIChild **) (state + 0x2C)))->f6 = 4;
    (*((struct AIChild **) (state + 0x2C)))->f8 = 4;
    (*((struct AIChild **) (state + 0x2C)))->fA = 0;
    (*((struct AIChild **) (state + 0x2C)))->fC = 0;
  }
  (*((struct AIChild **) (state + 0x2C)))->fE = scalePercentSaturate16(*((u16 *) (paramTable + 0x2E2)), 0x32);
  (*((struct AIChild **) (state + 0x2C)))->f16 = 5;
  (*((struct AIChild **) (state + 0x2C)))->f18 = 0x54;
  (*((struct AIChild **) (state + 0x2C)))->f10 = (u32) sprite;
  *((u32 *) (state + 0x18)) = *((u32 *) (entity + 0x24));
  *((u32 *) (entity + 0x24)) = (u32) sub_0808449C;
  *((u32 *) (sprite + 0x24)) = 0x084D962C;
  {
    u8 *dst = work + 0x20;
    tbl = D_080E4D44;
    variantPtr = entity + 0x9C;
    sub_08003A6C(dst, 0, *((void **) (tbl + ((*((u32 *) variantPtr)) * 8))));
  }
  *((u32 *) (work + 4)) = *((u32 *) (entity + 0x7C));
  *((u32 *) (state + 4)) = *((u32 *) (entity + 0x8C));
  *((u32 *) (state + 0x40)) = 0x50000;
  {
    u8 bval = *((u8 *) ((tbl + ((*((u32 *) variantPtr)) * 8)) + 4));
    u8 *dst = work + 0x48;
    *dst = bval;
    setDirectionVector(state, *dst);
  }
  *((u32 *) (state + 0x48)) = 0x18;
  *(((u8 *) ((((s16) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity))) + 0x19) = 0;
  g = (s32 *) 0x08671BB0;
  framePtr = variantPtr - 0x84;
  sub_080C31E4(framePtr, entity + 0x22, (void *) (*g));
  {
    u8 *p = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
    *(u8 *)(p + 0x19) = (u8)(*(u8 *)(p + 0x19) + 1);
  }
  {
    s16 idx = *((s16 *) (entity + 0x22));
    u8 *p = framePtr + (idx * 2);
    sub_080C31E0(entity, *((void **) ((*((u32 *) (entity + 0x14))) + ((*p) * 4))));
  }
}
