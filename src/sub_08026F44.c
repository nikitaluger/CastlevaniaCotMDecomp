extern s32 sub_0805F9B4(s32, s32);
extern void sub_08027A10(void *);
extern s32 sub_0800583C(s32);
extern s32 sub_08005820(s32);
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern s32 sub_08013B5C(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct MoveFlags { u8 _0; u8 flags; };
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

static inline u8 setBit6Byte(u8 value) { u32 mask = 0x40; mask |= value; return (u8)mask; }
static inline u16 setBit0Half(u16 value) { u32 mask = 1; mask |= value; return (u16)mask; }

/* Per-frame update for a moving entity: cull it when it leaves the camera view, follow its
 * owner, launch it with a random velocity under gravity, advance one script step, then
 * mirror its world position into sprite coordinates. */
void sub_08026F44(u8 *entity)
{
  s32 sprite = *((s32 *) (entity + 0x38));
  u8 *state = *((u8 **) (entity + 0x3C));
  u8 *anim = state + 0x34;
  u8 *extra = state + 0x48;

  if (sub_0805F9B4(*((s32 *) (state + 8)), *((s32 *) (state + 0xC))) == 1)
  {
    ((struct MoveFlags *) (*((u8 **) (state + 0x28))))->flags = 0;
    ((u8 *) sprite)[0x2A] = ((u8 *) sprite)[0x2A] & 0xBF;
    if (((*((u16 *) (entity + 0x64))) & 2) == 0) goto epilogue;
  }
  else
  {
    ((struct MoveFlags *) (*((u8 **) (state + 0x28))))->flags = 1;
    { u8 byteValue = *(volatile u8 *)((u8 *)sprite + 0x2A); *((u8 *)sprite + 0x2A) = setBit6Byte(byteValue); }
  }

  sub_08027A10(entity);
  do
  {
    if ((*((u16 *) (entity + 0x64))) & 0x41)
    {
      u16 halfValue = *(volatile u16 *)state;
      *(u16 *)state = setBit0Half(halfValue);
    }
    if ((*((u16 *) state)) & 1)
    {
      ((struct MoveFlags *) (*((u8 **) (state + 0x28))))->flags = 0;
      if (entity[((*((s16 *) (entity + 0x22))) * 2) + 0x1A] != 5)
      {
        s32 *callback;
        *((u32 *) (extra + 0x10)) = 0x16C1;
        *((u32 *) (state + 0x10)) = sub_0800583C(0x4000);
        *((u32 *) (state + 0x14)) = sub_08005820(0x2000);
        {
          void *parent = *((void **) (entity + 0x30));
          if (parent != NULL)
          {
            sub_080C31E0(parent, *((void **) (((u8 *) parent) + 0x24)));
          }
        }
        entity[((*((s16 *) (entity + 0x22))) * 2) + 0x1B] = 0;
        callback = (s32 *) 0x08671BDC;
        sub_080C31E8(entity + 0x18, entity + 0x22, 5, *callback);
      }
    }
    if (sub_08013B5C((void *) sprite, state) == 0)
    {
      s32 stepOff;
      u8 *script;
      u8 cmd;
      void **scriptTable;
      *((u32 *) (entity + 0x14)) = 0x0866D9BC;
      *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) + 1;
      {
        u32 byteOff = (u32)(*((s16 *) (entity + 0x22))) * 2;
        u8 *stepPtr = (u8 *)(byteOff + (u32)entity);
        stepPtr[0x19] = stepPtr[0x19] + 1;
      }
      stepOff = (*((s16 *) (entity + 0x22))) * 2;
      script = entity + 0x18;
      cmd = *(script + stepOff);
      scriptTable = *((void **) (entity + 0x14));
      sub_080C31E0(entity, scriptTable[cmd]);
      *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) - 1;
      if (((*((u16 *) (entity + 2))) & 0x8000) == 0)
      {
        sub_080113A8((void *) sprite, anim);
        sub_0801165C(state, *((s32 *) (extra + 0x10)));
      }
      else
      {
        goto epilogue;
      }
    }
    {
      u8 *coordBase = gCameraState;
      u8 *layerBase = gMainWorkspace;
      u8 *xBase;
      u8 *yBase;
      u32 layerIdx;
      layerBase += 0x18A8;
      layerIdx = (((u32) (*layerBase)) + 1) * 0x40;
      xBase = coordBase + 0x1278;
      *((u32 *) (((u8 *) sprite) + 0x14)) = (*((u32 *) (((u8 *) state) + 0x08))) - (((*((u32 *) (xBase + layerIdx))) + 0x8000) & 0xFFFF0000);
      layerIdx = (((u32) (*layerBase)) + 1) * ((unsigned char) 0x40);
      yBase = coordBase + 0x127C;
      *((u32 *) (((u8 *) sprite) + 0x18)) = (*((u32 *) (((u8 *) state) + 0x0C))) - (((*((u32 *) (yBase + layerIdx))) + 0xFFFF8000) & 0xFFFF0000);
    }
  epilogue:
    ;
  } while (0);
  ;
}
