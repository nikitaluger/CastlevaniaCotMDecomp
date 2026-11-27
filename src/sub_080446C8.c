void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

extern u32 gScriptStepCallbackTable;
extern u32 D_0866E238;

/* Runs the hit/damage responses for a weapon entity's owner and hitbox
 * sub-object: updates their collision state, spawns a contact effect, advances
 * the slot-driven state machine, dispatches the selected callback, and mirrors
 * the owner's camera-corrected position back through the coordinate table. */
void sub_080446C8(void *entity) {
    void *parent;
    void *obj;
    u8 *self = (u8 *)entity;

    parent = *(void **)(self + 0x38);
    obj = *(void **)(self + 0x3C);
    applySpritePaletteVariant(entity, parent);
    if (checkActorViewBounds(parent, obj) == 1) {
        sub_080C31E0((s32)entity, *(s32 *)(self + 0x24));
        return;
    }

    if (sub_08013558(parent, obj, *(void **)((u8 *)obj + 0x28)) != 0)
        spawnContactEffectOnHit(entity, *(void **)((u8 *)obj + 0x28));
    uploadPendingSpriteGraphic(entity, *(void **)((u8 *)obj + 0x28));

    if (*(u16 *)obj & 1) {
        u32 *argTable;
        u8 *slots;
        u8 slotByte;
        s32 slotOff;
        updateActorWorldPosition(entity);
        {
            u8 *slot;
            slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(slot + 0x19) = 0;
        }
        argTable = &gScriptStepCallbackTable;
        slots = self + 0x18;
        sub_080C31E4(slots, self + 0x22, *argTable);
        {
            u8 *slot;
            slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(slot + 0x19) = *(u8 *)(slot + 0x19) + 1;
        }
        slotOff = (s32)(s16)(*(s16 *)(self + 0x22)) * 2;
        slots += slotOff;
        slotByte = *slots;
        sub_080C31E0((s32)entity, *(s32 *)((u32)(slotByte * 4) + *(u32 *)(self + 0x14)));
        return;
    }

    if (updateObjectDisplayState(parent, obj) == 0) {
        u8 *slots;
        u8 slotByte;
        s32 slotOff;
        *(u32 *)(self + 0x14) = (u32)&D_0866E238;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        {
            u8 *slot;
            slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(slot + 0x19) = *(u8 *)(slot + 0x19) + 1;
        }
        slotOff = (s32)(s16)(*(s16 *)(self + 0x22)) * 2;
        slots = self;
        slots += 0x18;
        slots += slotOff;
        slotByte = *slots;
        sub_080C31E0((s32)entity, *(s32 *)((u32)(slotByte * 4) + *(u32 *)(self + 0x14)));
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    }
    sub_08013C8C(entity, parent);
}
