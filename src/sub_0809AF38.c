void advanceMotion(void *, s32);
void sub_0809C840(void *, void *);
void sub_080C31E4(void *, void *, s32);
void sub_0809BEB0(void);
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
struct S_r5_0809AF38
{
  u8 _0x00[0x0C];
  u32 field_0x0C;
  u8 _0x10[0x04];
  u32 field_0x14;
  u8 _0x18[0x30];
  u32 field_0x48;
};
struct S_03000830
{
  u8 _0x00[0x04];
  u16 field_0x04;
  u16 field_0x06;
};
extern struct S_03000830 gCrossfadeGfxState;
struct S_0809BE60
{
  u8 _0x00[0x14];
  u32 field_0x14;
  u8 _0x18[0x0A];
  s16 field_0x22;
  u8 _0x24[0x38];
  u8 field_0x5C;
  u8 _0x5D[3];
  u8 field_0x60;
};

/* Update an entity's motion and script state: refresh its flag word and
 * integrate its motion sub-object; while the motion counter is non-negative,
 * latch a position, clear the current script slot's flag and dispatch the
 * next script step from the table at 0x08671BB0. */
void sub_0809AF38(struct S_0807B12C *obj)
{
  void *flags = (void *) obj->field_0x38;
  struct S_0807B12C *base;
  u32 *pTable;
  struct S_r5_0809AF38 *motion = (struct S_r5_0809AF38 *) obj->field_0x3C;
  sub_0809C840(obj, flags);
  advanceMotion((void *) motion, 0x16C1);
  if (((s32) motion->field_0x14) >= 0)
  {
    motion->field_0x48 = motion->field_0x0C;
    base = obj;
    *((u8 *) ((((u8 *) base) + (obj->field_0x22 * 2)) + 0x19)) = 0;
    pTable = (u32 *) 0x08671BB0;
    sub_080C31E4(((u8 *) obj) + 0x18, ((u8 *) obj) + 0x22, *pTable);
  }
}

void sub_0809BE60(struct S_0809BE60 *arg0);
