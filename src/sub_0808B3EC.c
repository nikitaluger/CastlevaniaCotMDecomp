extern void sub_0808B458(void *);
extern u8 gCameraState[];

/* Demo/attract-mode input recorder: called once per frame with the recording
 * work block (entry index at +0, active flag at +8, {keys, frames} entries at
 * +0xC). Unless Start was just pressed it stores the current raw key state
 * (keyState+0x149C) into the current entry and counts consecutive frames of the
 * same keys; when the keys change it moves on to the next entry, starting a
 * fresh entry in the following slot when the index rolls over. */
void sub_0808B3EC(void *arg0) {
    u8 *keyState = gCameraState;
    if (*(u16 *)(keyState + 0x146C) & 8) {
        sub_0808B458(arg0);
    } else {
        u8 *recording = (u8 *)arg0;
        s32 entryIndex = *(s32 *)recording;
        u16 *entry = (u16 *)(recording + 0x0C + entryIndex * 4);
        u16 keys = *(u16 *)(keyState + 0x149C);
        if (*(s32 *)(recording + 8) == 0) {
            s32 one;
            entry[0] = keys;
            one = 1;
            entry[1] = (u16)one;
            *(s32 *)(recording + 8) = one;
        } else if (entry[0] == keys) {
            entry[1] = entry[1] + 1;
        } else {
            s32 next = entryIndex + 1;
            *(s32 *)recording = next;
            if (next <= 0) {
                entry += 2;
                entry[0] = keys;
                entry[1] = 1;
            }
        }
    }
}
