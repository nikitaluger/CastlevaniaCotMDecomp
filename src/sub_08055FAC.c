void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
void sub_08056BD8(void *, void *);
void sub_08056BF0(void *, void *);

/* Advance one step of an entity's behaviour script. First propagate the
 * component's position and active state to its linked list of child entities,
 * then run the script action selected by the current step. */
void sub_08055FAC(void *entity)
{
  int argAddr;
  void *parent;
  void *component;
  s32 action;
  u8 *self = (u8 *) entity;
  parent = *((void **) (self + 0x38));
  component = *((void **) (self + 0x3C));
  applySpritePaletteVariant(self, parent);
  sub_08056BD8(self, component);
  if (checkActorViewBounds(parent, component) == 1)
  {
    return;
  }
  if (sub_08013558(parent, component, *((void **) (((u8 *) component) + 0x28))) != 0)
  {
    spawnContactEffectOnHit(self, *((void **) (((u8 *) component) + 0x28)));
  }
  uploadPendingSpriteGraphic(self, *((void **) (((u8 *) component) + 0x28)));
  if ((*((u16 *) component)) & 1)
  {
    u8 *stepPtr;
    u8 opcode;
    s32 pcOffset;
    updateActorWorldPosition(self);
    {
      u8 *stepPtr;
      stepPtr = (u8 *) ((((u32) (*((s16 *) (((u8 *) entity) + 0x22)))) * 2) + ((u32) entity));
      *((u8 *) (stepPtr + 0x19)) = 0;
    }
    argAddr = 0x08671BB0;
    sub_080C31E4(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, *((u32 *) argAddr));
    {
      u8 *stepPtr;
      stepPtr = (u8 *) ((((u32) (*((s16 *) (((u8 *) entity) + 0x22)))) * 2) + ((u32) entity));
      *((u8 *) (stepPtr + 0x19)) = (*((u8 *) (stepPtr + 0x19))) + 1;
    }
    pcOffset = ((s32) ((s16) (*((s16 *) (((u8 *) entity) + 0x22))))) * 2;
    stepPtr = ((u8 *) entity) + 0x18;
    stepPtr += pcOffset;
    opcode = *stepPtr;
    action = *((s32 *) (((u32) (opcode * 4)) + (*((u32 *) (((u8 *) entity) + 0x14)))));
    sub_080C31E0((s32) entity, action);
    return;
  }
  sub_08056BF0(self, component);
  if (updateObjectDisplayState(parent, component) == 0)
  {
    u8 *stepPtr;
    u8 opcode;
    s32 pcOffset;
    *((u32 *) (((u8 *) entity) + 0x14)) = 0x0866E780;
    *((u16 *) (((u8 *) entity) + 0x22)) = (*((u16 *) (((u8 *) entity) + 0x22))) + 1;
    {
      u8 *stepPtr;
      stepPtr = (u8 *) ((((u32) (*((s16 *) (((u8 *) entity) + 0x22)))) * 2) + ((u32) entity));
      *((u8 *) (stepPtr + 0x19)) = (*((u8 *) (stepPtr + 0x19))) + 1;
    }
    pcOffset = ((s32) ((s16) (*((s16 *) (((u8 *) entity) + 0x22))))) * 2;
    stepPtr = ((u8 *) entity) + 0x18;
    stepPtr += pcOffset;
    opcode = *stepPtr;
    sub_080C31E0((s32) entity, *((s32 *) (((u32) (opcode * 4)) + (*((u32 *) (((u8 *) entity) + 0x14))))));
    *((u16 *) (((u8 *) entity) + 0x22)) = (*((u16 *) (((u8 *) entity) + 0x22))) - 1;
  }
  sub_08013C8C(entity, parent);
}
