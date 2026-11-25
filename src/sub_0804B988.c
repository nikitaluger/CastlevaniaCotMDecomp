extern void sub_080113A8(void *, void *);
extern void sub_08011674(void *, s32, s32);
extern s32 sub_08013B5C(void *, void *);
extern void sub_0804BB7C(void *, void *);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080C31E0(void *, void *);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_0866E47C[];

struct ActorStatus { u8 unk0; u8 flags; };

/* Advances one step of an entity's behaviour script, then writes its adjusted
 * world position from the camera-relative coordinate tables for this frame. */
void sub_0804B988(u8 *entity)
{
  u8 *parent;
  u8 *component;
  u8 *scriptPlayer;
  struct ActorStatus *status;
  u8 *stepPtr;
  u8 *tableBase;
  u8 *xTable;
  u8 *scrollIndexPtr;
  u32 tableOffset;
  u32 xScroll;
  u32 yScroll;
  u8 opcode;
  u8 *opcodePtr;
  s32 pcOffset;

  parent = *((u8 **) (entity + 0x38));
  component = *((u8 **) (entity + 0x3C));
  scriptPlayer = component + 0x34;
  status = *((struct ActorStatus **) (component + 0x28));
  status->flags |= 1;
  if (sub_0805F9B4(*((s32 *) (component + 0x08)), *((s32 *) (component + 0x0C))) == 1)
  {
    sub_080C31E0(entity, *((s32 *) (entity + 0x24)));
    return;
  }
  if (sub_08013B5C(parent, component) != 0)
  {
    goto common;
  }
  *((u32 *) (entity + 0x14)) = (u32) D_0866E47C;
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) + 1;
  stepPtr = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
  *((u8 *) (stepPtr + 0x19)) = (*((u8 *) (stepPtr + 0x19))) + 1;
  pcOffset = (*((s16 *) (entity + 0x22))) * 2;
  opcodePtr = entity;
  opcodePtr += 0x18;
  opcode = *((u8 *) (((u32) opcodePtr) + ((u32) pcOffset)));
  sub_080C31E0((void *) entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + (opcode * 4))));
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) - 1;
  if (((*((u16 *) (entity + 2))) & 0x8000) != 0)
  {
    return;
  }
  sub_080113A8(parent, scriptPlayer);
  sub_08011674(component, 0x80000, 0x80000);
  common:
  sub_0804BB7C(entity, parent);

  tableBase = D_02021E90;
  scrollIndexPtr = D_02025FF0;
  scrollIndexPtr += 0x18A8;
  tableOffset = (((u32) (*scrollIndexPtr)) + 1) * 0x40;
  xTable = tableBase + 0x1278;
  xScroll = *((u32 *) (xTable + tableOffset));
  *((u32 *) (parent + 0x14)) = (*((u32 *) (component + 8))) - ((xScroll + 0x8000) & 0xFFFF0000);
  tableOffset = (((u32) (*scrollIndexPtr)) + 1) * 0x40;
  tableBase += 0x127C;
  yScroll = *((u32 *) (tableBase + tableOffset));
  *((u32 *) (parent + 0x18)) = (*((u32 *) (component + 0x0C))) - ((yScroll + 0xFFFF8000) & 0xFFFF0000);
}
