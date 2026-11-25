/* Drives a body's vertical velocity (+0x14) toward the player's Y (D_02025FF0+0x1750):
 * pick -0x8000 / 0 / +0x28000 from a 3-entry table outside a +/-0x40000 dead zone,
 * then cancel the velocity at the level's lower/upper Y bounds. */
struct FollowVelocityTable { s32 speed[3]; };
extern struct FollowVelocityTable D_08102EFC;
struct GlobalState { u8 _0x000[0x1750]; u32 playerY; };
extern struct GlobalState D_02025FF0;
void sub_080BBB60(void *arg0)
{
    u8 *body = arg0;
    struct FollowVelocityTable velTable = D_08102EFC;
    s32 speedIndex;
    s32 speed;
    if ((s32)D_02025FF0.playerY < (s32)(*(s32 *)(body + 0x0C) + 0xFFFC0000)) speedIndex = 0;
    else if ((s32)D_02025FF0.playerY > (s32)(*(s32 *)(body + 0x0C) + 0x40000)) speedIndex = 2;
    else speedIndex = 1;
    speed = velTable.speed[speedIndex];
    *(s32 *)(body + 0x14) = speed;
    if (*(s32 *)(body + 0x0C) > 0x019D8000 && *(s32 *)(body + 0x14) > 0)
        *(s32 *)(body + 0x14) = 0;
    else if (*(s32 *)(body + 0x0C) <= 0x01027FFF && *(s32 *)(body + 0x14) < 0)
        *(s32 *)(body + 0x14) = 0;
}
