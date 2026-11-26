void *allocEffectPart(void *);
void sub_0806D2D0(void *);
u16 sub_0806D62C(u16, s32);
void sub_08003A6C(void *, s32, const void *);
void sub_0808449C(void);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);

extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 D_0849DB88[];
extern u8 D_0849DBE8[];
extern u8 D_084A0780[];
extern u8 D_084A0838[];
extern u8 D_084A1A78[];
extern u8 D_084A1AF8[];
extern u32 gMainObjTimerCallback[];

/* The parent's action state holds the new effect at +0x2C. It is read back
 * through a volatile slot on every field store, just as the original does. */
#define EFFECT ( *(u8 * volatile *)((u8 *)actionData + 0x2C) )

/* Spawn an animated effect from the free effect pool and attach it to the
 * parent's action state; configure one of three graphic variants according to
 * the action's effect kind, then advance the parent's animation step. */
void spawnActionEffect(void *parent)
{
    u8 *action = *(u8 **)((u8 *)parent + 0x6C);
    u8 *actionData = action + 4;
    u8 *child = *(u8 **)((u8 *)parent + 0x38);
    u8 *stats = gGameStatus;
    u8 *effect;

    effect = (u8 *)allocEffectPart(action);
    *(u8 **)(actionData + 0x2C) = effect;
    if (effect == 0)
    {
        sub_0806D2D0(parent);
        return;
    }

    /* Clear the four spare effect slots. */
    *(u32 *)(actionData + 0x30) = 0;
    *(u32 *)(actionData + 0x34) = 0;
    *(u32 *)(actionData + 0x38) = 0;
    *(u32 *)(actionData + 0x3C) = 0;

    /* Swap in the effect's cleanup callback. */
    *(u32 *)(actionData + 0x18) = *(u32 *)((u8 *)parent + 0x24);
    *(u32 *)((u8 *)parent + 0x24) = (u32)sub_0808449C;

    effect[1] = gMainWorkspace[0x1510] & 1;
    EFFECT[2] = 2;
    EFFECT[3] = 8;
    *(u16 *)(EFFECT + 4) = stats[0x304];
    *(u16 *)(EFFECT + 6) = 1;
    *(u16 *)(EFFECT + 8) = 1;
    *(u16 *)(EFFECT + 0x0A) = 0;
    *(u16 *)(EFFECT + 0x0C) = 0;
    *(u16 *)(EFFECT + 0x16) = 0x1E;
    *(u32 *)(EFFECT + 0x10) = (u32)child;

    {
        u8 kind = gMainWorkspace[0x14F0];
        action[0x55] = kind;
    }
    *(u32 *)(actionData + 0x14) = 1;

    switch (action[0x55])
    {
    case ACTION_EFFECT_KIND_SMALL:
        *(u16 *)(EFFECT + 0x0E) = sub_0806D62C(*(u16 *)(stats + 0x2E2), ACTION_EFFECT_SCALE_SMALL);
        *(u16 *)(EFFECT + 0x18) = ACTION_EFFECT_ANIM_SMALL;
        {
            u16 v = 0x400;
            *(u16 *)(child + 4) = v;
        }
        *(u16 *)(child + 6) = 0x40;
        *(u16 *)(child + 8) = 0;
        *(u32 *)(child + 0x24) = (u32)D_0849DB88;
        sub_08003A6C(action + 0x20, 0, D_0849DBE8);
        *(u32 *)(child + 0x1C) = ACTION_EFFECT_GFX_STANDARD;
        break;
    case ACTION_EFFECT_KIND_MEDIUM:
        *(u16 *)(EFFECT + 0x0E) = sub_0806D62C(*(u16 *)(stats + 0x2E2), ACTION_EFFECT_SCALE_MEDIUM);
        *(u16 *)(EFFECT + 0x18) = ACTION_EFFECT_ANIM_MEDIUM;
        *(u16 *)(child + 4) = 0x40;
        {
            u16 v = 0x1C0;
            *(u16 *)(child + 6) = v;
        }
        *(u16 *)(child + 8) = 0;
        *(u32 *)(child + 0x24) = (u32)D_084A0780;
        sub_08003A6C(action + 0x20, 0, D_084A0838);
        *(u32 *)(child + 0x1C) = ACTION_EFFECT_GFX_STANDARD;
        *(u32 *)(actionData + 0x54) = 0;
        break;
    case ACTION_EFFECT_KIND_LARGE:
        *(u16 *)(EFFECT + 0x0E) = sub_0806D62C(*(u16 *)(stats + 0x2E2), ACTION_EFFECT_SCALE_LARGE);
        *(u16 *)(EFFECT + 0x18) = ACTION_EFFECT_ANIM_LARGE;
        {
            u16 v = 0x400;
            *(u16 *)(child + 4) = v;
            *(u16 *)(child + 6) = v;
        }
        *(u16 *)(child + 8) = 0;
        *(u32 *)(child + 0x24) = (u32)D_084A1A78;
        sub_08003A6C(action + 0x20, 0, D_084A1AF8);
        *(u32 *)(child + 0x1C) = ACTION_EFFECT_GFX_LARGE;
        break;
    }

    /* Advance the parent's animation step by one and dispatch its handler. */
    {
        s16 idx;
        u8 *self = (u8 *)parent;
        u8 *stepPtr;
        u32 *scriptTable;

        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) = 0;

        scriptTable = gMainObjTimerCallback;
        stepPtr = self + 0x18;
        sub_080C31E4(stepPtr, self + 0x22, (void *)*scriptTable);

        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) += 1;

        idx = *(s16 *)(self + 0x22);
        stepPtr += idx * 2;
        {
            u8 step = *stepPtr;
            void **table = *(void ***)(self + 0x14);
            sub_080C31E0(parent, table[step]);
        }
    }
}
