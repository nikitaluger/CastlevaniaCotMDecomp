extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *a);
extern s16 scalePercentSaturate16(u16, u16);
extern void sub_08003A6C(void *a, s32 b, s32 c);
extern s32 sub_080C36E4(s32, s32);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern void sub_0808449C(void);

struct S_02025FF0 { u8 _0[0x1510]; u8 b1510; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gGameStatus[];
extern u8 D_080E5BFC[];
extern u8 D_080E5BC8[];

struct Child81 {
    u8 f0, f1, f2, f3;
    u16 f4, f6, f8, fA, fC, fE;
    u32 f10;
    u8 _14[2];
    u16 f16, f18;
    u8 _1A[0x0A];
    u32 f24;
};
struct Parent7 {
    u8 _0[0x18];
    u32 f18;
    u8 _1C[0x10];
    struct Child81 *f2C;
    u32 f30, f34, f38, f3C;
    u8 _40[0x14];
    u32 f54;
};

/* Spawn a child object for this actor: allocate it, fill its sprite/animation
 * and parameter fields from the slot's config table, install a new actor update
 * callback, then advance the script and dispatch its current step. Bails out
 * to sub_0806D2D0 when the child cannot be allocated. */
void sub_08081718(u8 *actor) {
    u8 *groupBase = *(u8 **)(actor + 0x6C);
    struct Parent7 *group = (struct Parent7 *)(groupBase + 4);
    u8 *sprite = *(u8 **)(actor + 0x38);
    u8 *params = gGameStatus;
    struct Child81 *spawn;
    u32 *slotPtr;
    u32 *stepCallbacks;
    u32 idx;
    u8 *table;
    u8 *animTable;

    spawn = (struct Child81 *)allocEffectPart();
    group->f2C = spawn;
    if (spawn == NULL) {
        sub_0806D2D0(actor);
        return;
    }
    group->f30 = 0;
    group->f34 = 0;
    group->f38 = 0;
    group->f3C = 0;

    slotPtr = (u32 *)(actor + 0x9C);
    idx = (*slotPtr & 3) * 0x18;
    table = D_080E5BFC + idx;

    group->f2C->f1 = gMainWorkspace.b1510 & 1;
    group->f2C->f2 = 2;
    group->f2C->f3 = 8;
    group->f2C->f4 = params[0xC1 << 2];
    group->f2C->f6 = *(u16 *)(table + 8);
    group->f2C->f8 = *(u16 *)(table + 0xA);
    group->f2C->fA = 0;
    group->f2C->fC = 0;
    group->f2C->fE = scalePercentSaturate16(*(u16 *)(params + 0x2E2), *(u16 *)(table + 0xC));
    group->f2C->f16 = 5;
    group->f2C->f18 = *(u16 *)(table + 0x14);
    group->f2C->f10 = (u32)sprite;

    group->f18 = *(u32 *)(actor + 0x24);
    *(u32 *)(actor + 0x24) = (u32)sub_0808449C;
    *(u32 *)(sprite + 0x24) = 0x084F240C;

    sub_08003A6C(groupBase + 0x20, 0, *(u32 *)(table + 0x10));

    animTable = D_080E5BC8;
    *(u32 *)(sprite + 0x14) = *(u32 *)(animTable + (sub_080C36E4(*slotPtr, 0x0D) << 2));
    *(u32 *)(sprite + 0x18) = 0xB00000;

    group->f54 = *(u32 *)(table + 4);
    *(u32 *)((u8 *)group + 0x0C) = *(u32 *)(table + 0);

    *((u8 *)((s16)*(s16 *)(actor + 0x22) * 2 + (u32)actor) + 0x19) = 0;

    stepCallbacks = (u32 *)0x08671BB0;
    {
        u8 *scriptState = actor + 0x18;
        sub_080C31E4(scriptState, actor + 0x22, *stepCallbacks);
        {
            u8 *stepSlot = (u8 *)((s16)*(s16 *)(actor + 0x22) * 2 + (u32)actor);
            *(u8 *)(stepSlot + 0x19) = (u8)(*(u8 *)(stepSlot + 0x19) + 1);
        }
        {
            u8 *stepParam = scriptState + (s16)*(s16 *)(actor + 0x22) * 2;
            sub_080C31E0(actor, *(u32 *)((u32)(*stepParam) * 4 + *(u32 *)(actor + 0x14)));
        }
    }
}
