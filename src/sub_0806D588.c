extern u8 gGameStatus[];
extern s32 sub_08007B78(s32, s32, s32);
extern void sub_080C31E0(void *a, void *b);

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

struct Obj {
    u8 pad0[0x14];
    s32 field14;
    s32 field18;
};

s32 sub_0806D654(struct Vec *arg0)
{
    s32 base = (s32)gTilemapPages + ((u32)gMainWorkspace.b << 6);
    s32 i;

    if ((u16)sub_08007B78(base, arg0->x, arg0->y) == 0)
        return 0;

    i = 0;
    while (1)
    {
        arg0->y += 0xFFFF0000;
        if ((u16)sub_08007B78(base, arg0->x, arg0->y) == 0)
            return 1;
        i++;
        if (i > 7)
            break;
    }
    return 0;
}

void sub_0806D860(s16 arg0)
{
    u8 *base = gGameStatus;
    s16 *p = (s16 *)(base + 0x2D4);
    s32 v = (s16)(*p + arg0);
    *p = (s16)v;
    {
        s16 *cap = (s16 *)((u8 *)p + 2);
        s16 c = *cap;
        if ((s16)v > c)
            *p = c;
    }
}

/* Convert a world-space position to screen-relative coordinates by
 * subtracting the current camera scroll, discarding the fractional bits. */
void sub_0806D588(struct Obj *obj, struct Vec *pos)
{
    u8 *camera = (u8 *)gTilemapPages + ((u32)gMainWorkspace.b << 6);
    obj->field14 = (pos->x & 0xFFFF0000) - *(s32 *)(camera + 0x18);
    obj->field18 = (pos->y & 0xFFFF0000) - *(s32 *)(camera + 0x1C);
}

void sub_080712AA(void *arg0)
{
    u8 *p = (u8 *)arg0;
    *(u32 *)(p + 0x14) = 0x0866EDD4;
    *(s16 *)(p + 0x22) = *(s16 *)(p + 0x22) + 1;
    {
        s16 idx = *(s16 *)(p + 0x22);
        *(u8 *)(p + 0x19 + idx * 2) += 1;
        {
            u8 b = *(u8 *)(p + 0x18 + idx * 2);
            void **tbl = *(void ***)(p + 0x14);
            sub_080C31E0(arg0, tbl[b]);
        }
    }
    *(s16 *)(p + 0x22) = *(s16 *)(p + 0x22) - 1;
}
