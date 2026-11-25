void sub_08006120(void);

/* Bring the sound players up, then stash the work area's affine scale pair
 * (D_02025FF0 + 0x14DC/+0x14DE) in D_0200A278/D_0200A27A, zero the Y scale and
 * set the effect field at +0x14E0 to 0x10.  sub_08006234 puts the saved scales
 * back when the scene change completes. */
void sub_080061CC(void) {
    u16 *savedScaleX;
    u8 *work;
    u16 *savedScaleY;
    u32 scaleXOff;
    u32 scaleYOff;
    u32 effectOff;
    sub_08006120();
    savedScaleX = (u16 *)0x0200A278;
    work = (u8 *)0x02025FF0;
    scaleXOff = 0x14DC;
    *savedScaleX = *(u16 *)(work + scaleXOff);
    savedScaleY = (u16 *)0x0200A27A;
    scaleYOff = 0x14DE;
    effectOff = 0xA7 << 5;
    *savedScaleY = *(u16 *)(work + scaleYOff);
    *(u16 *)(work + scaleYOff) = 0;
    *(u16 *)(work + effectOff) = 0x10;
}
