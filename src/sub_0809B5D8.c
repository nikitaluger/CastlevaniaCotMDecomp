s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void stepAnimationTrack(void *, void *);
void sub_08014668(void *, s32);
void advanceMotion(void *, s32);
void sub_0809C840(void *, void *);
void sub_0809BEB0(void);
struct S_0807B12C
{
  u8 _0x00[0x14];
  u32 scriptTable;
  u8 _0x18[0x0A];
  s16 stepIndex;
  u32 field_0x24;
  u8 _0x28[0x10];
  u32 sprite;
  u32 work;
};
struct S_0809B638
{
  u8 _0x00[0x24];
  u32 field_0x24;
  u8 _0x28[0x14];
  u32 field_0x3C;
  u8 _0x40[0x0C];
  u32 field_0x4C;
  u8 _0x50[0x0C];
  u32 field_0x5C;
  u8 _0x60[0x0C];
  u16 field_0x6C;
  u8 _0x6E[0x06];
  u8 field_0x74;
};
struct S_r5_0809AF38
{
  u8 _0x00[0x0C];
  u32 field_0x0C;
  u8 _0x10[0x38];
  u32 field_0x14;
  u8 _0x18[0x30];
  u32 field_0x48;
};
struct S_0809BE60
{
  u8 _0x00[0x14];
  u32 field_0x14;
  u16 field_0x22;
};
extern u16 D_03000830[4];

/* If the display-state handler did not consume this frame, advance the script
 * step byte and dispatch the next handler from the table at +0x14; then copy
 * the work position onto the sprite. */
void sub_0809B5D8(struct S_0807B12C *arg0)
{
  int byteBase;
  int byteOffset;
  void *sprite = (void *) arg0->sprite;
  if (updateObjectDisplayState(sprite, (void *) arg0->work) == 0)
  {
    arg0->scriptTable = 0x0866FC68;
    arg0->stepIndex += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->stepIndex * 2)) + 0x19)) += 1;
    byteBase = 0x18;
    byteOffset = arg0->stepIndex * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + byteBase) + byteOffset)))) * 4) + arg0->scriptTable)));
    arg0->stepIndex -= 1;
  }
  sub_08013C8C(arg0, sprite);
}

void sub_0809B638(struct S_0809B638 *arg0);
void sub_0809AF38(struct S_0807B12C *arg0);
void sub_0809BE60(struct S_0809BE60 *arg0);
