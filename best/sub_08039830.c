extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u8 gSpriteAnimDataTable[];
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
inline static short __repair_store_halfword(int x)
{
  x = ((unsigned int) x) << 16;
  x = ((int) x) >> 16;
  return x;
}

struct __rows_tbl_8
{
  struct 
  {
    char p0[0x4];
    u32 m4;
  } e[1];
};
struct __rows_t2_8
{
  struct 
  {
    char p0[0x4];
    u32 m4;
  } e[1];
};
struct __rows_t1_8
{
  struct 
  {
    char p0[0x4];
    u32 m4;
  } e[1];
};
struct __rows_gCameraState_40
{
  char pad[0x1240];
  struct 
  {
    char p0[0x38];
    s32 m38;
    s32 m3c;
  } e[1];
};
struct __rows_self_2
{
  char pad[0x18];
  struct 
  {
    u8 m0;
    u8 m1;
  } e[1];
};
void sub_08039830(void *arg0)
{
  u8 *__base_gSpriteAnimDataTable;
  u8 *self;
  u8 *sprite;
  u8 *work;
  u8 *init;
  u8 mode;
  u8 variant;
  u16 kind;
  s32 slot;
  u16 attrs;
  u8 *layer;
  u8 *gtbl;
  u8 *ptbl;
  u32 frame;
  s32 x;
  s32 y;
  u32 temp;
  self = arg0;
  sprite = (u8 *) allocSpriteObject();
  if (sprite == 0)
  {
    goto fail;
  }
  *((u32 *) (self + 0x38)) = (u32) sprite;
  work = (u8 *) allocWorkSlot(self, 0, 0x4C, 0);
  *((u32 *) (self + 0x3C)) = (u32) work;
  if (work == 0)
  {
    goto fail;
  }
  *((u32 *) (sprite + 0x1C)) = 0x80000009;
  do
  {
    do
    {
      init = work + 0x34;
    }
    while (0);
  }
  while (0);
  installUpdateHandler((void *) self, (void *) work, (void *) 0x08014291);
  variant = self[0x7C];
  if ((mode = self[0x84]) == 0)
  {
    u32 *tbl;
    ;
    if (self[0x80])
    {
      *((u16 *) (sprite + 2)) |= 0x10;
    }
    else
    {
      *((u16 *) (sprite + 2)) &= 0xFFEF;
    }
    temp = *((u32 *) (self + 0x5C));
    *((u32 *) (work + 8)) = temp - ((u32 *) 0x080CF140)[variant];
    *((u32 *) (work + 0xC)) = (*((u32 *) (self + 0x6C))) + ((struct __rows_tbl_8 *) ((u32 *) 0x080CF140))->e[variant].m4;
    *((u32 *) (work + 0x10)) = 0;
    *((u32 *) (work + 0x14)) = 0;
  }
  else
    if (mode == 1)
  {
    u32 *t1;
    u32 *t2;
    t1 = (u32 *) 0x080CF170;
    t2 = (u32 *) 0x080CF158;
    if (self[0x80])
    {
      *((u32 *) (work + 0x10)) = -t1[variant];
      *((u32 *) (work + 8)) = (*((u32 *) (self + 0x5C))) - t2[variant];
      *((u32 *) (work + 0xC)) = (*((u32 *) (self + 0x6C))) + ((struct __rows_t2_8 *) t2)->e[variant].m4;
      *((u32 *) (work + 0x14)) = ((struct __rows_t1_8 *) t1)->e[variant].m4;
    }
    else
    {
      *((u32 *) (work + 0x10)) = t1[variant];
      slot = *((u32 *) (self + 0x5C));
      *((u32 *) (work + 8)) = slot - t2[variant];
      *((u32 *) (work + 0xC)) = (*((u32 *) (self + 0x6C))) + ((struct __rows_t2_8 *) t2)->e[variant].m4;
      *((u32 *) (work + 0x14)) = ((struct __rows_t1_8 *) t1)->e[variant].m4;
    }
    {
      setSpriteFlipForDirection(sprite, *((s32 *) (work + 0x10)));
    }
  }
  (void) (&kind);
  *((u16 *) (work + 0x1C)) = __repair_store_halfword(kind = *((u16 *) (((u8 *) 0x080CF0BC) + (((u32) self[0x4C]) * 4))));
  slot = findKindIndex((s16) kind);
  *((u16 *) (work + 0x22)) = slot;
  if ((*((u16 *) (work + 0x22))) < 0)
  {
    goto fail;
  }
  attrs = (u16) (((slot << 6) + 0x200) + ((slot + 8) << 12));
  attrs |= *((u16 *) (gMainWorkspace + 0x18C2));
  *((u16 *) sprite) = attrs;
  initSpriteGraphics((void *) sprite, (void *) init, (u8 *) (gSpriteAnimDataTable + (((s32) kind) * 12)));
  if (mode)
  {
    setAnimationFrame((s32) ((u32) sprite), (void *) init, *((u16 *) (((u8 *) 0x080CF13A) + (((u32) variant) * 2))), 0);
  }
  else
  {
    setAnimationFrame((s32) ((u32) sprite), (void *) init, *((u16 *) (((u8 *) 0x080CF134) + (((u32) variant) * 2))), 0);
  }
  if (mode)
  {
    layer = ((u8 *(*)(u32)) 0x08077190)(((u32) 0x080CF134) + (((u32) variant) * 8));
  }
  else
  {
    layer = ((u8 *(*)(u32)) 0x08077190)(0x080CF0F4);
  }
  *((u32 *) (work + 0x28)) = (u32) layer;
  if (layer == 0)
  {
    goto fail;
  }
  do
  {
    layer[2] = 8;
    layer[1] = 1;
    layer[3] = 1;
    gtbl = (u8 *) 0x080CBDD0;
  }
  while (0);
  {
    u32 gi;
    u32 pi;
    y = *((s16 *) (work + 0x1C));
    gi = (((u32) y) * 40) + 4;
    *((u16 *) (layer + 4)) = *((u16 *) (gtbl + gi));
    ptbl = (mode) ? ((u8 *) 0x080CF134) : ((u8 *) 0x080CF0F4);
    *((u16 *) (layer + 6)) = *((u16 *) (ptbl + 2));
    *((u16 *) (layer + 8)) = *((u16 *) (ptbl + 4));
    *((u16 *) (layer + 10)) = *((u16 *) (ptbl + 6));
    *((u16 *) (layer + 12)) = *((u16 *) (ptbl + 8));
    frame = (((u32) (*((u16 *) (ptbl + 8)))) * 4) + ((u32) y); pi = frame * 8;
    *((u16 *) (layer + 14)) = *((u16 *) ((gtbl + pi) + 0xC));
  }
  *((u32 *) (layer + 0x10)) = (u32) sprite;
  frame = (float) (gMainWorkspace[0x18A8] + 1);
  x = (*((s32 *) (work + 8))) - ((((struct __rows_gCameraState_40 *) gCameraState)->e[frame].m38 + 0x8000) & 0xFFFF0000);
  *((u32 *) (work + 0x14)) = (u32) x;
  y = (*((s32 *) (work + 0x10))) - ((((struct __rows_gCameraState_40 *) gCameraState)->e[frame].m3c - 0x8000) & 0xFFFF0000);
  *((u32 *) (work + 0x18)) = (u32) y;
  *((u16 *) (self + 2)) |= 0x1000;
  {
    s32 step;
    s32 step_web1;
    u8 cmd;
    step = *((s16 *) (self + 0x22));
    *((u16 *) (self + 0x22)) = step + 1;
    ((struct __rows_self_2 *) self)->e[step].m1 += 1;
    sub_080C31E4((void *) self, (void *) (self + 0x22), *((void **) 0x08671BB0));
    step = *((s16 *) (self + 0x22));
    *((u16 *) (self + 0x22)) = step - 1;
    step_web1 = *((s16 *) (self + 0x22));
    cmd = ((struct __rows_self_2 *) self)->e[step_web1].m0;
    sub_080C31E0((void *) self, *((void **) ((*((u32 *) (self + 0x14))) + (((u32) cmd) * 4))));
  }
  return;
  fail:
  ((void (*)(u8 *, u32)) 0x080C32E0)(self, *((u32 *) (self + 0x24)));

}

