extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08023B74(void);
extern void sub_08023BA4(u8 *);
extern void sub_08023BDC(u8 *, u8 *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct SpriteAttribs { u8 _0; u8 kind; u8 subPriority; u8 shape; u16 baseTile; u16 tile0; u16 tile1; u16 tile2; u16 tile3; u16 extra; u32 object; u16 timer; };
struct SubAttribs { u16 f0; u16 f2; struct SpriteAttribs *attribs; };
struct EntityState { u8 _0[8]; s32 x; s32 y; u32 _10; u32 _14; u32 active; s16 animId; u8 _1E[4]; s16 variant; u32 updateCallback; struct SpriteAttribs *attribs; u8 _2C[0x48-0x2C]; struct SubAttribs sub; };
struct Entity { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 index; u8 _24[0x38-0x24]; u8 *object; struct EntityState *state; u8 _40[0x4C-0x40]; s16 spawnX; u8 _4E[6]; s16 spawnY; };
struct GlobalStateA { u8 _0[0x18A8]; u8 cameraIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GlobalStateA D_02025FF0;
struct GlobalStateB { u8 _0[0x1278]; u32 coordX; u32 coordY; };
extern struct GlobalStateB D_02021E90;
struct AnimTable { u8 _0[4]; u16 baseTile; u16 extra; u8 _8[0x28-8]; };
extern struct AnimTable D_080CBDD0[];
extern u16 D_080CE84C[];
extern u8 D_080CD400[];

/* Script command: spawn an effect's primary and secondary sprites from the
 * entity's spawn coordinates and animation id, then idle the script thread. */
void sub_08023634(struct Entity *entity) {
    u8 *sprite;
    struct EntityState *state;
    u8 *anim;
    struct SpriteAttribs *attribs;
    s32 kindIndex;
    u32 one;
    u8 *gfxBase;

    sprite = sub_0800355C();
    if (sprite == NULL) {
        sub_08023BA4((u8 *)entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->object = sprite;
    sub_0800168C((u8 *)entity, 0, 0x50, 0);
    state = entity->state;
    if (state == NULL) {
        sub_08023BA4((u8 *)entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    anim = (u8 *)state + 0x34;
    state->updateCallback = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)sub_08023B74;
    state->animId = 0x25;
    one = 1;
    state->active = one;
    state->x = entity->spawnX << 16;
    state->y = entity->spawnY << 16;
    kindIndex = sub_08013C2C(0x25);
    state->variant = kindIndex;
    if ((kindIndex << 16) < 0) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    sub_0801131C(sprite, anim, (s32)D_080CD400 + state->animId * 0xC);
    attribs = sub_08016190();
    state->attribs = attribs;
    if (attribs == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    state->attribs->kind = 0;
    state->attribs->subPriority = 8;
    state->attribs->shape = one;
    state->attribs->baseTile = D_080CBDD0[state->animId].baseTile;
    state->attribs->tile0 = D_080CE84C[0];
    state->attribs->tile1 = D_080CE84C[1];
    state->attribs->tile2 = D_080CE84C[2];
    state->attribs->tile3 = D_080CE84C[3];
    state->attribs->extra = D_080CBDD0[state->animId].extra;
    state->attribs->object = (u32)sprite;
    state->attribs->timer = 0;
    {
        u16 *o = (u16 *)sprite;
        u32 attr = (*o & 0xC00) |
                      ((((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
                        ((*(u16 *)((u8 *)state + 0x22) + 8) << 12)));
        *o = attr;
        *o = attr | D_02025FF0.gfxFlag;
    }
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    gfxBase = (u8 *)&D_02021E90;
    {
        u32 off = 0x1278;
        *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)(gfxBase + off + ((D_02025FF0.cameraIndex + 1) << 6)) + 0x8000) & 0xFFFF0000);
    }
    {
        u32 off = 0x127C;
        *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)(gfxBase + off + ((D_02025FF0.cameraIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    }
    {
        struct SubAttribs *sub = &state->sub;
        struct SpriteAttribs *attribs2;
        sub->f0 = 0;
        sub->f2 = 9;
        attribs2 = (struct SpriteAttribs *)sub_08016190();
        sub->attribs = attribs2;
        if (attribs2 == NULL) {
            sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        }
        sub->attribs->kind = 0;
        sub->attribs->subPriority = 8;
        sub->attribs->shape = one;
        sub->attribs->baseTile = D_080CBDD0[state->animId].baseTile;
        sub->attribs->tile0 = D_080CE84C[0];
        sub->attribs->tile1 = D_080CE84C[1];
        sub->attribs->tile2 = D_080CE84C[2];
        sub->attribs->tile3 = D_080CE84C[3];
        sub->attribs->extra = D_080CBDD0[state->animId].extra;
        sub->attribs->object = (u32)sprite;
        sub->attribs->timer = 0;
    }
    if (*(u16 *)((u8 *)entity + 0x6C) & 0x20) {
        *(u16 *)(sprite + 2) |= 0x10;
    }
    *(u8 *)(sprite + 0x2A) &= 0xBF;
    sub_08023BDC((u8 *)entity, sprite);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->index + 0x19) = 0;
    {
        s32 *callbackPtr = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackPtr);
    }
}
