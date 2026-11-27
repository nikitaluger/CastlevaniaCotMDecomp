struct TargetWork
{
  u8 _0[8];
  s32 worldX;
  s32 worldY;
  s32 _10;
  s32 _14;
  s32 kind;
  s16 spriteKind;
  u8 _1E[4];
  s16 animKind;
};
struct TargetSpawner
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x10];
  void (*update)(void *);
  u8 _18[0xA];
  s16 state;
  u8 _24[0x38 - 0x24];
  u8 *obj;
  struct TargetWork *work;
  u8 _40[0xC];
  s16 spawnX;
  u8 _4E[6];
  s16 spawnY;
  u8 _56[6];
  s16 variant;
  u8 _5E[0x6C - 0x5E];
  u16 spriteId;
};
struct TargetWorkspaceView
{
  u8 _0[0x18A8];
  u8 frameCounter;
  u8 _18A9[0x19];
  u16 renderFlags;
};
extern struct TargetWorkspaceView gMainWorkspace;
extern u8 gCameraState[];
extern u8 gSpriteAnimDataTable[];
extern u8 *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void updateScriptedEffectPosition(void *);

/*
 * Creates a target effect's sprite and work state, initializes its graphics
 * and camera-relative position, picks the starting frame from the variant,
 * and installs its per-frame update handler.
 */
void spawnTargetEffectSprite(struct TargetSpawner *self)
{
  u8 *sprite;
  struct TargetWork *work;
  u8 *animTrack;
  u8 *cameraState;
  u16 *attrs;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    _call_via_r1((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  self->obj = sprite;
  allocWorkSlot((u8 *) self, 0, 0x48, 0);
  work = self->work;
  if (work == NULL)
  {
    _call_via_r1((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  animTrack = ((u8 *) work) + 0x34;
  work->spriteKind = self->spriteId;
  work->kind = 1;
  work->worldX = self->spawnX << 16;
  work->worldY = self->spawnY << 16;
  work->animKind = findKindIndex((s32) work->spriteKind);
  if (work->animKind < 0)
  {
    _call_via_r1((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  initSpriteGraphics(sprite, animTrack, ((s32) gSpriteAnimDataTable) + (work->spriteKind * 0xC));
  attrs = (u16 *) sprite;
  {
    u16 shape = 0xC00 & (*((u16 *) sprite));
    s32 scale = ((s16) (*((s16 *) (((u8 *) work) + 0x22)))) << 6;
    scale += 0x200;
    scale |= (((u16) (*((u16 *) (((u8 *) work) + 0x22)))) + 8) << 12;
    *attrs = (u16) (shape | scale);
  }
  *attrs = (u16) ((*attrs) | gMainWorkspace.renderFlags);
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  cameraState = (u8 *) (&gCameraState);
  {
    u32 k = 0x1278;
    *((u32 *) (sprite + 0x14)) = work->worldX - (((*((u32 *) ((cameraState + k) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (sprite + 0x18)) = work->worldY - (((*((u32 *) ((cameraState + k) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  if (self->variant == 0)
    setAnimationFrame(sprite, animTrack, 0x14, 1);
  else
    setAnimationFrame(sprite, animTrack, 0x19, 1);
  self->flags |= 0x1000;
  self->flags |= 0x800;
  self->state = 0;
  self->update = updateScriptedEffectPosition;
}
