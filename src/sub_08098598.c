extern void sub_08005E80(u16);

/*
 * Timed repeating sound: while the countdown (*timer) is running, plays
 * soundId at the start of each cycle, advances *phase and wraps it at
 * phaseCount.
 */
void sub_08098598(s32 soundId, u32 *phase, u32 phaseCount, s32 *timer) {
    if (*timer != 0) {
        if (*phase == 0) {
            sub_08005E80((u16)soundId);
        }
        (*timer)--;
        (*phase)++;
        if (*phase >= phaseCount) {
            *phase = 0;
        }
    }
}
