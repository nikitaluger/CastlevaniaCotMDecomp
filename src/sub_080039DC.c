/* Run one step of a script stored as 8-byte entries at script+8, indexed by
 * the u16 at script+4. A data entry (bit 0x8000 clear) writes its masked value
 * to script+2, copies its three u16 params to out and advances the index,
 * returning 1. A command entry switches on its low nibble: 0 copies params,
 * resets the index and returns 0; 1 advances the index and 2 resets it, both
 * continuing the loop. */
s32 sub_080039DC(void *arg0, void *arg1) {
    u32 index;
    u8 *script = arg0;
    u8 *out = arg1;
    s32 status = -1;
    do {
        u16 *entry;
        index = *(u16 *)(script + 4);
        entry = (u16 *)(*(u8 **)(script + 8) + index * 8);
        if (entry[0] & 0x8000) {
            u16 command = entry[0] & 0xF;
            switch (command) {
            case 0:
                *(u16 *)(out + 0) = entry[1];
                *(u16 *)(out + 2) = entry[2];
                *(u16 *)(out + 4) = entry[3];
                *(u16 *)(script + 4) = command;
                status = 0;
                break;
            case 1:
                *(u16 *)(script + 4) = index + 1;
                break;
            case 2:
                *(u16 *)(script + 4) = 0;
                break;
            }
        } else {
            *(u16 *)(script + 2) = 0x1FFF & entry[0];
            *(u16 *)(out + 0) = entry[1];
            *(u16 *)(out + 2) = entry[2];
            *(u16 *)(out + 4) = entry[3];
            *(u16 *)(script + 4) = *(u16 *)(script + 4) + 1;
            status = 1;
        }
    } while (status < 0);
    return status;
}
