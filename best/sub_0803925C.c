extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void installUpdateHandler(u8 *, u8 *, void *);
extern void sub_080397B0(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

struct EffectPart3925C {
  u8 unk0;
  u8 kind;
  u8 layer;
  u8 priority;
  u16 gfxIndex;
  u16 anim0;
  u16 anim1;
  u16 anim2;
  u16 anim3;
  u16 palette;
  u32 object;
  u16 tail;
};
struct EffectWork3925C {
  u8 unk0[8];
  s32 worldX;
  s32 worldY;
  u32 radiusA;
  u32 radiusB;
  u32 state;
  s16 kind;
  u8 unk1E[4];
  s16 slot;
  u32 updateCb;
  struct EffectPart3925C *gfx;
  u8 pad2C[0x1C];
  struct EffectPart3925C *gfx2;
};
struct ScriptedObject3925C {
  u8 unk0[2];
  u16 flags;
  u8 unk4[0x22 - 4];
  s16 index;
  u8 unk24[0x38 - 0x24];
  u8 *sprite;
  struct EffectWork3925C *work;
  u8 unk40[0x4C - 0x40];
  u8 variant;
  u8 unk4D[0x8C - 0x4D];
};
struct EffectTemplate3925C {
  u8 unk0[4];
  u16 gfxIndex;
  u16 palette;
  u8 unk8[0x28 - 8];
};
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u8 gSpriteAnimDataTable[];
extern struct EffectTemplate3925C gEffectGfxTable[];
extern u32 D_080CF0BC[];
extern u16 D_080CF0C4[];
extern u32 gMainObjTimerCallbacks[];

void sub_0803925C(struct ScriptedObject3925C *arg0)
{
  u8 *sprite;
  struct EffectWork3925C *work;
  struct EffectWork3925C *workCheck;
  u8 *animState;
  s32 kindIndex;
  u16 *animTable;
  u32 layer;
  u32 priority;
  u8 *camera;
  u8 *workspace;
  u32 scrollIdx;
  u8 *scriptPtr;
  u8 *scriptBytePtr;
  u32 *scriptOps;

  sprite = allocSpriteObject();
  if (sprite == NULL) goto fail;
  arg0->sprite = sprite;
  allocWorkSlot((u8 *)arg0, 0, 0x4C, 0);
  workCheck = *(struct EffectWork3925C * volatile *)(((u8 *)arg0) + 0x3C);
  if (workCheck == NULL) goto fail;
  *((u32 *)(sprite + 0x1C)) = 0x8000000A;
  work = arg0->work;
  animState = ((u8 *)work) + 0x34;
  installUpdateHandler((u8 *)arg0, (u8 *)work, (void *)sub_080397B0);
  work->kind = D_080CF0BC[arg0->variant];
  kindIndex = findKindIndex(work->kind);
  work->slot = kindIndex;
  if (((s32)(kindIndex << 16)) < 0) goto fail;
  initSpriteGraphics(sprite, animState, 0x080CD400 + work->kind * 0xC);
  animTable = D_080CF0C4;
  work->gfx = allocEffectPart();
  if (work->gfx == NULL) goto fail;
  layer = 8;
  priority = 1;
  work->gfx->kind = 0;
  work->gfx->layer = layer;
  work->gfx->priority = priority;
  work->gfx->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
  work->gfx->anim0 = animTable[0];
  work->gfx->anim1 = animTable[1];
  work->gfx->anim2 = animTable[2];
  work->gfx->anim3 = animTable[3];
  work->gfx->palette = gEffectGfxTable[work->kind].palette;
  work->gfx->object = (u32)sprite;
  {
    u16 *animTable2 = animTable + 4;
  }
  work->gfx2 = allocEffectPart();
  if (work->gfx2 != NULL) goto main;
fail:
  _call_via_r1((u8 *)arg0, *(s32 *)(((u8 *)arg0) + 0x24));
  goto end;
main:
  work->gfx2->kind = 0;
  work->gfx2->layer = layer;
  work->gfx2->priority = priority;
  work->gfx2->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
  work->gfx2->anim0 = animTable[1];
  work->gfx2->anim1 = animTable[2];
  work->gfx2->anim2 = animTable[3];
  work->gfx2->anim3 = animTable[4];
  work->gfx2->palette = gEffectGfxTable[work->kind].palette;
  work->gfx2->object = (u32)sprite;
  camera = (u8 *)(&gCameraState);
  workspace = (u8 *)(&gMainWorkspace) + 0x18A8;
  scrollIdx = ((u32)*workspace + 1) * 0x40;
  *(u32 *)((u8 *)sprite + 0x14) = work->worldX - ((*(u32 *)(camera + 0x1278 + scrollIdx) + 0x8000) & 0xFFFF0000);
  scrollIdx = ((u32)*workspace + 1) * 0x40;
  *(u32 *)((u8 *)sprite + 0x18) = work->worldY - ((*(u32 *)(camera + 0x127C + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
  arg0->flags |= 0x1000;
  scriptBytePtr = (u8 *)((u32)(2 * arg0->index) + (u32)arg0) + 0x19;
  *scriptBytePtr = 0;
  scriptOps = (u32 *)gMainObjTimerCallbacks;
  scriptPtr = ((u8 *)arg0) + 0x18;
  _call_via_r2(scriptPtr, ((u8 *)arg0) + 0x22, *scriptOps);
  scriptBytePtr = (u8 *)((u32)(2 * arg0->index) + (u32)arg0) + 0x19;
  *scriptBytePtr = (u8)((*scriptBytePtr) + 1);
  scriptPtr += (u32)(2 * arg0->index);
  {
    u8 opcode = *scriptPtr;
    void *handler = ((void **)(*((void **)((u8 *)arg0 + 0x14))))[opcode];
    _call_via_r1((u8 *)arg0, (s32)handler);
  }
end:
  ;
}
