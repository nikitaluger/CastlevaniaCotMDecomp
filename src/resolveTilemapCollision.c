extern s32 getMetatileAttribute(void *, s32, s32);
extern s32 sub_08012A94(s32, s32, s32);

struct TilemapWorkspace {
    u8 _0[0x18A8];
    u8 pageIndex;   /* 0x18A8: index of the active map page */
};
extern struct TilemapWorkspace gMainWorkspace;
extern u8 gTilemapPages[];

/* Resolve a 16.16 movement step against the tilemap: probe the destination
 * metatile (and one above it), snap X to the tile centre when a wall is hit,
 * and report the vertical clearance together with the collision flags. */
void resolveTilemapCollision(s32 x, s32 y, s32 dx, s32 probeDy, struct TilemapCollision *out)
{
    s32 newX;
    s32 clearance;
    s32 step;
    s32 attr;
    void *page;
    out->flags = 0;
    newX = x + dx;
    if ((x & FIXED_POINT_FRAC_MASK) == (newX & FIXED_POINT_FRAC_MASK))
    {
        out->x = newX;
        out->y = y;
        return;
    }

    page = gTilemapPages + (gMainWorkspace.pageIndex << 6);
    attr = getMetatileAttribute(page, newX, y);
    if (attr == 8)
        goto set2;
    if (attr > 8)
        goto check12;
    if (attr == 1)
        goto set1;
    goto after;
check12:
    if (attr != 12)
        goto after;
set1:
    if (dx > 0)
        newX = (newX & TILEMAP_TILE_MASK) + TILEMAP_CENTER_DOWN;
    else
        newX = (newX & TILEMAP_TILE_MASK) + TILEMAP_CENTER_UP;
    out->flags |= TILEMAP_HIT_X;
    goto after;
set2:
    out->flags |= TILEMAP_HIT_Y;
after:
    if (probeDy != 0 && !(out->flags & TILEMAP_HIT_X))
    {
        page = gTilemapPages + (gMainWorkspace.pageIndex << 6);
        attr = getMetatileAttribute(page, newX, y - probeDy);
        if (attr == 1 || attr == 12)
        {
            if (dx > 0)
                newX = (newX & TILEMAP_TILE_MASK) + TILEMAP_CENTER_DOWN;
            else
                newX = (newX & TILEMAP_TILE_MASK) + TILEMAP_CENTER_UP;
            out->flags |= TILEMAP_HIT_X;
        }
    }

    clearance = sub_08012A94(newX, y, 2);
    step = dx;
    if (dx < 0)
        step = -dx;
    step &= FIXED_POINT_FRAC_MASK;
    if (clearance > ((step + 0x10000) * 2) || (out->flags & TILEMAP_HIT_Y))
    {
        if (dx > 0)
            newX = (newX & TILEMAP_TILE_MASK) + TILEMAP_CENTER_DOWN;
        else
            newX = (newX & TILEMAP_TILE_MASK) + TILEMAP_CENTER_UP;
        out->flags |= TILEMAP_HIT_Y;
        clearance = sub_08012A94(newX, y, 1);
    }

    {
        s32 ry = y + clearance;
        out->x = newX;
        out->y = ry;
    }
}
