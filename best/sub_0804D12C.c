extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, u32);
extern void sub_08015914(void);
extern void sub_0804D744(void);
extern u8 gSpriteAnimDataTable[];
extern u8 gSpriteKindTable[];
extern int D_080CF9CC[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
struct Entity
{
  u8 _0[0xAC];
  u32 ac;
};
struct Work
{
  u8 _0[4];
  u16 f4;
  u8 _6[2];
  u32 f8;
  u32 fC;
  u32 f10;
  u32 f14;
  u32 f18;
  s16 f1C;
  u8 _1E[4];
  s16 f22;
  u32 f24;
  u32 f28;
  u8 _2C[0x1C];
  u32 f48;
};
struct Part
{
  u8 f0;
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
  u16 f14;
};
inline static u8 *inline_fn(u8 *arg0, int arg1)
{
  return arg0 + arg1;
}

void sub_0804D12C(void *arg0)
{
  u8 *__base_gMainWorkspace;
  u8 *obj = (u8 *) arg0;
  u8 *sprite;
  struct Work *work;
  u8 *anim;
  u32 *r8;
  s32 kindIndex;
  u32 v;
  r8 = *((u32 **) (obj + 0xAC));
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  *((void **) (((u8 *) arg0) + 0x38)) = sprite;
  allocWorkSlot(obj, 0, 0x50, 0);
  work = *((struct Work **) inline_fn(obj, 0x3C));
  if (work == NULL)
  {
    goto fail;
  }
  do
  {
    anim = inline_fn((u8 *) work, 0x34);
    work->f24 = *((u32 *) inline_fn(obj, 0x24));
    *((u32 *) inline_fn(obj, 0x24)) = (u32) sub_0804D744;
    work->f1C = 0x4E;
    {
      u8 *kt = gSpriteKindTable;
      work->f18 = *((s16 *) inline_fn(inline_fn(kt, 0x4E * 0x14), 2));
    }
  }
  while (0);
  work->f8 = ((u32) (*((s16 *) inline_fn((u8 *) r8, 4)))) << 16;
  work->fC = ((u32) (*((s16 *) inline_fn((u8 *) r8, 6)))) << 16;
  kindIndex = findKindIndex(0x4E);
  work->f22 = (s16) kindIndex;
  if ((kindIndex + 1) <= 0)
  {
    goto fail2;
  }
  work->f4 = 0x10;
  initSpriteGraphics(sprite, anim, ((s32) gSpriteAnimDataTable) + (work->f1C * 0xC));
  {
    struct Part *p = allocEffectPart();
    work->f28 = (u32) p;
    if (p == NULL)
    {
      goto fail2;
    }
    p->f1 = 0;
    p->f2 = 8;
    p->f3 = 1;
    {
      u8 *kt = gSpriteKindTable;
      p->f4 = *((u16 *) inline_fn(kt, 0x4E * 0x14));
      p->f6 = D_080CF9CC[0];
      p->f8 = D_080CF9CC[1];
      p->fA = D_080CF9CC[2];
      p->fC = D_080CF9CC[3];
      p->fE = *((u16 *) inline_fn(inline_fn(kt, 0x4E * 0x14), 4));
    }
    p->f10 = (u32) sprite;
    p->f14 = 0;
  }
  {
    volatile int g = *((u16 *) sprite);
    short bits = (u32) (g & 0xC00);
    s16 slot = work->f22;
    bits = (((slot << 6) + 0x200) | (((u32) (((u16) slot) + 8)) << 12)) | bits;
    *((u16 *) sprite) = (u16) bits;
    __base_gMainWorkspace = gMainWorkspace;
    *((u16 *) sprite) = (u16) (bits | (*((u16 *) inline_fn(__base_gMainWorkspace, 0x18C2))));
  }
  *((u32 *) inline_fn(sprite, 0x1C)) = 0x8000000A;
  {
    u8 *ws = __base_gMainWorkspace;
    u32 idx = (((u32) (*inline_fn(ws, 0x18A8))) + 1) * 0x40;
    u8 *cam = gCameraState;
    *((u32 *) inline_fn(sprite, 0x14)) = work->f8 - (((*((u32 *) inline_fn(inline_fn(cam, 0x1278), idx))) + 0x8000) & 0xFFFF0000);
    idx = (((u32) (*inline_fn(ws, 0x18A8))) + 1) * 0x40;
    *((u32 *) inline_fn(sprite, 0x18)) = work->fC - (((*((u32 *) inline_fn(inline_fn(cam, 0x127C), idx))) + 0xFFFF8000) & 0xFFFF0000);
  }
  work->f48 = (u32) allocEffectPart();
  if (work->f48 == 0)
  {
    goto fail2;
  }
  return;
  fail2:
  sub_080C31E0(obj, *((u32 *) inline_fn(obj, 0x24)));

  return;
  fail:
  sub_080C31E0(obj, *((u32 *) inline_fn(obj, 0x24)));

  return;
}

