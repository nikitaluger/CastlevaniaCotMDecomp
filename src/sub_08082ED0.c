extern s32 sub_0806D450(void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_080C31E0(void *, void *);
struct S_02025FF0_82ED0
{
  u8 _0[0x10];
  u32 f10;
  u8 _14[0x14ED - 0x14];
  u8 f14ED;
  u8 _14EE[0x173A - 0x14EE];
  u8 f173A;
  u8 _173B[0x18C2 - 0x173B];
  u16 f18C2;
};
extern struct S_02025FF0_82ED0 gMainWorkspace;

// Updates an attached projectile/effect: runs the special-behavior check,
// integrates its velocity into the target object, advances its countdown timer
// and cancels the entity on a stop condition or when it leaves the world bounds.
void sub_08082ED0(void *entity)
{
  void *self = entity;
  void *child;
  u8 *vec;
  u8 *obj;
  child = *((void **) (((u8 *) self) + 0x6C));
  vec = ((u8 *) child) + 4;
  obj = *((u8 **) (((u8 *) self) + 0x38));
  if (((sub_0806D450(self, obj, vec) > 0) || ((*((u32 *) (obj + 0x14)) += *((u32 *) (vec + 8)), *((u32 *) (obj + 0x18)) += *((u32 *) (vec + 0xC)), *((u16 *) (obj + 0)) = gMainWorkspace.f18C2, sub_08003740(((u8 *) child) + 0x20, obj), gMainWorkspace.f173A == 0x1C))) || ((gMainWorkspace.f14ED == 0) && (gMainWorkspace.f10 != 0)))
  {
    sub_080C31E0(self, *((void **) (((u8 *) self) + 0x24)));
    return;
  }
  if ((*((s32 *) (obj + 0x18))) > 0xE00000)
  {
 do { sub_080C31E0(self, *((void **) (((u8 *) self) + 0x24))); } while (0);
  }
}
