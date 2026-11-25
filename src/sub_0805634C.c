void sub_0808DC40(void *, s32, s32);
void sub_080C31E0(void *, void *);
extern u8 D_080CFBF8[];

/* Command step: spawn a variant-2 effect at the actor's x position and its y
 * position plus a table-provided offset picked by the control block's index
 * byte, then re-dispatch the script. */
void sub_0805634C(void *obj) {
    void *self = obj;
    void *work = *(void **)((u8 *)self + 0x3C);
    u8 *ctrl = (u8 *)work + 0x48;
    void *x = *(void **)((u8 *)work + 8);
    u8 *table = D_080CFBF8;
    u8 index = ctrl[9];
    u32 offset = index * 0x24;
    table += 0x1C;
    sub_0808DC40(x, *(s32 *)((u8 *)work + 0xC) + *(s32 *)(table + offset), 8);
    sub_080C31E0(self, *(void **)((u8 *)self + 0x24));
}
