struct S_02025FF0 { u8 _0x000[0x189C]; u32 v; };
extern struct S_02025FF0 D_02025FF0;
extern s32 sub_08014900(s32);
extern s32 sub_0801491C(s32);
extern s32 sub_08014938(s32);
extern void sub_080C31E4(void *, void *, s32);

/* Enemy idle check: when the player is in the same vertical cell band and
 * close enough on both axes, turn to face the player and run the next
 * script command. */
void sub_080543BC(u8 *self) {
    u8 *motion = *(u8 **)(self + 0x3C);
    u8 *part = motion + 0x48;
    u32 frame = D_02025FF0.v & 0x3F;
    s32 row = *(s32 *)(motion + 0x0C);
    s32 zero;
    s32 dir;
    if (row < 0) row += 0x1FFFF;
    row = (row >> 17) & 0x3F;
    if (frame == (u32)row) {
        if (sub_08014900(*(s32 *)(motion + 0x08)) <= 0x700000) {
            if (sub_0801491C(*(s32 *)(motion + 0x0C)) <= 0x600000) {
                dir = sub_08014938(*(s32 *)(motion + 0x08)) << 8;
                zero = 0;
                *(u16 *)(part + 0x02) = (u16)dir;
                self[*(s16 *)(self + 0x22) * 2 + 0x19] = zero;
                {
                    u32 *pTable = (u32 *)0x08671BB0;
                    sub_080C31E4(self + 0x18, self + 0x22, *pTable);
                }
            }
        }
    }
}
