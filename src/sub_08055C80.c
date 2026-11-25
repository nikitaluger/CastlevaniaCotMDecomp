extern void *sub_0808DBB4(s32, s32, u16);
extern void sub_080C31E0(void *, void *);

/* Entity update: when the active command slot's counter reaches the threshold
 * (six times the object's pattern count plus a base), spawn a falling particle
 * at the work area's recorded position and call back into the entity. */
void sub_08055C80(void *arg0) {
    u8 *obj = arg0;
    void *work = *(void **)(obj + 0x3C);
    s16 slot = *(s16 *)(obj + 0x22);
    if ((s32)*(u8 *)((u8 *)arg0 + slot * 2 + 0x19) >= (s32)(*(s16 *)(obj + 0x7C) * 6 + 0x14)) {
        sub_0808DBB4(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC) + 0x80000, 8);
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
    }
}
