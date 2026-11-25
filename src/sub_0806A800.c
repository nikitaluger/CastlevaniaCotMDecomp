/* Load an actor definition from D_080DF598[defIndex] into its work state:
 * two fixed-point coordinates, four sprite parameters and five misc parameters
 * (the first of the latter masked by the shared result flags). */
struct ActorDef { void *coords; void *spriteCfg; void *miscCfg; };
extern struct ActorDef D_080DF598[];

struct ResultFlags { u8 _0[0x1510]; u8 mask; };
extern struct ResultFlags D_02025FF0;

struct SpriteCfgSrc { u16 p0, p2, p4, p6; };
struct SpriteCfgDst { u8 _0[6]; u16 p6, p8, pA, pC; };
struct MiscCfgSrc { u8 flags; u8 _1; u16 p2, p4, p6, p8, pA; };
struct MiscCfgDst { u8 _0; u8 flags; u8 _2[4]; u16 p6, p8, pA, pC; u8 _E[0xA]; u16 p18; };

struct WorkState {
    u8 _0[0x38];
    u32 x;
    u32 y;
    u8 _40[0xEC];
    struct SpriteCfgDst *volatile spriteCfg;
    struct MiscCfgDst *volatile miscCfg;
};

void sub_0806A800(struct WorkState *work, s32 defIndex) {
    struct ActorDef *def = &D_080DF598[defIndex];
    u32 *coords = def->coords;
    struct SpriteCfgSrc *spriteSrc = def->spriteCfg;
    struct MiscCfgSrc *miscSrc = def->miscCfg;
    work->x = coords[0];
    work->y = coords[1];
    work->spriteCfg->p6 = spriteSrc->p0;
    work->spriteCfg->p8 = spriteSrc->p2;
    work->spriteCfg->pA = spriteSrc->p4;
    work->spriteCfg->pC = spriteSrc->p6;
    work->miscCfg->flags = miscSrc->flags & D_02025FF0.mask;
    work->miscCfg->p18 = miscSrc->p2;
    work->miscCfg->p6 = miscSrc->p4;
    work->miscCfg->p8 = miscSrc->p6;
    work->miscCfg->pA = miscSrc->p8;
    work->miscCfg->pC = miscSrc->pA;
}
