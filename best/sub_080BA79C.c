void sub_080BB984(void *, void *);
void sub_080BBA08(void *);
void sub_080BB940(void *, void *);
s32 sub_08098754(void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
void sub_080BA760(void *arg0);
void sub_080BA79C(void *arg0)
{
  u8 *self = (u8 *) arg0;
  void *r0 = *((void **) (((u8 *) arg0) + 0x3C));
  sub_080BB984(r0, ((u8 *) r0) + 0x48);
  sub_080BBA08(arg0);
  if ((*((u8 *) ((((u8 *) arg0) + (2 * (*((s16 *) (((u8 *) arg0) + 0x22))))) + 0x19))) == 0x18)
  {
    *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
    {
      s32 *nv;
      sub_080C31E4(((u8 *) arg0) + 0x18, self + 0x22, *nv);
      nv = (s32 *) 0x08671BB0;
    }
  }
}

void sub_080BA7DA(void *arg0);
void sub_080BA644(void *arg0);
