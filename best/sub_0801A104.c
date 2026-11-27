struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x10];
  u32 callbackTable;
  u8 _18[0xA];
  s16 childIndex;
  u32 callback;
  u8 _28[0x10];
  u32 sprite;
  u32 gfxState;
  u8 _40[0xC];
  s16 param1;
  u8 _4E[6];
  s16 param2;
  u8 _56[6];
  s16 param3;
  u8 _5E[0xE];
  u32 animData;
};
struct Sprite
{
  u16 attr;
  u8 _02[0x12];
  u32 screenX;
  u32 screenY;
  u32 unk1C;
};
struct GfxState
{
  u8 _0[8];
  u32 x;
  u32 y;
  u8 _10[0xC];
  s16 spriteType;
  u8 _1E[4];
  s16 attrIndex;
  u8 _24[0x24];
  u32 posX;
  u32 posY;
  u8 _50[4];
  u32 f54;
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 f18A8;
  u8 _1[0x19];
  u16 f18C2;
};
typedef s32 (*TrigFn)(s32);
extern void stepAnimationTrack(void *, void *);
extern s32 divInt32(s32, s32);
extern void _call_via_r1(void *, void *);
extern void *gTrigFuncTable;
extern struct S_02025FF0 gMainWorkspace;
extern u8 gCameraState[];
extern void *D_0866D620[];

void sub_0801A104(struct Entity *arg0)
{
  struct Sprite *sprite = (struct Sprite *)arg0->sprite;
  struct GfxState *state = (struct GfxState *)arg0->gfxState;
  u8 *anim = ((u8 *)state) + 0x34;
  u8 *extra = ((u8 *)state) + 0x48;
  s32 scaled;
  u32 animData;
  u32 *trigAddr;
  s32 ret;

  arg0->callbackTable = (u32)D_0866D620;
  arg0->childIndex = arg0->childIndex + 1;
  {
    u8 *child = (u8 *)(((u32)arg0->childIndex) * 2 + (u32)arg0);
    child[0x19] = child[0x19] + 1;
  }
  {
    s32 idx = *(s16 *)((u8 *)arg0 + 0x22);
    u8 *script = ((u8 *)arg0) + 0x18;
    _call_via_r1(arg0, (void *)(*(u32 **)((u8 *)arg0 + 0x14))[*(u8 *)(idx * 2 + script)]);
  }
  arg0->childIndex = arg0->childIndex - 1;
  if (arg0->flags & 0x8000)
    return;
  stepAnimationTrack(sprite, anim);
  state->y = state->y + (u32)-0x20000;
  if ((s32)state->y < (s32)*(u32 *)(extra + 4) - 0x380000)
    state->y = *(u32 *)(extra + 4);
  {
    s32 diff = (s32)state->y - (s32)*(u32 *)(extra + 4);
    s32 absolute = diff + 0x1C0000;
    s32 q;
    s32 t;
    if (absolute < 0)
      absolute = -absolute;
    trigAddr = (u32 *)&gTrigFuncTable;
    q = divInt32(absolute, 0x70);
    ret = ((TrigFn)*trigAddr)(q + 0x4000);
    t = ret * 20;
    if (t < 0)
      t = t - 0x4000;
    scaled = t >> 16;
    ret = ((TrigFn)*trigAddr)((s32)*(u32 *)(extra + 0xC));
    state->x = state->posX + (u32)(ret * scaled);
  }
  animData = *(u32 *)(extra + 0xC);
  animData = (animData + 0x800) & 0xFFFF;
  *(u32 *)(extra + 0xC) = animData;
  if ((u32)(animData - 0x4000) <= 0x7FFF) {
    sprite->attr |= gMainWorkspace.f18C2;
    sprite->unk1C = 0x80000007;
  } else {
    sprite->attr |= gMainWorkspace.f18C2;
    sprite->unk1C = 0x8000000B;
  }
  {
    u8 *coordBase = gCameraState;
    u32 adjX = *((u32 *)((coordBase + 0x1278) + ((gMainWorkspace.f18A8 + 1) << 6)));
    adjX = (adjX + 0x8000) & 0xFFFF0000;
    sprite->screenX = state->x - adjX;
    {
      u32 adjY = *((u32 *)((coordBase + 0x127C) + ((gMainWorkspace.f18A8 + 1) << 6)));
      adjY = (adjY + 0xFFFF8000) & 0xFFFF0000;
      sprite->screenY = state->y - adjY;
    }
  }
}
