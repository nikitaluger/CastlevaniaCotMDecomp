extern u32 sub_080C0010(u32, ...);
extern u32 sub_080C0300(u32, u32, u32, u32);
extern volatile long long sub_080C0744(void *);
extern void sub_080C0758(void *);
extern void sub_080C0BB0(void *);
extern void sub_080C0C30(void *, void *);
extern u32 *D_03007FF0;
void sub_080BFDBE(void *arg0, u32 a, u32 b, u32 magic)
{
  u8 *task = (u8 *) arg0;
  u8 *pl;
  u8 *se;
  u8 *script;
  u32 flag;
  u32 mask;
  u32 v;
  int new_var;
  u8 *new_var4;
  u32 gp;
  u32 r2;
  char new_var2;
  u8 new_var3;
  u32 new_var5;
  s32 i;
  u8 code;
  u8 ch;
  unsigned int tmp;
  magic++;
  *((u32 *) (task + 0x34)) = magic;
  if ((*((u32 *) (task + 0x38))) != 0)
  {
    sub_080C0010(*((u32 *) (task + 0x3C)));
  }
  ch = *((u32 *) (task + 0x04));
  if (((s32) ch) < 0)
  {
    goto end;
  }
  gp = *D_03007FF0;
  sub_080C0BB0(task);
  code = 0x22;
  v = (*((u16 *) (task + code))) + (*((u16 *) (task + 0x20)));
  for (;;)
  {
    *((u16 *) (task + code)) = v;
    if (v >= 0x96)
    {
      v -= 0x96;
      i = *((u8 *) (task + 8));
      pl = *((u8 **) (task + 0x2C));
      flag = 1;
      mask = (*((u32 *) (task + 0x04)) = 0);
      for (;;)
      {
        if (((*pl) & 0x80) == 0)
        {
          goto next_a;
        }
        mask |= flag;
        se = *((u8 **) (pl + 0x20));
        while (se)
        {
          if ((se[0] & 0xC7) == 0)
          {
            sub_080C0744(se);
          }
          else
            if (se[0x10])
          {
            se[0x10]--;
            if (se[0x10] == 0)
            {
              se[0] |= 0x40;
            }
          }
          se = *((u8 **) (se + 0x34));
        }

        if ((*pl) & 0x40)
        {
          sub_080C0758(pl);
          *pl = 0x80;
          pl[0x0F] = 2;
          pl[0x13] = 0x40;
          pl[0x19] = 0x16;
          pl[0x24] = 1;
        }
        for (;;)
        {
          if (pl[1] != 0)
          {
            pl[1]--;
            if (pl[0x19] && pl[0x17])
            {
              if (pl[0x1C])
              {
                pl[0x1C]--;
                goto after_player;
              }
              tmp = pl[0x1A] + pl[0x19];
              pl[0x1A] = tmp;
              r2 = (((s8) (tmp - 0x40)) < 0) ? ((s8) tmp) : (0x80 - tmp);
              v = (((s32) pl[0x17]) * ((s32) r2)) >> 6;
              if ((s8) (pl[0x16] ^ ((u8) v)))
              {
                pl[0x16] = v;
                *pl |= (pl[0x18]) ? (3) : (0x0C);
              }
            }
          }
          script = *((u8 **) (pl + 0x40));
          code = *script;
          if (!(code >= (new_var2 = 0x80)))
          {
            if (code || task)
            {
              ch = pl[7];
            }
            else
            {
              ch = pl[7];
            }
          }
          else
          {
            *((u8 **) (pl + 0x40)) = script + 1;
            if (code >= 0xBD)
            {
              pl[7] = code;
            }
            ch = code;
          }
          new_var4 = script;
          new_var3 = ch;
          new_var5 = *((u32 *) (gp + 0x34));
          if (new_var3 >= 0xCF)
          {
            sub_080C0010(*((u32 *) (gp + 0x38)), ch - 0xCF, (u32) task, (u32) pl);
            continue;
          }
          if (ch > 0xB0)
          {
            u32 idx = ch - 0xB1;
            *((u8 *) (task + 0x0A)) = idx;
            sub_080C0010((u32) task, (u32) pl, (u32) new_var4, *((u32 *) (new_var5 + ((2 * idx) * 2))));
            if ((*pl) == 0)
            {
              goto after_player;
            }
            continue;
          }
          break;
          pl[1] = *((u8 *) ((0x0810C8AC + ch) - new_var2));
        }

        after_player:
        ;

        ;
        ;
        ;
        ;
        ;
        ;
        ;
        ;
        ;
        ;
        ;
        next_a:
        if ((--i) <= 0)
        {
        }

        pl += 0x50;
        flag <<= 1;
      }

      *((u32 *) (task + 0x0C)) = (*((u32 *) (task + 0x0C))) + 1;
      if (mask == 0)
      {
        *((u32 *) (task + 0x04)) = 0x80000000;
        goto end;
      }
      v = (*((u16 *) (task + code))) - 0x96;
    }
    else
    {
      i = *((u8 *) (task + 8));
      pl = *((u8 **) (task + 0x2C));
      for (;;)
      {
        u8 pf = *pl;
        new_var = 0;
        if ((pf & 0x80) == new_var)
        {
          goto next_b;
        }
        if ((pf & 0x0F) == 0)
        {
          goto next_b;
        }
        sub_080C0C30(task, pl);
        se = *((u8 **) (pl + 0x20));
        while (se)
        {
          if (!(se[0] & 0xC7))
          {
            sub_080C0744(se);
          }
          else
          {
            u8 r6 = se[1] & 7;
            if (pf & 3)
            {
              se[2] = (se[0x12] * pl[0x10]) >> 7;
              se[3] = (se[0x12] * pl[0x11]) >> 7;
              if (r6)
              {
                se[0x1D] |= 1;
              }
            }
            if (pf & 0x0C)
            {
              unsigned int pan = ((s8) pl[8]) + pl[9];
              if (pan < 0)
              {
                pan = 0;
              }
              if (r6)
              {
                *((u32 *) (se + 0x20)) = sub_080C0010(*((u32 *) (gp + 0x30)), r6, 0, pl[9]);
              }
              else
              {
                *((u32 *) (se + 0x20)) = sub_080C0300(*((u32 *) (se + 0x24)), pan, pl[9], 0);
              }
              se[0x1D] |= 2;
            }
          }
          se = *((u8 **) (se + 0x34));
        }

        *pl &= 0xF0;
        next_b:
        if ((--i) <= 0)
        {
          goto end;
        }

        pl += 0x50;
      }

    }
  }

  end:
  *((u32 *) (task + 0x34)) = 0x68736D53;

}

