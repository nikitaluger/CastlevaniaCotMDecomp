struct S_02025FF0 {
    u8 _0[0x1848];
    u32 field1848;
    u8 _1[0x18C5-0x184C];
    u8 field18C5;
    u8 field18C6;
};
extern struct S_02025FF0 D_02025FF0;

extern u32 D_08671BB0;
void sub_0805FBE4(void *arg0, u16 arg1);
void sub_0805FC0C(void *arg0, u16 arg1, u16 arg2);
void sub_080C31E4(void *arg0, void *arg1, u32 arg2);

// Marks global event flags (the field1848 bitmask plus two booleans), spawns a
// 0x14-byte child effect using the entity's stored parameters, clears the
// entity's per-slot byte, then calls the indirect effect callback.
void sub_0805EFF8(void *entity) {
    D_02025FF0.field1848 |= 0x4DFA0000;
    D_02025FF0.field18C6 = 1;
    D_02025FF0.field18C5 = 1;
    if (*(s16 *)((u8 *)entity + 0x5C) == 0) {
        sub_0805FBE4(entity, *(u16 *)((u8 *)entity + 0x4C));
    } else {
        sub_0805FC0C(entity, *(u16 *)((u8 *)entity + 0x4C), *(u16 *)((u8 *)entity + 0x54));
    }
    *(s8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
    {
        void **callbackSlot = &D_08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackSlot);
    }
}
