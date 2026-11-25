void sub_08097EB4(s32 song);
void sub_080BE8C8(void *obj, s32 value);
void sub_080C31E8(void *base, void *index, s32 value, s32 table);

/* Script-step handler: start the object's song, silence its sound channel,
 * clear this step's progress byte and run the script-step helper (mode 5). */
void sub_080BA4D4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mover = *(u8 **)(self + 0x3C) + 0x48;
    s32 *lit;
    sub_08097EB4(0x0841FB04);
    sub_080BE8C8(*(s32 *)(mover + 0x34), 0);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
    lit = (s32 *)0x08671BD8;
    sub_080C31E8(self + 0x18, self + 0x22, 5, *lit);
}
