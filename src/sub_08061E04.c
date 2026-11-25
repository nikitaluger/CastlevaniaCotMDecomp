/* Screen-effect parameter block at 0x02027A00: four fixed-point values, two
 * flag bytes and the effect's tile coordinates. */
struct ScreenFxParams { u32 f0; u32 f4; u32 f8; u32 fC; u8 f10; u8 f11; u8 tileX; u8 tileY; u16 f14; };
extern struct ScreenFxParams D_02027A00;

/* Graphics workspace; +0x1278 is the first X entry of the camera coordinate
 * table (16.16 fixed point, 0x40 bytes per camera). */
struct GraphicsWorkspace { u8 pad[0x1278]; u32 camX0; };
extern struct GraphicsWorkspace D_02021E90;

/* Preset A of the screen effect: clear its flag byte, reset the first camera
 * X coordinate and load its fixed-point parameters. */
void sub_08061E04(void) {
    D_02027A00.f10 = 0;
    D_02021E90.camX0 = 0xFFF00000;
    D_02027A00.f0 = 0xC0 << 12;
    D_02027A00.f4 = 0xC4 << 16;
}
