extern s64 sub_0808FBB4(void);
extern void sub_08005E80(s32);
extern void sub_08011344(s32, s32, s16, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_081003AC[]; /* animation frames: u16 id at +2, stride 4 */

/* When the reference point is outside the entity's activation box, restart its
 * animation from the table at D_081003AC, reset its animation/script state, play
 * sound 0x73 and move on to the next handler from 0x08671BB0. */
void sub_0808FAC8(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s16 stateIndex;
  u8 *view = *((u8 **) (self + 0x38));
  u8 *body = *((u8 **) (self + 0x3C));
  u8 *anim = body + 0x18;
  u32 zero;
  if (((s32) sub_0808FBB4()) == 0)
  {
    u8 *frameTable;
    s16 frameId;
    s32 *handlerTable;
    u32 frameOffset;
    frameTable = D_081003AC;
    frameOffset = (*((s32 *) body)) * 4;
    frameTable += 2;
    frameId = *((s16 *) (frameTable + frameOffset));
    sub_08011344((s32) view, (s32) anim, frameId, 0);
    zero = 0;
    *((u16 *) (body + 0x16)) = 1;
    *((u8 *) ((*((u8 **) (body + 4))) + 1)) = 7;
    sub_08005E80(0x73);
    stateIndex = *((s16 *) (self + 0x22));
    *((u8 *) ((self + (stateIndex * 2)) + 0x19)) = (u8) zero;
 do { handlerTable = (s32 *) 0x08671BB0; sub_080C31E4(self + 0x18, self + 0x22, *handlerTable); } while (0);
  }
}
