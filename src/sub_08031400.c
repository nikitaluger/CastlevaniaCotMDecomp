extern void sub_08005E80(s32);
extern s32 stepAnimationTrack(s32, void *);
extern void moveEntityWithCollision(void *, s32);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_08013AC4(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void sub_08013C5C(void *, s32);
extern void sub_08013C8C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern void sub_080142C0(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

struct R8 { u8 _0[8]; s16 f8; };

/* One update tick of a weapon entity: run the hit/damage responses, issue the
 * attack-end callback, dispatch the current state handler from the D_0866DC7C table,
 * mirror the entity's animation state into its sub-object, then finish with cleanup. */
void sub_08031400(u8 *self) {
    s32 parent = *(s32 *)(self + 0x38);
    u8 *obj = *(u8 **)(self + 0x3C);
    u8 *objSub = obj + 0x34;
    u8 *objState = obj + 0x48;
    u16 endFlag;

    if (sub_080141AC(parent, obj) == 1 &&
        (*(u16 *)(obj + 2) & 0x104) != 0 &&
        *(u8 *)((u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self) + 0x1A) == 0) {
        return;
    }
    sub_08013C5C(self, parent);
    if (sub_08013558(parent, obj, *(void **)(obj + 0x28)) != 0) {
        sub_08013978(self, *(void **)(obj + 0x28));
    }
    sub_080142C0(self, *(void **)(obj + 0x28));
    if (*(u16 *)obj & 1) {
        u8 *slot0 = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(slot0 + 0x1A) != 3) {
            u8 *slot;
            s32 *callbackTable;
            sub_08013AC4(self);
            sub_08005E80(0x88);
            slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(slot + 0x1B) = 0;
            callbackTable = (s32 *)0x08671BDC;
            sub_080C31E8(self + 0x18, self + 0x22, 3, *callbackTable);
        }
    }
    if (updateObjectDisplayState(parent, obj) != 0) goto skipExtra;
    {
        u8 *slot;
        s32 stateIdx;
        u8 *slotArea;
        u8 stateByte;
        void **handlers;
        void *handler;
        *(void **)(self + 0x14) = (void *)0x0866DC7C;
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
        slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        *(u8 *)(slot + 0x19) = (u8)(*(u8 *)(slot + 0x19) + 1);
        stateIdx = (*(s16 *)(self + 0x22)) * 2;
        slotArea = self + 0x18;
        stateByte = *(slotArea + stateIdx);
        handlers = *(void **)(self + 0x14);
        handler = handlers[stateByte];
        sub_080C31E0(self, handler);
        *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
        endFlag = *(u16 *)(self + 2) & 0x8000;
        if (endFlag != 0) return;
        stepAnimationTrack(parent, objSub);
        if (((struct R8 *)objState)->f8 == 1) {
            moveEntityWithCollision(obj, 0x16C1);
            if (*(u16 *)(obj + 2) & 4) {
                ((struct R8 *)objState)->f8 = 0;
            }
        }
    }
skipExtra:
    if (*(u16 *)(obj + 2) & 0x100) {
        *(u16 *)(obj + 4) = (u16)(*(u16 *)(obj + 4) | 0x100);
    } else {
        *(u16 *)(obj + 4) = (u16)(*(u16 *)(obj + 4) & 0xFEFF);
    }
    *(u16 *)(*(void * volatile *)objState + 4) = *(u16 *)(obj + 0x0A);
    *(s16 *)(*(void * volatile *)objState + 6) = (s16)(*(u16 *)(obj + 0x0E) + 1);
    sub_08013C8C(self, parent);
}
