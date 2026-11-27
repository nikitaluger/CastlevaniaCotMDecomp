extern s32 sub_080C31E0(u32, u32);
extern u32 gTrigFuncTable;
struct Vec3 { s32 v[3]; };
struct Part { u8 pad0[0x4C]; s32 unk4C; u8 pad50[0x0C]; s32 unk5C; u8 pad60[0x0C]; s32 unk6C; u8 pad70[0x0C]; s8 unk7C; };
struct Limb { struct Part *volatile parts[3]; };
struct Thing { struct Limb unk00[2]; u8 pad18[0x10]; struct Vec3 unk28[2]; struct Vec3 unk40[2]; u32 unk58[2]; };
void sub_080AA1DC(struct Thing *arg0)
{
  u32 i = 0;
  u32 k;
  int new_var;
  u32 *p58 = arg0->unk58;
  for (; i <= 1; i++)
  {
    u32 val = arg0->unk58[i];
    s32 v9 = ((s32) val) - 0x200;
    new_var = 0;
    if (arg0->unk00[i].parts[0]->unk7C > new_var)
    {
      do
      {
        arg0->unk28[i].v[0] = arg0->unk28[i].v[2] + ((sub_080C31E0(val + 0x3E00, gTrigFuncTable) >> 8) << 13);
      }
      while (0);
    }
    else
    {
      arg0->unk28[i].v[0] = arg0->unk28[i].v[2] - ((sub_080C31E0(val + 0x3E00, gTrigFuncTable) >> 8) << 13);
    }
    arg0->unk40[i].v[0] = arg0->unk40[i].v[2] + ((sub_080C31E0(v9, gTrigFuncTable) >> 8) << 13);
  }

  for (i = 0; i <= 1; i++)
  {
    u32 *q = p58;
    for (k = 0; k <= 2; k++)
    {
      struct Part *p;
      if (k != 1)
      {
        arg0->unk00[i].parts[k]->unk4C = arg0->unk28[i].v[k];
        arg0->unk00[i].parts[k]->unk5C = arg0->unk40[i].v[k];
        arg0->unk00[i].parts[k]->unk6C = *(u32 *)((u32)q + (i << 2));
      }
    }
  }
}
