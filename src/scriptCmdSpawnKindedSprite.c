extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void setSpriteFlip(u8 *, s32);
extern void registerScriptObject(u8 *, s32);
extern s32 signOf(s32);
extern void sub_080256F8(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
struct SpriteDef {
  u8 _0;
  u8 kind;
  u8 subkind;
  u8 state;
  u16 tile;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  u16 mode;
  u32 sprite;
  u16 zero;
};
struct SpawnedObject {
  u8 _0[8];
  s32 x;
  s32 y;
  u32 f10;
  u32 f14;
  u32 frameIndex;
  s16 kind;
  u8 _1E[4];
  s16 kindIndex;
  u32 callback;
  struct SpriteDef *spriteDef;
};
struct ScriptRef {
  s16 value0;
  s16 value1;
  s16 type;
};
struct ScriptRefHolder {
  u8 _0[4];
  struct ScriptRef *ref;
};
struct ScriptThread {
  u8 _0[2];
  u16 flags;
  u8 _4[0x22 - 4];
  s16 menuIndex;
  u8 _24[0x38 - 0x24];
  u8 *menuItems;
  struct SpawnedObject *work;
  u8 _40[0x4C - 0x40];
  s16 f4C;
  u8 _4E[6];
  s16 f54;
  u8 _56[0xAC - 0x56];
  struct ScriptRefHolder *refHolder;
};
struct S_02025FF0 {
  u8 _0[0x18A8];
  u8 mapIndex;
  u8 _18A9[0x19];
  u16 gfxFlag;
};
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 {
  u8 _0[0x1278];
  u32 cameraX;
  u32 cameraY;
};
extern struct S_02021E90 gCameraState;
struct KindTable {
  u16 tile;
  s16 frame;
  u16 mode;
  u8 _6[0x14 - 6];
};
extern struct KindTable gSpriteKindTable[];
extern u16 D_080CE8F0[];
extern u8 gSpriteAnimDataTable[];

/* Script command: spawn a sprite/effect object from the thread's script ref,
 * configure its position, animation and sprite attributes from the kind tables,
 * then idle the thread and advance the menu command state. */
void scriptCmdSpawnKindedSprite(struct ScriptThread *thread)
{
  u8 *sprite;
  struct SpawnedObject *work;
  struct SpawnedObject *newWork;
  u8 *anim;
  u8 *spriteDefPtr;
  s32 kindIndex;
  u32 attrs;
  u32 zero;
  u8 *gfxBase;
  u8 *kindTable;
  s32 *lit;
  struct ScriptRefHolder *refHolder;
  s16 refType;
  s32 m;
  refHolder = thread->refHolder;
  sprite = allocSpriteObject();
  work = NULL;
  spriteDefPtr = NULL;
  kindIndex = 0;
  if ((((sprite == NULL) || ((thread->menuItems = sprite, allocWorkSlot((u8 *) thread, 0, 0x8C, 0), newWork = thread->work, newWork == NULL))) || ((work = newWork, anim = ((u8 *) work) + 0x34, work->callback = *((u32 *) (((u8 *) thread) + 0x24)), *((u32 *) (((u8 *) thread) + 0x24)) = (u32) sub_080256F8, refType = refHolder->ref->type, (  {
    s16 k;
    switch (refType)
    {
      case 0xA9:
        k = 0x4A;
        break;

      case 0xAA:
        k = 0x80;
        break;

      default:
        goto _skip_kind;

    }

    work->kind = k;
    _skip_kind:
    0;

  }
), kindTable = (u8 *) gSpriteKindTable, work->frameIndex = ((struct KindTable *) kindTable)[work->kind].frame, work->x = refHolder->ref->value0 << 16, work->y = refHolder->ref->value1 << 16, kindIndex = findKindIndex(work->kind), zero = 0, work->kindIndex = kindIndex, ((s32) (kindIndex << 16)) < 0))) || ((initSpriteGraphics(sprite, anim, ((s32) gSpriteAnimDataTable) + (work->kind * 0xC)), spriteDefPtr = allocEffectPart(), work->spriteDef = (struct SpriteDef *) spriteDefPtr, spriteDefPtr == NULL)))
  {
    sub_080C31E0(thread, *((u32 *) (((u8 *) thread) + 0x24)));
    return;
  }
  work->spriteDef->kind = 0;
  work->spriteDef->subkind = 8;
  work->spriteDef->state = 1;
  work->spriteDef->tile = ((struct KindTable *) kindTable)[work->kind].tile;
  work->spriteDef->f6 = D_080CE8F0[0];
  work->spriteDef->f8 = D_080CE8F0[1];
  work->spriteDef->fA = D_080CE8F0[2];
  work->spriteDef->fC = D_080CE8F0[3];
  work->spriteDef->mode = ((struct KindTable *) kindTable)[work->kind].mode;
  work->spriteDef->sprite = (u32) sprite;
  work->spriteDef->zero = zero;
  attrs = 0x200;
  attrs = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (((u8 *) work) + 0x22))) << 6) + attrs) | (((*((u16 *) (((u8 *) work) + 0x22))) + 8) << 12));
  *((u16 *) sprite) = attrs;
  *((u16 *) sprite) = attrs | gMainWorkspace.gfxFlag;
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  gfxBase = (u8 *) (&gCameraState);
  {
    u32 coordOff = 0x1278;
    *((u32 *) (sprite + 0x14)) = work->x - (((*((u32 *) ((gfxBase + coordOff) + ((gMainWorkspace.mapIndex + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 coordOff = 0x127C;
    *((u32 *) (sprite + 0x18)) = work->y - (((*((u32 *) ((gfxBase + coordOff) + ((gMainWorkspace.mapIndex + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  {
    u8 *p14 = anim + 0x14;
    u8 *p30;
    *((u16 *) p14) = zero;
    *((u32 *) (p14 + 4)) = 0;
    *((u16 *) (p14 + 0x10)) = 0;
    p30 = anim + 0x2C;
    *((u32 *) p30) = 0;
    m = (((s32) signOf(work->x)) >> 31) & 0x8000;
    *((u32 *) (p30 + 4)) = m;
    *((u32 *) (p30 + 8)) = 0;
    *((u32 *) (p30 + 0xC)) = 0x24000;
    *((u32 *) (p30 + 0x10)) = 0x1800;
    *((u32 *) (p30 + 0x14)) = 0x200;
  }
  setSpriteFlip(sprite, m);
  setAnimationFrame(sprite, anim, 0, 1);
  registerScriptObject((u8 *) thread, 0);
  thread->flags |= 0x1000;
  *((u8 *) ((((u8 *) thread) + (2 * thread->menuIndex)) + 0x19)) = 0;
  lit = (s32 *) 0x08671BB0;
  sub_080C31E4(((u8 *) thread) + 0x18, ((u8 *) thread) + 0x22, *lit);
  {
    u32 idx2 = 2 * ((u32) thread->menuIndex);
    u8 *stateBytePtr;
    idx2 += (u32) thread;
    stateBytePtr = (u8 *) idx2;
    *((u8 *) (stateBytePtr + 0x19)) = (*((u8 *) (stateBytePtr + 0x19))) + 1;
  }
  {
    u8 *extra = ((u8 *) thread) + 0x18;
    extra += thread->menuIndex * 2;
    sub_080C31E0(thread, *((u32 *) ((*((u8 **) (((u8 *) thread) + 0x14))) + ((*extra) * 4))));
  }
}
