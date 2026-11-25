extern void *sub_08016190(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_08003A6C(void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0808449C(void);
extern u8 D_02025368[];

/* One child record reserved from the shared 0x34-byte spawn-slot pool. */
struct ChildSpawnRec {
    u8 unused0, active, kind, variant;
    u16 param4, param6, param8, paramA, paramC, paramE;
    u32 sprite;
    u8 pad14[2];
    u16 param16, param18;
};

/* Per-entity spawn state, held at entity->group + 4. */
struct EntitySpawnState {
    u8 pad0[4];
    u32 field04;
    u8 pad08[0x10];
    u32 cleanupHandler;
    u8 pad1C[0x10];
    struct ChildSpawnRec *spawn;
    u32 slot0, slot1, slot2, slot3;
};

/* Allocates a child spawn slot for an entity, fills its parameters from the
 * shared child-parameter table, installs the cleanup handler and sprite
 * graphics, then advances the entity's control slot to its next script step. */
void sub_0807A5F0(u8 *entity) {
    u8 *groupBase = *(u8 **)(entity + 0x6C);
    struct EntitySpawnState *state = (struct EntitySpawnState *)(groupBase + 4);
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *params = D_02025368;
    void *child;
    u32 zero;
    u8 *ctrlBase;
    s32 *callbackSlot;
    s32 i;

    child = sub_08016190();
    state->spawn = child;
    if (child == NULL) {
        sub_0806D2D0(entity);
        return;
    }
    zero = 0;
    state->slot0 = zero;
    state->slot1 = zero;
    state->slot2 = zero;
    state->slot3 = zero;
    *(u8 *)((u8 *)child + 1) = zero;
    state->spawn->kind = 2;
    state->spawn->variant = 8;
    state->spawn->param4 = *(u8 *)(params + (0xC1 << 2));
    state->spawn->param6 = 5;
    state->spawn->param8 = 0x5A;
    state->spawn->paramA = zero;
    state->spawn->paramC = zero;
    state->spawn->paramE = sub_0806D62C(*(u16 *)(params + 0x2E2), 0x64);
    state->spawn->param16 = 0x3C;
    state->spawn->param18 = 0x57;
    state->spawn->sprite = (u32)sprite;
    state->cleanupHandler = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)&sub_0808449C;
    *(u32 *)(sprite + 0x24) = 0x084D9E58;
    sub_08003A6C(groupBase + 0x20, 0, 0x084D9E80);
    *(u32 *)(groupBase + 4) = *(u32 *)(entity + 0x7C);
    *(u32 *)((u8 *)state + 4) = *(u32 *)(entity + 0x8C);
    *(u32 *)((u8 *)state + 0x10) = *(u32 *)(entity + 0x9C);
    *((u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity) + 0x19) = zero;
    callbackSlot = (s32 *)0x08671BB0;
    ctrlBase = entity + 0x18;
    sub_080C31E4(ctrlBase, entity + 0x22, *callbackSlot);
    {
        i = *(s16 *)(entity + 0x22);
        i *= 2;
        {
            u8 *p = (u8 *)((u32)i + (u32)entity);
            *(u8 *)(p + 0x19) = (u8)(*(u8 *)(p + 0x19) + 1);
        }
    }
    {
        u8 *p = ctrlBase + (s16)*(s16 *)(entity + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)((u32)(*p) * 4 + *(u32 *)(entity + 0x14)));
    }
}
