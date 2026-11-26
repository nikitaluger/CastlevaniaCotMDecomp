extern s32 getTileTerrain(void *, s32, s32);
extern s32 probeEntityCollision(s32, s32, s32, s32, u32, u32);
extern u8 gMainWorkspace[];
extern u8 gTilemapPages[];
extern s16 gTileTerrainFlags[];

/* Moving object: +2 touch flags, +4 collision checks, +6 probe mask,
 * +8/+0xC world position and +0x10 horizontal velocity (all 16.16). */
struct MovingObject {
    u8 _0[2];
    u16 touchFlags;
    u16 collideFlags;
    u16 probeMask;
    s32 x;
    s32 y;
    s32 velX;
};

/* Moves an object horizontally by its velocity, resolving tile collisions and
 * recording wall/floor/ceiling hits in the object's touch flags. */
void moveObjectHorizontally(struct MovingObject *obj, s32 probeNeg, s32 probePos)
{
    s32 velocity = obj->velX;
    s32 probeX, newX, candidateX, tile;
    s32 oldX, oldPage;
    u32 hit[5];

    obj->touchFlags = 0;
    if (obj->collideFlags & OBJ_CHECK_ENTITIES) {
        if (probeNeg != 0 || probePos != 0) {
            if (velocity < 0) probeX = obj->x - probeNeg;
            else probeX = obj->x + probePos;
        } else probeX = obj->x;
        if (probeEntityCollision(probeX, obj->y, velocity, 0, 0x900 | obj->probeMask, (u32)hit) == 1) {
            velocity += (s32)hit[1];
            if (*(u16 *)hit & PROBE_WALL_BITS) obj->touchFlags |= TOUCH_ENTITY_HIT;
        }
    }
    oldX = obj->x;
    oldPage = oldX & 0xFFFF0000;
    newX = oldX + velocity;
    if (oldPage == (newX & 0xFFFF0000)) {
        obj->x = newX;
    } else {
        if (probeNeg != 0 || probePos != 0) {
            if (velocity < 0) candidateX = newX - probeNeg;
            else candidateX = newX + probePos;
        } else candidateX = newX;

        tile = getTileTerrain((void *)(gTilemapPages + gMainWorkspace[0x18A8] * 0x40), candidateX, obj->y);
        if (gTileTerrainFlags[(u16)tile] & TERRAIN_BLOCK_MOVE) {
            if (obj->velX > 0) candidateX = (candidateX & 0xFFF80000) - 0x8000;
            else candidateX = (candidateX & 0xFFF80000) + 0x88000;
            obj->touchFlags |= TOUCH_WALL_LEFT;
        }
        if (obj->collideFlags & OBJ_CHECK_FLOOR) {
            tile = getTileTerrain((void *)(gTilemapPages + gMainWorkspace[0x18A8] * 0x40), candidateX, obj->y + 0x80000);
            if (gTileTerrainFlags[(u16)tile] & TERRAIN_SOLID) {
                if (obj->velX > 0) candidateX = (candidateX & 0xFFF80000) - 0x8000;
                else candidateX = (candidateX & 0xFFF80000) + 0x88000;
                obj->touchFlags |= TOUCH_WALL_RIGHT;
            }
        }
        if (obj->collideFlags & OBJ_CHECK_CEILING) {
            tile = getTileTerrain((void *)(gTilemapPages + gMainWorkspace[0x18A8] * 0x40), candidateX, obj->y - 0x80000);
            if (gTileTerrainFlags[(u16)tile] & TERRAIN_SOLID) {
                if (obj->velX > 0) candidateX = (candidateX & 0xFFF80000) - 0x8000;
                else candidateX = (candidateX & 0xFFF80000) + 0x88000;
                obj->touchFlags |= TOUCH_CEILING_HIT;
            }
        }
        if (probeNeg != 0 || probePos != 0) {
            if (velocity < 0) candidateX += probeNeg;
            else candidateX -= probePos;
        }
        obj->x = candidateX;
    }
}
