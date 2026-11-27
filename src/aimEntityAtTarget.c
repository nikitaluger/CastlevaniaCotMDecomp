s32 sub_08005910(s32, s32);   /* atan2(dy, dx): angle toward a point */
s32 sub_080059DC(s32, s32);   /* planar distance from a dx/dy pair */

/* Aim an entity at a target point: store the angle to (targetX,targetY) at +0x7C
 * and the distance to it at +0x8C, using the entity's origin at +0x4C/+0x5C. */
void aimEntityAtTarget(void *entity, s32 targetX, s32 targetY) {
    s32 dy;
    s32 dx;

    if (entity != NULL) {
        dx = *(s32 *)((u8 *)entity + 0x4C) - targetX;
        dy = *(s32 *)((u8 *)entity + 0x5C) - targetY;
        *(s32 *)((u8 *)entity + 0x7C) = sub_08005910(dy, dx);
        *(s32 *)((u8 *)entity + 0x8C) = sub_080059DC(dx, dy);
    }
}
