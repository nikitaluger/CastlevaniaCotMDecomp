extern s32 getAngleFromDelta(s32, s32);

/* Aim a three-part fan effect at (x, y): every actor gets that origin, an
 * angle 0x2000 (45 degrees) apart around the camera-to-point direction, and
 * the active flag at +0x7C. */
void sub_080B06F4(void **actors, s32 x, s32 y)
{
    u8 *camera = (u8 *)0x02025FF0;
    s32 angle;
    u32 i;
    void *actor;
    angle = getAngleFromDelta(*(s32 *)(camera + 0x1750) - y, *(s32 *)(camera + 0x174C) - x) + 0xFFFFE000;
    i = 0;
    do
    {
        actor = *(void * volatile *)actors;
        *(s32 *)(actor + 0x4C) = x;
        actor = *(void * volatile *)actors;
        *(s32 *)(actor + 0x5C) = y;
        actor = *(void * volatile *)actors;
        *(s32 *)(actor + 0x6C) = angle;
        actor = *actors++;
        *(u8 *)(actor + 0x7C) = 1;
        angle += 0x2000;
        i++;
    } while (i <= 2);
}
