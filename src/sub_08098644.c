/* Script-sequence runner state used by the cutscene/script helpers here:
 * +0x00 entry-pointer table, +0x0C end bound, +0x1C starting index, +0x35
 * end-of-script marker. */
struct ScriptRunner {
    s32 *entryTable;
    u8 pad04[8];
    s32 bound;
    u8 pad10[0x0C];
    u8 scriptId;
    u8 pad1D[0x35 - 0x1D];
    u8 endMarker;
};

/* Initialise a script runner: install its entry table and bound, select the
 * starting script index and mark it as not started. */
void sub_08098644(struct ScriptRunner *runner, s8 scriptId, s32 entryTable,
                  s32 bound) {
    runner->scriptId = (u8)scriptId;
    runner->entryTable = (s32 *)entryTable;
    runner->bound = bound;
    runner->endMarker = 0xFF;
}
