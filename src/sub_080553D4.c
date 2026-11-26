void setAnimationFrame(s32, void *, s32, s32); /* set animation frame */
void sub_080C31E4(void *, void *, s32); /* _call_via_r2 */
struct WorkFlags { u8 pad[4]; u16 flags; };

/* Idle-animation command: request frame 2; when the animation reports that it
 * finished, raise work flag 0x200, clear the current step's byte and run the
 * next command. */
void sub_080553D4(void *arg0)
{
  u8 *actor = (u8 *)arg0;
  s32 sprite = *(s32 *)(actor + 0x38);
  u8 *work = *(u8 **)(actor + 0x3C);
  u8 *anim = work + 0x34;
  setAnimationFrame(sprite, anim, 2, 0);
  if (*anim & 2) {
    s32 zero = 0;
    void **stream;
    ((struct WorkFlags *)work)->flags |= 0x200;
    *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = zero;
    stream = (void **)0x08671BB0;
    sub_080C31E4(actor + 0x18, actor + 0x22, (s32)*stream);
  }
}
