extern u8 gMainWorkspace[];

void sub_0806D588(void *, void *);
void _call_via_r1(void *, void *);

/* Reads the special-behavior flag word for the current area and, depending on
 * which high bit is set, applies signed byte deltas plus a flat offset to a
 * position vector and snaps it back to the grid through sub_0806D588, or invokes
 * the entity's callback. Returns a code for the action taken (0 none, 1 held,
 * 2 repositioned, -3/-4 callback). */
s32 applyAreaSpecialBehavior(void *entity, void *obj, void *vec)
{
    u8 *state = gMainWorkspace;
    u32 flags = *(u32 *)(state + 0x14B8);

    if ((flags & 0xF0) == 0)
        return 0;

    if (flags & 0x80)
        return 1;

    if (flags & 0x10)
    {
        s32 *pos = (s32 *)vec;
        s32 a;
        s32 b;

        a = *(u8 *)(state + 0x14C6);
        a = a << 24;
        b = pos[0];
        pos[0] = a + b - ((s32)*(u8 *)(state + 0x14C4) << 24) + *(s32 *)(state + 0x14D0);

        a = *(u8 *)(state + 0x14C7);
        a = a << 24;
        b = pos[1];
        pos[1] = a + b - ((s32)*(u8 *)(state + 0x14C5) << 24) + *(s32 *)(state + 0x14D4);

        sub_0806D588(obj, vec);
        *(u16 *)obj = *(u16 *)(state + 0x18C2);
        return 2;
    }

    if (flags & 0x20)
    {
        _call_via_r1(entity, *(void **)((u8 *)entity + 0x24));
        return -3;
    }

    if (flags & 0x40)
    {
        _call_via_r1(entity, *(void **)((u8 *)entity + 0x24));
        return -4;
    }

    return 0;
}
