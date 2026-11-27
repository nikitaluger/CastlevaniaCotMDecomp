extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern void sub_08005E80(s32);
extern s32 updateObjectDisplayState(s32, void *);
extern void stepAnimationTrack(s32, void *);
extern void advanceMotion(void *, s32);
extern void sub_08013C8C(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *gScriptEventCallbacks;
struct R8 { u16 f0; u16 f2; u8 _4[6]; s16 oneShot; };
struct S_02025FF0 { u8 _0[0x18BC]; u16 counter; };
extern struct S_02025FF0 gMainWorkspace;

/* One update tick of a weapon entity: run the hit/damage responses, issue the
 * attack-end callback, dispatch the current state handler from the D_0866E888
 * table, mirror the entity's animation state, then finish with cleanup. */
void sub_0805A3D4(u8 *arg0) {
    s32 parent = *(s32 *)(arg0 + 0x38);
    u8 *obj = *(u8 **)(arg0 + 0x3C);
    u8 *objSub = obj + 0x34;
    u8 *objState = obj + 0x48;

    if (checkActorViewBounds(parent, obj) == 1) {
        return;
    }
    applySpritePaletteVariant(arg0, parent);
    if (sub_08013558(parent, obj, *(void **)(obj + 0x28)) != 0) {
        spawnContactEffectOnHit(arg0, *(void **)(obj + 0x28));
    }
    uploadPendingSpriteGraphic(arg0, *(void **)(obj + 0x28));
    if (*(u16 *)obj & 1) {
        u8 *slot0 = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        if (*(u8 *)(slot0 + 0x1A) != 3) {
            u8 *slot;
            s32 *callbackTable;
            updateActorWorldPosition(arg0);
            sub_08005E80(0x85);
            slot = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(slot + 0x1B) = 0;
            callbackTable = (s32 *)0x08671BDC;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, *callbackTable);
        }
    }
    if (updateObjectDisplayState(parent, obj) == 0) {
        u8 *slot;
        s32 stateIdx;
        u8 *slotArea;
        u8 stateByte;
        void **handlers;
        void *handler;
        *(void **)(arg0 + 0x14) = (void *)0x0866E888;
        *(u16 *)(arg0 + 0x22) = (u16)(*(u16 *)(arg0 + 0x22) + 1);
        slot = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(slot + 0x19) = (u8)(*(u8 *)(slot + 0x19) + 1);
        stateIdx = (*(s16 *)(arg0 + 0x22)) * 2;
        slotArea = arg0 + 0x18;
        stateByte = *(slotArea + stateIdx);
        handlers = *(void **)(arg0 + 0x14);
        handler = handlers[stateByte];
        sub_080C31E0(arg0, handler);
        *(u16 *)(arg0 + 0x22) = (u16)(*(u16 *)(arg0 + 0x22) - 1);
        if ((*(u16 *)(arg0 + 2) & 0x8000) == 0) {
            stepAnimationTrack(parent, objSub);
            advanceMotion(obj, 0);
        } else {
            goto done;
        }
    } else {
        if (((struct R8 *)objState)->oneShot == 1) {
            ((struct R8 *)objState)->oneShot = 0;
            gMainWorkspace.counter -= 1;
        }
    }
    sub_08013C8C(arg0, parent);
done: ;
}
