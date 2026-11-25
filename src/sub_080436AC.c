extern void *sub_0800355C(void);
extern void sub_0800168C(void *a, s32 b, s32 c, s32 d);
extern s32 sub_08013C2C(s16);
extern void sub_0801131C(void *a, void *b, s32 c);
extern void sub_08011368(void *a, void *b, s32 c, s32 d);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);

struct S_02025FF0 {
    u8 _0[0x18A8];
    u8 f18A8;
    u8 _18A9[0x19];
    u16 f18C2;
};
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02021E90[];
extern u8 D_080CD400[];
extern u32 D_08671BB0;

/* Per-entity state allocated through sub_0800168C. */
struct EntityState {
    u8 _0[0x08];
    s32 worldX;       /* 0x08: spawn X, 16.16 */
    s32 worldY;       /* 0x0C: spawn Y, 16.16 */
    u8 _10[0x18-0x10];
    s32 type;         /* 0x18 */
    s16 id;           /* 0x1C: entity id / animation selector */
    u8 _1E[4];
    u16 animIndex;    /* 0x22: table index returned by sub_08013C2C */
};

/* Spawns one entity from a descriptor: allocates its sprite and state objects,
 * copies the id/position, sets up animation from D_080CD400, positions it
 * against the camera, then calls back through the pointer in D_08671BB0. */
void sub_080436AC(u8 *spawn) {
    u8 *sprite = sub_0800355C();
    struct EntityState *state;
    u8 *anim;
    u8 *camBase;
    u32 *callbackSlot;

    if (sprite == NULL) goto fail;
    *(u32 *)(spawn + 0x38) = (u32)sprite;
    sub_0800168C(spawn, 0, 0x48, 0);
    state = (struct EntityState *)*(u32 *)(spawn + 0x3C);
    if (state == NULL) goto fail;
    anim = (u8 *)state + 0x34;
    state->id = *(u16 *)(spawn + 0x6C);
    state->type = 1;
    state->worldX = (s16)*(s16 *)(spawn + 0x4C) << 16;
    state->worldY = (s16)*(s16 *)(spawn + 0x54) << 16;
    state->animIndex = sub_08013C2C(state->id);
    if ((s16)state->animIndex >= 0) goto main;
fail:
    sub_080C31E0(spawn, *(s32 *)(spawn + 0x24));
    return;
main:
    sub_0801131C(sprite, anim, (s32)D_080CD400 + state->id * 0xC);
    {
        u16 attr = 0xC00 & *(u16 *)sprite;
        s32 flags = (s16)(*(s16 *)((u8 *)state + 0x22)) << 6;
        flags += 0x200;
        flags |= ((u16)(*(u16 *)((u8 *)state + 0x22)) + 8) << 12;
        *(u16 *)sprite = (u16)(attr | flags);
    }
    *(u16 *)sprite = (u16)(*(u16 *)sprite | D_02025FF0.f18C2);
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camBase = D_02021E90;
    { u32 off = 0x1278; *(u32 *)(sprite + 0x14) = state->worldX - ((*(u32 *)(camBase + off + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 off = 0x127C; *(u32 *)(sprite + 0x18) = state->worldY - ((*(u32 *)(camBase + off + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    if ((s16)*(s16 *)(spawn + 0x5C) > 0) {
        *(u16 *)(sprite + 2) |= 0x10;
    }
    sub_08011368(sprite, anim, 7, 0);
    *(u16 *)(spawn + 2) |= 0x1000;
    *(u8 *)(spawn + (s16)*(s16 *)(spawn + 0x22) * 2 + 0x19) = 0;
    callbackSlot = &D_08671BB0;
    sub_080C31E4(spawn + 0x18, spawn + 0x22, *callbackSlot);
}
