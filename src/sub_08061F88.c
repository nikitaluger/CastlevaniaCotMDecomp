void sub_08061FBC(void);
void drawStatusHud(void);
void sub_08062418(u8, u8);

extern u8 D_02027A00[];

/* HUD/message-window state bytes. */
enum {
    HUD_MSG_PENDING = 0xDA,  /* nonzero while a message scene is queued */
    HUD_MSG_SCENE = 0xDC,    /* queued scene type */
    HUD_MSG_SCRIPT = 0xDD    /* queued script index */
};

/* Redraw the HUD and, when a message scene is queued, start it with the queued
 * scene type and script index, then clear the pending flag. */
void sub_08061F88(void) {
    sub_08061FBC();
    drawStatusHud();
    if (D_02027A00[HUD_MSG_PENDING] != 0) {
        sub_08062418(D_02027A00[HUD_MSG_SCENE], D_02027A00[HUD_MSG_SCRIPT]);
        D_02027A00[HUD_MSG_PENDING] = 0;
    }
}
