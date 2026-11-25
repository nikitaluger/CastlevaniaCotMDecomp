/* Decrement the effect's remaining-time counter at work+6 (state+0x48). */
void sub_080557E4(void *entity) {
    void *work;
    work = *(s32 *)((s8 *)entity + 0x3C) + 0x48;
    *(u16 *)((s8 *)work + 6) = (u16)(*(u16 *)((s8 *)work + 6) - 1);
}
