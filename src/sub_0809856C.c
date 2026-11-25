extern void sub_08005E80(u16 songId);

/* Plays song `songId` once every `period` calls: starts it when the frame
 * counter is zero, advances the counter, and wraps it back to zero. */
void sub_0809856C(int songId, u32 *counter, u32 period) {
    u32 t;
    if (*counter == 0) {
        sub_08005E80((u16)songId);
    }
    t = *counter + 1;
    *counter = t;
    if (t >= period) {
        *counter = 0;
    }
}
