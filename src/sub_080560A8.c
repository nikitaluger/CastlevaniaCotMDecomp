void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);
void sub_0808DC40(void *, s32, s32);

/* Run one script command out of line: save the sprite, temporarily advance the
 * script step and its action byte, dispatch the command at the new step from
 * the standard command table (0x0866E78C), then restore the step and sprite. */
void sub_080560A8(void *self) {
    void *sprite = *(void **)((u8 *)self + 0x38);
    sub_080144D8(self, sprite);
    *(void **)((u8 *)self + 0x14) = (void *)0x0866E78C;
    *(u16 *)((u8 *)self + 0x22) = (u16)(*(u16 *)((u8 *)self + 0x22) + 1);
    {
        u8 *entry = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        entry[0x19] = (u8)(entry[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)self + 0x22)) * 2;
            u8 *commands = (u8 *)self + 0x18;
            u8 command = *(commands + stepOffset);
            void **commandTable = *(void **)((u8 *)self + 0x14);
            void *handler = commandTable[command];
            sub_080C31E0(self, handler);
        }
    }
    *(u16 *)((u8 *)self + 0x22) = (u16)(*(u16 *)((u8 *)self + 0x22) - 1);
    sub_080144FC(self, sprite);
}
