#ifndef M2C_DEFINES
#define M2C_DEFINES
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
long long sub_08015BA8(void *, s32, s32, s32, s32, s32 *, s32 *, u16 *, s32);
M2C_UNK sub_0801604C(M2C_UNK *);
M2C_UNK sub_080C31E8(void *, M2C_UNK *);
inline u16 *inline_fn(M2C_UNK *arg0, int arg1)
{
  return (u16 *) (((s8 *) arg0) + arg1);
}

s32 probeEntityCollision(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5)
{
  u16 sp14;
  M2C_UNK sp18;
  s32 *new_var;
  M2C_UNK sp2C;
  s32 sp4C;
  s32 sp54;
  s32 sp58;
  s32 sp5C;
  s32 sp60;
  s32 sp64;
  s32 sp68;
  unsigned int new_var6;
  s16 temp_r1;
  s16 temp_r1_3;
  int new_var4;
  s16 temp_r3;
  s16 temp_r3_2;
  s32 temp_r0;
  s32 temp_r0_2;
  s32 temp_r1_2;
  s32 temp_r2;
  void **new_var3;
  s8 *new_var5;
  s32 temp_r2_2;
  s32 sp50;
  s32 temp_r3_3;
  s32 temp_r4_2;
  u16 new_var2;
  void *temp_r4;
  void *var_r7;
  sp54 = arg0;
  sp58 = arg1;
  sp5C = arg2;
  sp60 = arg3;
  sp64 = (s32) ((u16) arg4);
  *((s32 *) (((s8 *) arg5) + 0x10)) = 0;
  *((s32 *) (((s8 *) arg5) + 0xC)) = (*((s32 *) (((s8 *) arg5) + 4)) = 0);
  *((s32 *) (((s8 *) arg5) + 8)) = 0;
  *inline_fn(arg5, 0) = 0U;
  temp_r4 = NULL;
  new_var3 = (void **) 0x0201E8A0;
  var_r7 = *new_var3;
  if (var_r7 == NULL)
  {
  }
  else
  {
    loop_2:
    if (sub_08015BA8(var_r7, sp54, sp58, sp5C, sp60, &sp4C, &sp50, &sp14, sp64) == 0)
    {
    }
    else
    {
      *inline_fn(&sp2C, 0) = (u16) sp64;
      temp_r4 = (s8 *) arg5;
      *((u16 *) (((s8 *) (&sp2C)) + 2)) = (u16) sp14;
      *((s32 *) (((s8 *) (&sp2C)) + 4)) = sp54;
      *((s32 *) (((s8 *) (&sp2C)) + 8)) = sp58;
      *((s32 *) (((s8 *) (&sp2C)) + 0xC)) = sp4C;
      *((s32 *) (((s8 *) (&sp2C)) + 0x10)) = sp50;
      new_var5 = (s8 *) (&sp2C);
      *((s32 *) (((s8 *) (&sp2C)) + 0x14)) = sp5C;
      *((s32 *) (((s8 *) (&sp2C)) + 0x18)) = sp60;
      *((M2C_UNK **) (new_var5 + 0x1C)) = &sp18;
      temp_r4 = *((void **) (((s8 *) var_r7) + 0xC));
      if ((*((s32 *) (((s8 *) temp_r4) + 0x9C))) == 0)
      {
        sub_0801604C(&sp2C);
      }
      else
      {
        sub_080C31E8(temp_r4, &sp2C);
      }
      if (temp_r4 == NULL)
      {
        *inline_fn(arg5, 0) = (u16) ((*((u16 *) (temp_r4 + 0))) | (*((u16 *) (((s8 *) (&sp18)) + 0))));
        *((s32 *) (temp_r4 + 4)) = (s32) (*((s32 *) (((s8 *) (&sp18)) + 4)));
        *((s32 *) (((s8 *) arg5) + 8)) = (s32) (*((s32 *) (((s8 *) (&sp18)) + 8)));
        goto block_34;
      }
      temp_r1 = *((s16 *) (((s8 *) var_r7) + 4));
      temp_r3 = *((s16 *) (((s8 *) var_r7) + 8));
      new_var4 = temp_r1 - temp_r3;
      temp_r0 = new_var4 << 0x10;
      temp_r1_2 = (temp_r1 + temp_r3) << 0x10;
      sp68 = ((*((s16 *) (((s8 *) var_r7) + 6))) + (*((s16 *) (((s8 *) var_r7) + 0xA)))) << 0x10;
      new_var6 = (s32) (*((s32 *) (temp_r4 + 4)));
      temp_r1_3 = *((s16 *) (((s8 *) temp_r4) + 4));
      temp_r3_2 = *((s16 *) (((s8 *) temp_r4) + 8));
      temp_r4_2 = (temp_r1_3 - temp_r3_2) << 0x10;
      new_var = (s32 *) (((s8 *) arg5) + 8);
      temp_r3_3 = (temp_r1_3 + temp_r3_2) << 0x10;
      temp_r0_2 = ((*((s16 *) (((s8 *) temp_r4) + 0xA))) + (*((s16 *) (((s8 *) temp_r4) + 6)))) << 0x10;
      if (sp5C > 0)
      {
        if (((s32) (*((s32 *) (((s8 *) (&sp18)) + 4)))) <= ((s32) (*((s32 *) (((s8 *) arg5) + 4)))))
        {
          goto block_13;
        }
      }
      else
        if (((s32) (*((s32 *) (((s8 *) (&sp18)) + 4)))) >= new_var6)
      {
        block_13:
        *((u16 *) (((s8 *) arg5) + 0)) = (u16) ((*((u16 *) (((s8 *) arg5) + 0))) | (*((u16 *) (((s8 *) (&sp18)) + 0))));

        *((s32 *) (((s8 *) arg5) + 4)) = *((s32 *) (((s8 *) (&sp18)) + 4));
      }
      if (sp60 > 0)
      {
        temp_r2 = *((s32 *) (((s8 *) (&sp18)) + 8));
        if (temp_r2 <= ((s32) (*((s32 *) (temp_r4 + 8)))))
        {
          *((u16 *) (((s8 *) arg5) + 0)) = (u16) ((*((u16 *) (((s8 *) arg5) + 0))) | (*((u16 *) (((s8 *) (&sp18)) + 0))));
          *new_var = temp_r2;
        }
      }
      else
      {
        new_var2 = *inline_fn(&sp18, 0);
        if (sp5C > 0)
        {
          if ((sp54 < temp_r0) && (sp54 < temp_r4_2))
          {
            sp58 = *((s32 *) (((s8 *) (&sp18)) + 8));
            if (sp68 > temp_r0_2)
            {
              if (temp_r0 <= temp_r4_2)
              {
                *((u16 *) (temp_r4 + 0)) = (u16) (((*inline_fn(arg5, 0)) | (*((u16 *) (((s8 *) (&sp18)) + 0)))) & 0xFF77);
                *((s32 *) (((s8 *) arg5) + 8)) = (s32) sp58;
                goto block_34;
              }
            }
            else
              if (temp_r0 < temp_r4_2)
            {
              goto block_32;
            }
          }
          else
          {
            goto block_32;
          }
        }
        else
          if (((sp5C < 0) && (sp54 >= temp_r1_2)) && (sp54 >= temp_r3_3))
        {
          if (sp68 > temp_r0_2)
          {
            if (temp_r1_2 >= temp_r3_3)
            {
              *((u16 *) (((s8 *) arg5) + 0)) = (u16) (((*inline_fn(arg5, 0)) | new_var2) & 0xFF77);
              *new_var = (s32) sp58;
              goto block_34;
            }
          }
          else
            if (temp_r1_2 > temp_r3_3)
          {
            goto block_32;
          }
        }
        else
        {
          block_32:
          temp_r2_2 = *((s32 *) (((s8 *) (&sp18)) - (-8)));

          if (temp_r2_2 >= ((s32) (*((s32 *) (temp_r4 + 8)))))
          {
            *((u16 *) (((s8 *) arg5) + 0)) = (u16) ((*((u16 *) (((s8 *) arg5) + 0))) | (*inline_fn(&sp18, 0)));
            *((s32 *) (((s8 *) arg5) + 8)) = temp_r2_2;
            block_34:
            temp_r4 = var_r7;

          }
        }
      }
    }

    var_r7 = *((void **) (((s8 *) var_r7) + 0x10));
    if (var_r7 != NULL)
    {
      goto loop_2;
    }
  }
  if ((*inline_fn(arg5, 0)) == 0)
  {
    return 0;
  }
  return 1;
}

