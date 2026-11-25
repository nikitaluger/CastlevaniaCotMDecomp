extern void sub_080C0B70(void *player);
extern void sub_080C0440(u16 songId);
extern u8 D_08106DCC[];   /* 12-byte sound-player entries; +0 = MPlay info pointer */
extern u8 D_08106E38[];   /* 8-byte song entries: +0 = song header, +4 = player index */

/* Starts song/sound `songId`: if that sound player is already busy with a song
 * of strictly higher priority, leave it alone; otherwise stop the player and
 * start the requested song. */
void sub_08005E80(u16 songId) {
    u16 idx;
    u8 *playerTable;
    u8 *songTable;
    u16 *songEntry;
    void *player;
    s32 status;
    idx = songId;
    playerTable = D_08106DCC;
    songTable = D_08106E38;
    songEntry = (u16 *)(songTable + idx * 8);
    player = *(void **)(playerTable + songEntry[2] * 12);
    status = *(s32 *)((u8 *)player + 4);
    if (status < 0) goto fail;
    if ((status & 0xFFFF) != 0) goto check;
fail:
    sub_080C0B70(player);
    sub_080C0440(idx);
    return;
check:
    if (*(u8 *)((u8 *)*(void **)player + 2) <= *(u8 *)((u8 *)*(void **)songEntry + 2)) {
        sub_080C0B70(player);
        sub_080C0440(idx);
    }
}
