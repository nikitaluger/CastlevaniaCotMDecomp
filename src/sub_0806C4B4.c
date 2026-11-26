extern u8 gMainWorkspace[];

struct GameState {
    u8 pad0[0x14B8];
    u32 modeFlags;
    u8 pad1[8];
    u8 fracXFrom;
    u8 fracYFrom;
    u8 fracXTo;
    u8 fracYTo;
    u32 srcX;
    u32 srcY;
    u8 pad2[0x258];
    u32 viewX;
    u32 viewY;
    u8 pad3[0x1C];
    u32 playerX;
    u32 playerY;
    u8 pad4[0x150];
    u32 mode;
};
struct ParamValue { u8 pad[0xC]; s16 value; };
struct Context { u8 pad[0x12C]; struct ParamValue *value; };
struct Point { u32 x; u32 y; };

/*
 * Chooses a world position from the global state's mode flags, applies the
 * fractional scroll correction and the context's vertical offset, writes the
 * player and view coordinates, and returns which mode was used
 * (0 = none, 1 = held, 2 = interpolated, 3 = direct).
 */
s32 sub_0806C4B4(struct Context *ctx, struct Point *out) {
    struct GameState *gs = (struct GameState *)gMainWorkspace;
    u32 flags = gs->modeFlags;
    u32 adjX;
    if (!(flags & 0x0F)) return 0;
    if (flags & 0x08) return 1;
    if (flags & 0x05) {
        out->x = gs->srcX;
        out->y = gs->srcY;
        adjX = ((u32)gs->fracXTo << 24) + out->x - ((u32)gs->fracXFrom << 24);
        out->x = adjX;
        out->y = ((u32)gs->fracYTo << 24) + out->y - ((u32)gs->fracYFrom << 24);
        gs->playerX = adjX;
        gs->playerY = out->y + ((s32)ctx->value->value << 16);
        gs->viewX = out->x;
        gs->viewY = out->y;
        return 2;
    }
    if (flags & 0x02) {
        out->x = gs->srcX;
        out->y = gs->srcY;
        gs->playerX = out->x;
        gs->playerY = out->y + ((s32)ctx->value->value << 16);
        gs->viewX = out->x;
        gs->viewY = out->y;
        gs->mode = 5 & flags;
        return 3;
    }
    return 0;
}
