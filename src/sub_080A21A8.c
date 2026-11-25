extern void sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern void sub_0801131C(void *, void *, void *);
extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 D_02025FF0;

/* Allocates a new scripted entity, sets its sprite/animation state and then
 * dispatches its first behaviour through the script function table. */
void sub_080A21A8(void *arg0)
{
  void *newObj;
  void *component;
  void *component34;
  s32 gfxIndex;
  u8 *script;
  void **effectRoutinePtr;
  s32 *behaviorTable;
  u8 *scriptBytePtr;

  newObj = sub_0800355C();
  if (newObj == NULL)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  *((void **) (((char *) arg0) + 0x38)) = newObj;
  sub_0800168C(arg0, 0, 0x48, 0);
  if ((*((vu32 *) (((char *) arg0) + 0x3C))) == 0)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  *((s32 *) (((char *) newObj) + 0x1C)) = 0x80000009;
  component = *((void **) (((char *) arg0) + 0x3C));
  component34 = ((char *) component) + 0x34;
  *((s16 *) (((char *) component) + 0x1C)) = 0x54;
  *((s32 *) (((char *) component) + 0x08)) = *((s32 *)(((char *) arg0) + 0x4C));
  *((s32 *) (((char *) component) + 0x0C)) = *((s32 *)(((char *) arg0) + 0x5C));
  gfxIndex = sub_08013C2C(0x54);
  *((s16 *) (((char *) component) + 0x22)) = (s16) gfxIndex;
  if (((s32) (((u32) gfxIndex) << 16)) < 0)
  {
    sub_080C31E0(arg0, *((s32 *) (((char *) arg0) + 0x24)));
    return;
  }
  gfxIndex = *((s16 *) (((char *) component) + 0x22));
  gfxIndex <<= 6;
  gfxIndex += 0x200;
  gfxIndex &= 0xFC0;
  *((u16 *) newObj) = (u16) gfxIndex;
  *((u16 *) newObj) = (u16) (gfxIndex | (&D_02025FF0)->w);
  sub_0801131C(newObj, component34, (void *) ((((s32) (*((s16 *) (((char *) component) + 0x1C)))) * 0xC) + 0x080CD400));
  sub_08011368(newObj, component34, 0, 0);
  *((u16 *) (((char *) arg0) + 0x02)) |= 0x1000;
  {
    u8 *stepBase = (u8 *) ((((s16) (*((s16 *) (((char *) arg0) + 0x22)))) * 2) + ((u32) arg0));
    stepBase[0x19] = 0;
  }
  effectRoutinePtr = (void **) 0x08671BB0;
  script = ((char *) arg0) + 0x18;
  sub_080C31E4(script, ((char *) arg0) + 0x22, (s32) (*effectRoutinePtr));
  {
    u8 *stepBase = (u8 *) ((((s16) (*((s16 *) (((char *) arg0) + 0x22)))) * 2) + ((u32) arg0));
    stepBase[0x19] = stepBase[0x19] + 1;
  }
  scriptBytePtr = script + (((s16) (*((s16 *) (((char *) arg0) + 0x22)))) * 2);
  {
    u8 behaviorId = *scriptBytePtr;
    behaviorTable = *((s32 **) (((char *) arg0) + 0x14));
    sub_080C31E0(arg0, behaviorTable[behaviorId]);
  }
}
