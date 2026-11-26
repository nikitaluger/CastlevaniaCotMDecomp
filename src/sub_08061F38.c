extern void sub_08061FBC(void);
extern void drawStatusHud(void);
extern u8 gGameStatus[];
extern u8 D_02027A00[];
struct S_02021E90 { u8 pad[0x1260]; u16 gfxTileBase; };
extern struct S_02021E90 gCameraState;
static inline u8 zero_b(void) { u8 v = 0; return v; }
static inline u16 zero_h(void) { u16 v = 0; return v; }

/* Clear the HUD banner timer and state, reload the status graphics and redraw
 * the HUD; when the mode word at gGameStatus+0x94 is 0x300, set the 0x2000
 * graphics flag. The two inline helpers keep the byte/halfword zeros distinct. */
void sub_08061F38(void)
{
  u8 *stats = gGameStatus;
  u8 *hud = D_02027A00;
  u16 *bannerTimer = (u16 *) (hud + 0xD8);
  register u16 halfZero = zero_h();
  register u8 byteZero = zero_b();
  *bannerTimer = halfZero;
  *((u8 *)hud + 0xDA) = byteZero;
  sub_08061FBC();
  drawStatusHud();
  if ((*((u16 *) (stats + 0x94))) == 0x300)
  {
    gCameraState.gfxTileBase |= 0x2000;
  }
}
