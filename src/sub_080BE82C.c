/* Starts an attack on an effect part: sets its state flag to 1 and stores an
 * attack value and a facing/direction byte. */
void sub_080BE82C(void *part, s32 value, s32 dir) {
    *(s32 *)((s8 *)part + 0x4C) = 1;
    *(s32 *)((s8 *)part + 0x5C) = value;
    *(s32 *)((s8 *)part + 0x6C) = dir;
}
