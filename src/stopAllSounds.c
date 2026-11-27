extern void sub_080C0B70(u32);
extern u8 D_00000009;

/* Stop every sound player in the nine-entry player table. */
void stopAllSounds(void)
{
    u16 count = (u16)((u32)&D_00000009);
    if (count != 0) {
        u32 *player = (u32 *)0x08106DCC;
        u32 remaining = count;
        do {
            sub_080C0B70(*player);
            player = (u32 *)((u8 *)player + 12);
            remaining--;
        } while (remaining != 0);
    }
}
