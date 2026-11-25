struct ScriptInterp {
    u8 pad0[4];
    s32 reg4;
    s32 reg8;
    u8 padC[4];
    s32 reg10;
};

/* Script command: store the three command arguments into the interpreter's
 * register slots at +0x10, +4 and +8. */
void sub_08098654(struct ScriptInterp *interp, s32 value10, s32 value4, s32 value8) {
    interp->reg10 = value10;
    interp->reg4 = value4;
    interp->reg8 = value8;
}
