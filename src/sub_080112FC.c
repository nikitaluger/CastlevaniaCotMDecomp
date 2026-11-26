/* The work buffer at 0x02025FF0; these two 16-bit state fields sit at +0x1504. */
struct S_02025FF0_1504 { u8 _0x000[0x1504]; u16 field04; u16 field06; };
extern struct S_02025FF0_1504 gMainWorkspace;

/* Clears the two 16-bit state fields at gMainWorkspace+0x1504 and +0x1506. */
void sub_080112FC(void) {
    gMainWorkspace.field04 = 0;
    gMainWorkspace.field06 = 0;
}
