struct Movement119B4 {
    u8 _0[2];
    u16 touchFlags;
    u16 flags;
    u16 collisionMask;
    s32 x;
    s32 y;
    s32 velX;
    s32 velY;
};

s32 getTileTerrain(s32 map, s32 x, s32 y);
s32 sub_08012A94(s32 x, s32 y, s32 count);
s32 probeEntityCollision(s32 x, s32 y, s32 velX, s32 velY, s32 mask, void *out);
extern u8 gMainWorkspace[];
extern u8 gTilemapPages[];
extern s16 gTileTerrainFlags[];

void sub_080119B4(struct Movement119B4 *entity, s32 accel, s32 height, s32 halfWidth, s32 width) {
    s32 probe[5];
    s32 probeHit;
    s32 yLimit;
    s32 rightLimit;
    s32 velX;
    s32 velY;
    s32 terrain;
    s32 newX;
    s32 edge;

    entity->touchFlags = 0;
    if (entity->velX != 0) {
        s32 velY;
        velX = entity->velX;
        entity->velY = 0;
        velY = entity->velY;
        if (entity->flags & 0x10) {
            if (velX < 0) {
                probeHit = probeEntityCollision(entity->x - halfWidth, entity->y, velX, velY, entity->collisionMask | 0x200, probe);
                if (probeHit == 1) {
                    velX += probe[1];
                    if (*(u16 *)&probe[0] & 1) entity->touchFlags |= 0x100;
                    if (*(u16 *)&probe[0] & 6) entity->touchFlags |= 0x200;
                }
                if (height != 0) {
                    if (probeEntityCollision(entity->x - halfWidth, entity->y - height, velX, velY, entity->collisionMask | 0x300, probe) == 1) {
                        velX += probe[1];
                        if (*(u16 *)&probe[0] & 6) entity->touchFlags |= 0x200;
                        if (*(u16 *)&probe[0] & 8) entity->touchFlags |= 0x400;
                    }
                }
                probeHit = probeEntityCollision(entity->x + width, entity->y, velX, velY, entity->collisionMask | 0x400, probe);
                if ((probeHit == 1) && (*(u16 *)&probe[0] & 1)) entity->touchFlags |= 0x100;
                if (height != 0) {
                    probeHit = probeEntityCollision(entity->x + width, entity->y - height, velX, velY, entity->collisionMask | 0x500, probe);
                    if ((probeHit == 1) && (*(u16 *)&probe[0] & 8)) entity->touchFlags |= 0x400;
                }
            } else {
                probeHit = probeEntityCollision(entity->x + width, entity->y, velX, velY, entity->collisionMask | 0x400, probe);
                if (probeHit == 1) {
                    velX += probe[1];
                    if (*(u16 *)&probe[0] & 1) entity->touchFlags |= 0x100;
                    if (*(u16 *)&probe[0] & 6) entity->touchFlags |= 0x200;
                }
                if (height != 0) {
                    if (probeEntityCollision(entity->x + width, entity->y - height, velX, velY, entity->collisionMask | 0x500, probe) == 1) {
                        velX += probe[1];
                        if (*(u16 *)&probe[0] & 6) entity->touchFlags |= 0x200;
                        if (*(u16 *)&probe[0] & 8) entity->touchFlags |= 0x400;
                    }
                }
                probeHit = probeEntityCollision(entity->x - halfWidth, entity->y, velX, velY, entity->collisionMask | 0x200, probe);
                if ((probeHit == 1) && (*(u16 *)&probe[0] & 1)) entity->touchFlags |= 0x100;
                if (height != 0) {
                    probeHit = probeEntityCollision(entity->x - halfWidth, entity->y - height, velX, velY, entity->collisionMask | 0x300, probe);
                    if ((probeHit == 1) && (*(u16 *)&probe[0] & 8)) entity->touchFlags |= 0x400;
                }
            }
        }
        terrain = getTileTerrain(gTilemapPages + (gMainWorkspace[0x18A8] << 6), entity->x + velX - halfWidth, entity->y + 0x80000);
        if ((gTileTerrainFlags[(u16)terrain] & 0xE) || (gTileTerrainFlags[(u16)getTileTerrain(gTilemapPages + (gMainWorkspace[0x18A8] << 6), entity->x + velX + width, entity->y + 0x80000)] & 0xE)) {
            entity->touchFlags |= 4;
        }
        newX = entity->x + velX;
        if ((entity->x & 0xFFFF0000) == (newX & 0xFFFF0000)) {
            entity->x = newX;
            return;
        }
        edge = newX + width;
        if (velX < 0) edge = newX - halfWidth;
        terrain = getTileTerrain(gTilemapPages + (gMainWorkspace[0x18A8] << 6), edge, entity->y);
        if (gTileTerrainFlags[(u16)terrain] & 0xA) {
            if (velX > 0) edge = (edge & 0xFFF80000) + 0xFFFF8000;
            else edge = (edge & 0xFFF80000) + 0x88000;
            entity->touchFlags |= 1;
        } else {
            terrain = getTileTerrain(gTilemapPages + (gMainWorkspace[0x18A8] << 6), edge, entity->y - height);
            if (gTileTerrainFlags[(u16)terrain] & 0xA) {
                if (velX > 0) edge = (edge & 0xFFF80000) + 0xFFFF8000;
                else edge = (edge & 0xFFF80000) + 0x88000;
                entity->touchFlags |= 1;
            }
        }
        if (velX < 0) entity->x = edge + halfWidth;
        else entity->x = edge - width;
        return;
    }

    velY = entity->velY;
    entity->velY = velY + accel;
    if (entity->flags & 0x10) {
        probeHit = probeEntityCollision(entity->x - halfWidth, entity->y, 0, velY, entity->collisionMask | 0x200, probe);
        if (probeHit == 1) {
            velY += probe[2];
            if (*(u16 *)&probe[0] & 1) entity->touchFlags |= 0x100;
            if (*(u16 *)&probe[0] & 6) entity->touchFlags |= 0x200;
            if (*(u16 *)&probe[0] & 8) entity->touchFlags |= 0x400;
        }
        probeHit = probeEntityCollision(entity->x + width, entity->y, 0, velY, entity->collisionMask | 0x400, probe);
        if (probeHit == 1) {
            velY += probe[2];
            if (*(u16 *)&probe[0] & 1) entity->touchFlags |= 0x100;
            if (*(u16 *)&probe[0] & 6) entity->touchFlags |= 0x200;
            if (*(u16 *)&probe[0] & 8) entity->touchFlags |= 0x400;
        }
    }
    yLimit = sub_08012A94(entity->x - halfWidth, entity->y, 2);
    rightLimit = sub_08012A94(entity->x + width, entity->y, 2);
    if (rightLimit > yLimit) yLimit = rightLimit;
    if (yLimit > velY) {
        entity->y = entity->y + velY;
    } else {
        entity->y = entity->y + yLimit;
        entity->touchFlags |= 4;
        entity->velY = 0;
    }
    if (entity->touchFlags & 0x100) entity->velY = 0;
}
