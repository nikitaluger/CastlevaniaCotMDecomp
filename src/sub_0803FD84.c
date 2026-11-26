s32 sub_080113A8(s32, void *);
s32 setAnimationFrameAndRecord(s32, void *, void *, u16);
s32 sub_08040B34(void *, s32, void *);
extern void _call_via_r2(void *, void *, s32);

extern u16 D_080CF478[];
extern s32 gMainObjTimerCallback[];

/* Tick this enemy's animation; once it finishes, select the next shot animation
 * from the variant table, raise the part a pixel, optionally spawn a projectile
 * for non-default variants, then clear this script step and dispatch the next. */
void sub_0803FD84(void *entity)
{
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    void *part = *(void **)((u8 *)entity + 0x3C);
    void *anim = (u8 *)part + 0x34;
    void *ext = (u8 *)part + 0x48;

    sub_080113A8(sprite, anim);

    if (*(u8 *)anim & 0x02) {
        u32 base = (u32)D_080CF478;
        u8 variant = *(u8 *)((u8 *)entity + 0x4C);
        u16 shotAnim = *(u16 *)(base + variant * 2);
        setAnimationFrameAndRecord(sprite, anim, ext, shotAnim);
        *(s32 *)((u8 *)part + 0x0C) += 0x10000;
        if (*(volatile u8 *)((u8 *)entity + 0x4C) != 0) {
            sub_08040B34(entity, sprite, part);
        }
        {
            s32 step = *(s16 *)((u8 *)entity + 0x22);
            *((u8 *)entity + step * 2 + 0x19) = 0;
        }
        {
            s32 *scriptTable = (s32 *)0x08671BB0;
            _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptTable);
        }
    }
}
