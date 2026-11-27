void sub_08013C5C(void *, void *);
s32 sub_080141AC(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Runs the hit/damage responses for a weapon entity's owner and hitbox
 * sub-object: updates their collision state, spawns a contact effect, advances
 * the slot-driven state machine, dispatches the selected callback, and mirrors
 * the owner's camera-corrected position back through the coordinate table. */
void sub_0803CBEC(void *self) {
    void *parent;
    void *obj;
    s32 callback;
    parent = *(void **)((u8 *)self + 0x38);
    obj = *(void **)((u8 *)self + 0x3C);
    sub_08013C5C(self, parent);
    if (sub_080141AC(parent, obj) == 1) {
        callback = *(s32 *)((u8 *)self + 0x24);
        sub_080C31E0((s32)self, callback);
    } else {
        if (sub_08013558(parent, obj, *(void **)((u8 *)obj + 0x28)) != 0)
            sub_08013978(self, *(void **)((u8 *)obj + 0x28));
        sub_080142C0(self, *(void **)((u8 *)obj + 0x28));
        if (*(u16 *)obj & 1) {
            u32 *argTable;
            u8 *slots;
            u8 slotByte;
            u32 callbackTable;
            s32 slotOff;
            sub_08013AC4(self);
            {
                u8 *slot;
                slot = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
                *(u8 *)(slot + 0x19) = 0;
            }
            argTable = (u32 *)0x08671BB0;
            slots = (u8 *)self + 0x18;
            sub_080C31E4(slots, (u8 *)self + 0x22, *argTable);
            {
                u8 *slot;
                slot = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
                *(u8 *)(slot + 0x19) = *(u8 *)(slot + 0x19) + 1;
            }
            slotOff = (s32)(s16)(*(s16 *)((u8 *)self + 0x22)) * 2;
            slots += slotOff;
            slotByte = *slots;
            callbackTable = *(u32 *)((u8 *)self + 0x14);
            callback = *(s32 *)((u32)(slotByte * 4) + callbackTable);
            sub_080C31E0((s32)self, callback);
        } else {
            if (updateObjectDisplayState(parent, obj) == 0) {
                u8 *slots;
                u8 slotByte;
                u32 callbackTable;
                s32 slotOff;
                *(u32 *)((u8 *)self + 0x14) = 0x0866DFC4;
                *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
                {
                    u8 *slot;
                    slot = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
                    *(u8 *)(slot + 0x19) = *(u8 *)(slot + 0x19) + 1;
                }
                slotOff = (s32)(s16)(*(s16 *)((u8 *)self + 0x22)) * 2;
                slots = (u8 *)self;
                slots += 0x18;
                slots += slotOff;
                slotByte = *slots;
                callbackTable = *(u32 *)((u8 *)self + 0x14);
                sub_080C31E0((s32)self, *(s32 *)((u32)(slotByte * 4) + callbackTable));
                *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
            }
            sub_08013C8C(self, parent);
        }
    }
}
