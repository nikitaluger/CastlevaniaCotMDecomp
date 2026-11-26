extern void copyPoseAttrs(s32, s32);

/* Copy the four-halfword attribute record that matches the sprite kind (3, 5
 * or 6) into the work object's attribute block. The records live at
 * 0x080CF970/0x080CF978/0x080CF980 and hold {4,10,0,-6}, {4,4,0,0} and
 * {4,10,0,6}. */
void sub_0804ACB0(void *work, void *sprite) {
    s32 record = 0;
    switch (*(u16 *)((u8 *)sprite + 0x28)) {
    case 3: record = 0x080CF970; break;
    case 5: record = 0x080CF978; break;
    case 6: record = 0x080CF980; break;
    }
    copyPoseAttrs(*(s32 *)((u8 *)work + 0x28), record);
}
