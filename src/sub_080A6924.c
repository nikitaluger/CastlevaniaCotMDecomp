/* Load an actor's per-action parameters from tables indexed by its action byte
 * (self+0x4C) into its work struct, then step and dispatch its behavior script. */
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

struct ActionParam {
  u32 value;
  u32 unused;
};
extern struct ActionParam D_08102094[];
extern s32 D_081020A4[];

void sub_080A6924(void *actor)
{
  u8 *self = (u8 *) actor;
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *state;
  u8 *script;
  s32 *dispatchArg;
  u32 zero;
  u32 param;
  state = work + 0xEF;
  zero = 0;
  *state = 2;
 do { *((u32 *) (work + 0xE8)) = zero; param = D_08102094[*((u8 *) (self + 0x4C))].value; } while (0);
  *((u32 *) (work + 0x10C)) = param;
  *((s32 *) (work + 0x118)) = -D_081020A4[*((u8 *) (self + 0x4C))];
  *((u32 *) (work + 0x110)) = zero;
  *((u8 *) (work + 0x120)) = zero;
  *((u32 *) (work + 0x114)) = 0x300;
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
  dispatchArg = (s32 *) 0x08671BB0;
  script = self + 0x18;
  sub_080C31E4(script, self + 0x22, *dispatchArg);
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) += 1;
  script = script + ((*((s16 *) (self + 0x22))) * 2);
  sub_080C31E0(actor, *((void **) ((*((u32 *) (self + 0x14))) + ((*((u8 *) script)) * 4))));
}
