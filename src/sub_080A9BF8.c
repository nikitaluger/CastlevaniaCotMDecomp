s32 setObjectAnimation(s32, s32, s32, s32);
s32 sub_08011528(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

inline s32 ActorOf(void *obj)
{
  return *((s32 *) (((u8 *) obj) + 0x38));
}

/* Advance the actor's sprite animation; when the script counter at the current
 * step reaches the value at obj+0x70, switch to animation 0x2C and step on. */
void sub_080A9BF8(void *arg0)
{
  s32 anim;
  void *self;
  s32 actor;
  actor = ActorOf(arg0);
  anim = (*((s32 *) (((u8 *) arg0) + 0x3C))) + 0x34;
  self = arg0;
  sub_08011528(actor, anim);
  if ((*((u8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) == (*((u8 *) (((u8 *) self) + 0x70))))
  {
    setObjectAnimation(actor, anim, 0x2C, 0);
    *((s8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    actor = 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) actor));
  }
}
