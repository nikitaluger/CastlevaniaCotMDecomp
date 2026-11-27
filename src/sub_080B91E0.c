s32 sub_080141AC(void *, void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Behaviour-script callback: on a contact request hand control back to the
 * owner; when the owner is active, fire an effect at the acting child and
 * dispatch one script command; otherwise acquire a nearby target, advance the
 * script index to dispatch a command, then copy position offsets onto the
 * target. */
void sub_080B91E0(void *behav) {
    u8 *target = *(u8 **)((u8 *)behav + 0x38);
    u8 *owner = *(u8 **)((u8 *)behav + 0x3C);
    u8 *self = (u8 *)behav;

    if (sub_080141AC(target, owner) == 1) {
        sub_080C31E0(self, *(void **)(self + 0x24));
        return;
    }

    if (*(u16 *)owner & 1) {
        s32 scriptOff;
        u8 *cmdArray;
        s32 *effectTable;
        u8 cmdByte;
        *(u8 *)(*(u8 **)(owner + 0x28) + 1) = 0;
        scriptOff = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)scriptOff + (u32)self + 0x19) = 0;
        effectTable = (s32 *)0x08671BB0;
        cmdArray = self;
        cmdArray += 0x18;
        sub_080C31E4(cmdArray, self + 0x22, *effectTable);
        scriptOff = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)scriptOff + (u32)self + 0x19) = *(u8 *)((u32)scriptOff + (u32)self + 0x19) + 1;
        scriptOff = *(s16 *)(self + 0x22) * 2;
        cmdArray += scriptOff;
        cmdByte = *(u8 *)cmdArray;
        sub_080C31E0(self, *(void **)(cmdByte * 4 + *(u32 *)(self + 0x14)));
        return;
    }

    if (updateObjectDisplayState(target, owner) == 0) {
        s32 scriptOff;
        u8 *cmdArray;
        u8 cmdByte;
        *(u32 *)(self + 0x14) = 0x08670578;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        scriptOff = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)scriptOff + (u32)self + 0x19) = *(u8 *)((u32)scriptOff + (u32)self + 0x19) + 1;
        scriptOff = *(s16 *)(self + 0x22) * 2;
        cmdArray = self;
        cmdArray += 0x18;
        cmdArray += scriptOff;
        cmdByte = *(u8 *)cmdArray;
        sub_080C31E0(self, *(void **)(cmdByte * 4 + *(u32 *)(self + 0x14)));
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    }
    sub_08013C8C(self, target);
}
