s32 checkGlobalStateChange(void *, void *, void *);
void sub_0806D588(void *, void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
s16 divInt32(s32, s32);
extern s32 gScriptStepCallbackTable;
struct S_02025FF0
{
  u8 pad0[0x10];
  s32 field10;
  u8 pad14[0x14ED - 0x14];
  u8 field14ED;
  u8 pad14EE[0x173A - 0x14EE];
  u8 field173A;
};
extern struct S_02025FF0 gMainWorkspace;

/* Shrinks the entity's box each frame, recomputes the scaled target values,
 * resets its action once the box is small, and despawns when required. */
void sub_0807FFDC(u8 *entity)
{
  u8 *target;
  u8 *new_var;
  u8 *subObj = *((u8 **) (entity + 0x6C));
  u8 *obj = subObj + 4;
  u8 *ctx = *((u8 **) (entity + 0x38));
  s32 rc;
  s32 value;
  rc = checkGlobalStateChange(entity, ctx, obj);
  if (rc == 0)
  {
    rc = 1;
    *((u16 *) (ctx + 4)) -= 0x20;
    *((u16 *) (ctx + 6)) -= 0x20;
    new_var = *((u8 **) (obj + 0x2C));
    target = new_var;
    value = *((s16 *) (ctx + 4));
    *((s16 *) (target + 6)) = divInt32(0x1000, value);
    target = *((u8 **) (obj + 0x2C));
    value = *((s16 *) (ctx + 6));
    *((s16 *) (target + 8)) = divInt32(0xB00, value);
    if ((*((s16 *) (ctx + 4))) <= 0x100)
    {
      *((u8 *) ((entity + (((s32) (*((s16 *) (entity + 0x22)))) * 2)) + 0x19)) = 0;
      {
        s32 *pd = &gScriptStepCallbackTable;
        sub_080C31E4(entity + 0x18, entity + 0x22, *pd);
      }
    }
    *((s32 *) (subObj + 4)) += *((s32 *) (obj + 8));
    sub_0806D588(ctx, obj);
    if ((gMainWorkspace.field173A == 0x1C) || ((gMainWorkspace.field14ED == 0) && (gMainWorkspace.field10 != 0)))
    {
      sub_080C31E0(entity, *((s32 *) (entity + 0x24)));
    }
  }
}
