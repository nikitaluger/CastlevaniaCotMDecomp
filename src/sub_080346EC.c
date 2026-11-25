extern void sub_08005E80(s32);
extern s32 sub_08013B5C(s32, void *);
extern void sub_08013C8C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern s32 sub_08016238(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BDC;
typedef struct
{
  u16 flags;
  u8 _p1[0x14 - 2];
  u32 callbackTable;
  u8 _p2[0x22 - 0x18];
  s16 stepIndex;
  u32 despawnReason;
  void *contact;
  u8 _p3[0x38 - 0x2C];
  u32 sprite;
  void *actor;
} ScriptObj;

/* Runs one tick of a scripted entity: flags the actor when its state changes,
 * performs a one-time step action, then dispatches the current script step. */
void sub_080346EC(ScriptObj *self)
{
  void *sprite = (void *) self->sprite;
  ScriptObj *actor = (ScriptObj *) self->actor;
  if (sub_080141AC((s32) sprite, actor) == 1)
  {
    sub_080C31E0(self, (s32) self->despawnReason);
    return;
  }
  if (sub_08016238(actor->contact) != 0)
  {
    actor->flags = (u16) (1 | actor->flags);
  }
  if (1 & (*((u16 *) (((u8 *) actor->contact) + 0x14))))
  {
    actor->flags = (u16) (1 | actor->flags);
  }
  if ((1 & actor->flags) && ((*((u8 *) ((((u8 *) self) + (((s32) self->stepIndex) * 2)) + 0x1A))) != 1))
  {
    sub_08005E80(0x189);
    *(((u8 *) actor->contact) + 1) = 0;
    *((((u8 *) self) + (((s32) self->stepIndex) * 2)) + 0x1B) = 0;
    {
      s32 *fnaddr = &D_08671BDC;
      sub_080C31E8(((u8 *) self) + 0x18, ((u8 *) self) + 0x22, 1, *fnaddr);
    }
  }
  if (sub_08013B5C((s32) sprite, actor) == 0)
  {
    s32 stepOffset;
    u8 *stepByte;
    u8 stepId;
    u32 callback;
    self->callbackTable = (u32) 0x0866DD60;
    self->stepIndex = (s16) (((u16) self->stepIndex) + 1);
    (((u8 *) self) + (((s32) self->stepIndex) * 2))[0x19] = (u8) (((((u8 *) self) + (((s32) self->stepIndex) * 2))[0x19]) + 1);
    stepOffset = self->stepIndex * 2;
    stepByte = ((u8 *) self) + 0x18;
    stepByte = stepByte + stepOffset;
    stepId = *stepByte;
    callback = self->callbackTable;
    callback = *((u32 *) (callback + (stepId * 4)));
    sub_080C31E0(self, (s32) callback);
    self->stepIndex = (s16) (((u16) self->stepIndex) - 1);
  }
  sub_08013C8C(self, (s32) sprite);
}
