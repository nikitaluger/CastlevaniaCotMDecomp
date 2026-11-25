s32 sub_0800168C(void *, s32, s32, s32);
void *sub_0800355C(void);
void sub_0806D2D0(void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);

struct GameState {
    u8 _0x000[0x18C2];
    u16 w;
};
extern struct GameState D_02025FF0;

extern u32 D_08671BB0[];

/* Spawns a projectile effect: reserves a sprite slot, allocates and initializes
 * the effect object, then fires the end callback and advances the animation. */
void sub_08075770(void *entity)
{
    u8 *self = (u8 *)entity;
    void *effect;

    if (sub_0800168C(entity, 0, 0x68, 3) == 0)
    {
        sub_080C31E0(entity, *(s32 *)(self + 0x24));
        return;
    }

    effect = sub_0800355C();
    if (effect == 0)
    {
        sub_0806D2D0(entity);
        return;
    }

    *(void **)(self + 0x38) = effect;
    *(u32 *)((u8 *)effect + 0x1C) = 0x80000005;
    {
        u16 w = D_02025FF0.w;
        u32 z = 0;
        *(u16 *)effect = w;

        {
            s32 idx = *(s16 *)(self + 0x22);
            *(u8 *)(self + idx * 2 + 0x19) = z;
        }
    }

    {
        const u32 *callback = (const u32 *)0x08671BB0;
        void *frameByte = self + 0x18;
        sub_080C31E4(frameByte, self + 0x22, *callback);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        frameByte = (u8 *)frameByte + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)frameByte * 4));
    }
}
