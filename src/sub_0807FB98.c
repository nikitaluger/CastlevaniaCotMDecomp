s32 allocWorkSlot(void *, s32, s32, s32);
void *allocSpriteObject(void);
void cleanupFailedEffectSpawn(void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);

struct S_02025FF0 {
    u8 _0x000[0x18C2];
    u16 w;
};
extern struct S_02025FF0 gMainWorkspace;

extern u32 gMainObjTimerCallbacks[];

void sub_0807FB98(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *tmp;

    if (allocWorkSlot(arg0, 0, 0x68, 3) == 0)
    {
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
        return;
    }

    tmp = allocSpriteObject();
    if (tmp == 0)
    {
        cleanupFailedEffectSpawn(arg0);
        return;
    }

    *(void **)(self + 0x38) = tmp;
    *(u32 *)((u8 *)tmp + 0x1C) = 0x80000006;
    {
        u16 w = gMainWorkspace.w;
        u32 z = 0;
        *(u16 *)tmp = w;

        {
            s32 idx = *(s16 *)(self + 0x22);
            *(u8 *)(self + idx * 2 + 0x19) = z;
        }
    }

    {
        const u32 *lit = (const u32 *)0x08671BB0;
        void *r4 = self + 0x18;
        sub_080C31E4(r4, self + 0x22, *lit);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        r4 = (u8 *)r4 + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)r4 * 4));
    }
}
