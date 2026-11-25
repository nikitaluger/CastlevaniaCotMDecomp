s32 sub_08014114(s32, s32, s32, s32, s32, s32);
void sub_080C31E0(void *self, void *fn);
s32 sub_08013B5C(void *, void *);
void sub_080113A8(void *, void *);
void sub_0801165C(void *, s32);

extern u8 D_02021E90[];
extern u8 D_02025FF0[];

/* Update a view-bound object: drop it when it leaves the active camera area;
 * otherwise advance its display state and animation, then place its sprite at
 * the object's world position minus the current scroll offset. */
void sub_08024D74(u8 *obj)
{
    u8 *sprite = *(u8 **)(obj + 0x38);
    u8 *state = *(u8 **)(obj + 0x3C);
    u8 *anim = state + 0x34;
    u8 *flagPtr;
    u8 *scroll;
    u8 *camState;

    flagPtr = *(u8 **)(state + 0x28);
    {
        s32 flags = 1 | *(u8 *)(flagPtr + 1);
        *(u8 *)(flagPtr + 1) = flags;
    }

    if (sub_08014114(*(s32 *)(state + 8), *(s32 *)(state + 0xC), -0x30, 0x30, -0x30, 0x30) == 0) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
        return;
    }

    if (sub_08013B5C(sprite, state) == 0) {
        sub_080113A8(sprite, anim);
        sub_0801165C(state, 0);
    }

    scroll = D_02021E90;
    camState = D_02025FF0;
    camState += 0x18A8;

    {
        u32 idx;
        u8 *xTable;
        u8 *yTable;

        idx = ((u32)*camState + 1) * 0x40;
        xTable = scroll + 0x1278;
        *(u32 *)(sprite + 0x14) = *(u32 *)(state + 8) - ((*(u32 *)(xTable + idx) + 0x8000) & 0xFFFF0000);

        idx = ((u32)*camState + 1) * 0x40;
        yTable = scroll + 0x127C;
        *(u32 *)(sprite + 0x18) = *(u32 *)(state + 0xC) - ((*(u32 *)(yTable + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
