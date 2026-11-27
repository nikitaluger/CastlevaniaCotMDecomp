struct S_02025FF0 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

extern void stepAnimationTrack(void *, void *);
extern void *spawnBudgetedEffect(u32, s32);
extern void sub_080C31E0(void *, s32);

/* During the first few script steps, spawn a child object at the part's
 * position and copy the entity's extra byte, step and variant into it. Then
 * tick the animation and, once it ends, dispatch the next script step. */
void sub_08046CF0(void *entity)
{
    void *child;
    void *sprite;
    void *part;
    void *anim;
    u8 extraByte;
    u8 variantByte;
    u8 subStep;

    sprite = *(void **)((u8 *)entity + 0x38);
    part = *(void **)((u8 *)entity + 0x3C);
    anim = (u8 *)part + 0x34;
    if (*(u8 *)((u8 *)entity + ((s32)*(s16 *)((u8 *)entity + 0x22) * 2) + 0x19) <= 6) {
        child = spawnBudgetedEffect(gMainWorkspace.v, 0x122);
        if (child != 0) {
            *(s32 *)((u8 *)child + 0x5C) = *(s32 *)((u8 *)part + 8);
            *(s32 *)((u8 *)child + 0x6C) = *(s32 *)((u8 *)part + 0xC);
            extraByte = *(u8 *)((u8 *)entity + 0x7C);
            *(u8 *)((u8 *)child + 0x7C) = extraByte;
            subStep = 3 & *(u8 *)((u8 *)entity + ((s32)*(s16 *)((u8 *)entity + 0x22) * 2) + 0x19);
            *(u8 *)((u8 *)child + 0x90) = subStep;
            variantByte = *(u8 *)((u8 *)entity + 0x4C);
            *(u8 *)((u8 *)child + 0x4C) = variantByte;
        }
    }
    stepAnimationTrack(sprite, anim);
    if (2 & *(u8 *)anim) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
