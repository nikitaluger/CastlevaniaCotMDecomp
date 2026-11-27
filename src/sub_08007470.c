extern s32 updateObjectTree(void *);
extern s32 sub_080C31E0(s32, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
void sub_08007470(u8 *arg0)
{
  u8 *r4;
  u8 *r6;
  u8 *r7;
  u8 *r5;
  u8 *r8;
  u8 *r2;
  u8 *r0;
  void *t;
  r6 = arg0;
  r4 = (u8 *) 0x02025FF0;
  updateObjectTree(*((void **) (r4 + 0x1854)));
  r7 = r4 + 0x1860;
  updateObjectTree(*((void **) r7));
  r5 = r4 + 0x1894;
  *((u32 *) r5) += 1;
  r8 = r4 + 0x1888;
  updateObjectTree(*((void **) r8));
  if ((*((s32 *) (r4 + 0x14C0))) >= 0)
  {
    struct 
    {
      u8 _[8];
      u16 x;
    } *p = (void *) 0x03000830;
    p->x += 2;
    if ((p->x & 0xFFFF) != 0x10)
    {
      return;
    }
  }
  r2 = r4 + 0x14B8;
  r0 = r4 + 0x14B4;
  *((u32 *) r2) = ((*((u32 *) r0)) & 0x0F) | 0x80;
  updateObjectTree(*((void **) (r4 + 0x184C)));
  updateObjectTree(*((void **) (r4 + 0x185C)));
  updateObjectTree(*((void **) r7));
  *((u32 *) r5) += 1;
  updateObjectTree(*((void **) (r4 + 0x1864)));
  t = *((void **) (r4 + 0x1858));
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  t = *((void **) (r4 + 0x1868));
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  t = *((void **) (r4 + 0x186C));
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  t = *((void **) (r4 + 0x1870));
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  t = *((void **) (r4 + 0x1874));
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  t = *((void **) (r4 + 0x1878));
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  t = *((void **) (r4 + 0x187C));
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  t = *((void **) (r4 + 0x1880));
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  t = *((void **) r8);
  sub_080C31E0((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
  *((u8 *) ((r6 + ((*((s16 *) (r6 + 0x22))) * 2)) + 0x19)) = 0;

  {
    u32 *rr = (u32 *) 0x08671BD0;
    sub_080C31E8(r6 + 0x18, r6 + 0x22, 1, *rr);
  }
}
