extern s32 D_080CFE10[]; /* per-type cap for the speed/phase timer */
extern s32 D_080CFE1C[]; /* per-type amount added to the timer each step */
extern s32 D_080CFE28[]; /* per-type heading turn step */

s32 sub_08005910(s32, s32);
s32 sub_0801473C(s32, s32);
void sub_080146D0(u8 *, s32, s32);
s32 advanceMotion(void *, s32);
void setSpriteFlip(u16 *, s32);
void stepAnimationTrack(s32, void *);

/* Update a homing projectile: advance its timer, steer its heading toward the
 * target, then set velocity, apply movement and refresh its sprite animation. */
void sub_0805BC78(u8 *self)
{
    u8 *sprite;
    u8 *entity;
    u8 *anim;
    u8 *moving;
    u16 angle16;

    sprite = *(u8 **)(self + 0x38);
    entity = *(u8 **)(self + 0x3C);
    anim = entity + 0x34;
    moving = entity + 0x48;

    *(s32 *)(moving + 4) += D_080CFE1C[moving[0]];
    if (*(s32 *)(moving + 4) >= D_080CFE10[moving[0]])
        *(s32 *)(moving + 4) = D_080CFE10[moving[0]];

    {
        s32 curAngle = *(s32 *)(moving + 8);
        u8 *target = (u8 *)0x02025FF0;
        s32 dx = *(s32 *)(target + 0x1750) - *(s32 *)(entity + 0x0C);
        s32 dy = *(s32 *)(target + 0x174C) - *(s32 *)(entity + 0x08);
        s32 turn = sub_0801473C(curAngle, sub_08005910(dx, dy));

        if (turn != -1)
        {
            if (turn == 1)
                *(s32 *)(moving + 8) += D_080CFE28[moving[0]];
        }
        else
        {
            *(s32 *)(moving + 8) -= D_080CFE28[moving[0]];
        }
    }

    angle16 = *(u16 *)(moving + 8);
    *(s32 *)(moving + 8) = angle16;

    sub_080146D0(entity, angle16, *(s32 *)(moving + 4));
    advanceMotion(entity, 0);
    setSpriteFlip((u16 *)sprite, *(s32 *)(moving + 8));
    stepAnimationTrack((s32)sprite, anim);
}
