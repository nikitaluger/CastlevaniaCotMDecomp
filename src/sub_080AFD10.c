extern u8 gCameraState[];
extern u8 gMainWorkspace[];

struct S2 { u8 pad[2]; u16 f2; };

/* Tracking update: mirrors a parent entity's direction/flags and position, then applies
 * smoothed coordinate corrections from the shared table to this entity's graphics object. */
void sub_080AFD10(void *arg0) {
    void *obj = *(void **)((u8 *)arg0 + 0x38);
    void *state = *(void **)((u8 *)arg0 + 0x3C);
    void *parent = *(void **)((u8 *)arg0 + 0x28);
    void *parentState = *(void **)((u8 *)parent + 0x3C);
    void *parentObj = *(void **)((u8 *)parent + 0x38);
    s32 dir;
    struct S2 *objFlags = (struct S2 *)obj;

    if (0x10 & *(u16 *)((u8 *)parentObj + 2)) {
        objFlags->f2 |= 0x10;
        dir = 1;
    } else {
        *(u16 *)((u8 *)obj + 2) = 0xFFEF & *(u16 *)((u8 *)obj + 2);
        dir = -1;
    }

    if (!(*(u16 *)parentState & 1)) {
        *(s32 *)((u8 *)state + 8) = *(s32 *)((u8 *)parentState + 8) - (dir * 0x190000);
        *(s32 *)((u8 *)state + 0x0C) = *(s32 *)((u8 *)parentState + 0x0C) + 0xC0000;
    }
    {
        void *parent2;
        void *parentObj2;
        *(u16 *)((u8 *)obj + 2) = 0xFBFF & *(u16 *)((u8 *)obj + 2);
        parent2 = *(void **)((u8 *)arg0 + 0x28);
        parentObj2 = *(void **)((u8 *)parent2 + 0x38);
        *(u16 *)((u8 *)obj + 2) = (0x400 & *(u16 *)((u8 *)parentObj2 + 2)) | *(u16 *)((u8 *)obj + 2);
    }
    {
        void *stateSub = *(void **)((u8 *)state + 0x28);
        void *parentSub = *(void **)((u8 *)parentState + 0x28);
        *(u8 *)((u8 *)stateSub + 1) = *(u8 *)((u8 *)parentSub + 1);
    }
    {
        u8 *pt = gCameraState;
        u8 *pb = gMainWorkspace;
        u8 *base1;
        u8 *base2;
        u32 idx;
        pb += 0x18A8;
        idx = ((u32)*pb + 1) * 0x40;
        base1 = pt + 0x1278;
        *(u32 *)((u8 *)obj + 0x14) = *(u32 *)((u8 *)state + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
        idx = ((u32)*pb + 1) * 0x40;
        base2 = pt + 0x127C;
        *(u32 *)((u8 *)obj + 0x18) = *(u32 *)((u8 *)state + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
