s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void stepAnimationTrack(void *, void *);
void advanceMotion(void *, s32);
void sub_080C31E4(void *, void *, s32);
extern u32 gMainWorkspace[];

/* Action-script object shared with the command handlers at 0x080B95CC..:
 * 0x14 command-pointer table, 0x18 per-step command bytes, 0x22 step index,
 * 0x24 mode-7 handler, 0x38 sprite, 0x3C work/position struct. */
struct ActionScript
{
  u8 _0x00[0x14];
  u32 field_0x14;
  u8 _0x18[0x0A];
  s16 field_0x22;
  u32 field_0x24;
  u8 _0x28[0x10];
  u32 field_0x38;
  u32 field_0x3C;
};

/* Wait for the current step's sprite animation to finish; when it has, step the
 * script forward, bump the new step's repeat counter and run its command
 * callback once, then refresh the sprite's screen position. (Script table
 * 0x0867058C, the twin of sub_080B5E90.) */
void sub_080B956C(struct ActionScript *arg0)
{
  int cmdArrayOffset;
  int stepOffset;
  void *sprite = (void *) arg0->field_0x38;
  if (updateObjectDisplayState(sprite, (void *) arg0->field_0x3C) == 0)
  {
    arg0->field_0x14 = 0x0867058C;
    arg0->field_0x22 += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->field_0x22 * 2)) + 0x19)) += 1;
    cmdArrayOffset = 0x18;
    stepOffset = arg0->field_0x22 * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + cmdArrayOffset) + stepOffset)))) * 4) + arg0->field_0x14)));
    arg0->field_0x22 -= 1;
  }
  sub_08013C8C(arg0, sprite);
}

/* Animate the linked body, accelerate it horizontally by the fixed-point value
 * at self+0x7C, then integrate its position from its velocity. */
void sub_080B9398(void *arg0) {
    u8 *self = arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *body = *(u8 **)(self + 0x3C);
    stepAnimationTrack((void *)sprite, body + 0x34);
    *(s32 *)(body + 0x10) += *(s32 *)(self + 0x7C) << 13;
    advanceMotion(body, 0);
}

/* Animate the linked body; after 0x10 phase steps restart the counter and
 * advance to the next script command. */
void sub_080B935C(void *arg0) {
    u8 *self = arg0;
    stepAnimationTrack(*(s32 *)(self + 0x38), *(u8 **)(self + 0x3C) + 0x34);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x10) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}

/* In game mode 7 (gMainWorkspace word 16) run this object's mode handler at
 * self+0x24; otherwise just keep the sprite coordinates in sync. */
void sub_080B97F0(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    if (gMainWorkspace[16] == 7) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }
    sub_08013C8C(arg0, sprite);
}
