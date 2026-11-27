extern u32 gMainWorkspace[];
void syncSpriteToWorldPosition(void *entity, void *sprite);
void sub_080C31E0(void *entity, void *callback);

/* Update an entity's display: when the global mode word at gMainWorkspace+0x40
 * is 7, abandon the step and chain to the saved script callback; otherwise
 * refresh the sprite's screen position from the entity's world position. */
void sub_080B97F0(void *entity) {
    void *sprite = *(void **)((u8 *)entity + 0x38);

    if (gMainWorkspace[16] == 7) {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    syncSpriteToWorldPosition(entity, sprite);
}
