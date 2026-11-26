extern void sub_08062770(void*);
extern u8 gCameraState[];

/* Record the cutscene frame counter in game state, arm the next animation,
 * and after 16 frames advance to the following cutscene state. */
void sub_08062734(void *obj) {
    u8 *gameState = gCameraState;
    u16 frames = *(u16*)((u8*)obj + 0x22);
    gameState[0x13AE] = (u8)frames;
    gameState[0x1360] = 6;
    if ((s16)frames > 0x0F) {
        *(u16*)((u8*)obj + 0x22) = 0;
        *(void**)((u8*)obj + 0x14) = &sub_08062770;
    }
}
