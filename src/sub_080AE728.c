s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void _call_via_r1(void *, void *);
void _call_via_r2(void *, void *, s32);
void sub_08011368(void *, void *, s32, s32);
void sub_0801165C(void *, s32);
extern u16 D_03000830[4];
struct S_02025FF0_18BC { u8 _0[0x18BC]; u16 v; };
extern struct S_02025FF0_18BC D_02025FF0_18BC;

struct ActorCmd
{
  u8 _0x00[0x14];
  u32 handlerTable;
  u8 _0x18[0x0A];
  s16 step;
  u32 _0x24;
  u8 _0x28[0x10];
  u32 sprite;
  u32 work;
};
/* Once the sprite check passes, install the command handler table, advance the
 * script step and dispatch its handler; then refresh the sprite position. */
void sub_080AE6C8(struct ActorCmd *actor)
{
  int cmdOffset;
  int stepOffset;
  void *sprite = (void *) actor->sprite;
  if (sub_08013B5C(sprite, (void *) actor->work) == 0)
  {
    actor->handlerTable = 0x086701EC;
    actor->step += 1;
    *((u8 *) ((((u8 *) actor) + (actor->step * 2)) + 0x19)) += 1;
    cmdOffset = 0x18;
    stepOffset = actor->step * 2;
    _call_via_r1(actor, *((void **) ((((u32) (*((u8 *) ((((u8 *) actor) + cmdOffset) + stepOffset)))) * 4) + actor->handlerTable)));
    actor->step -= 1;
  }
  sub_08013C8C(actor, sprite);
}

/* At sub-step 2, play animation 9, set the work's velocity and restart the script. */
void sub_080AE728(void *arg0) {
    u8 *actor = arg0;
    u8 *sprite = *(u8 **)(actor + 0x38);
    u8 *work = *(u8 **)(actor + 0x3C);
    u8 *anim = work + 0x34;
    s32 *advanceCb;
    if (*(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) == 2) {
        sub_08011368(sprite, anim, 9, 0);
        *(u32 *)(work + 0x14) = 0xFFFC0000;
        *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        advanceCb = (s32 *)0x08671BB0;
        _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
    }
}

/* Write the actor's global effect state and restart the script at sub-step 0xF0. */
void sub_080AEAF0(void *arg0) {
    u8 *actor = arg0;
    u8 value;
    u8 *stepBase;
    s32 *advanceCb;
    D_03000830[2] = 0xFD << 6;
    value = *(u8 *)(actor + 0x50);
    D_03000830[3] = (u16)(value | ((0x10 - value) << 8));
    D_02025FF0_18BC.v = 1;
    stepBase = actor + *(s16 *)(actor + 0x22) * 2;
    if (*(u8 *)(stepBase + 0x19) == 0xF0) {
        *(u8 *)(stepBase + 0x19) = 0;
        advanceCb = (s32 *)0x08671BB0;
        _call_via_r2(actor + 0x18, actor + 0x22, *advanceCb);
    }
}

/* Add 0x800 to the sprite's OAM attribute 0, then integrate the work's motion. */
void sub_080AE09C(void *arg0) {
    u16 *attr0 = *(u16 **)((u8 *)arg0 + 0x38);
    int rotated;
    rotated = 0x800 + *attr0;
    *attr0 = (u16)rotated;
    sub_0801165C(*(void **)((u8 *)arg0 + 0x3C), 0);
}
