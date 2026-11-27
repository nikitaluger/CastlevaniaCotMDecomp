extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void sub_0801F02C(void *);
extern void sub_0801EF68(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

/* A child sprite record allocated from the shared spawn-slot pool. */
struct ChildSprite {
    u8 unused0, active, kind, variant;
    u16 param4, param6, param8, paramA, paramC, paramE;
    u32 owner;
    u16 param14;
};

/* Per-entity state reached through entity->state. */
struct EntityState {
    u8 _0[8];
    s32 x;
    s32 y;
    u32 _10, _14;
    u32 enabled;
    s16 animKind;
    u8 _1E[4];
    s16 seqResult;
    u32 prevUpdate;
    struct ChildSprite *child;
    u8 _2C[0x48-0x2C];
    u16 unk48, unk4A;
};

struct Entity {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22-4];
    s16 ctrlIndex;
    u8 _24[0x38-0x24];
    u8 *obj;
    struct EntityState *state;
    u8 _40[0x4C-0x40];
    s16 spawnX;
    u8 _4E[6];
    s16 spawnY;
    u8 _56[0x8C-0x56];
    u16 animKind;
};

struct GlobalState { u8 _0[0x18A8]; u8 coordIndex; u8 _18A9[0x19]; u16 attrMask; };
extern struct GlobalState gMainWorkspace;
struct CoordTable { u8 _0[0x1278]; u32 xTable, yTable; };
extern struct CoordTable gCameraState;
struct SpriteDef { u8 _0[8]; u16 param8, paramA; u8 _C[0x28-0xC]; };
extern struct SpriteDef gEffectGfxTable[];
extern u16 D_080CE740[];
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;

void sub_0803EAB4(struct Entity *entity)
{
    u8 *obj;
    struct EntityState *state;
    u8 *anim;
    u8 *childSlot;
    s32 v;
    u32 gfxAttr;
    u32 zero;
    u32 one;
    u8 *coordBase;
    s32 *callbackSlot;

    obj = allocSpriteObject();
    if (obj == NULL) {
        sub_0801F02C(entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->obj = obj;
    allocWorkSlot((u8 *)entity, 0, 0x48, 0);
    state = entity->state;
    if (state == NULL) {
        sub_0801F02C(entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    anim = (u8 *)state + 0x34;
    state->prevUpdate = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)sub_0801EF68;
    state->animKind = entity->animKind;
    zero = 0;
    one = 1;
    state->enabled = one;
    state->x = entity->spawnX << 16;
    state->y = entity->spawnY << 16;
    v = findKindIndex(state->animKind);
    state->seqResult = v;
    if ((v << 16) < 0) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    initSpriteGraphics(obj, anim, (s32)gSpriteAnimDataTable + state->animKind * 0xC);
    childSlot = allocEffectPart();
    state->child = (struct ChildSprite *)childSlot;
    if (childSlot == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    state->child->active = zero;
    state->child->kind = 8;
    state->child->variant = one;
    state->child->param4 = gEffectGfxTable[state->animKind].param8;
    state->child->param6 = D_080CE740[0];
    state->child->param8 = D_080CE740[1];
    state->child->paramA = D_080CE740[2];
    state->child->paramC = D_080CE740[3];
    state->child->paramE = gEffectGfxTable[state->animKind].paramA;
    state->child->owner = (u32)obj;
    state->child->param14 = zero;
    gfxAttr = (*(u16 *)obj & 0xC00) |
              (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
               ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)obj = gfxAttr;
    *(u16 *)obj = gfxAttr | gMainWorkspace.attrMask;
    *(u32 *)(obj + 0x1C) = 0x0A000080;
    coordBase = (u8 *)&gCameraState;
    { u32 off = 0x1278; *(u32 *)(obj + 0x14) = state->x - ((*(u32 *)(coordBase + off + ((gMainWorkspace.coordIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 off = 0x127C; *(u32 *)(obj + 0x18) = state->y - ((*(u32 *)(coordBase + off + ((gMainWorkspace.coordIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    {
        u16 *half = (u16 *)((u8 *)state + 0x48);
        half[0] = 0xB4;
        half[1] = (u16)zero;
    }
    *(u16 *)(obj + 0x28) = 0x0100;
    entity->flags |= 0x2000;
    *(u8 *)((u8 *)entity + 2 * entity->ctrlIndex + 0x19) = zero;
    callbackSlot = (s32 *)gMainObjTimerCallbacks;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackSlot);
}
