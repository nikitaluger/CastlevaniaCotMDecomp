extern struct 
{
  u8 _0[0x18C2];
  u16 w;
} gMainWorkspace;
extern u32 gMainObjTimerCallback[];
struct Half2
{
  u8 _0[2];
  u16 f;
};
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, s32);
extern s32 findKindIndex(void);
extern void _call_via_r1(void *, void *);
extern void _call_via_r2(void *, void *, u32);
void sub_080B943C(u8 *arg0)
{
  u8 *alloc = allocSpriteObject();
  u8 *p;
  u8 *r7;
  u8 *r8;
  u8 *parg;
  s32 t;
  u32 i;
  u8 *q;
  if (alloc == NULL)
  {
    _call_via_r1(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  *((u32 *) (arg0 + 0x38)) = (u32) alloc;
  allocWorkSlot(arg0, 0, 0x120, 0);
  if ((*((u8 **) (arg0 + 0x3C))) == NULL)
  {
    _call_via_r1(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  *((u32 *) (alloc + 0x1C)) = *((u32 *) (arg0 + 0x5C));
  r7 = alloc + 0x2A;
  *r7 &= 0xBF;
  p = *((u8 **) (arg0 + 0x3C));
  r8 = p + 0x48;
  installUpdateHandler(arg0, p, 0x08097DC9);
  *((u16 *) (p + 0x1C)) = 0x67;
  t = findKindIndex();
  *((u16 *) (p + 0x22)) = t;
  if ((t << 16) < 0)
  {
    _call_via_r1(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  t = *((s16 *) (p + 0x22));
  t = t << 6;
  t += 0x200;
  t &= 0xFC0;
  *((u16 *) alloc) = (u16) t;
  *((u16 *) alloc) = (u16) (t | (&gMainWorkspace)->w);
  {
    u16 w = *((u16 *) (alloc + 2));
    w |= 0x400;
    *((u16 *) (alloc + 2)) = w;
  }
  *((u32 *) (p + 0x48)) = 0;
  *((u32 *) (r8 + 4)) = (*((u32 *) (arg0 + 0x4C))) - 1;
  *((u32 *) (alloc + 0x24)) = 0x0841EB04;
  i = 0;
  r8 = (u8 *) (&gMainObjTimerCallback);
  alloc = arg0 + 0x18;
  parg = arg0 + 0x22;
  {
    u8 *dst = p + 0x110;
    u8 *src = r7;
    for (; i < 16; i++)
    {
      dst[i] = *src;
    }

  }
  (*((struct Half2 *) arg0)).f |= 0x1000;
  q = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
  *((u8 *) (q + 0x19)) = 0;
  _call_via_r2(alloc, parg, *((u32 *) r8));
  ;
  *((u8 *) (((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0))) + 0x19)) += 1;
  {
    s32 idx = (*((s16 *) (arg0 + 0x22))) * 2;
    u8 b = *(alloc + idx);
    void **tbl = *((void **) (arg0 + 0x14));
    void *fn = tbl[b];
    _call_via_r1(arg0, fn);
  }
}
