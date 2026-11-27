extern void sub_08013C5C(void *, void *);
extern s32 sub_080141AC(void *, void *);
extern s32 sub_08013558(void *, void *, u32);
extern void sub_08013978(void *, u32);
extern void sub_080142C0(void *, u32);
extern void sub_08013AC4(void *);
extern s32 updateObjectDisplayState(void *, void *);
extern void sub_08013C8C(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Script-driven enemy update: run the hit/collision helpers, then advance the
 * script step and dispatch its handler from the entity's function table. */
void sub_08049B44(void *arg0) {
    u8 *owner = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *comp = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *compTail = comp + 0x48;
    u8 *self = (u8 *)arg0;

    sub_08013C5C(self, owner);

    if (*(u8 *)(compTail + 0x0A) == 0) {
        *(u16 *)owner = (*(u16 *)owner & 0x0FFF) | 0xC000;
    }

    if (sub_080141AC(owner, comp) == 1) {
        if (*(u8 *)(compTail + 0x0A) != 0) {
            sub_080C31E0(self, *(void **)(self + 0x24));
        }
        return;
    }

    if (sub_08013558(owner, comp, *(u32 *)(comp + 0x28)) != 0) {
        sub_08013978(self, *(u32 *)(comp + 0x28));
    }
    sub_080142C0(self, *(u32 *)(comp + 0x28));

    if (*(u16 *)comp & 1) {
        s32 idx2;
        u8 *scriptData;
        s32 *audioCmd;
        u8 handlerId;

        sub_08013AC4(self);
        idx2 = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)idx2 + (u32)self + 0x19) = 0;
        audioCmd = (s32 *)0x08671BB0;
        scriptData = self;
        scriptData += 0x18;
        sub_080C31E4(scriptData, self + 0x22, *audioCmd);
        idx2 = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)idx2 + (u32)self + 0x19) = *(u8 *)((u32)idx2 + (u32)self + 0x19) + 1;
        idx2 = *(s16 *)(self + 0x22) * 2;
        scriptData += idx2;
        handlerId = *scriptData;
        sub_080C31E0(self, *(void **)(handlerId * 4 + *(u32 *)(self + 0x14)));
        return;
    }

    if (updateObjectDisplayState(owner, comp) == 0) {
        s32 idx2;
        u8 *scriptData;
        u8 handlerId;

        *(u32 *)(self + 0x14) = 0x0866E3F0;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        idx2 = *(s16 *)(self + 0x22) * 2;
        *(u8 *)((u32)idx2 + (u32)self + 0x19) = *(u8 *)((u32)idx2 + (u32)self + 0x19) + 1;
        idx2 = *(s16 *)(self + 0x22) * 2;
        scriptData = self;
        scriptData += 0x18;
        scriptData += idx2;
        handlerId = *scriptData;
        sub_080C31E0(self, *(void **)(handlerId * 4 + *(u32 *)(self + 0x14)));
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    }
    sub_08013C8C(self, owner);
}
