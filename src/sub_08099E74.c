extern void setObjectAnimation(s32, s32, s32, s32);
extern void initCrossfadeGfxState(void);
extern void setEffectBehavior(void *, s32);
extern void sub_0809C510(void *, s32, s32);
extern void sub_080C050C(s32);
extern void sub_080C31E4(void *, void *, s32);

/* Handle a state effect: based on its id spawn a projectile or play a sound, tick a counter, and on wrap set the end animation, refresh the HUD, and finish the state. */
void sub_08099E74(void *arg0)
{
  u8 *self = arg0;
  u8 *gfx = *(u8 **)((u8 *)self + 0x38);
  u8 *entity = *(u8 **)((u8 *)self + 0x3C);
  u8 *anim = entity + 0x34;
  u8 *state = entity + 0x48;
  u8 stateId = *(u8 *)((u8 *)self + ((*(s16 *)((u8 *)self + 0x22)) * 2) + 0x19);
  if (stateId > 3)
  {
    if (stateId <= 7)
    {
      sub_0809C510(*(void **)(state + 0x08), *(s32 *)(state + 0x18), 1);
    }
    else
    {
      sub_080C050C(0x166);
      setEffectBehavior(*(void **)(state + 0x08), 0);
      sub_0809C510(*(void **)(state + 0x08), *(s32 *)(state + 0x18), 0);
    }
    {
      s32 counter = (s32)*(u16 *)(state + 0x24) + 0x80;
      s32 wrapped;
      *(u16 *)(state + 0x24) = (u16)counter;
      wrapped = counter << 16;
      if (wrapped == 0)
      {
        wrapped = 1;
        *(u8 *)(*(u8 **)(*(u8 **)(*(u8 **)(state + 0x08) + 0x3C) + 0x28) + 0x01) = 5;
        setEffectBehavior(*(void **)(state + 0x08), 1);
        setObjectAnimation((s32)gfx, (s32)anim, 0x0F, 0);
        initCrossfadeGfxState();
        *(u8 *)((u8 *)self + ((*(s16 *)((u8 *)self + 0x22)) * 2) + 0x19) = 0;
        {
          s32 *cbTable = (s32 *)0x08671BB0;
          u8 *cbArg = (u8 *)self + 0x18;
          sub_080C31E4(cbArg, (u8 *)self + 0x22, *cbTable);
        }
      }
    }
  }
}
