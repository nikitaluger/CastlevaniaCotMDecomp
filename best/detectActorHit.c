extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteKindTable[];
extern u8 gEffectGfxTable[];
s32 sub_080C36E4(s16, s32);
void *hitTestEntities(void *);
s32 terrainHasSolidFlags(u32, u32);
s32 sub_0806D5C4(u16, u16);
s32 sub_0806D5F8(u16, u16);
void sub_0808D7BC(s32, s32, s32, s32);
void sub_080158BC(void *, void *);
struct C13558
{
  u16 f0;
  u8 pad02[2];
  u16 f4;
  u8 pad06[2];
  u32 f8;
  u32 fC;
  u8 pad10[8];
  u32 f18;
  s16 f1C;
  u8 pad1E[2];
  s16 f20;
  u8 pad22[14];
  u32 f30;
};
struct Ent13558
{
  u16 f0;
  u8 pad02[2];
  u16 f4;
  u8 pad06[0x20];
  s16 f26;
  s16 f28;
  u16 f2A;
  u16 f2C;
  s16 f2E;
  s16 f30;
  s16 f32;
};
u32 detectActorHit(struct Ent13558 *b, struct C13558 *c, struct Ent13558 *d)
{
    u8 *__base_D_080CBDD0;
  struct Ent13558 *e = 0;
  u8 *new_var3;
  s16 idx;
  
s32 __repair_phase_r12;
s32 __repair_phase___repair_phase_r12;
  s32 r1;
  
  
s32 __repair_phase_t;
  u16 cf;
  u8 *p;
u8 *__repair_phase_p;
  int new_var;
  s32 a2a;
  int new_var2;
  s32 d2a;
  int temp;
  
  do { cf = (c->f0 &= 0xFFFD);
  d->f4 &= 0xFDFF;
  __repair_phase___repair_phase_r12 = cf & 1;
  if (__repair_phase___repair_phase_r12)
  {
    *((u8 *) (((u8 *) d) + 1)) &= 0xFA;
    return 0;
  } } while (0);
  idx = c->f20;
  if (idx > 0)
  {
    idx = c->f20;
    __repair_phase_t = (s16) sub_080C36E4(idx, 3);
    switch (__repair_phase_t)
    {
      case 0:
        b->f0 = (b->f0 & 0x0FFF) | 0xD000;
        break;

      case 1:
        b->f0 = (b->f0 & 0x0FFF) | 0xC000;
        break;

    }

    c->f20 = c->f20 - 1;
    d->f4 |= 0x200;
    hitTestEntities(d);
    return 0;
  }
  if (!((*((u8 *) (((u8 *) d) + 1))) & 4))
  {
    return 0;
  }
  p = gMainWorkspace + 0x18BE;
  if ((*((s16 *) p)) != 0)
  {
    idx = c->f1C;
    __base_D_080CBDD0 = gEffectGfxTable;
    __repair_phase_p = __base_D_080CBDD0 + (((idx * 4) + idx) * 8);
    if (((*((s16 *) (__repair_phase_p + 2))) != 0) && (c->f30 != 0))
    {
      if (!(c->f4 & 0x200))
      {
        if ((*((u16 *) (c->f30 + 2))) & 1)
        {
          if (!(c->f4 & 0x100))
          {
            if (terrainHasSolidFlags(c->f8, c->fC + 0x10000) != 1)
            {
              goto skip;
            }
          }
          p = gSpriteKindTable + (((idx * 4) + idx) * 4);
          new_var3 = gMainWorkspace + 0x174C;
          __repair_phase_r12 = (u16) sub_0806D5C4(*((u16 *) (gMainWorkspace + 0x18BE)), *((u16 *) (p + 6)));
          {
            if (((double) __repair_phase_r12) <= 0)
            {
              __repair_phase_r12 = 1;
            }
            c->f18 = c->f18 - __repair_phase_r12;
            __repair_phase_t = *((s32 *) new_var3);
            idx = d->f30;
            if (__repair_phase_t < idx)
            {
              __repair_phase___repair_phase_r12 = (((idx << 16) + 0x8000) + (*((u32 *) ((gCameraState + 0x1278) + ((((u8) (*(gMainWorkspace + 0x18A8))) + 1) << 6))))) - (d->f26 << 16);
            }
            else
            {
              __repair_phase___repair_phase_r12 = (((idx << 16) + 0x8000) + (*((u32 *) ((gCameraState + 0x1278) + ((((u8) (*(gMainWorkspace + 0x18A8))) + 1) << 6))))) + (d->f26 << 16);
            }
            r1 = (((d->f32 << 16) + 0xFFFF8000) + (*((u32 *) ((gCameraState + 0x127C) + ((((u8) (*(gMainWorkspace + 0x18A8))) + 1) << 6))))) - (d->f28 << 16);
          }
          sub_0808D7BC(__repair_phase___repair_phase_r12, r1, __repair_phase_r12, 0);
          if (((s32) c->f18) <= 0)
          {
            c->f18 = 0;
 { c->f0 |= 1; }
          }
          else
          {
            c->f0 |= 2;
          }
          c->f20 = 0x1E;
          return 0;
        }
      }
    }
  }
  skip:
  e = (struct Ent13558 *) hitTestEntities(d);

  if (e == 0)
  {
    return 0;
  }
  if (d->f4 & 0x100)
  {
    c->f0 |= 0x10;
    return (u32) e;
  }
  a2a = e->f2A & 0xF;
  d2a = d->f2A & 0xF;
  new_var = 0xC;
  new_var2 = 6;
  idx = c->f1C;
  p = gSpriteKindTable + (2 * (2 * ((idx * 4) + idx)));
  if ((d2a != 0) && (a2a == d2a))
  {
    __repair_phase_r12 = ((u16) sub_0806D5F8(e->f2C, *((u16 *) (p + new_var2)))) >> 1;
  }
  else
  {
    __repair_phase_r12 = (u16) sub_0806D5F8(e->f2C, *((u16 *) (p + new_var2)));
  }
  if (__repair_phase_r12 <= 0)
  {
    __repair_phase_r12 = 1;
  }
  if (__repair_phase_r12 > 9999)
  {
    __repair_phase_r12 = 9999;
  }
  c->f18 = c->f18 - __repair_phase_r12;
  if (e->f30 < d->f30)
  {
    __repair_phase___repair_phase_r12 = (((d->f30 << 16) + 0x8000) + (*((u32 *) ((gCameraState + 0x1278) + ((((u8) (*(gMainWorkspace + 0x18A8))) + 1) << new_var2))))) - (d->f26 << 16);
  }
  else
  {
    idx = (d->f30 << 16) + 0x8000;
    r1 = (idx + (*((u32 *) ((gCameraState + 0x1278) + ((((u8) (*(gMainWorkspace + 0x18A8))) + 1) << new_var2))))); __repair_phase___repair_phase_r12 = r1 + (d->f26 << 16);
  }
  r1 = (((d->f32 << 16) + 0xFFFF8000) + (*((u32 *) ((gCameraState + 0x127C) + ((((u8) (*(gMainWorkspace + 0x18A8))) + 1) << new_var2))))) - (d->f28 << 16);
  sub_0808D7BC(__repair_phase___repair_phase_r12, r1, __repair_phase_r12, 0);
  if (c->f30 != 0)
  {
    *((u32 *) (c->f30 + 8)) = (u32) e;
  }
  if (((s32) c->f18) <= 0)
  {
    switch (a2a) {
        case 2:
            if ((!(c->f0 & 0xC)) && (d2a != 2))
            {
              c->f18 = 1;
              c->f0 |= 4;
            }
            else
            {
              c->f18 = 0;
              c->f0 |= 1;
            }
            break;
        case 5:
            if ((!(c->f0 & new_var)) && (d2a != 5))
            {
              c->f18 = 1;
              c->f0 |= 8;
            }
            else
            {
              c->f18 = 0;
              c->f0 |= 1;
            }
            break;
        default:
            c->f18 = 0;
            c->f0 |= 1;
            break;
    }
  }
  else
  {
    c->f0 |= 2;
  }
  if (e->f2E != 0)
  {
    c->f20 = e->f2E;
  }
  else
  {
    c->f20 = 0x1E;
  }
  sub_080158BC(c, e);
  return (u32) e;
}
