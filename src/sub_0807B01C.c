struct S_02025FF0_7B01C
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
extern struct S_02025FF0_7B01C D_02025FF0;
extern s32 sub_0806D450(void *, void *, void *);
extern void sub_0806D2F8(void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_080C31E0(void *, void *);

/* Gravity step: if no special area behaviour claims the entity, accelerate its
 * vertical velocity, integrate x/y, then either spawn a landing effect and hand
 * control to the entity callback (when the flags ask for it) or snap the
 * position vector to the grid and refresh the state object. */
void sub_0807B01C(void *arg0)
{
  void *entity = arg0;
  void *body = *((void **) (((u8 *) entity) + 0x6C));
  u8 *bodyPos = ((u8 *) body) + 4;
  u8 *stateObj = *((u8 **) (((u8 *) entity) + 0x38));
  u8 *vec = bodyPos;
  s32 vy;
  s32 newY;
  u16 flags;
  if (sub_0806D450(entity, stateObj, vec) == 0)
  {
    vy = (*((s32 *) (vec + 0xC))) + 0x4000;
    *((s32 *) (vec + 0xC)) = vy;
    if (vy > 0x80000)
    {
      *((s32 *) (vec + 0xC)) = 0x80000;
    }
    *((s32 *) (((u8 *) body) + 4)) += *((s32 *) (vec + 8));
    newY = (*((s32 *) (vec + 4))) + (*((s32 *) (vec + 0xC)));
    *((s32 *) (vec + 4)) = newY;
    flags = *((u16 *) ((*((u8 **) (vec + 0x2C))) + 0x14));
    if (!(flags & 1))
    {
      goto skip;
    }
    if (flags & 2)
    {
      goto skip;
    }
    sub_0808DBF8(*((s32 *) (((u8 *) body) + 4)), newY, 0);
    goto block_9;
    skip:
    ;

    ;
    *((u16 *) stateObj) = D_02025FF0.f18C2;
    sub_08003740(bodyPos + 0x1C, stateObj);
    sub_0806D588(stateObj, vec);
    if ((D_02025FF0.f173A == 0x1C) || ((D_02025FF0.f14ED == 0) && (D_02025FF0.f10 != 0)))
    {
      block_9:
      sub_080C31E0(entity, *((void **) (((u8 *) entity) + 0x24)));

    }
    else
    {
 do { sub_0806D2F8(entity, stateObj); } while (0);
    }
  }
}
