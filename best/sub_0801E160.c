extern void setAnimationFrame(s32,  void *);
extern void sub_080C31E4(void *, void *, s32);
extern void *spawnBudgetedEffect(s32, s32);
extern s32 getSpriteFacingSign(s32);
extern u8 D_02025FF0[];
extern u32 *gMainObjTimerCallbacks;
struct __rows_script_2
{
  char pad[0x18];
  struct 
  {
    char p0[0x1];
    u8 m1;
  } e[1];
};
struct __rows_D_02025FF0_2
{
  char pad[0x1c];
  struct 
  {
    s16 m0;
  } e[1];
};
typedef struct 
{
  unsigned char pad_0[76];
  short field_4C;
  unsigned char pad_4E[6];
  short field_54;
  unsigned char pad_56[6];
  unsigned short field_5C;
  unsigned char pad_5E[14];
  int field_6C;
  unsigned char pad_70[12];
  short field_7C;
} __repair_record_obj;
void sub_0801E160(void *arg0)
{
  int flag;
int __repair_phase_flag;
  s16 __repair_narrow_0;
  u32 *pgMainObjTimerCallbacks;
  u32 *__repair_probe;
  s32 sum;
  u8 *script = (u8 *) arg0;
  s32 parent = *((s32 *) (script + 0x38));
  u8 *motion = *((u8 **) (script + 0x3C));
  u8 *anim = motion + 0x34;
  u8 *state = motion + 0x48;
  setAnimationFrame(parent,  anim);
  do
  {
    if (((*((s16 *) (state + 0x28))) <= 0) && ((*((s16 *) (state + 8))) <= 0))
    {
u32 *__branch_pgMainObjTimerCallbacks;

      void **slot = (void **) (motion + 0x58);
      s32 i;
      for (i = 5; i >= 0; i--)
      {
        if ((*slot) != 0)
        {
          u16 *p = (u16 *) (((u8 *) (*slot)) + 0x5C);
          *p |= 1;
          *slot = 0;
        }
        slot++;
      }

      {
        __repair_narrow_0 = *((s16 *) (script + 0x22));
        __branch_pgMainObjTimerCallbacks = gMainObjTimerCallbacks;
        ((struct __rows_script_2 *) ((u8 *) arg0))->e[__repair_narrow_0].m1 = (__repair_probe = __branch_pgMainObjTimerCallbacks, 0);
      }
      sub_080C31E4(script + 0x18, script + 0x22, (s32) (*__repair_probe));
      return;
    }
  }
  while (0);
  {
    s32 v;
    void *obj;
    s32 r5;
    v = *((s32 *) (D_02025FF0 + 0x189C));
    if ((v / 2) & 1)
    {
      *((s32 *) state) = 0x10000;
    }
    __repair_phase_flag = (*((u16 *) (state + 8))); *((u16 *) (state + 8)) = __repair_phase_flag - 1;
    if (((s16) (*((u16 *) (state + 8)))) >= 0)
    {
      return;
    }
    r5 = 6 - (*((s16 *) (state + 0x28)));
    if ((*((s16 *) (state + 0x2A))) == 0)
    {
      obj = spawnBudgetedEffect(*((s32 *) (D_02025FF0 + 0x1870)), 0x96);
    }
    else
    {
      obj = spawnBudgetedEffect(*((s32 *) (D_02025FF0 + 0x1870)), 0x97);
    }
    sum = state + 0x10;
    *((void **) (sum + (r5 * 4))) = obj;
    if (obj == 0)
    {
      goto fail;
    }
    if ((*((s16 *) (state + 0x2A))) == 0)
    {
      s32 sign = getSpriteFacingSign((s32) script);
      if (sign < 0)
      {
        s32 x = *((s16 *) ((((u8 *) D_02025FF0) + 0x2C) + (r5 * 2)));
        s32 y = ((struct __rows_D_02025FF0_2 *) D_02025FF0)->e[r5].m0;
        s32 tmp = (x << 16) + 0x8000;
        s32 tmp2 = ((0xF0 - y) << 16) + 0x8000;
        flag = tmp < 0;
        if (flag)
        {
          tmp += 0xFFFF;
        }
        __repair_narrow_0 = (s16) (tmp >> 16);
        ((__repair_record_obj *) obj)->field_4C = __repair_narrow_0;
        if (tmp2 < 0)
        {
          tmp2 += 0xFFFF;
        }
        ((__repair_record_obj *) obj)->field_54 = (s16) (tmp2 >> 16);
      }
      else
      {
        s32 x = (*(&((struct __rows_D_02025FF0_2 *) D_02025FF0)->e[r5])).m0;
        s32 y = *((s16 *) ((((u8 *) D_02025FF0) + 0x2C) + (r5 * 2)));
        s32 tmp = (x << 16) + 0x8000;
        s32 tmp2 = ((0xF0 - y) << 16) + 0x8000;
        if (tmp < 0)
        {
          tmp += 0xFFFF;
        }
        flag = (s16) (tmp >> 16);
        ((__repair_record_obj *) obj)->field_4C = flag;
        if (tmp2 < 0)
        {
          tmp2 += 0xFFFF;
        }
        ((__repair_record_obj *) obj)->field_54 = (s16) (tmp2 >> 16);
      }
    }
    else
    {
      s32 sign = getSpriteFacingSign((s32) script);
      (void) sign;
    }
    ((__repair_record_obj *) obj)->field_7C = (s16) r5;
    ((__repair_record_obj *) obj)->field_5C = 0x10;
    ((__repair_record_obj *) obj)->field_6C = (s32) arg0;
    *((u16 *) (state + 8)) = 10;
    *((s16 *) (state + 0x28)) = (*((s16 *) (state + 0x28))) - 1;
    if ((*((s16 *) (state + 0x28))) == 0)
    {
      sum = state + 8;
      *((u16 *) sum) = 20;
    }
    return;
    fail:
    {
      void **slot = (void **) (motion + 0x58);
      s32 i;
      for (i = 5; i >= 0; i--)
      {
        do { do { if ((*slot) != 0)
        {
          u16 *p = (u16 *) (((u8 *) (*slot)) + 0x5C);
          *p |= 1;
          *slot = 0;
        } } while (0); } while (0);
        slot++;
      }

      {
        s16 step = *((s16 *) (script + 0x22));
        ((struct __rows_script_2 *) script)->e[step].m1 = 0;
      }
      pgMainObjTimerCallbacks = gMainObjTimerCallbacks;
      sub_080C31E4(script + 0x18, script + 0x22, (s32) (*pgMainObjTimerCallbacks));
    }

  }
}

