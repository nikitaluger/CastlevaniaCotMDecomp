/* Allocate a graphics object for the entity and clear its two coordinate fields,
 * then, based on the entity's variant, fire one of two script events and dispatch
 * the resulting handler. */
extern void *sub_0800355C(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);

extern void *D_08671BD0;

void sub_08009B2C(u8 *entity)
{
    void *gfx;
    void *handler;

    gfx = sub_0800355C();
    if (gfx == 0)
    {
        handler = *(void **)(entity + 0x24);
        sub_080C31E0(entity, handler);
        return;
    }

    *(void **)(entity + 0x38) = gfx;
    *(s32 *)((u8 *)gfx + 0x18) = 0;
    *(s32 *)((u8 *)gfx + 0x14) = 0;

    switch (*(s8 *)(entity + 0x3C))
    {
    case 0:
    {
        s16 stepIndex;
        u8 *stepTable;
        void **scriptFn;

        stepIndex = *(s16 *)(entity + 0x22);
        *(u8 *)(entity + stepIndex * 2 + 0x19) = 0;
        scriptFn = &D_08671BD0;
        stepTable = entity + 0x18;
        sub_080C31E8(stepTable, entity + 0x22, 1, *scriptFn);

        stepIndex = *(s16 *)(entity + 0x22);
        *(u8 *)(entity + stepIndex * 2 + 0x19) += 1;

        stepIndex = *(s16 *)(entity + 0x22);
        stepTable += stepIndex * 2;
        handler = *(void **)(*(u32 *)(entity + 0x14) + *stepTable * 4);
        sub_080C31E0(entity, handler);
        return;
    }
    case 1:
    {
        s16 stepIndex;
        u8 *stepTable;
        void **scriptFn;

        stepIndex = *(s16 *)(entity + 0x22);
        *(u8 *)(entity + stepIndex * 2 + 0x19) = 0;
        scriptFn = &D_08671BD0;
        stepTable = entity + 0x18;
        sub_080C31E8(stepTable, entity + 0x22, 3, *scriptFn);

        stepIndex = *(s16 *)(entity + 0x22);
        *(u8 *)(entity + stepIndex * 2 + 0x19) += 1;

        stepIndex = *(s16 *)(entity + 0x22);
        stepTable += stepIndex * 2;
        handler = *(void **)(*(u32 *)(entity + 0x14) + *stepTable * 4);
        sub_080C31E0(entity, handler);
        return;
    }
    }
}
