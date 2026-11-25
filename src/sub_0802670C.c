struct GameGlobals { u8 _0[0x174C]; u32 playerX; u32 playerY; };
extern struct GameGlobals D_02025FF0;
void sub_08014DB4(void *, void *, u32, u32);
void sub_080C31E4(void *, void *, u32);

/* Drive a bounded follow controller toward the player; when its turn timer
 * expires (bit 2 of the controller's direction flags), reset its travel
 * limits and motion rates and move on to the next script step. */
void sub_0802670C(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *body = work + 0xA8;
    u8 *path = work + 0xDC;
    u32 *stepTable;
    sub_08014DB4(body, path, D_02025FF0.playerX, D_02025FF0.playerY);
    if (4 & *(u16*)(work + 0xF4)) {
        *(u32*)(path + 8) = 0;
        *(u32*)(path + 0xC) = 0x30000;
        *(u32*)(path + 0x10) = 0x2000;
        *(u32*)(path + 0x14) = 0x200;
        *(u8*)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        stepTable = (u32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
    }
}
