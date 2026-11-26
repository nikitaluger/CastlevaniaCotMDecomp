/* Map script state inside the graphics workspace. */
struct MapScriptState {
    u8 pad0[0x143C];
    u8 scriptDelay;   /* +0x143C: frames between commands */
    u8 pad1[5];
    u8 scriptSide;    /* +0x1442: which side's command interpreter runs */
    u8 pad2[2];
    u8 delayCounter;  /* +0x1445: frames left before the next command */
    u8 pad3[0xE];
    u8 *cursor;       /* +0x1454: current position in the map script */
};
extern struct MapScriptState gCameraState;
s32 sub_080609F0(void);
void sub_08060A1C(u16);

/*
 * Runs the ordinary (non jump-table) map script command under the cursor once
 * its delay has elapsed: the command byte is biased by 0x26 and handed to the
 * interpreter; the cursor then advances. Returns 2 while still waiting on the
 * delay, 0 after a command was run.
 */
s32 sub_080609B8(void) {
    if (sub_080609F0() != 0) {
        sub_08060A1C((u16)(*gCameraState.cursor - 0x26));
        gCameraState.cursor += 1;
        return 0;
    }
    return 2;
}
