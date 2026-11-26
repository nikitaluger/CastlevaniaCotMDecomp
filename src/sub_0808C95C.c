extern u32 gMainWorkspace[];

void sub_080C31E0(void *, void *);

/* Grows the sprite's rotation counter by a quarter of its current value each
 * frame; once it passes 0x07FF, sets the global game mode to 2 (when the script
 * flag at +0x14B0 is 1) or 0, provided work+0x30 is clear, then dispatches the
 * next state handler. */
void sub_0808C95C(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x6C) + 4;
    u8 *sprite = *(u8 **)((u8 *)arg0 + 0x38);
    s32 angle;
    s32 quarter;
    u16 oldAngle;
    s32 newAngle;
    u32 modeOffset;
    u32 flagOffset;
    u32 *mode;
    u32 flag;
    u32 newMode;
    angle = *(s16 *)(sprite + 6);
    quarter = angle;
    if (quarter < 0) quarter += 3;
    quarter = (quarter >> 2);
    oldAngle = *(u16 *)(sprite + 6);
    newAngle = quarter + oldAngle;
    *(u16 *)(sprite + 6) = (u16)newAngle;
    if ((s32)((u16)newAngle << 16) > 0x07FF0000) {
        if (*(s32 *)(work + 0x30) == 0) {
            modeOffset = 0x14AC;
            flagOffset = 0x14B0;
            mode = (u32 *)((u8 *)gMainWorkspace + modeOffset);
            flag = *(u32 *)((u8 *)gMainWorkspace + flagOffset);
            newMode = 0;
            if (flag == 1) newMode = 2;
            *mode = newMode;
        }
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
    }
}
