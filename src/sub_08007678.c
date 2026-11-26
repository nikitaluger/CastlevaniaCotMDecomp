struct GlobalState {
    u8 _0[0x1768];
    u16 paletteColor;
    u8 _1[0x1854 - 0x176A];
    u32 objTreeA;
    u8 _2[0x1884 - 0x1858];
    u32 objTreeB;
    u8 _3[0x18C4 - 0x1888];
    u8 transitionFlag;
};
extern struct GlobalState gMainWorkspace;
void updateObjectTree(void *);
void sub_080C31E0(void *, void *);
void sub_080C31E8(void *, void *, s32, void *);

/* Run cleanup scripts on both global object trees. Once (flag == 0), mark the
 * transition as done, run the second tree's script at +0x24, set the background
 * palette color, clear the current script step's action byte and advance it. */
void sub_08007678(void *arg0) {
    u8 *entity = arg0;
    u8 flag;
    void **callback;
    updateObjectTree((void *)gMainWorkspace.objTreeA);
    updateObjectTree((void *)gMainWorkspace.objTreeB);
    flag = *(volatile u8 *)&gMainWorkspace.transitionFlag;
    if (flag == 0) {
        gMainWorkspace.transitionFlag = 0xFF;
        sub_080C31E0((void *)gMainWorkspace.objTreeB, *(void **)((u8 *)gMainWorkspace.objTreeB + 0x24));
        *(vu16 *)0x05000000 = gMainWorkspace.paletteColor;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = flag;
        callback = (void **)0x08671BD0;
        sub_080C31E8(entity + 0x18, entity + 0x22, 3, *callback);
    }
}
