s32 sub_08016238(void *);
void sub_08005E80(s32);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct F0 { u16 f0; };

/* Runs a weapon entity's hit/state update: reports contact with the target
 * object, then advances either the hit-reaction slot dispatch or the normal
 * state-machine dispatch and mirrors the owner's camera-corrected position. */
void sub_080A4134(void *arg0) {
    u8 *parent = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *obj = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *self = (u8 *)arg0;

    if (sub_08016238(*(void **)(obj + 0x28)) != 0) {
        sub_08005E80(0x189);
        ((struct F0 *)obj)->f0 |= 1;
    }

    if (*(u16 *)(*(u8 **)(obj + 0x28) + 0x14) & 1) {
        sub_08005E80(0x189);
        ((struct F0 *)obj)->f0 |= 1;
    }

    if (*(u16 *)obj & 1) {
        s32 slotOff;
        u8 *slots;
        s32 *argTable;
        u8 slotByte;
        *(u8 *)(*(u8 **)(obj + 0x28) + 1) = 0;
        slotOff = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)slotOff + (u32)self + 0x19) = 0;
        argTable = (s32 *)0x08671BB0;
        slots = self;
        slots += 0x18;
        sub_080C31E4(slots, self + 0x22, *argTable);
        slotOff = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)slotOff + (u32)self + 0x19) = *(u8 *)((u32)slotOff + (u32)self + 0x19) + 1;
        slotOff = *(s16 *)(self + 0x22) * 2;
        slots += slotOff;
        slotByte = *(u8 *)slots;
        sub_080C31E0(self, *(void **)(slotByte * 4 + *(u32 *)(self + 0x14)));
        return;
    }

    if (sub_08013B5C(parent, obj) == 0) {
        s32 slotOff;
        u8 *slots;
        u8 slotByte;
        *(u32 *)(self + 0x14) = 0x0866FEF4;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        slotOff = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)slotOff + (u32)self + 0x19) = *(u8 *)((u32)slotOff + (u32)self + 0x19) + 1;
        slotOff = *(s16 *)(self + 0x22) * 2;
        slots = self;
        slots += 0x18;
        slots += slotOff;
        slotByte = *(u8 *)slots;
        sub_080C31E0(self, *(void **)(slotByte * 4 + *(u32 *)(self + 0x14)));
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    }
    sub_08013C8C(self, parent);
}
