/* Map script state inside the graphics workspace (shared with sub_080609B8
 * and sub_08060A1C). */
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
extern struct MapScriptState D_02021E90;

/* Read the second byte of the map-script command under the cursor as a biased
 * parameter value (+3), skipping the two-byte command and advancing the cursor. */
s32 sub_08060998(void) {
    u8 *cmd;
    u8 *next;
    s32 param;
    cmd = D_02021E90.cursor;
    next = cmd + 1;
    D_02021E90.cursor = next;
    param = *(u8 *)(cmd + 1);
    D_02021E90.cursor = next + 1;
    return param + 3;
}
