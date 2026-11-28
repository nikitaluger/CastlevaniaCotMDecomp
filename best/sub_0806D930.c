extern s32 sub_08061C78(void);
extern s32 divInt32(s32, s32);
extern s32 sub_080C3824(s32, s32);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 D_080E08C4[];
extern u8 D_080E0970[];
extern u8 D_080E0AB8[];
extern u8 D_080E0AC0[];
extern u8 D_080E4764[];
inline static int inline_fn(s32 arg0, u8 *arg1)
{
  return arg0 + (*((u16 *) (arg1 + 2)));
}

void sub_0806D930(u8 *arg0)
{
  u8 *base = gGameStatus;
  s16 idx = *((s16 *) (base + 0x8C));
  u8 *t = D_080E08C4 + (((idx * 8) + idx) * 4);
  u16 r4 = (*((u16 *) (arg0 + 0x38))) - 1;
  s32 r7;
  s32 r6;
  s32 r3v;
  s32 r2v;
  volatile int repair_scratch;
  u8 *p2;
  *((s32 *) (arg0 + 0x04)) = ((*((s32 *) (t + 0x00))) + ((*((s32 *) (t + 0x04))) * ((s32) r4))) + (((s32) base[0x3C5]) * 0xA0000);
  *((s32 *) (arg0 + 0x0C)) = ((*((s32 *) (t + 0x08))) + ((*((s32 *) (t + 0x0C))) * ((s32) r4))) + (((s32) base[0x3C6]) * 0xA0000);
  *((s16 *) (arg0 + 0x12)) = (((*((s16 *) (t + 0x12))) * ((s32) r4)) + (*((u16 *) (t + 0x10)))) + (((s32) base[0x3C4]) * 6);
  (void) (&r7);
  r7 = ((*((u16 *) (t + 0x16))) * ((s32) r4)) + (*((u16 *) (t + 0x14)));
  *((s16 *) (arg0 + 0x18)) = r7;
  r6 = ((*((u16 *) (t + 0x1A))) * ((s32) r4)) + (*((u16 *) (t + 0x18)));
  *((s16 *) (arg0 + 0x20)) = r6;
  (void) (&r3v);
  r3v = ((*((u16 *) (t + 0x1E))) * ((s32) r4)) + (*((u16 *) (t + 0x1C)));
  *((s16 *) (arg0 + 0x28)) = r3v;
  (void) (&r2v);
  r2v = ((*((u16 *) (t + 0x22))) * ((s32) r4)) + (*((u16 *) (t + 0x20)));
  *((s16 *) (arg0 + 0x30)) = r2v;
  *((s16 *) (arg0 + 0x1A)) = r7;
  *((s16 *) (arg0 + 0x22)) = r6;
  *((s16 *) (arg0 + 0x2A)) = r3v;
  *((s16 *) (arg0 + 0x32)) = r2v;
  repair_scratch = *((u8 *) (arg0 + 0x42));
  if (repair_scratch != 0)
  {
    u8 *e = D_080E0970 + ((*((u8 *) (arg0 + 0x42))) * 8);
    *((s16 *) (arg0 + 0x1A)) = r7 + (*((u16 *) (e + 0)));
    *((s16 *) (arg0 + 0x22)) = inline_fn(r6, e);
    *((s16 *) (arg0 + 0x2A)) = r3v + (*((u16 *) (e + 4)));
    *((s16 *) (arg0 + 0x32)) = r2v + (*((u16 *) (e + 6)));
  }
  repair_scratch = (int) (arg0 + 0x43);
  p2 = arg0 + 0x44;
  if ((*((u8 *) repair_scratch)) != 0)
  {
    u8 *e;
    if (((*((u8 *) repair_scratch)) == 0x17) && ((*p2) == 0x17))
    {
      e = D_080E0AB8;
    }
    else
    {
      e = D_080E0970 + ((*((u8 *) repair_scratch)) * 8);
    }
    *((s16 *) (arg0 + 0x1A)) = (*((s16 *) (arg0 + 0x1A))) + (*((u16 *) (e + 0)));
    *((s16 *) (arg0 + 0x22)) = (*((s16 *) (arg0 + 0x22))) + (*((u16 *) (e + 2)));
    *((s16 *) (arg0 + 0x2A)) = (*((s16 *) (arg0 + 0x2A))) + (*((u16 *) (e + 4)));
    *((s16 *) (arg0 + 0x32)) = (*((s16 *) (arg0 + 0x32))) + (*((u16 *) (e + 6)));
  }
  if ((*p2) != 0)
  {
    u8 *e;
    if ((*p2) == 0x18)
    {
      e = D_080E0AC0;
    }
    else
    {
      e = (void *) D_080E0970;
    }
    e = (void *) (((char *) e) + ((s32) ((*p2) * 8)));
    *((s16 *) (arg0 + 0x1A)) = (*((s16 *) (arg0 + 0x1A))) + (*((u16 *) (e + 0)));
    *((s16 *) (arg0 + 0x22)) = (*((s16 *) (arg0 + 0x22))) + (*((u16 *) (e + 2)));
    *((s16 *) (arg0 + 0x2A)) = (*((s16 *) (arg0 + 0x2A))) + (*((u16 *) (e + 4)));
    *((s16 *) (arg0 + 0x32)) = (*((s16 *) (arg0 + 0x32))) + (*((u16 *) (e + 6)));
  }
  *((s16 *) (arg0 + 0x1C)) = *((s16 *) (arg0 + 0x1A));
  *((s16 *) (arg0 + 0x24)) = *((s16 *) (arg0 + 0x22));
  *((s16 *) (arg0 + 0x2C)) = *((s16 *) (arg0 + 0x2A));
  *((s16 *) (arg0 + 0x34)) = *((s16 *) (arg0 + 0x32));
  *((s16 *) (arg0 + 0x1E)) = *((s16 *) (arg0 + 0x1A));
  *((s16 *) (arg0 + 0x26)) = *((s16 *) (arg0 + 0x22));
  *((s16 *) (arg0 + 0x2E)) = *((s16 *) (arg0 + 0x2A));
  *((s16 *) (arg0 + 0x36)) = *((s16 *) (arg0 + 0x32));
  {
    u8 v305 = gGameStatus[0x305];
    u8 *rec = D_080E4764 + (((v305 * 16) - v305) * 8);
    u8 v304 = base[0x304];
    u8 *entry = rec + ((v304 * 3) * 4);
    u8 *flagp = gMainWorkspace + 0x14ED;
    u8 flag = *flagp;
    if (flag != 0)
    {
      *((s16 *) (arg0 + 0x1C)) = sub_080C3824((*((s16 *) (arg0 + 0x1C))) * ((s32) (*((s16 *) (entry + 8)))), 100);
    }
    switch (flag)
    {
      case 0x22:
        *((s16 *) (arg0 + 0x24)) = ((*((s16 *) (arg0 + 0x24))) * 5) / 4;
        break;

      case 0x23:
        *((s16 *) (arg0 + 0x34)) = ((*((s16 *) (arg0 + 0x34))) * 5) / 4;
        break;

      case 0x24:
      {
        s32 x = sub_08061C78();
        *((s16 *) (arg0 + 0x24)) = (*((s16 *) (arg0 + 0x24))) + sub_080C3824(x * 3, 10);
        break;
      }

      case 0x27:
        *((s16 *) (arg0 + 0x2C)) = ((*((s16 *) (arg0 + 0x2C))) * 5) / 4;
        break;

      case 0x28:
      {
        s32 x = sub_08061C78();
        *((s16 *) (arg0 + 0x1C)) = (*((s16 *) (arg0 + 0x1C))) + sub_080C3824(x * 3, 10);
        break;
      }

      case 0x29:
        *((s16 *) (arg0 + 0x24)) = (*((s16 *) (arg0 + 0x24))) * 2;
        break;

      case 0x2A:
 do { *((s16 *) (arg0 + 0x24)) = (*((s16 *) (arg0 + 0x24))) / 2; break; } while (0);

      case 0xA5:
        *((s16 *) (arg0 + 0x24)) = (*((s16 *) (arg0 + 0x24))) + divInt32(*((s32 *) (base + 0x90)), 0x5460);
        break;

      case 0xA8:
        *((s16 *) (arg0 + 0x1C)) = (*((s16 *) (arg0 + 0x1C))) + divInt32(*((s32 *) (base + 0x90)), 0x5460);
        break;

      default:
        break;

    }

    *((s16 *) (arg0 + 0x1E)) = sub_080C3824((*((s16 *) (arg0 + 0x1E))) * ((s32) (*((s16 *) (entry + 8)))), 100);
  }
  if ((*((s16 *) (arg0 + 0x18))) <= 0)
  {
    *((s16 *) (arg0 + 0x18)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x20))) <= 0)
  {
    *((s16 *) (arg0 + 0x20)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x28))) <= 0)
  {
    *((s16 *) (arg0 + 0x28)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x30))) <= 0)
  {
    *((s16 *) (arg0 + 0x30)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x1A))) <= 0)
  {
    *((s16 *) (arg0 + 0x1A)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x22))) <= 0)
  {
    *((s16 *) (arg0 + 0x22)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x2A))) <= 0)
  {
    *((s16 *) (arg0 + 0x2A)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x32))) <= 0)
  {
    *((s16 *) (arg0 + 0x32)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x1C))) <= 0)
  {
    *((s16 *) (arg0 + 0x1C)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x24))) <= 0)
  {
    *((s16 *) (arg0 + 0x24)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x2C))) <= 0)
  {
    *((s16 *) (arg0 + 0x2C)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x34))) <= 0)
  {
    *((s16 *) (arg0 + 0x34)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x1E))) <= 0)
  {
    *((s16 *) (arg0 + 0x1E)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x26))) <= 0)
  {
    *((s16 *) (arg0 + 0x26)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x2E))) <= 0)
  {
    *((s16 *) (arg0 + 0x2E)) = 1;
  }
  if ((*((s16 *) (arg0 + 0x36))) <= 0)
  {
    *((s16 *) (arg0 + 0x36)) = 1;
  }
  if ((*((s32 *) (arg0 + 0x04))) > 0x270F0000)
  {
    *((s32 *) (arg0 + 0x04)) = 0x270F0000;
  }
  if ((*((s32 *) (arg0 + 0x0C))) > 0x270F0000)
  {
    *((s32 *) (arg0 + 0x0C)) = 0x270F0000;
  }
  if ((*((s16 *) (arg0 + 0x12))) > 0x3E7)
  {
    *((s16 *) (arg0 + 0x12)) = 0x3E7;
  }
  if ((*((s16 *) (arg0 + 0x18))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x18)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x20))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x20)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x28))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x28)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x30))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x30)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x1A))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x1A)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x22))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x22)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x2A))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x2A)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x32))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x32)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x1C))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x1C)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x24))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x24)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x2C))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x2C)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x34))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x34)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x1E))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x1E)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x26))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x26)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x2E))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x2E)) = 0x270F;
  }
  if ((*((s16 *) (arg0 + 0x36))) > 0x270F)
  {
    *((s16 *) (arg0 + 0x36)) = 0x270F;
  }
}
