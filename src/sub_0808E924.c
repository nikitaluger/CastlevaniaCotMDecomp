extern void sub_080113A8(void *, void *);
extern void sub_080C31E0(void *, void *);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];

// Updates an object's position relative to the current scroll: after a flag
// check that can cancel the entity, it indexes two offset tables by the scroll
// counter and subtracts their rounded values from the object's x/y coordinates.
void sub_0808E924(void *entity)
{
    u8 *scrollIdx;
    u8 *state;
    void *obj;
    u8 *flag;

    obj = *(void **)((u8 *)entity + 0x38);
    flag = *(u8 **)((u8 *)entity + 0x3C);
    sub_080113A8(obj, flag);

    if (*flag & 2)
    {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }

    state = gCameraState;
    scrollIdx = gMainWorkspace;
    scrollIdx += 0x18A8;

    {
        u32 tableOffset;
        u8 *xTable;
        u8 *yTable;

        tableOffset = ((u32)*scrollIdx + 1) * 0x40;
        xTable = state + 0x1278;
        *(u32 *)((u8 *)obj + 0x14) = *(u32 *)((u8 *)entity + 0x4C) - ((*(u32 *)(xTable + tableOffset) + 0x8000) & 0xFFFF0000);

        tableOffset = ((u32)*scrollIdx + 1) * 0x40;
        yTable = state + 0x127C;
        *(u32 *)((u8 *)obj + 0x18) = *(u32 *)((u8 *)entity + 0x5C) - ((*(u32 *)(yTable + tableOffset) + 0xFFFF8000) & 0xFFFF0000);
    }
}
