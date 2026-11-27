void *allocSpriteObject(void);
void allocWorkSlot(void *, s32, s32, s32);
void setObjectAnimation(void *, s32, s32, s32);
s32 findKindIndex(void);
void installUpdateHandler(void *, void *, void *);
void sub_0809C2F0(void *, void *, s32, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
extern u32 gMainObjTimerCallbacks;
struct Obj {
  u8 _0[2]; u16 f02; u8 _1[0x14 - 4]; u32 f14;
  u8 _2[0x22 - 0x18]; s16 f22; u32 f24;
  u8 _3[0x38 - 0x28]; u32 f38; u32 f3C;
  u8 _4[0x7C - 0x40]; u8 f7C;
};
struct R6 { u16 f00; u8 _0[0x1C - 2]; u32 f1C; };
struct R4 { u8 _0[0x1C]; u16 f1C; u8 _1[0x22 - 0x1E]; u16 f22; };

/* Set up a companion sprite for this object, initialise its script state, then
 * dispatch the current script step from the object's handler table. */
void sub_0809A750(struct Obj *obj)
{
  u32 opcode;
  struct Obj *dispatchObj;
  struct R6 *sprite;
  struct R4 *scriptState;
  struct Obj *objSelf;
  s32 playerIndex;
  u8 *objBytes;
  u8 *handlerPtr;
  u8 *stateArg;
  u8 *stepTable;
  u16 *stepIndexPtr;
  u8 *opcodePtr;
  u32 stepValue;
  u32 fn;
  s16 stepIndex;
  u8 zeroByte;
  sprite = allocSpriteObject();
  if (sprite == 0) goto done;
  obj->f38 = (u32) sprite;
  allocWorkSlot(obj, 0, 0x48, 0);
  if (obj->f3C == 0) { if (1) { goto done; } }
  sprite->f1C = 8;
  scriptState = (struct R4 *) obj->f3C;
  stateArg = ((u8 *) scriptState) + 0x34;
  installUpdateHandler(obj, scriptState, (void *)0x08097D91);
  zeroByte = 0;
  scriptState->f1C = 0x44;
  playerIndex = findKindIndex();
  scriptState->f22 = playerIndex;
  if ((playerIndex << 16) >= 0) goto setupDone;
done:
  sub_080C31E0(obj, obj->f24);
  return;
setupDone:
  sprite->f00 = gMainWorkspace.f18C2;
  sub_0809C2F0(sprite, stateArg, 0x20, 4);
  setObjectAnimation(sprite, stateArg, 0x13, 0);
  objSelf = obj;
  objSelf->f7C = zeroByte;
  objSelf->f02 = objSelf->f02 | 0x1000;
  stepIndex = objSelf->f22;
  stepIndexPtr = (u16 *) objSelf;
  ((u8 *) (&stepIndexPtr[stepIndex]))[0x19] = zeroByte;
  objBytes = (u8 *) objSelf;
  {
    u32 *pbb0 = &gMainObjTimerCallbacks;
    stepTable = objBytes + 0x18;
    sub_080C31E4((s32) stepTable, (s32) (objBytes + 0x22), (s32) (*pbb0));
  }
  dispatchObj = objSelf;
  stepIndex = objSelf->f22;
  stepIndexPtr = (u16 *) dispatchObj;
  fn = stepIndex;
  handlerPtr = (u8 *)((s32)(fn << 1) + (s32)dispatchObj);
  handlerPtr[0x19] = handlerPtr[0x19] + 1;
  stepIndex = objSelf->f22;
  stepIndexPtr = (u16 *) stepTable;
  opcodePtr = (u8 *) (&stepIndexPtr[stepIndex]);
  handlerPtr = opcodePtr;
  stepValue = *handlerPtr;
  opcode = stepValue;
  fn = *((u32 *) (((u8 *) objSelf->f14) + (opcode * 4)));
  sub_080C31E0(dispatchObj, fn);
}
