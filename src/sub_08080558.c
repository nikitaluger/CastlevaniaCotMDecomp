extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern s32 scalePercentSaturate16(s32, s32);
extern void sub_08003A6C(void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern u8 gGameStatus[];
struct S_FF0 { u8 _0[0x1510]; u8 f1510; };
extern struct S_FF0 gMainWorkspace;
extern u8 D_080E574C[];
extern u8 D_080E576C[];
extern u32 gMainObjTimerCallbacks;
inline u32 inline_fn(u8 *arg0, u32 arg1) { return ((u32) arg0[arg1]) << 5; }
static inline u8 and1(u8 b) { u32 m = 1; m &= b; return (u8)m; }

void sub_08080558(void *arg0)
{
  void *r8; void *r6; void *r5; s32 r3; u32 idx; u8 *t4_2;
  u8 *ptr; u8 *base; u8 *tbl; s32 z; s32 i2;
  r8 = *((void **) (((u8 *) arg0) + 0x6C));
  r6 = ((u8 *) r8) + 4;
  r5 = *((void **) (((u8 *) arg0) + 0x38));
  base = gGameStatus;
  r3 = (s32) allocEffectPart();
  *((s32 *) (((u8 *) r6) + 0x2C)) = r3;
  if (r3 == 0) { sub_0806D2D0(arg0); return; }
  *((s32 *) (((u8 *) r6) + 0x30)) = 0;
  *((s32 *) (((u8 *) r6) + 0x34)) = 0;
  *((s32 *) (((u8 *) r6) + 0x38)) = 0;
  *((s32 *) (((u8 *) r6) + 0x3C)) = 0;
  tbl = D_080E574C;
  idx = *((u32 *) (((u8 *) arg0) + 0x9C));
  idx = inline_fn(tbl, idx);
  t4_2 = D_080E576C + idx;
  ptr = (u8 *) r3;
  ptr[1] = and1(gMainWorkspace.f1510);
  *((u8 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 2)) = 2;
  *((u8 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 3)) = 8;
  z = 0;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 4)) = base[0x304] | z;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 6)) = *((u16 *) t4_2);
  *((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 8)) = *((u16 *) (t4_2 + 2));
  *((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 0x0A)) = 0;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 0x0C)) = 0;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 0x0E)) = (u16) scalePercentSaturate16(*((u16 *) (base + 0x2E2)), *((u16 *) (t4_2 + 4)));
  *((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 0x16)) = 5;
  *((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 0x18)) = *((u16 *) (t4_2 + 0x1C));
  *((void **) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 0x10)) = r5;
  *((void **) (((u8 *) r6) + 0x18)) = *((void **) (((u8 *) arg0) + 0x24));
  *((void **) (((u8 *) arg0) + 0x24)) = (void *) 0x0808449D;
  *((s32 *) (((u8 *) r5) + 0x24)) = *((s32 *) (t4_2 + 0x08));
  sub_08003A6C(((u8 *) r8) + 0x20, 0, *((s32 *) (t4_2 + 0x0C)));
  *((s32 *) (((u8 *) r5) + 0x14)) = *((s32 *) (t4_2 + 0x10));
  *((s32 *) (((u8 *) r5) + 0x18)) = 0xFFD00000;
  *((s32 *) (((u8 *) r6) + 0x08)) = *((s32 *) (t4_2 + 0x14));
  *((s32 *) (((u8 *) r6) + 0x0C)) = *((s32 *) (t4_2 + 0x18));
  {
    u8 *pp = (u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + ((u32) arg0));
    pp[0x19] = (u8) z;
  }
  {
    u32 *script = &gMainObjTimerCallbacks;
    u8 *t4_3 = ((u8 *) arg0) + 0x18;
    sub_080C31E4(t4_3, ((u8 *) arg0) + 0x22, *script);
    {
      u8 *pp2;
      i2 = *((s16 *) (((u8 *) arg0) + 0x22));
      i2 = i2 * 2;
      pp2 = (u8 *) (((u32) i2) + ((u32) arg0));
      pp2[0x19] = (u8) (pp2[0x19] + 1);
    }
    {
      u8 *q = t4_3 + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2);
      u8 byte = *q;
      u32 ptrv = *((u32 *) (((u8 *) arg0) + 0x14));
      u32 val = *((u32 *) (ptrv + (byte * 4)));
      sub_080C31E0(arg0, (void *) val);
    }
  }
}
