extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern s32 findKindIndex(void);
extern void installUpdateHandler(void *, void *, void *);
extern void initSpriteGfx(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);
struct S_02025FF0 { u8 _0[0x18C2]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
extern u32 gMainObjTimerCallback;
extern u8 D_08102F0C[];
struct Entity {
  u8 _0[2]; u16 flags; u8 _1[0x14 - 4]; u32 actionTable; u8 _2[0x22 - 0x18];
  s16 scriptPc; u32 onFailAction; u8 _3[0x38 - 0x28]; u32 spawnedObj; u32 component;
  u8 _4[0x4C - 0x40]; u32 dataIndex; u8 _5[0x5C - 0x50]; u32 timer;
};
struct SpawnObject { u16 flags; u16 flags2; u8 _0[0x1C - 4]; u32 config; u8 _1[0x2A - 0x20]; u8 statusFlag; };
struct Component { u8 _0[0x1C]; u16 param; u8 _1[0x22 - 0x1E]; u16 kind; };

/* Spawn and configure a new object for an entity's action, then dispatch the
 * script step's callback from the entity's handler table; if the spawn or
 * component setup fails, despawn instead. */
void sub_080BC050(struct Entity *entity)
{
  struct SpawnObject *spawnedObj;
  struct Component *component;
  u8 *scriptPlayer;
  s32 kind;
  u8 *stepPtr;
  u32 opcode;
  u32 action;
  s16 pcOffset;
  u16 *pcWords;
  u16 *stepEntry;
  spawnedObj = allocSpriteObject();
  if (spawnedObj == NULL) goto Lend;
  entity->spawnedObj = (u32)spawnedObj;
  allocWorkSlot(entity, 0, 0x48, 0);
  if (entity->component == 0) goto Lend;
  spawnedObj->config = 0x80000009;
  spawnedObj->statusFlag &= 0xBF;
  component = (struct Component *)entity->component;
  scriptPlayer = ((u8 *)component) + 0x34;
  installUpdateHandler(entity, component, &sub_08097D90);
  component->param = 0x68;
  kind = findKindIndex();
  component->kind = kind;
  if ((kind << 16) >= 0) goto Lcont;
Lend:
  sub_080C31E0(entity, entity->onFailAction);
  return;
Lcont:
  spawnedObj->flags = spawnedObj->flags | gMainWorkspace.f18C2;
  initSpriteGfx(spawnedObj, scriptPlayer, D_08102F0C[entity->dataIndex], 2);
  spawnedObj->flags2 = spawnedObj->flags2 | 0x400;
  entity->timer = 0;
  entity->flags = entity->flags | 0x1000;
  pcOffset = entity->scriptPc;
  pcWords = (u16 *)entity;
  ((u8 *)(&pcWords[pcOffset]))[0x19] = 0;
  {
    u32 *pbb0 = &gMainObjTimerCallback;
    stepPtr = ((u8 *)entity) + 0x18;
    sub_080C31E4(stepPtr, ((u8 *)entity) + 0x22, *pbb0);
  }
  pcOffset = entity->scriptPc;
  pcWords = (u16 *)entity;
  ((u8 *)(&pcWords[pcOffset]))[0x19] = ((u8 *)(&pcWords[pcOffset]))[0x19] + 1;
  pcOffset = entity->scriptPc;
  pcWords = (u16 *)stepPtr;
  stepEntry = &pcWords[pcOffset];
  opcode = ((u8 *)stepEntry)[0];
  action = *((u32 *)(((u8 *)entity->actionTable) + (opcode * 4)));
  sub_080C31E0(entity, action);
}
