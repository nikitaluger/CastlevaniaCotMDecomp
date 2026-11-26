extern void sub_08097F70(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
/* gMainWorkspace-based save/state block: mode is the game mode word at +0x40. */
struct S_40 { u8 pad[0x40]; u32 mode; };
extern struct S_40 gMainWorkspace;
/* When the game is in mode 2: hide the sprite at self+0x4C, decompress the
 * tileset at 0x0840ABCC into the object tile block at 0x06014000, set the two
 * sub-object state bytes to 5 and 1, then clear the substep and advance. */
void sub_080B0DE8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *sprite = *(u8 **)(self + 0x4C);
    if (gMainWorkspace.mode == 2) {
        u8 *visible = sprite + 0x34;
        s32 zero = 0;
        *visible = zero;
        sub_08097F70(0x0840ABCC, 0);
        *(u8 *)(*(u8 **)(work + 0x28) + 1) = 5;
        *(u8 *)(*(u8 **)(work + 0x48) + 1) = 1;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        {
            s32 *scriptAdvance = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptAdvance);
        }
    }
}
