void sub_0805FBE4(void *, s32);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0_96DF0 {
    u8 pad0[0x1848];
    u32 progressFlags;
    u8 pad1[0x18C5 - 0x1848 - 4];
    u8 flag18C5;
    u8 flag18C6;
};
extern struct S_02025FF0_96DF0 gMainWorkspace;

/* Set the global progress bits and the two related flags, spawn effect object
 * 0x8153, then clear the script step and advance via the table at 0x08671BB0. */
void sub_08096DF0(void *arg0) {
    s32 *scriptCb;
    gMainWorkspace.progressFlags |= 0x4D7E0000;
    gMainWorkspace.flag18C6 = 1;
    gMainWorkspace.flag18C5 = 1;
    sub_0805FBE4(arg0, 0x8153);
    *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
    scriptCb = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptCb);
}
