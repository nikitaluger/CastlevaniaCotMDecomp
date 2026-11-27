struct ProjectileWork
{
  u8 _0[8];
  s32 x;
  s32 y;
  s32 _10;
  s32 _14;
  u8 _18[4];
  s16 id;
  u8 _1E[4];
  s16 rotation;
};
struct ProjectileSpawner
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x10];
  void (*update)(void *);
  u8 _18[0xA];
  s16 state;
  u8 _24[0x38 - 0x24];
  u8 *obj;
  struct ProjectileWork *work;
  u8 _40[0xC];
  s16 spawnX;
  u8 _4E[6];
  s16 spawnY;
  u8 _56[6];
  u16 spriteId;
};
struct ProjectileWorkspaceView
{
  u8 _0[0x18A8];
  u8 layer;
  u8 _18A9[0x19];
  u16 spriteFlags;
};
extern struct ProjectileWorkspaceView gMainWorkspace;
struct ProjectileCameraView
{
  u8 _0[0x1278];
  u32 f1278;
  u32 f127C;
};
extern struct ProjectileCameraView gCameraState;
extern u8 gSpriteAnimDataTable[];
extern u8 *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void updateProjectileSprite(void *);

/* Spawn a projectile: allocate its sprite object and work slot, copy the
 * spawner's position and sprite id into the work state, place the sprite
 * against the camera scroll, and install its per-frame update callback. */
void spawnProjectileEntity(struct ProjectileSpawner *self)
{
  u8 *obj;
  struct ProjectileWork *work;
  u8 *animTrack;
  u8 *cameraTable;
  u16 *attrs;
  obj = allocSpriteObject();
  if (obj == NULL)
  {
    _call_via_r1((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  self->obj = obj;
  allocWorkSlot((u8 *) self, 0, PROJECTILE_WORK_SLOT, 0);
  work = self->work;
  if (work == NULL)
  {
    _call_via_r1((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  animTrack = ((u8 *) work) + 0x34;
  work->id = self->spriteId;
  work->x = self->spawnX << 16;
  work->y = self->spawnY << 16;
  work->rotation = findKindIndex((s32) work->id);
  if (work->rotation < 0)
  {
    _call_via_r1((u8 *) self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  attrs = (u16 *) obj;
  initSpriteGraphics(obj, animTrack, ((s32) gSpriteAnimDataTable) + (work->id * 0xC));

  {
    u16 shape = 0xC00 & (*((u16 *) obj));
    s32 scale = ((s16) (*((s16 *) (((u8 *) work) + 0x22)))) << 6;
    scale += 0x200;
    scale |= (((u16) (*((u16 *) (((u8 *) work) + 0x22)))) + 8) << 12;
    *attrs = (u16) (shape | scale);
  }
  *attrs = (u16) ((*attrs) | gMainWorkspace.spriteFlags);
  *((u32 *) (obj + 0x1C)) = PROJECTILE_GFX_ID;
  cameraTable = (u8 *) (&gCameraState);
  {
    u32 k = PROJECTILE_SCROLL_X_OFFSET;
    *((u32 *) (obj + 0x14)) = work->x - (((*((u32 *) ((cameraTable + k) + ((gMainWorkspace.layer + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = PROJECTILE_SCROLL_Y_OFFSET;
    *((u32 *) (obj + 0x18)) = work->y - (((*((u32 *) ((cameraTable + k) + ((gMainWorkspace.layer + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  setAnimationFrame(obj, animTrack, PROJECTILE_ANIM_FRAME, 0);
  self->flags |= PROJECTILE_READY_FLAG;
  self->flags |= PROJECTILE_READY_FLAG_ALT;
  self->state = 0;
  self->update = updateProjectileSprite;
}
