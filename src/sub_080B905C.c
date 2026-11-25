struct GlobalState { u8 _0[0x18C2]; u16 w; };
extern struct GlobalState D_02025FF0;
struct EntityCfg { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct Object { u8 _0[8]; u32 f8, fC; u8 _10[0xC]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4]; struct EntityCfg *f28; };
struct BdEntry { u8 _0[0xC]; u16 f4; u16 f6; u8 _8[0x16]; };
extern struct BdEntry D_080CBDD0[];
extern u16 D_08102E08[];
extern u8 D_080CD400[];
extern u32 D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_08014668(void *, s32);
extern void sub_080B98B8(void *, s32, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/* Creates a new entity for this object, fills its config block from the
 * animation/stat tables, and dispatches a child-creation callback. */
void sub_080B905C(u8 *arg0) {
  s32 newEnt;
  struct Object *obj;
  u8 *objSub;
  u32 kind;
  u8 *slots;
  u32 *callback;
  u8 *slot;
  u16 *cfgTable;

  newEnt = (s32)sub_0800355C();
  if (newEnt == 0) goto fail;
  *(u32 *)(arg0 + 0x38) = newEnt;
  sub_0800168C(arg0, 0, 0x48, 0);
  if (*(u32 *)(arg0 + 0x3C) == 0) goto fail;
  *(u32 *)(newEnt + 0x1C) = 2;
  obj = (struct Object *)*(u32 *)(arg0 + 0x3C);
  objSub = (u8 *)obj + 0x34;
  sub_08014288(arg0, obj, sub_08097DC8);
  obj->f1C = 0x67;
  obj->f8 = *(u32 *)(arg0 + 0x5C);
  obj->fC = *(u32 *)(arg0 + 0x6C);
  kind = sub_08013C2C(0x67);
  obj->f22 = kind;
  if (((s16)kind) < 0) goto fail;
  kind = *(s16 *)((u8 *)obj + 0x22);
  kind = kind << 6;
  kind = kind + 0x200;
  kind &= 0xFC0;
  *(u16 *)newEnt = kind;
  *(u16 *)newEnt |= D_02025FF0.w;
  sub_0801131C((void *)newEnt, objSub, (obj->f1C * 0xC) + (u32)D_080CD400);
  sub_08011368((void *)newEnt, objSub, 0x16, 1);
  sub_08014668((void *)newEnt, *(s32 *)(arg0 + 0x7C));
  cfgTable = D_08102E08;
  obj->f28 = sub_08016190();
  if (obj->f28 == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
  return;
ok:
  obj->f28->f1 = 1;
  obj->f28->f2 = 8;
  obj->f28->f3 = 1;
  obj->f28->f4 = D_080CBDD0[obj->f1C].f4;
  obj->f28->f6 = cfgTable[0];
  obj->f28->f8 = cfgTable[1];
  obj->f28->fA = cfgTable[2];
  obj->f28->fC = cfgTable[3];
  obj->f28->fE = D_080CBDD0[obj->f1C].f6;
  obj->f28->f10 = newEnt;
  sub_080B98B8(arg0, 2, 4, *(u32 *)((u8 *)newEnt + 0x1C));
  *(u16 *)(arg0 + 2) |= 0x1000;
  {
    s16 slotIdx = *(s16 *)(arg0 + 0x22);
    *(u8 *)(arg0 + (u32)slotIdx * 2 + 0x19) = 0;
  }
  callback = &D_08671BB0;
  slots = arg0 + 0x18;
  sub_080C31E4(slots, arg0 + 0x22, *callback);
  {
    s16 slotIdx = *(s16 *)(arg0 + 0x22);
    *(u8 *)(arg0 + (u32)slotIdx * 2 + 0x19) += 1;
    slotIdx = *(s16 *)(arg0 + 0x22);
    slot = slots + (u32)slotIdx * 2;
    sub_080C31E0(arg0, *(void **)(*(u8 **)(arg0 + 0x14) + *(u8 *)slot * 4));
  }
}
