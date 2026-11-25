typedef struct {
    u16 flags;
    s32 x;
    s32 y;
} MoveResult;

void sub_080126B4(s32, s32, s32 *, s32 *);
void sub_08012704(s32, s32, s32, s32, MoveResult *);
s32 sub_08012A94(s32, s32, s32);
s32 sub_080133EC(s32, s32);

/* Move a fixed-point (x, y) by a signed distance along a cardinal direction,
 * snapping to terrain boundaries and writing back the resulting direction. */
void sub_0801235C(s32 distance, s32 *dir, s32 *x, s32 *y)
{
    s32 dx;
    s32 dy;
    MoveResult result;
    s32 clearance;
    u32 hitFlag;

    sub_080126B4(distance, *dir, &dx, &dy);
    if (distance > 0) {
        if (dy > 0) {
            clearance = sub_08012A94(*x, *y, 2);
            if (clearance <= dy) {
                *y = *y + clearance;
                *dir = 0xC000;
                return;
            }
            if (sub_080133EC(*x - 0x10000, *y + dy) == 0) {
                *x = ((*x - 0x10000) & 0xFFFF0000) + 0x8000;
                *y = ((*y + dy) & 0xFFF80000) + 0x8000;
                *dir = 0x4000;
                return;
            }
            *y = *y + dy;
            return;
        }
        if (dy < 0) {
            if (sub_080133EC(*x, *y + dy) == 1) {
                *y = ((*y + dy) & 0xFFF80000) + 0x88000;
                *dir = 0x4000;
                return;
            }
            if (sub_080133EC(*x + 0x10000, *y + dy) == 0) {
                *x = ((*x + 0x10000) & 0xFFFF0000) + 0x8000;
                *y = ((*y + dy) & 0xFFF80000) + 0x78000;
                *dir = 0xC000;
                return;
            }
            *y = *y + dy;
            return;
        }
        if (dx > 0) {
            sub_08012704(*x, *y, dx, 0, &result);
            hitFlag = result.flags & 1;
            if (hitFlag) {
                *x = result.x;
                *y = result.y;
                *dir = 0x8000;
                return;
            }
            if (result.flags & 2) {
                *x = ((result.x + 0x10000) & 0xFFFF0000) + 0x8000;
                *y = ((result.y + 0x10000) & 0xFFFF0000) + 0x8000;
                *dir = hitFlag;
                return;
            }
            *x = result.x;
            *y = result.y;
            return;
        }
        if (dx < 0) {
            if (sub_080133EC(*x + dx, *y) == 1) {
                *x = (((*x + dx) + 0x80000) & 0xFFF80000) + 0x8000;
                *dir = 0;
                return;
            }
            if (sub_080133EC(*x + dx, *y - 0x10000) == 0) {
                *x = ((*x + dx) & 0xFFF80000) + 0x78000;
                *y = ((*y - 0x10000) & 0xFFFF0000) + 0x8000;
                *dir = 0x8000;
                return;
            }
            *x = *x + dx;
            return;
        }
        return;
    }
    if (dy > 0) {
        clearance = sub_08012A94(*x, *y, 2);
        if (clearance <= dy) {
            *y = *y + clearance;
            *dir = 0xC000;
            return;
        }
        if (sub_080133EC(*x + 0x10000, *y + dy) == 0) {
            *x = ((*x + 0x10000) & 0xFFFF0000) + 0x8000;
            *y = ((*y + dy) & 0xFFF80000) + 0x8000;
            *dir = 0x4000;
            return;
        }
        *y = *y + dy;
        return;
    }
    if (dy < 0) {
        if (sub_080133EC(*x, *y + dy) == 1) {
            *y = ((*y + dy) & 0xFFF80000) + 0x88000;
            *dir = 0x4000;
            return;
        }
        if (sub_080133EC(*x - 0x10000, *y + dy) == 0) {
            *x = ((*x - 0x10000) & 0xFFFF0000) + 0x8000;
            *y = ((*y + dy) & 0xFFF80000) + 0x78000;
            *dir = 0xC000;
            return;
        }
        *y = *y + dy;
        return;
    }
    if (dx < 0) {
        sub_08012704(*x, *y, dx, 0, &result);
        if (result.flags & 1) {
            *x = result.x;
            *y = result.y;
            *dir = 0;
            return;
        }
        if (result.flags & 2) {
            *x = ((result.x - 0x10000) & 0xFFFF0000) + 0x8000;
            *y = ((result.y + 0x10000) & 0xFFFF0000) + 0x8000;
            *dir = 0x8000;
            return;
        }
        *x = result.x;
        *y = result.y;
        return;
    }
    if (dx > 0) {
        if (sub_080133EC(*x + dx, *y) == 1) {
            *x = (((*x + dx) - 0x80000) & 0xFFF80000) + 0x78000;
            *dir = 0x8000;
            return;
        }
        if (sub_080133EC(*x + dx, *y - 0x10000) == 0) {
            *x = ((*x + dx) & 0xFFF80000) + 0x8000;
            *y = ((*y - 0x10000) & 0xFFFF0000) + 0x8000;
            *dir = 0;
            return;
        }
        *x = *x + dx;
        return;
    }
    return;
}
