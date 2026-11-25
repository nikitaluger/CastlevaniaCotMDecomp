struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState D_02025FF0;
struct SubObject {
    u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10;
};
struct HostObject {
    u8 _0[8]; u32 f8; u32 fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; s16 f22; u8 _24[4];
    struct SubObject *f28; u8 _2C[0x1C]; u32 f48;
};
struct SpawnParams { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x20]; };
extern struct SpawnParams D_080CBDD0[];
extern u16 D_08102708[];
extern void *D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(void);
extern void sub_08014668(void *, s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/*
 * Build an actor's graphics/sub-object pair, set up its animation and palette,
 * look up its palette value, copy in the spawn defaults, then advance its
 * script index.
 */
void sub_080B29D4(u8 *actor)
{
  s32 gfx;
  struct HostObject *host;
  u8 *animState;
  s32 value;
  u32 v;
  u16 *defaults;
  u8 *scriptPtr;
  void **scriptTablePtr;
  u8 *scriptEntry;

  gfx = (s32) sub_0800355C();
  if (gfx == 0)
  {
    goto fail;
  }
  *((u32 *) (actor + 0x38)) = gfx;
  sub_0800168C(actor, 0, 0x48, 0);
  if ((*((u32 *) (actor + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (gfx + 0x1C)) = 0x8000000A;
  host = (struct HostObject *) (*((u8 **) (actor + 0x3C)));
  animState = ((u8 *) host) + 0x34;
  sub_08014288(actor, (u8 *) host, sub_08097DC8);
  host->f1C = 0x65;
  value = sub_08013C2C();
  host->f22 = value;
  if (((s16) value) < 0)
  {
    goto fail;
  }
  value = host->f22;
  value = value << 6;
  value = value + 0x200;
  value &= 0xFC0;
  *((u16 *) gfx) = value;
  *((u16 *) gfx) |= D_02025FF0.gfxFlags;
  sub_08014668((void *) gfx, *((u32 *) (actor + 0x4C)));
  sub_0801131C((void *) gfx, animState, ((*((s16 *) (((u8 *) host) + 0x1C))) * 0xC) + 0x080CD400);
  sub_08011368((void *) gfx, animState, 0, 0);
  {
    s16 entryIndex = *((s16 *) (animState + 0xE));
    u8 indexAdjust = *((u8 *) (animState + 1));
    void **table = *((void ***) (animState + 8));
    u32 sum = (u32) (entryIndex + indexAdjust);
    void *tableBase = *table;
    u32 offset = sum * 4;
    u8 *entry = (u8 *) (offset + (u32) tableBase) - 4;
    u16 lookup = *((u16 *) (entry + 2));
    *((u16 *) (actor + 0x5C)) = lookup;
  }
  defaults = D_08102708;
  host->f28 = sub_08016190();
  if (host->f28 != NULL)
  {
    goto cont;
  }
  fail:
  sub_080C31E0(actor, *((void **) (actor + 0x24)));

  return;
  cont:
  host->f28->f1 = 1;

  host->f28->f2 = 8;
  host->f28->f3 = 1;
  host->f28->f4 = D_080CBDD0[*((s16 *) (((u8 *) host) + 0x1C))].f4;
  host->f28->f6 = defaults[0];
  host->f28->f8 = defaults[1];
  host->f28->fA = defaults[2];
  host->f28->fC = defaults[3];
  host->f28->fE = D_080CBDD0[*((s16 *) (((u8 *) host) + 0x1C))].f6;
  host->f28->f10 = gfx;
  *((u16 *) (gfx + 2)) |= 0x400;
  *((u32 *) (actor + 4)) = 0;
  *((u16 *) (actor + 2)) |= 0x1000;
  *((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x19)) = 0;
  scriptTablePtr = &D_08671BB0;
  scriptPtr = actor;
  scriptPtr += 0x18;
  sub_080C31E4(scriptPtr, actor + 0x22, (s32) (*scriptTablePtr));
  *((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x19)) += 1;
  scriptEntry = scriptPtr + (((u32) (*((s16 *) (actor + 0x22)))) * 2);
  sub_080C31E0(actor, *((void **) ((*((u8 **) (actor + 0x14))) + ((*((u8 *) scriptEntry)) * 4))));
}
