void sub_08005E80(u16);

extern u8 D_08106DCC[];
extern u8 D_08106E38[];

/* Starts song `songId` unless its sound player already has that song loaded. */
void sub_08005EE4(u16 songId)
{
    u16 idx = songId;
    u8 *playerTable = D_08106DCC;
    u8 *songTable = D_08106E38;
    u16 *songEntry = (u16 *)(songTable + idx * 8);
    u32 *playerInfo = *(u32 **)(playerTable + songEntry[2] * 12);

    if (*playerInfo != *(u32 *)songEntry)
        sub_08005E80(idx);
}
