/* Drive an entity's animation from a target object's state: tick the sound
 * counter, play a sound, then on states 2 or 0 update the pose, frame data and
 * animation command. */
extern void sub_080114DC(s32, s32, s32, s32);
extern void sub_08014588(void *, s32);
extern void sub_0809856C(s32, void *, s32);
extern void sub_0809E4F8(void *);
extern s32 sub_080A041C(s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_0809D93C(void *arg0)
{
  u8 *entity = arg0;
  s32 view = *(s32 *)((u8 *)entity + 0x38);
  u8 *body = *(u8 **)((u8 *)entity + 0x3C);
  u8 *bodyData = body + 0x34;
  u8 *motion = body + 0x48;
  sub_0809856C(0x16E, body + 0x8C, 0x0C);
  sub_0809E4F8(arg0);
  if (sub_080A041C(*(s32 *)(motion + 0x28)) == 2)
  {
    *(u8 *)(motion + 0x0D) = 1;
    *(s32 *)(body + 0x0C) = *(s32 *)(motion + 0x08) + (s32)0xFFDE0000;
    sub_080114DC(view, (s32)bodyData, 0x1A, 1);
  }
  {
    s32 state = sub_080A041C(*(s32 *)(motion + 0x28));
    if (state == 0)
    {
      *(u8 *)(*(u8 **)(body + 0x28) + 0x01) = 1;
      sub_08014588(*(u8 **)(body + 0x28), 0x081019AC);
      *(s32 *)(motion + 0x44) = state;
      *(u8 *)((u8 *)entity + ((*(s16 *)((u8 *)entity + 0x22)) * 2) + 0x19) = (u8)state;
      {
        s32 *animScript = (s32 *)0x08671BB0;
        u8 *animState = (u8 *)entity + 0x18;
        sub_080C31E4(animState, (u8 *)entity + 0x22, *animScript);
      }
    }
  }
}
