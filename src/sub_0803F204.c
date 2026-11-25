extern void *sub_0808DC40(s32 x, s32 y, u16 param);
extern void sub_080C31E0(void *entity, s32 handler);

/* One-shot step: spawn effect variant 2 well below the entity's work position,
 * then hand control to the next handler. */
void sub_0803F204(void *entity) {
    void *work = *(void **)((u8 *)entity + 0x3C);
    sub_0808DC40(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC) + 0x180000, 8);
    sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
}
