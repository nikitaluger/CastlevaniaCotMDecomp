extern s32 sub_0805FEC8(u16);
extern void sub_08061F38(void);
extern void sub_080C31E0(void *, s32);

struct S_02025FF0_14A4 {
    u8 pad[0x14A4];
    s8 mapLoadResult;
};
extern struct S_02025FF0_14A4 gMainWorkspace;

/* Load the map named by the id at +0x4C and remember the result at
 * gMainWorkspace+0x14A4; when loading fails (result 0), reset the HUD and switch the
 * entity to its next script state. */
void sub_0805FCC8(s8 *entity) {
    gMainWorkspace.mapLoadResult = sub_0805FEC8(*(u16 *)(entity + 0x4C));
    if (gMainWorkspace.mapLoadResult == 0) {
        sub_08061F38();
        sub_080C31E0(entity, *(s32 *)(entity + 0x24));
    }
}
