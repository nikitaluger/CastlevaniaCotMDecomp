extern void sub_080C2F1C(s32, s32, s32);

/* No-op: issue the CpuSet BIOS wrapper (SWI 0x0B) as a zero-length, 16-bit
 * copy — source, destination and transfer mode are all zero. */
void sub_08000890(void) {
    sub_080C2F1C(0, 0, 0);
}
