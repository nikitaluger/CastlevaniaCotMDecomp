s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);
s8 scaleByRandom(s32);
void loadEffectPalette(u32, void *);
extern void sub_0809BEE8(void);

struct S_0807B12C
{
  u8 _0x00[0x14];
  u32 field_0x14;
  u8 _0x18[0x0A];
  s16 field_0x22;
  u32 field_0x24;
  u8 _0x28[0x10];
  u32 field_0x38;
  u32 field_0x3C;
};
void sub_0809C12C(struct S_0807B12C *arg0)
{
  int new_var;
  int new_var2;
  void *r5 = (void *) arg0->field_0x38;
  if (updateObjectDisplayState(r5, (void *) arg0->field_0x3C) == 0)
  {
    arg0->field_0x14 = 0x0866FC8C;
    arg0->field_0x22 += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->field_0x22 * 2)) + 0x19)) += 1;
    new_var = 0x18;
    new_var2 = arg0->field_0x22 * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + new_var) + new_var2)))) * 4) + arg0->field_0x14)));
    arg0->field_0x22 -= 1;
  }
  sub_08013C8C(arg0, r5);
}

/* Initialise the work area's effect state (+0x48): set flags 1/0xFF and a
 * random byte, then clear the entity's script-step counter and advance its
 * command script via the shared advance callback. */
void sub_0809C18C(void *entity) {
    u8 *state = *(u8 **)((u8 *)entity + 0x3C) + 0x48;
    u8 zero = 0;
    state[2] = 1;
    state[3] = 0xFF;
    state[1] = scaleByRandom(0x18);
    *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2 + 0x19) = zero;
    {
        s32 *advanceCb = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *advanceCb);
    }
}

struct S_08101808 { u32 a, b, c; };
extern struct S_08101808 D_08101808;
void sub_0809BEB0(void *arg0) {
    struct S_08101808 sp;
    sp = D_08101808;
    loadEffectPalette(*(u32 *)((u8 *)&sp + *(u32 *)((u8 *)arg0 + 0x4C) * 4), (u8 *)&sp + 12);
    *(void **)((u8 *)arg0 + 0x14) = (void *)sub_0809BEE8;
    *(u16 *)((u8 *)arg0 + 0x22) = 1;
    sub_080C31E0(arg0, (void *)sub_0809BEE8);
}

void sub_0809C490(void *arg0, void *arg1, void *arg2, void *arg3) {
    if (arg0 != NULL) {
        *(u32 *)((u8 *)arg0 + 0x4C) = *(u32 *)((u8 *)arg2 + 8);
        *(u32 *)((u8 *)arg0 + 0x5C) = *(u32 *)((u8 *)arg2 + 0xC);
        *(s32 *)((u8 *)arg0 + 0x6C) = (0x10 & *(u16 *)((u8 *)arg1 + 2)) ? 1 : -1;
        {
            u8 *p3 = *(u8 **)((u8 *)arg3 + 8);
            s32 idx = *(s16 *)((u8 *)arg3 + 0xE) + *(u8 *)((u8 *)arg3 + 1);
            u16 v = *(u16 *)(p3 + idx * 4 - 4 + 2);
            *(u8 *)((u8 *)arg0 + 0x80) = (v == 0x8F) ? 0 : 1;
        }
    }
}
