struct ScriptTargetFlags { u8 f0; u8 hitFlags; };
struct MainWorkspace { u8 _0[0x18A8]; u8 frameCounter; };
struct ScriptObject {
  u8 _0[2];
  u16 flags;
  u8 _4[0x10];
  u32 stepTable;
  u8 _18[0x0A];
  s16 stepIndex;
  u32 cleanupCb;
  u8 _28[0x10];
  u32 sprite;
  u32 work;
  u8 _40[0x2C];
  u16 f6C;
};
struct SpriteObj { u8 _0[0x14]; u32 screenX; u32 screenY; u8 _1C[0xE]; u8 f2A; };
struct WorkState {
  u16 hitFlags;
  u16 flags;
  u8 _04[4];
  u32 worldX;
  u32 worldY;
  u32 f10;
  u32 f14;
  u8 _18[0x10];
  void *target;
};

extern void sub_08005E80(s32);              /* play a sound effect */
extern void sub_080113A8(s32, void *);      /* advance an animation track */
extern void sub_08011EE8(void *, s32, s32); /* effect at the work state's position */
extern s32 sub_08013B5C(s32, void *);       /* apply the object's display state */
extern s32 hitTestEntities(void *);         /* hit-test the collision target */
extern void sub_0802CB5C(s32, void *);      /* refresh the sprite's frame parameters */
extern s32 sub_0805F9B4(s32, s32);          /* outside camera bounds? */
extern void sub_080C31E0(void *, void *);   /* indirect cleanup callback */
extern void sub_080C31E8(void *, void *, s32, void *); /* indirect script handler */
extern void *sScriptStepCallbacks;
extern u8 gCameraState[];                     /* scroll-offset table */
extern struct MainWorkspace gMainWorkspace;

/* Per-frame update of a script-driven object: test camera bounds and hits, run
   the death/cancel path, dispatch one command from the object's script table,
   then place the sprite in camera space. */
void updateScriptedObject(struct ScriptObject *obj)
{
  struct SpriteObj *sprite;
  struct WorkState *work;
  u8 *animTrack;
  u8 *stepState;
  struct ScriptTargetFlags *target;
  struct ScriptTargetFlags *target2;
  s32 zero;
  s32 stepOffset;
  u8 *scriptBase;
  u8 opcode;
  void **stepHandlers;
  u32 coordOffset;
  u8 *cameraTable;
  u32 originX;
  u32 originY;

  sprite = (struct SpriteObj *)obj->sprite;
  work = (struct WorkState *)obj->work;
  animTrack = ((u8 *)work) + 0x34;
  stepState = ((u8 *)work) + 0x48;
  target = (struct ScriptTargetFlags *)work->target;
  target->hitFlags |= 5;
  if (sub_0805F9B4(work->worldX, work->worldY) == 1) {
    sub_080C31E0(obj, (void *)obj->cleanupCb);
    return;
  }
  if (hitTestEntities(work->target) != 0) {
    work->hitFlags |= 1;
  }
  target2 = (struct ScriptTargetFlags *)work->target;
  if (((*(u16 *)((u8 *)target2 + 0x14)) & 1) || (work->flags & 0xD)) {
    work->hitFlags |= 1;
  }
  if (work->hitFlags & 1) {
    target2->hitFlags &= 0xFB;
    {
      u8 *q = (u8 *)(((u32)obj->stepIndex) * 2 + (u32)obj);
      if (q[0x1A] != 1) {
        zero = 0;
        *(u16 *)stepState = zero;
        sub_0802CB5C((s32)sprite, work);
        sub_08005E80(0x18A);
        ((u8 *)(((u32)obj->stepIndex) * 2 + (u32)obj))[0x1B] = zero;
        {
          void **fnaddr = &sScriptStepCallbacks;
          sub_080C31E8(((u8*)obj) + 0x18, ((u8*)obj) + 0x22, 1, *fnaddr);
        }
      }
    }
  }
  if ((sub_08013B5C((s32)sprite, work) != 0) && (*(s16 *)stepState != 0)) {
    goto lab_de;
  }
  obj->stepTable = (u32)gObjectScriptStepTable;
  obj->stepIndex = obj->stepIndex + 1;
  {
    u8 *q = (u8 *)(((u32)obj->stepIndex) * 2 + (u32)obj);
    q[0x19] = q[0x19] + 1;
  }
  stepOffset = obj->stepIndex * 2;
  scriptBase = ((u8 *)obj) + 0x18;
  opcode = *(scriptBase + stepOffset);
  stepHandlers = *(void **)(&obj->stepTable);
  sub_080C31E0(obj, stepHandlers[opcode]);
  obj->stepIndex = obj->stepIndex - 1;
  if ((obj->flags & 0x8000) != 0) {
    goto done;
  }
  sub_080113A8((s32)sprite, animTrack);
  if (*(s16 *)stepState == 1) {
    sub_08011EE8(work, 0x16C1, 0);
  }
lab_de:
  sub_0802CB5C((s32)sprite, work);
  *(u16 *)((u8 *)work->target + 0x14) = 0;
  coordOffset = 0x1278;
  cameraTable = gCameraState;
  originX = *((u32 *)((cameraTable + coordOffset) + ((gMainWorkspace.frameCounter + 1) << 6)));
  originX = originX + 0x8000;
  originX = originX & 0xFFFF0000;
  sprite->screenX = work->worldX - originX;
  coordOffset = 0x127C;
  originY = *((u32 *)((cameraTable + coordOffset) + ((gMainWorkspace.frameCounter + 1) << 6)));
  originY = originY + 0xFFFF8000;
  originY = originY & 0xFFFF0000;
  sprite->screenY = work->worldY - originY;
done:
  ;
}
