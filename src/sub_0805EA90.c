extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u16 sub_080C3824(u16, s32);
extern u16 sub_080C389C(u16, s32);

struct S_02025368 { u8 _pad[0xC3 << 2]; u8 data[1]; };
extern struct S_02025368 D_02025368;

/* Mark this entity's map cell in the visited-flag table, play a sound, clear
 * then bump its script slot, and start the associated script/entity callback. */
void sub_0805EA90(void *arg0) {
    u8 *self = (u8 *)arg0;
    struct S_02025368 *base = &D_02025368;
    u8 *state = self + 0x4C;
    u16 cell = *(u16 *)(state + 8);
    u16 col = sub_080C389C(cell, 0xA);
    u16 row = sub_080C3824(cell, 0xA);
    u32 idx = col + row * 0xA;
    u8 *flags = base->data;
    u8 *cellFlag = flags + idx;
    cell = 0;
    *cellFlag = 1;
    sub_08005E80(0x1B4);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = cell;
    {
        s32 *scriptTable = (s32 *)0x08671BB0;
        u8 *slot = self + 0x18;
        sub_080C31E4(slot, self + 0x22, *scriptTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        slot = slot + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)slot * 4));
    }
}
