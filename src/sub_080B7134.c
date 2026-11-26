extern void initSpriteGraphics(void *sprite, void *animState, void *desc);

/* Point this sprite's animation state at the shared descriptor at 0x08102D58
 * and install the descriptor's update callback; used by many actor spawners. */
void sub_080B7134(void *sprite, void *animState) {
    initSpriteGraphics(sprite, animState, (void *)0x08102D58);
}
