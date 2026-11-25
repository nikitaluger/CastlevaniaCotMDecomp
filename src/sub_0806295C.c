extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern void _call_via_r1(void *, u32);
extern void _call_via_r2(void *, void *, u32);
void *sub_08016190(void);
struct Slot
{
  u8 _00;
  u8 f01;
  u8 f02;
  u8 f03;
  u16 f04;
  u8 _06[8];
  u16 f0E;
  void *f10;
  u8 _14[2];
  u16 f16;
  u16 f18;
};
struct P
{
  u8 _00[4];
  u32 f04;
  u8 _08[0x10C];
  u32 f114;
  u32 f118;
  u8 _11C[8];
  u8 f124;
  u8 f125;
  u8 f126;
  u8 _127[9];
  struct Slot *f130;
  struct Slot *f134;
};

/* Effect setup: configure two draw-parameter words from the global settings,
 * register this object's sprite with the global system, allocate two effect
 * slots and fill them with sprite/animation parameters, then dispatch the
 * current command-script step; if either slot allocation fails, fall back to
 * the object's default handler at +0x24. */
void sub_0806295C(void *arg0)
{
  u8 *obj = (u8 *) arg0;
  struct P *block = (struct P *) (*((u32 *) (obj + 0x6C)));
  u8 *raw;
  u8 *fields = ((u8 *) block) + 4;
  void *sprite = *((void **) (obj + 0x38));
  u8 *cfg = D_02025368;
  s32 zero;
  u8 *sys;
  u32 offA;
  u32 offB;
  struct Slot *slot;
  u32 *handler;
  raw = (u8 *) block;
  *((u32 *) (raw + 4)) = 0x780000;
  *((u32 *) (fields + 4)) = 0x7F0000;
  sys = D_02025FF0;
  *((void **) (sys + 0x171C)) = sprite;
  *((void **) (sys + 0x1720)) = fields;
  *((void **) (sys + 0x1724)) = fields;
  offA = 0x8A << 1;
  *((u32 *) (((u8 *) block) + offA)) = (zero = 0);
  offB = 0x8C << 1;
  *((u32 *) (((u8 *) block) + offB)) = zero;
  block->f124 = cfg[0x3C4];
  block->f125 = cfg[0x3C5];
  block->f126 = cfg[0x3C6];
  slot = (struct Slot *) sub_08016190();
  block->f130 = slot;
  if (slot == 0)
  {
    if (block->f130)
    {
      _call_via_r1(obj, (u32) (*((void **) (obj + 0x24))));
      return;
    }
    else
    {
      _call_via_r1(obj, (u32) (*((void **) (obj + 0x24))));
      return;
    }
  }
  slot->f02 = 1;
  block->f130->f03 = 0x80;
  block->f130->f04 = 0;
  block->f130->f0E = 0xA;
  block->f130->f10 = sprite;
  block->f130->f16 = 0x1E;
  slot = (struct Slot *) sub_08016190();
  block->f134 = slot;
  if (slot == 0)
  {
    if (block->f134)
    {
      _call_via_r1(obj, (u32) (*((void **) (obj + 0x24))));
      return;
    }
    else
    {
      _call_via_r1(obj, (u32) (*((void **) (obj + 0x24))));
      return;
    }
  }
  block->f134->f01 = 0;
  block->f134->f02 = 1;
  block->f134->f03 = 8;
  block->f134->f04 = 0;
  block->f134->f0E = *((u16 *) (cfg + (0xB8 << 2)));
  block->f134->f10 = sprite;
  block->f134->f16 = 0x1E;
  block->f134->f18 = 0;
  *((u8 *) ((obj + ((*((s16 *) (obj + 0x22))) * 2)) + 0x19)) = 0;
  handler = (u32 *) 0x08671BB0;
  _call_via_r2(obj + 0x18, obj + 0x22, *handler);
}
