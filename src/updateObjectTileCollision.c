extern void stepDelayTimer(void *, s32);
extern void startEffectTimer(void *, s32, s32);
extern void playSound(s32);
extern u16 getTileTerrainB(s32, s32, s32);
extern void cullOffscreenEntity(void *, s32);
extern s32 checkGlobalStateChange(void *, s32, void *);
extern void setSpriteScreenPosition(s32, void *);
extern void spawnKind2CEntity(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern struct TilePageWorkspace gMainWorkspace;

/* Advance a moving actor one frame: once the global-state guard allows it,
   probe the tile under its projected position. A solid tile cancels the
   pending motion, plays the hit sound, restarts the hit animation and
   dispatches the current script step; otherwise the motion is committed and
   a flagged effect is spawned before the sprite is repositioned and culled. */
void updateObjectTileCollision(u8 *actor) {
    u8 *scene = *(u8 **)(actor + 0x6C);
    u8 *body = scene + 4;
    s32 sprite = *(s32 *)(actor + 0x38);
    u8 *bodyKeep = body;
    s32 guard = checkGlobalStateChange(actor, sprite, body);
    s32 collision;
    if (guard != 0) return;

    collision = (u16)getTileTerrainB(0x02023130 + (gMainWorkspace.pageIndex << 6),
                       ((struct TileCollisionScene *)scene)->coordX + ((struct TileCollisionBody *)body)->offsetX,
                       ((struct TileCollisionBody *)body)->coordY + ((struct TileCollisionBody *)body)->offsetY);
    if (collision != 0) {
        u8 *stepByte;
        s32 *callback;
        startEffectTimer(scene + 0x30, 0, (void *)TILE_COLLISION_ANIM_DATA);
        ((struct TileCollisionBody *)body)->offsetX = guard;
        ((struct TileCollisionBody *)body)->offsetY = guard;
        ((struct TileCollisionBody *)body)->bounce = TILE_COLLISION_BOUNCE;
        playSound(TILE_COLLISION_SFX);
        stepByte = (u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor);
        *(u8 *)(stepByte + 0x19) = guard;
        callback = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        sub_080C31E4(actor + 0x18, actor + 0x22, *callback);
    } else {
        s32 zero;
        ((struct TileCollisionScene *)scene)->coordX = ((struct TileCollisionScene *)scene)->coordX + ((struct TileCollisionBody *)body)->offsetX;
        ((struct TileCollisionBody *)body)->coordY = ((struct TileCollisionBody *)body)->coordY + ((struct TileCollisionBody *)body)->offsetY;
        if (((struct TileCollisionEffect *)((struct TileCollisionBody *)body)->effect)->flags & 1) {
            u8 *stepByte;
            s32 *callback;
            u8 *effect;
            startEffectTimer(scene + 0x30, 0, (void *)TILE_COLLISION_ANIM_DATA);
            ((struct TileCollisionBody *)body)->offsetX = collision;
            ((struct TileCollisionBody *)body)->offsetY = collision;
            ((struct TileCollisionBody *)body)->bounce = TILE_COLLISION_BOUNCE;
            spawnKind2CEntity(*(s32 *)(actor + 0x28), TILE_COLLISION_EFFECT_KIND, ((struct TileCollisionScene *)scene)->coordX, ((struct TileCollisionBody *)body)->coordY);
            effect = ((struct TileCollisionBody *)body)->effect;
            zero = 0;
            ((struct TileCollisionEffect *)effect)->flags = collision;
            playSound(TILE_COLLISION_SFX);
            stepByte = (u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor);
            *(u8 *)(stepByte + 0x19) = zero;
            callback = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
            sub_080C31E4(actor + 0x18, actor + 0x22, *callback);
        }
    }
    setSpriteScreenPosition(sprite, bodyKeep);
    stepDelayTimer(body + 0x2C, sprite);
    cullOffscreenEntity(actor, sprite);
}
