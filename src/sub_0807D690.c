s32 allocWorkSlot(void *, s32, s32, s32);
void *allocSpriteObject(void);
void sub_0806D2D0(void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);

struct S_02025FF0 {
    u8 _0x000[0x18C2];
    u16 spriteIndex;
};
extern struct S_02025FF0 gMainWorkspace;

extern u32 gMainObjTimerCallback[];

/* Spawn-time setup for an entity: allocate its motion object and sprite view,
 * seed the sprite index and clear the animation-frame slot, run the first
 * animation command, then dispatch the callback chosen by the animation state. */
void sub_0807D690(void *entity)
{
    u8 *self = (u8 *)entity;
    void *view;

    if (allocWorkSlot(entity, 0, 0x68, 3) == 0)
    {
        sub_080C31E0(entity, *(s32 *)(self + 0x24));
        return;
    }

    view = allocSpriteObject();
    if (view == 0)
    {
        sub_0806D2D0(entity);
        return;
    }

    *(void **)(self + 0x38) = view;
    *(u32 *)((u8 *)view + 0x1C) = 0x80000004;
    {
        u16 spriteIndex = gMainWorkspace.spriteIndex;
        u32 zero = 0;
        *(u16 *)view = spriteIndex;

        {
            s32 animIndex = *(s16 *)(self + 0x22);
            *(u8 *)(self + animIndex * 2 + 0x19) = zero;
        }
    }

    {
        const u32 *animScript = (const u32 *)0x08671BB0;
        void *animState = self + 0x18;
        sub_080C31E4(animState, self + 0x22, *animScript);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        animState = (u8 *)animState + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)animState * 4));
    }
}
