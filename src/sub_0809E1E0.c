extern void *sub_0808E670(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_08671BB0;

/* Spawn three effect objects in a horizontal spread (16.16 offsets +1.5, 0
 * and -1.5) around the linked object's position, then clear the step's
 * substate and run the script interpreter. */
void sub_0809E1E0(void *arg0) {
    u8 *task = (u8 *)arg0;
    u8 *work = *(u8 **)(task + 0x3C);
    s32 *scriptHandlers;

    sub_0808E670(*(s32 *)(work + 0x08), *(s32 *)(work + 0x0C) + 0xFFF00000, 0x18000, 0xFFFC8000);
    sub_0808E670(*(s32 *)(work + 0x08), *(s32 *)(work + 0x0C) + 0xFFF00000, 0, 0xFFFC8000);
    sub_0808E670(*(s32 *)(work + 0x08), *(s32 *)(work + 0x0C) + 0xFFF00000, 0xFFFE8000, 0xFFFC8000);

    *(u8 *)(task + 0x19 + (*(s16 *)(task + 0x22) * 2)) = 0;
    scriptHandlers = &D_08671BB0;
    sub_080C31E4(task + 0x18, task + 0x22, *scriptHandlers);
}
