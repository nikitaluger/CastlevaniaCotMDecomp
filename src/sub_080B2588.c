s32 updateObjectDisplayState(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
void _call_via_r1(void *, void *);

/* Actor update for a follower: copy the parent object's position and X-flip flag into
 * its own work/sprite, apply the display state, dispatch the next handler from a
 * temporary table through the indirect-call thunk, then refresh screen coordinates. */
void sub_080B2588(void *entity)
{
    void *sprite;
    void *work;
    void *parent;
    void *parentWork;

    sprite = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    parent = *(void **)((u8 *)entity + 0x28);
    parentWork = *(void **)((u8 *)parent + 0x3C);
    *(u32 *)((u8 *)work + 8) = *(u32 *)((u8 *)parentWork + 8);
    *(u32 *)((u8 *)work + 0xC) = *(u32 *)((u8 *)parentWork + 0xC);

    if (*(u16 *)((u8 *)*(void **)((u8 *)parent + 0x38) + 2) & 0x10) {
        s32 flipFlags = 0x10 | *(u16 *)((u8 *)sprite + 2);
        *(u16 *)((u8 *)sprite + 2) = flipFlags;
    } else {
        *(u16 *)((u8 *)sprite + 2) &= 0xFFEF;
    }

    if (updateObjectDisplayState(sprite, work) == 0) {
        u8 *stepEntry;
        u8 stepCommand;
        u32 handlerTable;
        s32 stepOffset;

        *(u32 *)((u8 *)entity + 0x14) = 0x08670308;
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
        {
            u8 *stepFlagPtr;
            stepFlagPtr = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepFlagPtr + 0x19) = *(u8 *)(stepFlagPtr + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        stepEntry = (u8 *)entity;
        stepEntry += 0x18;
        stepEntry += stepOffset;
        stepCommand = *stepEntry;
        handlerTable = *(u32 *)((u8 *)entity + 0x14);
        _call_via_r1(entity, (void *)*(s32 *)((u32)(stepCommand * 4) + handlerTable));
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    }

    syncSpriteToWorldPosition(entity, sprite);
}
