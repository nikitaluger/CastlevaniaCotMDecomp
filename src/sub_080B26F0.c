s16 sub_080C2F20(s32, s32); /* BIOS Div: returns the quotient */
void sub_080C31E0(void *, s32);

/* Give every sprite in the object's list the y position 0x600/(7-command),
 * then dispatch the stored callback once the command is 6. */
void sub_080B26F0(void *arg0) {
    void *node;

    node = *(void **)((u8 *)arg0 + 0x30);
    if (node != NULL) {
        do {
            *(s16 *)((u8 *)*(void **)((u8 *)node + 0x38) + 6) = sub_080C2F20(0x600, 7 - *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19));
            node = *(void **)((u8 *)node + 0x2C);
        } while (node != NULL);
    }
    if (*(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) == 6) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
