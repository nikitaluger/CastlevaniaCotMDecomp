extern u8 gMainWorkspace[];

/*
 * Selects a world position from the global state's mode flags, applies the
 * fractional scroll correction and the context's vertical offset, then writes
 * the player and camera coordinates. Returns the mode used.
 */
s32 syncViewPosition(struct ViewSyncContext *ctx, struct WorldPosition *out) {
    struct ViewSyncState *state = (struct ViewSyncState *)gMainWorkspace;
    u32 modeFlags = state->modeFlags;
    u32 adjustedX;
    if (!(modeFlags & VIEW_SYNC_FLAGS_MASK)) return VIEW_SYNC_MODE_NONE;
    if (modeFlags & VIEW_SYNC_FLAG_HELD) return VIEW_SYNC_MODE_HELD;
    if (modeFlags & VIEW_SYNC_FLAG_INTERP) {
        out->x = state->srcX;
        out->y = state->srcY;
        adjustedX = ((u32)state->fracXTo << 24) + out->x - ((u32)state->fracXFrom << 24);
        out->x = adjustedX;
        out->y = ((u32)state->fracYTo << 24) + out->y - ((u32)state->fracYFrom << 24);
        state->playerX = adjustedX;
        state->playerY = out->y + ((s32)ctx->param->offsetY << 16);
        state->viewX = out->x;
        state->viewY = out->y;
        return VIEW_SYNC_MODE_INTERPOLATED;
    }
    if (modeFlags & VIEW_SYNC_FLAG_DIRECT) {
        out->x = state->srcX;
        out->y = state->srcY;
        state->playerX = out->x;
        state->playerY = out->y + ((s32)ctx->param->offsetY << 16);
        state->viewX = out->x;
        state->viewY = out->y;
        state->mode = VIEW_SYNC_FLAG_INTERP & modeFlags;
        return VIEW_SYNC_MODE_DIRECT;
    }
    return VIEW_SYNC_MODE_NONE;
}
