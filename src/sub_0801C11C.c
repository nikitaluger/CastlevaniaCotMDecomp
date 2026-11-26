/* Allocate the entity's mover and sprite work object, install the update
 * callback, and set its screen position from the scroll table. */
extern void *allocSpriteObject(void);
extern void sub_0801C4BC(void *);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void sub_0801C43C(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

struct SpriteDesc { u8 _0; u8 enabled; u8 type; u8 subtype; u16 gfx0; u16 gfx1; u16 gfx2; u16 gfx3; u16 gfx4; u16 frame; u32 owner; u16 tail; };
struct MoverState { u8 _0[8]; s32 x; s32 y; u32 velX; u32 velY; u32 flags18; s16 anim; u8 _1E[4]; s16 state; u32 prevCallback; struct SpriteDesc *desc; };
struct Entity { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 scriptIndex; u8 _24[0x38-0x24]; u8 *workObj; struct MoverState *mover; u8 _40[0x4C-0x40]; s16 posX; u8 _4E[6]; s16 posY; u8 _56[0x6C-0x56]; s16 f5C; u8 _5E[0x6C-0x5E]; u16 f6C; };
struct Globals { u8 _0[0x18A8]; u8 frame; u8 _18A9[0x19]; u16 flags; };
extern struct Globals gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct ScrollTable gCameraState;
extern u8 gSpriteAnimDataTable[];
extern s32 gMainObjTimerCallback[];

void sub_0801C11C(struct Entity *entity) {
    u8 *workObj;
    struct MoverState *mover;
    u8 *moverTarget;
    s32 poseIndex;
    u32 tmp;
    u32 zero;
    u8 *scrollBase;
    s32 *cmdTable;

    workObj = allocSpriteObject();
    if (workObj == NULL) {
        sub_0801C4BC(entity);
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    entity->workObj = workObj;
    allocWorkSlot((u8 *)entity, 0, 0x48, 0);
    mover = entity->mover;
    if (mover == NULL) {
        sub_0801C4BC(entity);
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    moverTarget = (u8 *)mover + 0x34;
    mover->prevCallback = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)sub_0801C43C;
    mover->anim = 0x87;
    mover->flags18 = 1;
    mover->x = entity->posX << 16;
    mover->y = entity->posY << 16;
    poseIndex = findKindIndex(0x87);
    mover->state = poseIndex;
    if ((s32)(poseIndex << 16) < 0) {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    initSpriteGraphics(workObj, moverTarget, (s32)gSpriteAnimDataTable + mover->anim * 0xC);
    tmp = (*(u16 *)workObj & 0xC00) |
          (((*(s16 *)((u8 *)mover + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)mover + 0x22) + 8) << 12));
    *(u16 *)workObj = tmp;
    *(u16 *)workObj = tmp | gMainWorkspace.flags;
    *(u32 *)(workObj + 0x1C) = 0x80000009;
    scrollBase = (u8 *)&gCameraState;
    { u32 scrollOff = 0x1278; *(u32 *)(workObj + 0x14) = mover->x - ((*(u32 *)(scrollBase + scrollOff + ((gMainWorkspace.frame + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 scrollOff = 0x127C; *(u32 *)(workObj + 0x18) = mover->y - ((*(u32 *)(scrollBase + scrollOff + ((gMainWorkspace.frame + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    setAnimationFrame(workObj, moverTarget, 0x0F, 0);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->scriptIndex + 0x19) = 0;
    cmdTable = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *cmdTable);
}
