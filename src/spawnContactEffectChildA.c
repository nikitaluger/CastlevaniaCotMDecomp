void *allocMotionTracker(void);

struct Sub_08013F28 {
    u16 flags;
    u8 _pad[0x16];
    void *linkedObject;
    u8 _pad2[2];
    u16 timer;
    u8 _pad3[0xC];
    void * volatile effect;
};

/* Allocate a 0x14-byte effect object from the pool and initialize it with the
 * four parameters plus a back-pointer to parent; record it on the parent with
 * a 0x12C countdown, or clear the parent's flags and fail if the pool is full. */
s32 spawnContactEffectChildA(void *parent, u16 param1, u16 param2, u16 param3, u16 param4)
{
    struct Sub_08013F28 *r4 = *(struct Sub_08013F28 **)((u8 *)parent + 0x3C);
    if (r4->effect == NULL) {
        void *p = allocMotionTracker();
        r4->effect = p;
        if (p == NULL) {
            r4->flags = (r4->flags & 0xFFFB) | 1;
            r4->linkedObject = NULL;
            return 0;
        }
    }
    {
        u8 *effectBytes = (u8 *)r4->effect;
        u16 zero = 0;
        effectBytes[1] = 1;
        *(u16 *)((u8 *)r4->effect + 2) = zero;
    }
    *(u16 *)((u8 *)r4->effect + 4) = param1;
    *(u16 *)((u8 *)r4->effect + 6) = param2;
    *(u16 *)((u8 *)r4->effect + 8) = param3;
    *(u16 *)((u8 *)r4->effect + 0xA) = param4;
    *(void **)((u8 *)r4->effect + 0xC) = parent;
    r4->timer = 0x12C;
    return 1;
}
