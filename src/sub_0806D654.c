extern u8 gGameStatus[];
extern s32 getMapTileAttribute(s32, s32, s32);   /* tile query at (x, y) */
extern void sub_080C31E0(void *a, void *b);

/* Current camera coordinate-table index. */
struct S_02025FF0_18A8 {
    u8 pad[0x18A8];
    u8 b;
};
extern struct S_02025FF0_18A8 gMainWorkspace;
extern u8 gTilemapPages[];

struct Vec {
    s32 x;
    s32 y;
};

/* If the point lies in a marked tile, search up to 8 sixteen-pixel steps
 * upward for a free tile; return 1 if one is found, else 0. */
s32 sub_0806D654(struct Vec *arg0)
{
    u8 *sceneState = (u8 *)&gMainWorkspace;
    s32 tileBase = (s32)gTilemapPages + ((u32)sceneState[0x18A8] << 6);
    s32 step;

    if ((u16)getMapTileAttribute(tileBase, arg0->x, arg0->y) != 0)
    {
        step = 0;
        while (1)
        {
            arg0->y += 0xFFFF0000;
            if ((u16)getMapTileAttribute(tileBase, arg0->x, arg0->y) == 0)
            {
                return 1;
            }
            step++;
            if (step > 7)
            {
                break;
            }
        }
    }
    return 0;
}

/* Raise the s16 value at state+0x2D4 by delta, clamping it to the maximum
 * stored just after it. */
void sub_0806D860(s16 delta)
{
    u8 *state = gGameStatus;
    s16 *value = (s16 *)(state + 0x2D4);
    s32 raised = (s16)(*value + delta);
    *value = (s16)raised;
    {
        s16 *maxPtr = (s16 *)((u8 *)value + 2);
        s16 max = *maxPtr;
        if ((s16)raised > max)
            *value = max;
    }
}

/* Advance an action script by one step: install the step table at 0x0866EDD4,
 * bump the step index and its counter, call the new step's command handler and
 * restore the index. */
void sub_080712AA(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s16 step;

    *(u32 *)(self + 0x14) = 0x0866EDD4;
    *(s16 *)(self + 0x22) = *(s16 *)(self + 0x22) + 1;

    step = *(s16 *)(self + 0x22);
    *(u8 *)(self + 0x19 + step * 2) = *(u8 *)(self + 0x19 + step * 2) + 1;

    {
        u8 command = *(u8 *)(self + 0x18 + step * 2);
        u32 *commandTable = *(u32 **)(self + 0x14);
        sub_080C31E0(arg0, (void *)commandTable[command]);
    }

    *(s16 *)(self + 0x22) = *(s16 *)(self + 0x22) - 1;
}
