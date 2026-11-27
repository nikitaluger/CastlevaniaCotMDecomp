extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 sub_08014F14(s32, void *, void *, void *);
extern void spawnChildPair(void *, void *, void *, void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern void sub_08005E80(s32);
extern s32 sub_0801576C(s32, void *, void *, void *, void *, void *);
extern void stepAnimationTrack(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_0803BB10(void *, s32);
extern void sub_08013C8C(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 sScriptStepCallbacks[];
extern u8 D_0866DF6C[];

/* One update tick of a two-sub-object weapon entity: clear/prime the sub-objects' hit
 * state, apply the hit responses, issue the attack-end callback, dispatch the current
 * state handler from the D_0866DF6C table, then update and clean up. */
void sub_0803B618(u8 *self)
{
    s32 parent = *(s32 *)(self + 0x38);
    u8 *obj = *(u8 **)(self + 0x3C);
    u8 *objSub = obj + 0x34;
    u8 *objState = obj + 0x48;
    u8 *effectState;
    u8 *objTail;
    s32 hitResult;
    u32 zero;
    u8 *hit0;

    hit0 = *(u8 **)(objState + 8);
    zero = 0;
    *(u8 *)(hit0 + 1) = zero;
    if (checkActorViewBounds(parent, obj) == 1) {
        *(u8 *)(*(u8 **)(objState + 0x0C) + 1) = zero;
    } else {
        *(u8 *)(*(u8 **)(objState + 0x0C) + 1) = 5;
    }
    applySpritePaletteVariant(self, parent);
    hitResult = sub_08014F14(parent, obj, *(void **)(obj + 0x28), *(void **)(objState + 0x0C));
    objTail = obj + 0x2C;
    effectState = objState + 0x10;
    if (hitResult != 0) {
        spawnChildPair(self, *(void **)(obj + 0x28), *(void **)(objState + 0x0C), objTail, effectState);
    }
    uploadPendingSpriteGraphic(self, *(void **)(obj + 0x28));
    uploadPendingSpriteGraphic(self, *(void **)(objState + 0x0C));
    uploadPendingSpriteGraphic(self, *(void **)(objState + 8));
    if (*(u16 *)obj & 1) {
        u8 *slot0 = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(slot0 + 0x1A) != 2) {
            u8 *slot;
            u32 *callbackTable;
            updateActorWorldPosition(self);
            sub_08005E80(0x85);
            slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(slot + 0x1B) = 0;
            callbackTable = (u32 *)0x08671BDC;
            sub_080C31E8(self + 0x18, self + 0x22, 2, *callbackTable);
        }
    }
    if (sub_0801576C(parent, obj, *(void **)(obj + 0x28), *(void **)(objState + 0x0C), objTail, effectState) == 0) {
        u8 *slot;
        s32 stateIdx;
        u8 *slotArea;
        u8 stateByte;
        u32 *handlers;
        u32 handler;
        *(u32 *)(self + 0x14) = (u32)D_0866DF6C;
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
        slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        *(u8 *)(slot + 0x19) = (u8)(*(u8 *)(slot + 0x19) + 1);
        stateIdx = (*(s16 *)(self + 0x22)) * 2;
        slotArea = self + 0x18;
        stateByte = *(slotArea + stateIdx);
        handlers = (u32 *)*(u32 *)(self + 0x14);
        handler = handlers[stateByte];
        sub_080C31E0(self, (void *)handler);
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
        if (*(u16 *)(self + 2) & 0x8000) goto end;
        stepAnimationTrack(parent, objSub);
        sub_08011EE8(obj, 0x16C1, 0);
    }
    if ((*(u16 *)obj & 0x0D) == 0) {
        *(u8 *)(*(u8 **)(objState + 8) + 1) = 1;
    }
    sub_0803BB10(self, parent);
    sub_08013C8C(self, parent);
end:
    ;
}
