s32 sub_080141AC(void *, void *);
s32 sub_08016238(void *);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);

/* Behaviour-script callback: on a contact request hand control back to the owner;
 * otherwise acquire a nearby target and set the owner's active flag, dispatch a script
 * command, advance to the next command, then copy position offsets onto the target. */
void sub_0803887C(void *behav) {
    void *target;
    void *owner;
    u32 *cmdTable;

    target = *(void **)((u8 *)behav + 0x38);
    owner = *(void **)((u8 *)behav + 0x3C);
    if (sub_080141AC(target, owner) == 1) {
        sub_080C31E0((s32)behav, *(s32 *)((u8 *)behav + 0x24));
        return;
    }
    if (sub_08016238(*(void **)((u8 *)owner + 0x28)) != 0) {
        s32 newFlags = 1 | *(u16 *)owner;
        *(u16 *)owner = newFlags;
    }
    if ((1 & *(u16 *)((u8 *)*(void **)((u8 *)owner + 0x28) + 0x14)) ||
        (0x0D & *(u16 *)((u8 *)owner + 0x02))) {
        *(u16 *)owner |= 1;
    }
    if (1 & *(u16 *)owner) {
        if ((u8)(*(u8 *)((u32)(*(s16 *)((u8 *)behav + 0x22)) * 2 + (u32)behav + 0x1A) - 1) > 1) {
            *(u8 *)((u32)(*(s16 *)((u8 *)behav + 0x22)) * 2 + (u32)behav + 0x1B) = 0;
            cmdTable = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)behav + 0x18, (u8 *)behav + 0x22, 1, *cmdTable);
        }
    }
    if (sub_08013B5C(target, owner) == 0) {
        u8 *entry;
        u8 cmd;
        s32 scriptOff;
        *(u32 *)((u8 *)behav + 0x14) = 0x0866DEA4;
        *(u16 *)((u8 *)behav + 0x22) = *(u16 *)((u8 *)behav + 0x22) + 1;
        ((u8 *)behav + *(s16 *)((u8 *)behav + 0x22) * 2)[0x19]++;
        scriptOff = (s32)(s16)(*(s16 *)((u8 *)behav + 0x22)) * 2;
        entry = (u8 *)behav;
        entry += 0x18;
        entry += scriptOff;
        cmd = *entry;
        sub_080C31E0((s32)behav, *(s32 *)((u32)(cmd * 4) + *(u32 *)((u8 *)behav + 0x14)));
        *(u16 *)((u8 *)behav + 0x22) = *(u16 *)((u8 *)behav + 0x22) - 1;
    }
    sub_08013C8C(behav, target);
}
