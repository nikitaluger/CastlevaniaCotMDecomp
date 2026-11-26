void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_02021E90_Check { u8 pad[0x146C]; u16 field; };
extern struct S_02021E90_Check gCameraState;

/* When global flag bit 3 is set, advance this text object's current slot: clear
 * its counter byte, refill the slot via sub_080C31E4 with the shared char-data
 * table, bump the counter, then dispatch the callback picked from obj->table. */
void sub_08008EB0(void *obj) {
    u8 *bytes = (u8 *)obj;
    if (8 & gCameraState.field) {
        u8 *entry;
        s32 *charData;
        *(u8 *)(bytes + *(s16 *)(bytes + 0x22) * 2 + 0x19) = 0;
        charData = (s32 *)0x08671BB0;
        entry = bytes + 0x18;
        sub_080C31E4(entry, bytes + 0x22, *charData);
        *(u8 *)(bytes + *(s16 *)(bytes + 0x22) * 2 + 0x19) += 1;
        entry += *(s16 *)(bytes + 0x22) * 2;
        sub_080C31E0(obj, *(void **)((u8 *)*(u32 *)(bytes + 0x14) + *(u8 *)entry * 4));
    }
}
