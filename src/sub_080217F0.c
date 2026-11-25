extern void *sub_0800355C(void);
extern void sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, void *);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08016664(u8 *, s32);
extern void sub_0801468C(u8 *, s32);
extern s32 sub_08014938(s32);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_080CD400[];
extern u8 D_080CE828[];
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
  s32 posX;
  s32 posY;
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
  u32 callback;
  u8 _28[0x38 - 0x28];
  u8 *menuItems;
  struct SpawnedObject *work;
  u8 _40[0xAC - 0x40];
  struct ScriptRefHolder *refHolder;
};
struct S_02025FF0 {
  u8 _0[0x18A8];
  u8 mapIndex;
  u8 _18A9[0x19];
  u16 gfxFlag;
};
struct S_02021E90 {
  u8 _0[0x1278];
  u32 cameraX;
  u32 cameraY;
};
struct KindTable {
  u16 tile;
  s16 frame;
  u16 mode;
  u8 _6[0x14 - 6];
};
extern struct S_02025FF0 D_02025FF0;
extern struct S_02021E90 D_02021E90;
extern struct KindTable D_080CB2B8[];

/* Script command: spawn a sprite/effect object from the thread's script ref,
 * configure its position, animation and sprite attributes from the kind tables,
 * then idle the thread and advance the menu command state. */
void sub_080217F0(struct ScriptThread *thread)
{
  struct ScriptRefHolder *refHolder;
  u8 *sprite;
  struct SpawnedObject *work;
  struct SpawnedObject *newWork;
  u8 *anim;
  s32 kindIndex;
  s32 direction;
  u32 attr;
  u32 zero;
  u8 *gfxBase;
  u8 *kindTable;
  u8 *menuState;
  s32 *lit;
  refHolder = thread->refHolder;
  sprite = sub_0800355C();
  work = NULL;
  if ((sprite == NULL) || ((thread->menuItems = sprite, sub_0800168C((u8 *) thread, 0, 0x94, 0), (newWork = thread->work) == NULL)))
  {
    sub_080C31E0((u8 *) thread, thread->callback);
    return;
  }
  work = newWork;
  anim = ((u8 *) work) + 0x34;
  work->callback = thread->callback;
  thread->callback = 0x08022149;
  {
    s16 refType = refHolder->ref->type;
    switch (refType)
    {
      case 0x9E:
        work->kind = 0x22;
        break;

      case 0x9F:
        work->kind = 0x6E;
        break;

    }

  }
  kindTable = (u8 *) D_080CB2B8;
  work->frameIndex = ((struct KindTable *) (kindTable + (((s32) work->kind) * 0x14)))[0].frame;
  work->posX = refHolder->ref->value0 << 16;
  work->posY = refHolder->ref->value1 << 16;
  kindIndex = sub_08013C2C(work->kind);
  zero = 0;
  work->kindIndex = kindIndex;
  if ((kindIndex << 16) < 0)
  {
    sub_080C31E0((u8 *) thread, thread->callback);
    return;
  }
  sub_0801131C(sprite, anim, D_080CD400 + (work->kind * 0xC));
  work->spriteDef = (struct SpriteDef *) sub_08016190();
  if (work->spriteDef == NULL)
  {
    sub_080C31E0((u8 *) thread, thread->callback);
    return;
  }
  work->spriteDef->kind = 0;
  work->spriteDef->subkind = 8;
  work->spriteDef->state = 1;
  work->spriteDef->tile = ((struct KindTable *) kindTable)[work->kind].tile;
  work->spriteDef->f6 = *((u16 *) (D_080CE828 + 0));
  work->spriteDef->f8 = *((u16 *) (D_080CE828 + 2));
  work->spriteDef->fA = *((u16 *) (D_080CE828 + 4));
  work->spriteDef->fC = *((u16 *) (D_080CE828 + 6));
  work->spriteDef->mode = ((struct KindTable *) kindTable)[work->kind].mode;
  work->spriteDef->sprite = (u32) sprite;
  work->spriteDef->zero = zero;
  attr = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (((u8 *) work) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) work) + 0x22))) + 8) << 12));
  *((u16 *) sprite) = attr;
  *((u16 *) sprite) = attr | D_02025FF0.gfxFlag;
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  gfxBase = (u8 *) (&D_02021E90);
  {
    u32 k = 0x1278;
    *((u32 *) (sprite + 0x14)) = work->posX - (((*((u32 *) ((gfxBase + k) + ((D_02025FF0.mapIndex + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (sprite + 0x18)) = work->posY - (((*((u32 *) ((gfxBase + k) + ((D_02025FF0.mapIndex + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  {
    u8 *anim14 = anim + 0x14;
    *((u32 *) (anim + 0x14)) = zero;
    *((u16 *) (anim14 + 4)) = zero;
    *((u16 *) (anim14 + 6)) = zero;
    *((u16 *) (anim14 + 8)) = zero;
    *((u16 *) (anim14 + 10)) = zero;
  }
  {
    u8 *anim34 = anim + 0x34;
    *((u32 *) (anim + 0x34)) = zero;
    direction = (sub_08014938(work->posX) >> 31) & 0x8000;
    *((u32 *) (anim34 + 4)) = direction;
    *((u32 *) (anim34 + 8)) = zero;
    *((u32 *) (anim34 + 0xC)) = 0x28000;
    *((u32 *) (anim34 + 0x10)) = 0x2000;
    *((u32 *) (anim34 + 0x14)) = 0x100;
  }
  sub_0801468C(sprite, direction);
  sub_08011368(sprite, anim, 0, 1);
  sub_08016664((u8 *) thread, 0);
  thread->flags |= 0x1000;
  *((u8 *) ((((u8 *) thread) + (2 * thread->menuIndex)) + 0x19)) = 0;
  {
    lit = (s32 *) 0x08671BB0;
    menuState = ((u8 *) thread) + 0x18;
    sub_080C31E4(menuState, ((u8 *) thread) + 0x22, *lit);
  }
  {
    u32 off = 2 * ((u32) thread->menuIndex);
    u8 *pp;
    off += (u32) thread;
    pp = (u8 *) off;
    *((u8 *) (pp + 0x19)) = (*((u8 *) (pp + 0x19))) + 1;
  }
  {
    u8 *pp = menuState + (2 * thread->menuIndex);
    sub_080C31E0((u8 *) thread, *((u32 *) ((*((u8 **) (((u8 *) thread) + 0x14))) + ((*((u8 *) pp)) * 4))));
  }
}
