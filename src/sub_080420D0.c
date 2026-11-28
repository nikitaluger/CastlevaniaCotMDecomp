extern void *spawnVariant2Effect(s32 x, s32 y, u16 param);
extern void sub_08005E80(u16 songId);
extern void sub_080C31E0(void *entity, s32 handler);

/* One-shot step: spawn effect variant 2 at the entity's work position, play
 * sound 0x88, then hand control to the next handler. */
void sub_080420D0(void *entity) {
    void *work = *(void **)((u8 *)entity + 0x3C);
    spawnVariant2Effect(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC), 8);
    sub_08005E80(0x88);
    sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
}
