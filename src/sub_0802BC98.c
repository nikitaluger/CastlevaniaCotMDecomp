/* Update an entity's mover flags and state, spawn a requested effect, advance
 * its script, and write the mover's scroll-relative screen coordinates. */
extern void sub_08005E80(s32);
extern void sub_080113A8(s32, void *);
extern void advanceMotion(void *, s32);
extern s32 sub_08013B5C(s32, void *);
extern s32 hitTestEntities(void *);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct MoverFlags { u16 flags; };
struct StateFlags { u8 a; u8 flags; };
struct StateExt { u8 _0[0x14]; u16 flags2; };
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
void sub_0802BC98(u8 *entity)
{
  s32 workObj = *((s32 *) (entity + 0x38));
  u8 *mover = *((u8 **) (entity + 0x3C));
  u8 *moverTarget = mover + 0x34;
  u8 *state;
  state = *((u8 **) (mover + 0x28));
  ((struct StateFlags *) state)->flags |= 5;
  if (sub_0805F9B4(*((s32 *) (mover + 8)), *((s32 *) (mover + 0xC))) == 1)
  {
    sub_080C31E0(entity, *((void **) (entity + 0x24)));
    return;
  }
  if (hitTestEntities(*((void **) (mover + 0x28))) != 0)
    ((struct MoverFlags *) mover)->flags |= 1;
  if (1 & ((struct StateExt *) (*((u8 **) (mover + 0x28))))->flags2)
    ((struct MoverFlags *) mover)->flags |= 1;
  if (1 & (*((u16 *) mover)))
  {
    s32 *cmd;
    ((struct StateFlags *) (*((u8 **) (mover + 0x28))))->flags &= 0xFB;
    if ((*((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x1A))) != 1)
    {
      sub_08005E80(0x18A);
      *((u8 *) (((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)) + 0x1B)) = 0;
      cmd = (s32 *) 0x08671BDC;
      sub_080C31E8(entity + 0x18, entity + 0x22, 1, *cmd);
    }
  }
  if (sub_08013B5C(workObj, mover) == 0)
  {
    s32 idx2; u8 *bytePtr; u8 val; void **scriptTable; void *target; u8 *q;
    *((void **) (entity + 0x14)) = (void *) 0x0866DB1C;
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) + 1);
    q = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    *((u8 *) (q + 0x19)) = (u8) ((*((u8 *) (q + 0x19))) + 1);
    idx2 = (*((s16 *) (entity + 0x22))) * 2;
    bytePtr = entity + 0x18;
    val = *(bytePtr + idx2);
    scriptTable = *((void **) (entity + 0x14));
    target = scriptTable[val];
    sub_080C31E0(entity, target);
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) - 1);
    if (((*((u16 *) (entity + 2))) & 0x8000) == 0)
    {
      sub_080113A8(workObj, moverTarget);
      advanceMotion(mover, 0x16C1);
    }
    else goto done;
  }
  ((struct StateExt *) (*((u8 **) (mover + 0x28))))->flags2 = 0;
  {
    u8 *coordTable = gCameraState;
    u8 *framePtr = gMainWorkspace;
    u8 *xTable;
    u8 *yTable;
    u32 coordIdx;
    framePtr += 0x18A8;
    coordIdx = ((u32)*framePtr + 1) * 0x40;
    xTable = coordTable + 0x1278;
    *(u32 *)((u8 *)workObj + 0x14) = *(u32 *)((u8 *)mover + 0x08) - ((*(u32 *)(xTable + coordIdx) + 0x8000) & 0xFFFF0000);
    coordIdx = ((u32)*framePtr + 1) * 0x40;
    yTable = coordTable + 0x127C;
    *(u32 *)((u8 *)workObj + 0x18) = *(u32 *)((u8 *)mover + 0x0C) - ((*(u32 *)(yTable + coordIdx) + 0xFFFF8000) & 0xFFFF0000);
  }
done:
  ;
}
