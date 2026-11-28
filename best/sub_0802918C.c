#define POSX (((s16 *)*(u32 *)(ctx + 4))[0])
#define POSY (((s16 *)*(u32 *)(ctx + 4))[1])
extern s32 isOutsideCameraBounds(s32, s32);
extern s32 sub_08014090(s32);
extern u32 scaleByRandom(u32);
extern s32 sub_08016830(s32);
extern s32 absYFromFocus(s32);
extern void *spawnBudgetedEffect(s32, s32);
extern void allocWorkSlot(void *, s32, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 rollProbability(s32);
extern s32 signOf(s32);
extern s32 sub_08065420(s32);
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u8 D_080CE958[];
struct MwView
{
  u8 _0[0x1750];
  s32 a1750;
  u8 _1754[0x1870 - 0x1754];
  s32 a1870;
  u8 _1874[0x18A8 - 0x1874];
  u8 frameCounter;
};
struct ScrollRow
{
  s32 x;
  u8 _4[0x3c];
};
struct ScrollTable
{
  u8 _0[0x1278];
  struct ScrollRow rows[16];
};
inline static int inline_fn(int arg0)
{
  return arg0 + ((struct MwView *) gMainWorkspace)->a1750;
}

void sub_0802918C(u8 *obj)
{
  u8 *ctx = *((u8 **) (obj + 0xac));
  u8 *work = *((u8 **) (obj + 0x3c));
  s32 v;
  s32 sc;
  void *newObj;
  u8 *newCtx;
  s32 scroll;
  if (isOutsideCameraBounds(POSX << 16, POSY << 16) == 1)
  {
    ((void (*)(void *)) (*((u32 *) (obj + 0x24))))(obj);
    return;
  }
  if (sub_08014090(*((s16 *) (work + 0))) == 1)
  {
    return;
  }
  newObj = (void *) (*((u16 *) (work + 2))); v = ((u32) newObj) - 1;
  *((u16 *) (work + 2)) = v;
  if ((v << 16) > 0)
  {
    return;
  }
  *((u16 *) (work + 2)) = scaleByRandom(0x8d) + 0xb4;
  if (sub_08016830(0xb7) > 3)
  {
    return;
  }
  if (absYFromFocus(POSY << 16) > (0xb4 << 15))
  {
    sc = *((s16 *) (work + 2));
    *((u16 *) (work + 2)) = sc / 0x10;
    return;
  }
  newObj = spawnBudgetedEffect(((struct MwView *) gMainWorkspace)->a1870, 0xb7);
  if (newObj == 0)
  {
    return;
  }
  allocWorkSlot(newObj, 0, 8, 7);
  newCtx = *((u8 **) (newObj + 0xac));
  if (newCtx == 0)
  {
    ((void (*)(void *)) (*((u32 *) (newObj + 0x24))))(newObj);
    return;
  }
  *((u16 *) newCtx) = 0;
  *((u32 *) (newCtx + 4)) = (u32) D_080CE958;
  if (absXFromFocus(POSX << 16) <= 0x17FFFF)
  {
    if (rollProbability(0x1388) != 1)
    {
      goto fallback;
    }
    scroll = ((struct ScrollTable *) gCameraState)->rows[((struct MwView *) gMainWorkspace)->frameCounter + 1].x + 0xFFF08000;
  }
  else
  {
    if (signOf(POSX << 16) <= 0)
    {
      goto fallback;
    }
    scroll = ((struct ScrollTable *) gCameraState)->rows[((struct MwView *) gMainWorkspace)->frameCounter + 1].x + 0xFFF08000;
    goto join;
    fallback:
    scroll = ((struct ScrollTable *) gCameraState)->rows[((struct MwView *) gMainWorkspace)->frameCounter + 1].x + 0x01008000;

  }
  join:
  {
    s32 a = inline_fn(sub_08065420(0x140001) + 0xFFF60000);
    s32 b = scroll;
    s32 bHi;
    s32 aHi;
    bHi = b / 0x10000;
    *((u16 *) (newObj + 0x4c)) = (u16) bHi;
    aHi = a / 0x10000;
    *((u16 *) (newObj + 0x54)) = (u16) aHi;
  }

}

