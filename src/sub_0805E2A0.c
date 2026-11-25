struct InitParams {        /* spawn parameters at obj+0x4C */
  u32 f0;
  void *f4;
  u16 f8;
  s16 fA;
};
struct SpriteTail { u8 _0[0x1C]; u32 f1C; };
struct Part {              /* the sub-object allocated for the entity */
  u8 _0;
  u8 f1;
  u8 f2;
  u8 f3;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  u16 fE;
  void *f10;
  u16 f14;
};
struct Entity {
  u8 _0[8];
  u32 f8;
  u32 fC;
  u8 _10[4];
  u32 f14;
  s32 f18;
  u8 _1C[8];
  s32 f24;
  struct Part *f28;
  u8 _2C[8];
  u16 f34;
};
struct InitObj {
  u8 _0[2];
  u16 f2;
  u8 _4[0x10];
  u32 f14;
  u8 _18[0x0A];
  s16 f22;
  u32 f24;
  u8 _28[0x10];
  u32 f38;
  u32 f3C;
  u8 _40[0xC];
  struct InitParams f4C;
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 f18A8;
  u8 _18A9[0x19];
  u16 f18C2;
};
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02021E90[];
extern u32 D_080D00EC[];                    /* parameter index table */
extern u8 D_0865FDF4[];                     /* animation entry table */
extern u8 D_080D00A8[];
extern s32 D_08671BB0[];
extern void *sub_0800355C(void);            /* create the sprite object */
extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_08016190(void);            /* allocate a part object */
extern void sub_0805E688(void);             /* entity cleanup callback */
extern void sub_080C31E0(void *, s32);      /* cleanup callback */
extern void sub_080C31E4(void *, void *, s32); /* run a script handler */

/* Creates an entity and sprite from the object's spawn parameters, positions the sprite
   relative to the scroll offset, then runs the object's first script step. */
void sub_0805E2A0(struct InitObj *obj)
{
  struct InitParams *params;
  void *sprite;
  struct Entity *ent;
  u8 *scrollTbl;
  u8 *stepPtr;
  s32 *scriptOp;
  s32 offA;
  u16 z;
  int byteScale;
  params = &obj->f4C;
  sprite = sub_0800355C();
  if (sprite == 0)
  {
    goto fail;
 do { } while (0);
  }
  obj->f38 = (u32) sprite;
  sub_0800168C(obj, 0, 0x38, 0);
  ent = obj->f3C;
  if (ent == 0)
  {
    goto fail;
  }
  ent->f24 = obj->f24;
  obj->f24 = (u32) sub_0805E688;
  ent->f18 = 1;
  ent->f8 = params->f0;
  ent->fC = (u32) params->f4;
  ent->f28 = sub_08016190();
  if (ent->f28 != 0)
  {
    goto body;
  }
  fail:
  sub_080C31E0(obj, obj->f24);

  return;
  body:
  z = 0;

  ent->f28->f1 = 4;
  ent->f28->f2 = 0x80;
  ent->f28->f3 = z;
  ent->f28->f4 = 0;
  ent->f28->f6 = 6;
  ent->f28->f8 = 6;
  ent->f28->fA = z;
  ent->f28->fC = 0xFFF8;
  ent->f28->fE = 0;
  ent->f28->f10 = sprite;
  ent->f28->f14 = 0;
  *((u16 *) sprite) |= D_02025FF0.f18C2;
  ((struct SpriteTail *) sprite)->f1C = 0x80000007;
  scrollTbl = (u8 *) (&D_02021E90);
  {
    u32 k = 0x1278;
    *((u32 *) (((u8 *) sprite) + 0x14)) = (*((u32 *) (((u8 *) ent) + 0x08))) - (((*((u32 *) ((scrollTbl + k) + ((D_02025FF0.f18A8 + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (((u8 *) sprite) + 0x18)) = (*((u32 *) (((u8 *) ent) + 0x0C))) - (((*((u32 *) ((scrollTbl + k) + ((D_02025FF0.f18A8 + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  ent->f14 = 0x20000;
  ent->f34 = 0x258;
  offA = 0xA;
  {
    u32 *ec = D_080D00EC;
    u16 tt = params->f8;
    u8 *p = D_0865FDF4 + (((u32) (*((u16 *) (&ec[tt])))) << 3);
    *((u32 *) (((u8 *) sprite) + 0x24)) = (u32) ((void *) D_080D00A8);
    *((u16 *) (((u8 *) sprite) + 0x28)) = z;
    *((u16 *) sprite) = (*((u16 *) sprite)) | (((*((u16 *) (p + 4))) & 0xF000) + (((s32) (*((s16 *) (((u8 *) params) + offA)))) << (byteScale = 2)));
  }
  obj->f2 = (u16) (obj->f2 | 0x1000);
  *((u8 *) ((((u8 *) obj) + 0x19) + (byteScale * obj->f22))) = 0;
  scriptOp = D_08671BB0;
  stepPtr = ((u8 *) obj) + 0x18;
  sub_080C31E4(stepPtr, &obj->f22, *scriptOp);
  *((u8 *) ((((u8 *) obj) + 0x19) + (byteScale * obj->f22))) = (u8) ((*((u8 *) ((((u8 *) obj) + 0x19) + (byteScale * obj->f22)))) + 1);
  stepPtr += obj->f22 * byteScale;
  sub_080C31E0(obj, *((u32 *) (((u8 *) obj->f14) + (4 * (*stepPtr)))));
}
