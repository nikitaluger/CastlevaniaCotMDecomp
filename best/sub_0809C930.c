extern void *allocSpriteObject(void);
extern void allocWorkSlot(u8 *, s32, s32, s32);
extern void installUpdateHandler(u8 *, u8 *, s32);
extern void initSpawnedObject(u8 *, u8 *, u8 *, u32, s32);
extern void sub_080A012C(u8 *, u8 *, s32, s32);
extern void setObjectAnimation(u8 *, u8 *, s32, s32);
extern void sub_08097EF4(s32, s32, s32, s32);
extern void *allocEffectPart(void);
extern u8 *sub_0805FAEC(u8 *, s32);
extern void sub_080A0154(u8 *, u8 *, u8 *, u8);
extern void sub_080A0194(u8 *, u8 *, u8 *, s32);
extern void sub_080A01E0(u8 *, u8 *, s32);
extern void sub_080A03C8(u8 *, u8 *, u8 *, u8);
extern void registerScriptObject(u8 *, s32);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
struct TBL2
{
  u16 f0;
  u8 _2[2];
  u16 f4;
  u8 _6[0x14 - 6];
};
struct F3
{
  u8 _0[2];
  u16 f2;
};
extern struct TBL2 gSpriteKindTable[];
void sub_0809C930(u8 *arg0)
{
  u32 savedAC;
  u8 *obj;
  u8 *new_var;
  u8 *P;
  u8 *p34;
  u8 *p48;
  u8 *attribs;
  u8 *new_var2;
  u8 *tiles;
  u8 **p8p;
  s32 v;
  u32 *cbTable;
  u8 *entries;
  savedAC = *((u32 *) (arg0 + 0xAC));
  obj = allocSpriteObject();
  if (obj == NULL)
  {
    goto fail0;
  }
  goto ok0;
  fail0:
  sub_080C31E0(arg0, *((s32 *) (arg0 + 0x24)));

  return;
  ok0:
  *((u32 *) (arg0 + 0x38)) = (u32) obj;

  allocWorkSlot(arg0, 0, 0x90, 0);
  if ((*((u32 *) (arg0 + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (obj + 0x1C)) = 0x8000000A;
  P = *((u8 **) (arg0 + 0x3C));
  p34 = P + 0x34;
  p48 = P + 0x48;
  installUpdateHandler(arg0, *((u8 **) (arg0 + 0x3C)), 0x08097D91);
  initSpawnedObject(arg0, obj, P, savedAC, 0x4C);
  sub_080A012C(obj, p34, 0x80, 6);
  setObjectAnimation(obj, p34, 0, 1);
  p8p = *((u8 ***) (p34 + 8));
  v = (*((s16 *) (p34 + 0x0E))) + (*((u8 *) (p34 + 1)));
  *((u16 *) (p48 + 0x3E)) = ((struct F3 *) (((*p8p) + (v * 4)) - 4))->f2;
  sub_08097EF4(0, 0x083CEA4C, 0, 1);
  sub_08097EF4(0, 0x083CEA6C, 1, 1);
  sub_08097EF4(0, 0x083CEA8C, 2, 1);
  tiles = (u8 *) 0x0810199C;
  attribs = allocEffectPart();
  *((u32 *) (P + 0x28)) = (u32) attribs;
  if (attribs == NULL)
  {
    goto fail;
  }
  goto fields;
  fail:
  sub_080C31E0(arg0, *((s32 *) (arg0 + 0x24)));

  return;
  fields:
  *((u8 *) (attribs + 1)) = 5;

  *((u8 *) ((*((u8 **) (P + 0x28))) + 2)) = 8;
  *((u8 *) ((*((u8 **) (P + 0x28))) + 3)) = 1;
  *((u16 *) ((*((u8 **) (P + 0x28))) + 4)) = gSpriteKindTable[*((s16 *) (P + 0x1C))].f0;
  *((u16 *) ((*((u8 **) (P + 0x28))) + 6)) = *((u16 *) (tiles + 0));
  *((u16 *) ((*((u8 **) (P + 0x28))) + 8)) = *((u16 *) (tiles + 2));
  *((u16 *) ((*((u8 **) (P + 0x28))) + 0x0A)) = *((u16 *) (tiles + 4));
  *((u16 *) ((*((u8 **) (P + 0x28))) + 0x0C)) = *((u16 *) (tiles + 6));
  *((u16 *) ((*((u8 **) (P + 0x28))) + 0x0E)) = gSpriteKindTable[*((s16 *) (P + 0x1C))].f4;
  *((u32 *) ((*((u8 **) (P + 0x28))) + 0x10)) = (u32) obj;
  new_var2 = p48 + 0x38;
  *((u32 *) (p48 + 0x18)) = (u32) sub_0805FAEC(arg0, 0x180);
  sub_080A0154(*((u8 **) (p48 + 0x18)), obj, P, *((u8 *) (P + 0x88)));
  *((u32 *) (p48 + 0x1C)) = (u32) sub_0805FAEC(arg0, 0x181);
  sub_080A0194(*((u8 **) (p48 + 0x1C)), obj, P, -(*((s32 *) new_var2)));
  *((u32 *) (p48 + 0x20)) = (u32) sub_0805FAEC(arg0, 0x183);
  *((u32 *) (p48 + 0x24)) = (u32) sub_0805FAEC(arg0, 0x186);
  sub_080A01E0(*((u8 **) (p48 + 0x24)), P, -(*((s32 *) new_var2)));
  *((u32 *) (p48 + 0x28)) = (u32) sub_0805FAEC(arg0, 0x188);
  new_var = arg0;
  new_var = new_var + 2;
  sub_080A03C8(*((u8 **) (p48 + 0x28)), obj, P, *((u8 *) (p48 + 0x0D)));
  *((u16 *) (p48 + 0x2C)) = (*((s32 *) ((*((u8 **) (arg0 + 0x3C))) + 0x18))) >> 1;
  registerScriptObject(arg0, 0);
  *((u16 *) (arg0 + 2)) = 0x1000 | (*((u16 *) new_var));
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = 0;
  cbTable = (u32 *) 0x08671BB0;
  entries = arg0 + 0x18;
  sub_080C31E4(entries, arg0 + 0x22, *cbTable);
  {
    s16 slot = *((s16 *) (arg0 + 0x22));
    u8 *p19;
    ((u8 *) ((((s32) slot) * 2) + ((u32) arg0)))[0x19] = ((u8 *) ((((s32) slot) * 2) + ((u32) arg0)))[0x19] + 1;
  }
  {
    s16 slot2 = *((s16 *) (arg0 + 0x22));
    u8 *entry = entries + (((s32) slot2) * 2);
    sub_080C31E0(arg0, *((s32 *) ((*((u8 **) (arg0 + 0x14))) + ((*((u8 *) entry)) * 4))));
  }
}

