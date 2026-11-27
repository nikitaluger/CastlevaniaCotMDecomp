s32 allocWorkSlot(void *, s32, s32, s32);
void *allocSpriteObject(void);
void cleanupFailedEffectSpawn(void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, u32);

extern u8 gMainWorkspace[];
extern u32 gMainObjTimerCallbacks;

/* Acquire a sprite slot for the script, falling back to its current object;
 * allocate and link a new object, copy flags and a template value into it,
 * then run the script callback and select the resulting object. */
void sub_08076B6C(void *script)
{
    void *obj;
    s16 idx;
    u32 zero;
    u8 *base;
    u32 *pd;

    if (allocWorkSlot(script, 0, 0x68, 3) == 0) {
        sub_080C31E0(script, *(void **)((u8 *)script + 0x24));
        return;
    }

    obj = allocSpriteObject();
    if (obj == 0) {
        cleanupFailedEffectSpawn(script);
        return;
    }

    *(void **)((u8 *)script + 0x38) = obj;
    *(u32 *)((u8 *)obj + 0x1C) = 0x80000004;

    {
        u32 flags;
        flags = (u16)(*(u16 *)((u8 *)*(void **)((u8 *)*(void **)((u8 *)script + 0x28) + 0x38) + 2) & 0x10U) | *(u16 *)((u8 *)obj + 2);
        zero = 0;
        *(u16 *)((u8 *)obj + 2) = (u16)flags;
    }

    {
        u32 addr = (u32)gMainWorkspace;
        addr += 0x18C2;
        *(u16 *)((u8 *)obj + 0) = *(u16 *)addr;
    }

    *(u8 *)((u8 *)obj + 0x2A) &= 0xBF;

    idx = *(s16 *)((u8 *)script + 0x22);
    *(u8 *)((u8 *)script + idx * 2 + 0x19) = (u8)zero;

    pd = &gMainObjTimerCallbacks;
    base = (u8 *)script + 0x18;
    sub_080C31E4(base, (u8 *)script + 0x22, *pd);

    idx = *(s16 *)((u8 *)script + 0x22);
    (*(u8 *)((u8 *)script + idx * 2 + 0x19))++;

    idx = *(s16 *)((u8 *)script + 0x22);
    base = base + idx * 2;
    {
        u32 b = *base;
        void **table = *(void ***)((u8 *)script + 0x14);
        sub_080C31E0(script, table[b]);
    }
}
