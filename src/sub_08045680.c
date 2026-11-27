extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Walk the enemy briefly in its facing direction: clear motion, start the walk
 * animation, and while the frame/counter window lasts set horizontal speed from
 * the facing test; when the animation ends, clear this step and dispatch the next. */
void sub_08045680(void *entity)
{
    void *sprite;
    void *part;
    void *anim;
    void *ext;
    s32 frame;
    s32 speed;
    u32 *scriptTable;

    sprite = *(void **)((u8 *)entity + 0x38);
    part = *(void **)((u8 *)entity + 0x3C);
    anim = (u8 *)part + 0x34;
    ext = (u8 *)part + 0x48;
    *(s32 *)((u8 *)part + 0x14) = 0;
    *(s32 *)((u8 *)part + 0x10) = 0;
    *(u16 *)((u8 *)ext + 4) = *(u16 *)((u8 *)ext + 4) + 1;
    setAnimationFrame(sprite, anim, 7, 0);
    frame = *(u8 *)((u8 *)anim + 1) - 1;
    if (frame > 0 && (s16)*(u16 *)((u8 *)ext + 4) <= 0x31) {
        speed = getSpriteFacingSign(sprite);
        if (speed > 0)
            speed = 0x10000;
        else
            speed = 0xFFFF0000;
        *(s32 *)((u8 *)part + 0x10) = speed;
    }
    if (2 & *(u8 *)anim) {
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity) + 0x19) = 0;
        scriptTable = (u32 *)0x08671BD0;
        sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 0, *scriptTable);
    }
}
