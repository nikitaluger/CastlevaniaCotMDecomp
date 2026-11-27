void forceAnimationFrame(void *, void *, s32, s32);
void sub_08011528(void *, void *);

extern u8 D_08102258[];

#define PARENT (*(u8 *volatile *)(self + 0x28))
#define PARENT_GFX (*(u8 *volatile *)((u8 *)PARENT + 0x38))

/* Inherit a child actor's graphics/animation state from its parent: replay the current animation, optionally override it from a table, then copy the parent's graphics fields. */
void sub_080AD440(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *entity = *(u8 **)(self + 0x3C);
    u8 *anim = entity + 0x34;
    u8 *parentEntity = *(u8 **)(*(u8 **)(self + 0x28) + 0x3C);

    sub_08011528(gfx, anim);

    if ((*(u8 *)(anim) & 2) && *(u8 *)(self + 0x50)) {
        u32 animTable = (u32)D_08102258;
        s32 slot = *(u8 *)(self + 0x4C);
        s32 animId = *(s16 *)(animTable + slot * 2);
        forceAnimationFrame(gfx, anim, animId, 0);
    }

    *(u8 **)(entity + 8) = *(u8 **)(parentEntity + 8);
    *(u8 **)(entity + 0x0C) = *(u8 **)(parentEntity + 0x0C);

    *(u16 *)(gfx) = *(u16 *)(PARENT_GFX);
    *(u16 *)(gfx + 2) = *(u16 *)((u8 *)PARENT_GFX + 2);
    {
        u8 b = *(u8 *)((u8 *)PARENT_GFX + 0x2A);
        *(u8 *)(gfx + 0x2A) = b;
    }
    *(u16 *)(gfx + 4) = *(u16 *)((u8 *)PARENT_GFX + 4);
    *(u16 *)(gfx + 6) = *(u16 *)((u8 *)PARENT_GFX + 6);
    *(u16 *)(gfx + 8) = *(u16 *)((u8 *)PARENT_GFX + 8);
}
