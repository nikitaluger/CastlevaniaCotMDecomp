s32 sub_08005E80(s32);
s32 sub_080A5504(s32);

/* Periodic timer: while active, every 0x30 ticks toggle a phase flag, play a
 * sound on odd phases, and spawn a child effect. */
void sub_080A3E4C(s32 owner, void *state) {
    s32 countdown;
    s32 phase;

    if (*(s32 *)((u8 *)state + 0x5C) != 0) {
        countdown = *(s32 *)((u8 *)state + 0x40) + 1;
        *(s32 *)((u8 *)state + 0x40) = countdown;
        if (countdown == 0x30) {
            *(s32 *)((u8 *)state + 0x40) = 0;
            phase = (*(s32 *)((u8 *)state + 0x44) + 1) & 1;
            *(s32 *)((u8 *)state + 0x44) = phase;
            if (phase != 0) {
                sub_08005E80(0x173);
            }
            sub_080A5504(owner);
        }
    }
}
