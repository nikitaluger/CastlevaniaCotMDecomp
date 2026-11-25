/* Update an entity's motion state from its mover, fire a queued spawn request,
 * then convert its world position into scroll-relative screen coordinates. */
struct Entity {
    u8 _00[0x38]; void *motion; void *mover; u8 _40[0x0C];
    u32 worldX; u8 _50[0x0C]; u32 worldY; u8 _60[0x0C]; u32 facing;
    u8 _70[0x0C]; u16 pose; u8 _7E[6]; s8 requestedPose; u8 _85[3]; s8 currentPose; u8 _89[3]; u8 spawnRequest;
};
struct Mover {
    u8 _00[0x08]; u32 x; u32 y; u32 facing; u8 _14[0x14]; u32 linkData; u8 _2C[8];
};
struct Motion {
    u8 _00[0x02]; u16 flags; u8 _04[0x04]; u16 pose; u8 _0A[0x0A]; u32 screenX; u32 screenY;
};
struct Offset { u32 dx; u32 dy; };
struct ScrollState { u8 _0[0x18A8]; u8 frame; };
extern u8 D_02021E90[];
extern struct ScrollState D_02025FF0;
extern s16 D_081017F0[];
extern struct Offset D_081017F8[];
void sub_08014668(void *, u32);
void sub_080114A8(void *, u32, s16, u32);
void sub_0809C678(u32, u32);
void sub_0809C87C(u32, u32);
void sub_0809C8A8(u32, u32, u16, s32);

void sub_0809B824(void *a) {
    struct Entity *entity = a;
    struct Motion *motion = entity->motion;
    struct Mover *mover = entity->mover;
    u8 *coordTable;
    u8 *xTable;
    u8 *yTable;
    u32 moverTarget = 0x34 + (u32)mover;
    u32 spawnX, spawnY, baseX;
    u32 coordIdx;

    mover->x = entity->worldX;
    mover->y = entity->worldY;
    mover->facing = entity->facing;
    motion->pose = entity->pose;
    sub_08014668(motion, mover->facing);
    if ((s8)entity->currentPose != (s8)entity->requestedPose) {
        entity->currentPose = entity->requestedPose;
        sub_080114A8(motion, moverTarget, D_081017F0[(s32)(s8)entity->requestedPose], 0);
    }
    if (entity->spawnRequest != 0) {
        baseX = mover->x;
        if ((motion->flags & 0x10) != 0) {
            spawnX = baseX + D_081017F8[entity->spawnRequest - 1].dx;
        } else {
            spawnX = baseX - D_081017F8[entity->spawnRequest - 1].dx;
        }
        spawnY = mover->y + D_081017F8[entity->spawnRequest - 1].dy;
        switch (entity->spawnRequest) {
        case 1:
            sub_0809C87C(spawnX, spawnY);
            break;
        case 2:
            sub_0809C8A8(spawnX, spawnY, (u16)(0x1000 + entity->pose), (motion->flags & 0x10) ? 1 : -1);
            break;
        }
        entity->spawnRequest = 0;
    }
    sub_0809C678(moverTarget, mover->linkData);
    coordTable = D_02021E90;
    coordIdx = (D_02025FF0.frame + 1) * 64;
    xTable = coordTable + 0x1278;
    motion->screenX = mover->x - ((*(u32 *)(xTable + coordIdx) + 0x8000) & 0xFFFF0000);
    coordIdx = (D_02025FF0.frame + 1) * 64;
    yTable = coordTable + 0x127C;
    motion->screenY = mover->y - ((*(u32 *)(yTable + coordIdx) + 0xFFFF8000u) & 0xFFFF0000);
}
