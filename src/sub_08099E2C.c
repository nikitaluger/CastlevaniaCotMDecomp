void sub_0809C510(s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Reconfigure this object's sound voice, then advance its phase counter by
 * -0x80; when the counter lands on the 0xD800 marker, reset the current
 * command slot's step counter and restart the command script. */
void sub_08099E2C(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *sfx = *(u8 **)(self + 0x3C) + 0x48;
    u32 phase;
    sub_0809C510(*(s32 *)(sfx + 0x08), *(s32 *)(sfx + 0x18), 2);
    phase = *(u16 *)(sfx + 0x24) - 0x80;
    *(u16 *)(sfx + 0x24) = phase;
    if ((phase << 16) == 0xD8000000) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *tokenTable;
            tokenTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *tokenTable);
        }
    }
}
