extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_08014288(void *, void *, void *);
extern void sub_08014290(void);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0801131C(void *, u8 *, s32);
extern void sub_08011368(void *, u8 *, s32, s32);
struct CameraInfo { u8 _0[0x18C2]; u16 spriteAttrMask; };
extern struct CameraInfo D_02025FF0;
extern u8 D_080CD400[];
extern u32 D_08671BB0;
extern u32 D_08671BFC;

/* The sprite object created for the entity. */
struct Sprite {
    u16 gfxAttr;
    u8 _[0x1C - 2];
    u32 flags;
};

/* Per-entity actor state reached through entity->actor. */
struct Actor {
    u8 _0[8];
    s32 x;
    s32 y;
    s32 scaleX;
    s32 scaleY;
    u8 _1[0x1C - 0x18];
    s16 id;
    u8 _2[0x22 - 0x1E];
    s16 dirIndex;
};

struct Entity {
    u8 _0[2];
    u16 flags;
    u8 _1[0x14 - 4];
    u32 fnTable;
    u8 _2[0x22 - 0x18];
    s16 dirIndex;
    u32 prevUpdate;
    u8 _3[0x38 - 0x28];
    u32 sprite;
    u32 actor;
    u8 _4[0x4C - 0x40];
    s32 xPos;
    u8 _5[0x5C - 0x50];
    s32 yPos;
    u8 _6[0x6C - 0x60];
    s32 param6C;
    u8 _7[0x7C - 0x70];
    s32 param7C;
};

/* Spawns an entity's sprite and actor state, seeds its position and scale,
 * sets up the initial animation, then registers the entity's script and
 * dispatches its next step. */
void sub_0803D088(struct Entity *arg) {
    struct Sprite *sprite;
    struct Actor *actor;
    u8 *anim;
    s32 ret;
    u8 *ctrlBase;
    u32 v;
    u32 fn;
    s16 i;
    u16 *arr;
    u16 *new_var;
    u32 *pfc;
    s16 v22;
    s16 *pf22;

    sprite = (struct Sprite *)sub_0800355C();
    if (sprite == NULL) goto Lend;
    arg->sprite = (u32)sprite;
    sub_0800168C(arg, 0, 0x48, 0);
    if (arg->actor == 0) goto Lend;
    sprite->flags = 0x8000000B;
    actor = (struct Actor *)arg->actor;
    anim = ((u8 *)actor) + 0x34;
    sub_08014288(arg, actor, &sub_08014290);
    actor->id = 0x2D;
    actor->x = arg->xPos;
    actor->y = arg->yPos;
    pfc = &D_08671BFC;
    actor->scaleX = (arg->param6C >> 8) * (sub_080C31E0(arg->param7C + 0x4000, *pfc) >> 8);
    actor->scaleY = (arg->param6C >> 8) * (sub_080C31E0(arg->param7C, *pfc) >> 8);
    ret = sub_08013C2C(actor->id);
    actor->dirIndex = ret;
    if ((ret << 16) >= 0) goto Lcont;
Lend:
    sub_080C31E0((s32)arg, arg->prevUpdate);
    return;
Lcont:
    pf22 = (s16 *)actor;
    v22 = pf22[0x11];
    sprite->gfxAttr = ((v22 << 6) + 0x200) | ((u16)(ret + 8) << 12);
    sprite->gfxAttr = sprite->gfxAttr | D_02025FF0.spriteAttrMask;
    sub_0801131C((u8 *)sprite, anim, (s32)D_080CD400 + actor->id * 0xC);
    sub_08011368((u8 *)sprite, anim, 0x14, 0);
    arg->flags = arg->flags | 0x1000;
    i = arg->dirIndex;
    arr = (u16 *)arg;
    ((u8 *)(&arr[i]))[0x19] = 0;
    {
        u32 *scriptData = &D_08671BB0;
        ctrlBase = ((u8 *)arg) + 0x18;
        sub_080C31E4(ctrlBase, ((u8 *)arg) + 0x22, *scriptData);
    }
    i = arg->dirIndex;
    arr = (u16 *)arg;
    ((u8 *)(&arr[i]))[0x19] = ((u8 *)(&arr[i]))[0x19] + 1;
    i = arg->dirIndex;
    arr = (u16 *)ctrlBase;
    new_var = &arr[i];
    v = ((u8 *)new_var)[0];
    fn = *((u32 *)(((u8 *)arg->fnTable) + (v * 4)));
    sub_080C31E0((s32)arg, fn);
}
