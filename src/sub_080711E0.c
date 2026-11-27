s32 sub_0806D450(void *a, void *b, void *c);
void sub_0806D588(void *a, void *b);
void setDirectionVector(void *a, s32 v);
void cullOffscreenEntity(void *a, void *b);
void sub_080C31E0(void *a, s32 b);

extern s32 D_0866EB44[];
extern s32 D_080E00A8[];

struct S_02025FF0 {
    u8 _0[0x10];
    s32 field10;
    u8 _14[0x14ED - 0x14];
    u8 field14ED;
    u8 _14EE[0x14FC - 0x14EE];
    s32 field14FC;
    u8 _1500[0x173A - 0x1500];
    u8 field173A;
};
extern struct S_02025FF0 gMainWorkspace;

/* Motion state at *(entity + 0x6C) + 4, in 16.16 fixed point. */
struct ProjectileMotion {
    s32 x;
    s32 y;
    s32 dirX;
    s32 dirY;
    u8 _10[0x4C - 0x10];
    s32 baseX;
    s32 fallVel;
    s32 angle;
};

/* Advances a gravity-driven projectile: apply gravity, rotate its angle, derive
 * the direction vector, integrate and screen-project its position, pick the
 * per-octant sprite data, then abort or run the off-screen release check. */
void sub_080711E0(void *entity)
{
    u8 *actor = *(u8 **)((u8 *)entity + 0x6C);
    struct ProjectileMotion *mover = (struct ProjectileMotion *)(actor + 4);
    u8 *world = *(u8 **)((u8 *)entity + 0x38);
    s32 angle;

    if (sub_0806D450(entity, world, mover) > 0)
        goto abort;

    mover->fallVel += 0xFFFC0000;
    angle = (mover->angle + 6) & 0xFF;
    mover->angle = angle;

    setDirectionVector(mover, angle);

    mover->x = mover->baseX + mover->dirX * 0x28;
    mover->y = mover->fallVel;

    sub_0806D588(world, mover);

    {
        s32 *animTable = D_0866EB44;
        s32 angleValue = mover->angle;
        s32 octant = ((angleValue + 0x10) & 0xFF) >> 5;
        *(s32 *)(world + 0x24) = animTable[octant];
        *(s32 *)(world + 0x1C) = D_080E00A8[octant];
    }

    if (gMainWorkspace.field14FC != 0)
        goto abort;
    if (gMainWorkspace.field173A == 0x1C)
        goto abort;
    if (gMainWorkspace.field14ED != 0)
        goto offscreen;
    if (gMainWorkspace.field10 == 0)
        goto offscreen;

abort:
    sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    return;

offscreen:
    cullOffscreenEntity(entity, world);
}
