extern u32 D_0810C9E0[];

/* Script-step dispatcher: take the command byte at the cursor stored in the
 * task at +0x40, advance the cursor, then run the handler selected from the
 * D_0810C9E0 table. */
void sub_080C1640(void *owner, void *task) {
    u32 *p = (u32 *)task;
    u8 *cursor;
    u8 command;
    u32 handler;
    cursor = (u8 *)p[0x40 / 4];
    command = cursor[0];
    p[0x40 / 4] = (u32)(cursor + 1);
    handler = D_0810C9E0[command];
    sub_080C31E4(owner, task, handler);
}
