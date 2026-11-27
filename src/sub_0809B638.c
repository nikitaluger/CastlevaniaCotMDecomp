extern void setSpriteFlipForDirection(void *, s32);
extern void stepAnimationTrack(void *, void *);
extern void sub_080C31E0(void *, s32);

/* Actor draw step: copy the entity's parameters into its sprite control block
 * and animation player, set the sprite's flip flag from the signed direction,
 * advance the animation, and dispatch the script handler when the animation
 * reports completion (flag 0x02). */
void sub_0809B638(void *arg0)
{
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    void *ctrl = *(void **)((u8 *)arg0 + 0x3C);
    void *anim = (u8 *)ctrl + 0x34;
    *(u32 *)(ctrl + 0x08) = *(u32 *)((u8 *)arg0 + 0x4C);
    *(u32 *)(ctrl + 0x0C) = *(u32 *)((u8 *)arg0 + 0x5C);
    {
        u8 dir = *((u8 *)arg0 + 0x74);
        *(s32 *)(ctrl + 0x10) = (s32)(s8)dir;
    }
    *(u16 *)(sprite + 0x08) = *(u16 *)((u8 *)arg0 + 0x6C);
    setSpriteFlipForDirection(sprite, *(vu32 *)(ctrl + 0x10));
    stepAnimationTrack(sprite, anim);
    if (*(u8 *)anim & 2)
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
