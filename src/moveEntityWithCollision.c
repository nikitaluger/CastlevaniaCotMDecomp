s32 getTileTerrain(s32 map, s32 x, s32 y);
s32 sub_08012A94(s32 x, s32 y, s32 count);
s32 sub_08012C44(s32 x, s32 y, s32 count);
s32 probeEntityCollision(s32 x, s32 y, s32 velX, s32 velY, s32 mask, void *out);
extern u8 gMainWorkspace[];
extern u8 gTilemapPages[];
extern s16 gTileTerrainFlags[];

/* Partial view of a moving entity: +2 holds the result touch/collision flags. */
struct Entity { u8 _0[2]; u16 touchFlags; };

/* Move an entity by its velocity: apply gravity to the Y velocity, probe other
 * entities for collisions, resolve the terrain slope under the X step, and cap
 * the Y step at the floor, recording contacts in the entity's touch flags. */
void moveEntityWithCollision(void *entity, s32 accel) {
    s32 probe[5];       /* out from the collision probe: {u16 flags, s32 dx, s32 dy} */
    s32 probeHit;
    s32 yLimit;
    s32 velX, velY;
    s32 terrain;
    s32 newX;

    velX = *(s32 *)((u8 *)entity + 0x10);
    velY = *(s32 *)((u8 *)entity + 0x14);
    *(s32 *)((u8 *)entity + 0x14) = velY + accel;
    ((struct Entity *)entity)->touchFlags = 0;
    if (0x10 & *(u16 *)((u8 *)entity + 0x04)) {
        probeHit = probeEntityCollision(*(s32 *)((u8 *)entity + 0x08), *(s32 *)((u8 *)entity + 0x0C), velX, velY, 0x800 | *(u16 *)((u8 *)entity + 0x06), &probe[0]);
        if (probeHit == 1) {
            velX += probe[1];
            velY += probe[2];
            if (1 & *(u16 *)&probe[0]) {
                ((struct Entity *)entity)->touchFlags |= 0x100;
            }
            if (6 & *(u16 *)&probe[0]) {
                ((struct Entity *)entity)->touchFlags |= 0x200;
            }
        }
    }
    {
        s32 newX;
        newX = *(s32 *)((u8 *)entity + 0x08) + velX;
        *(s32 *)((u8 *)entity + 0x08) = newX;
        terrain = getTileTerrain((s32)(gTilemapPages + (gMainWorkspace[0x18A8] << 6)), newX, *(s32 *)((u8 *)entity + 0x0C));
        if ((4 & gTileTerrainFlags[(u16)terrain]) || (4 & *(u16 *)((u8 *)entity + 0x04))) {
            yLimit = sub_08012C44(*(s32 *)((u8 *)entity + 0x08), *(s32 *)((u8 *)entity + 0x0C), 2);
        } else {
            yLimit = sub_08012A94(*(s32 *)((u8 *)entity + 0x08), *(s32 *)((u8 *)entity + 0x0C), 2);
        }
    }
    if (yLimit > velY) {
        *(s32 *)((u8 *)entity + 0x0C) = *(s32 *)((u8 *)entity + 0x0C) + velY;
        if (0x100 & ((struct Entity *)entity)->touchFlags) {
            *(s32 *)((u8 *)entity + 0x14) = 0;
        }
    } else {
        if (yLimit > 0) {
            *(s32 *)((u8 *)entity + 0x0C) = *(s32 *)((u8 *)entity + 0x0C) + yLimit;
            ((struct Entity *)entity)->touchFlags |= 4;
            *(s32 *)((u8 *)entity + 0x14) = 0;
        } else {
            ((struct Entity *)entity)->touchFlags |= 4;
            *(s32 *)((u8 *)entity + 0x14) = 0;
        }
    }
}
