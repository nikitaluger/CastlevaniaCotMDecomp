/* Draft from identical target sub_0801BD58, retargeted and judged independently. */
s32 getSpriteFacingSign(s32);
void *hitTestEntities(void);
void sub_0808E9AC(s32, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
s32 sub_080185B4(void *arg0)
{
  void *p38;
void *__repair_phase_p38;
  void *p3C;
  u8 *r6;
  u32 *new_var4;
  s32 result;
  void *r4;
  s32 cur;
  s32 off;
  s32 addr_1;
  s32 addr_2;
  s32 val;
  u8 *base;
  
  u8 *t;
  u8 *new_var3;
  s32 *new_var5;
  u16 f26;
  s32 *new_var;
  u32 k;
  t = *((void **) (((u8 *) arg0) + 0x3C));
  p38 = *((void **) (((u8 *) arg0) + 0x38));
  p3C = t;
  r6 = ((u8 *) p3C) + 0x48;
  f26 = *((u16 *) (r6 + 0x26));
  new_var4 = (u32 *) (r6 + 0x34);
  if (((s32) (*((s16 *) (r6 + 0x26)))) > 0)
  {
    s32 result_1;
    result_1 = f26 - 1;
    *((u16 *) (r6 + 0x26)) = result_1;
  }
  else
  {
    if ((*((u32 *) (r6 + 0x34))) == 0)
    {
      return 0;
    }
    r4 = hitTestEntities();
    if (r4 == 0)
    {
      return 0;
    }
    new_var3 = ((u8 *) p3C) + 8;
    if (getSpriteFacingSign((s32) p38) < 0)
    {
      s32 result_2;
      base = gMainWorkspace;
      __repair_phase_p38 = base + 0x174C;
      cur = *((s32 *) new_var3);
      if ((*((s32 *) __repair_phase_p38)) > (cur + ((s32) 0xFFDC0000)))
      {
        return 0;
      }
      off = (s32) 0xFFD80000;
      addr_1 = cur + off;
      val = (((s32) (*((s16 *) (((u8 *) r4) + 0x32)))) << 16) + ((s32) 0xFFFF8000);
      t = gCameraState;
      k = *((u8 *) (base + 0x18A8));
      k = k + 1;
      k = k << 6;
      t = t + 0x127C;
      val += *((s32 *) (t + k));
      new_var = (s32 *) (((u8 *) p3C) + 0xC);
      off = (*new_var) + ((s32) 0xFFC00000);
      if (val < off)
    {
      val = off;
    }
      else
      if (val > ((*new_var) + ((s32) 0xFFF00000)))
    {
      val = (*new_var) + ((s32) 0xFFF00000);
    }
      sub_0808E9AC(addr_1, val, 8);
      result_2 = 6;
      *((u16 *) (r6 + 0x26)) = result_2;
    }
    else
    {
      s32 result_3;
      base = gMainWorkspace;
      new_var5 = (s32 *) (base + 0x174C);
      cur = *((s32 *) new_var3);
      if ((*((s32 *) new_var5)) < (cur + 0x240000))
      {
        return 0;
      }
      off = 0x280000;
      addr_2 = cur + off;
      val = (((s32) (*((s16 *) (((u8 *) r4) + 0x32)))) << 16) + ((s32) 0xFFFF8000);
      t = gCameraState;
      k = *((u8 *) (base + 0x18A8));
      k = k + 1;
      k = k << 6;
      t = t + 0x127C;
      val += *((s32 *) (t + k));
      new_var = (s32 *) (((u8 *) p3C) + 0xC);
      off = (*new_var) + ((s32) 0xFFC00000);
      if (val < off)
    {
      val = off;
    }
      else
      if (val > ((*new_var) + ((s32) 0xFFF00000)))
    {
      val = (*new_var) + ((s32) 0xFFF00000);
    }
      sub_0808E9AC(addr_2, val, 8);
      result_3 = 6;
      *((u16 *) (r6 + 0x26)) = result_3;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
  }
  
  return 1;
}

