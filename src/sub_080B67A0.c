/* Allocate an entity's mover and sprite descriptor, fill them from the global
 * tuning tables, install its update callback and advance its script pointer. */
struct GlobalFlags { u8 _0[0x18C2]; u16 flags; };
extern struct GlobalFlags D_02025FF0;
struct SpriteDesc { u8 _0, enabled, type, subtype; u16 gfx0, gfx1, gfx2, gfx3, gfx4; s16 frame; u32 owner; };
struct MoverState {
    u8 _0[8]; u32 x, y, velX, velY; u8 _18[4]; u16 anim; u8 _1E[4]; u16 state; u8 _24[4];
    struct SpriteDesc *desc;
};
struct FrameDef { u8 _0[0x18]; u16 data0; u16 data1; u8 _18[0x0C]; };
struct MoveParam { s32 velX; s32 velY; };
extern struct FrameDef D_080CBDD0[];
extern struct MoveParam D_08102D14[];
extern u16 D_08102D0C[];
extern u32 D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern void sub_08014668(void *, s32);
extern void sub_080B7134(void *, void *);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(u8 *, u32);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern void sub_08097DC8(void);

void sub_080B67A0(u8 *entity) {
    u8 *workObj;
    struct MoverState *mover;
    u8 *moverTarget;
    u16 *gfxParams;
    u8 *scriptPtr;
    s32 *cmdTable;
    u8 *q;

    workObj = sub_0800355C();
    if (workObj == NULL) goto fail;
    *(u32 *)(entity + 0x38) = (u32)workObj;
    sub_0800168C(entity, 0, 0x48, 0);
    if (*(u32 *)(entity + 0x3C) == 0) goto fail;
    *(u32 *)(workObj + 0x1C) = 0x8000000B;
    mover = (struct MoverState *)*(u32 *)(entity + 0x3C);
    moverTarget = (u8 *)mover + 0x34;
    sub_08014288(entity, mover, sub_08097DC8);
    mover->anim = 0x66;
    *(u16 *)workObj |= D_02025FF0.flags;
    mover->x = *(u32 *)(entity + 0x4C);
    mover->y = *(u32 *)(entity + 0x5C);
    mover->velX = D_08102D14[*(u8 *)(entity + 0x70)].velX * (s8)*(u8 *)(entity + 0x6C);
    mover->velY = D_08102D14[*(u8 *)(entity + 0x70)].velY;
    sub_08014668(workObj, -mover->velX);
    sub_080B7134(workObj, moverTarget);
    sub_08011368(workObj, moverTarget, 0, 1);
    gfxParams = D_08102D0C;
    mover->desc = sub_08016190();
    if (mover->desc == NULL) goto fail;
    goto cont;
fail:
    sub_080C31E0(entity, *(u32 *)(entity + 0x24));
    return;
cont:
    mover->desc->enabled = 1;
    mover->desc->type = 8;
    mover->desc->subtype = 1;
    mover->desc->gfx0 = D_080CBDD0[*(s16 *)((u8 *)mover + 0x1C)].data0;
    mover->desc->gfx1 = gfxParams[0];
    mover->desc->gfx2 = gfxParams[1];
    mover->desc->gfx3 = gfxParams[2];
    mover->desc->gfx4 = gfxParams[3];
    mover->desc->frame = D_080CBDD0[*(s16 *)((u8 *)mover + 0x1C)].data1;
    mover->desc->owner = (u32)workObj;
    *(u16 *)(entity + 2) |= 0x1000;
    *(u8 *)(entity + (u32)(*(s16 *)(entity + 0x22)) * 2 + 0x19) = 0;
    cmdTable = &D_08671BB0;
    scriptPtr = entity + 0x18;
    sub_080C31E4(scriptPtr, entity + 0x22, *cmdTable);
    *(u8 *)(entity + (u32)(*(s16 *)(entity + 0x22)) * 2 + 0x19) += 1;
    q = scriptPtr + (u32)(*(s16 *)(entity + 0x22)) * 2;
    sub_080C31E0(entity, *(u32 *)(*(u32 *)(entity + 0x14) + *(u8 *)q * 4));
}
