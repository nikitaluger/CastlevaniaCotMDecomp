extern s32 sub_08004740(void *, s32, s32);
extern s32 sub_08012A94(s32, s32, s32);

struct S_02025FF0 {
    u8 _0[0x18A8];
    u8 idx;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 D_02023130[];

struct Out {
    u16 flags;
    u16 pad;
    s32 x;
    s32 y;
};

void sub_08012704(s32 arg0, s32 arg1, s32 arg2, s32 arg3, struct Out *out)
{
    s32 r4;
    s32 y;
    s32 h;
    s32 v;
    void *base;

    out->flags = 0;
    r4 = arg0 + arg2;
    if ((arg0 & 0xFFFF0000) == (r4 & 0xFFFF0000))
    {
        out->x = r4;
        out->y = arg1;
        return;
    }

    base = D_02023130 + (gMainWorkspace.idx << 6);
    v = sub_08004740(base, r4, arg1);
    if (v == 8)
        goto set2;
    if (v > 8)
        goto check12;
    if (v == 1)
        goto set1;
    goto after;
check12:
    if (v != 12)
        goto after;
set1:
    if (arg2 > 0)
        r4 = (r4 & 0xFFF80000) + 0xFFFF8000;
    else
        r4 = (r4 & 0xFFF80000) + 0x88000;
    out->flags |= 1;
    goto after;
set2:
    out->flags |= 2;
after:
    if (arg3 != 0 && !(out->flags & 1))
    {
        base = D_02023130 + (gMainWorkspace.idx << 6);
        v = sub_08004740(base, r4, arg1 - arg3);
        if (v == 1 || v == 12)
        {
            if (arg2 > 0)
                r4 = (r4 & 0xFFF80000) + 0xFFFF8000;
            else
                r4 = (r4 & 0xFFF80000) + 0x88000;
            out->flags |= 1;
        }
    }

    y = sub_08012A94(r4, arg1, 2);
    h = arg2;
    if (arg2 < 0)
        h = -arg2;
    h &= 0xFFFF0000;
    if (y > ((h + 0x10000) * 2) || (out->flags & 2))
    {
        if (arg2 > 0)
            r4 = (r4 & 0xFFF80000) + 0xFFFF8000;
        else
            r4 = (r4 & 0xFFF80000) + 0x88000;
        out->flags |= 2;
        y = sub_08012A94(r4, arg1, 1);
    }

    {
        s32 ry = arg1 + y;
        out->x = r4;
        out->y = ry;
    }
}
