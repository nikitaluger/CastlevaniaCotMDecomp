extern void *allocSpriteObject(void);
extern void allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void sub_08030810(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern void sub_080C31E8(u8 *, u8 *, s32, s32);
struct SpriteAttribs { u8 _0; u8 kind; u8 subPriority; u8 shape; u16 baseTile; u16 tile0; u16 tile1; u16 tile2; u16 tile3; u16 extra; u32 object; u16 timer; };
struct EntityState { u8 _0[8]; s32 x; s32 y; u32 _10; u32 _14; u32 active; s16 animId; u8 _1E[4]; s16 variant; u32 updateCallback; struct SpriteAttribs *attribs; u8 _2C[0x48 - 0x2C]; };
struct Entity { u8 _0[2]; u16 flags; u8 _4[0x22 - 4]; s16 index; u8 _24[0x38 - 0x24]; u8 *object; struct EntityState *state; u8 _40[0x6C - 0x40]; u16 status; };
struct GlobalStateA { u8 _0[0x18A8]; u8 cameraIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GlobalStateA gMainWorkspace;
struct GlobalStateB { u8 _0[0x1278]; u32 coordX; u32 coordY; };
extern struct GlobalStateB gCameraState;
struct AnimTable { u8 _0[4]; u16 baseTile; u16 extra; u8 _8[0x28 - 8]; };
extern struct AnimTable gEffectGfxTable[];
extern u16 D_080CEB30[];
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallback;
void sub_08030188(struct Entity *arg0)
{
  u8 *obj;
  struct EntityState *state;
  u8 *anim;
  u8 *attribs;
  s32 variantRnd;
  u32 one;
  u8 *coordBase;
  s32 *cb;
  u8 *q;
  obj = allocSpriteObject();
  if (obj == NULL)
  {
    arg0->status |= 8;
    *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = 0;
    { s32 *fcb = (s32 *) 0x08671BD0; sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 2, *fcb); }
    return;
  }
  arg0->object = obj;
  allocWorkSlot((u8 *) arg0, 0, 0x124, 0);
  state = arg0->state;
  if (state == NULL)
  {
    arg0->status |= 8;
    *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = 0;
    { s32 *fcb = (s32 *) 0x08671BD0; sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 2, *fcb); }
    return;
  }
  anim = ((u8 *) state) + 0x34;
  state->updateCallback = *((u32 *) (((u8 *) arg0) + 0x24));
  *((u32 *) (((u8 *) arg0) + 0x24)) = (u32) sub_08030810;
  state->animId = 0x0A;
  one = 1;
  state->active = one;
  state->x = 0;
  state->y = 0;
  variantRnd = findKindIndex(state->animId);
  state->variant = variantRnd;
  if ((variantRnd << 16) >= 0)
  {
    initSpriteGraphics(obj, anim, ((s32) gSpriteAnimDataTable) + (state->animId * 0xC));
    attribs = allocEffectPart();
    state->attribs = (struct SpriteAttribs *) attribs;
    if (attribs != NULL) goto success;
  }
  arg0->status |= 8;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = 0;
  { s32 *fcb = (s32 *) 0x08671BD0; sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 2, *fcb); }
  return;
  success:
  state->attribs->kind = 0;
  state->attribs->subPriority = 8;
  state->attribs->shape = one;
  state->attribs->baseTile = gEffectGfxTable[state->animId].baseTile;
  state->attribs->tile0 = D_080CEB30[0];
  state->attribs->tile1 = D_080CEB30[1];
  state->attribs->tile2 = D_080CEB30[2];
  state->attribs->tile3 = D_080CEB30[3];
  state->attribs->extra = gEffectGfxTable[state->animId].extra;
  state->attribs->object = (u32) obj;
  state->attribs->timer = 0;
  {
    u16 *o = (u16 *) obj;
    u32 gfxAttr = ((*o) & 0xC00) | ((((*((s16 *) (((u8 *) state) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) state) + 0x22))) + 8) << 12));
    *o = gfxAttr;
    *o = gfxAttr | gMainWorkspace.gfxFlag;
  }
  *((u32 *) (obj + 0x1C)) = 0x8000000A;
  coordBase = (u8 *) (&gCameraState);
  {
    u32 off = 0x1278;
    *((u32 *) (obj + 0x14)) = state->x - (((*((u32 *) ((coordBase + off) + ((gMainWorkspace.cameraIndex + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 off = 0x127C;
    *((u32 *) (obj + 0x18)) = state->y - (((*((u32 *) ((coordBase + off) + ((gMainWorkspace.cameraIndex + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  state->_14 = 0;
  state->_10 = 0;
  *((u8 *) (obj + 0x2A)) &= 0xBF;
  arg0->flags |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = 0;
  cb = (s32 *) 0x08671BB0;
  q = ((u8 *) arg0) + 0x18;
  sub_080C31E4(q, ((u8 *) arg0) + 0x22, *cb);
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = (*((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19))) + 1;
  q = q + (2 * arg0->index);
  {
    u8 idxb = *q;
    s32 *table = *((s32 **) (((u8 *) arg0) + 0x14));
    sub_080C31E0((u8 *) arg0, table[idxb]);
  }
}
