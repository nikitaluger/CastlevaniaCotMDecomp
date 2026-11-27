extern s32 updateObjectTree(void *root);
extern s32 _call_via_r1(s32, s32);
extern s32 _call_via_r3(void *, void *, s32, s32);
extern u8 gMainWorkspace[];
extern u8 gCrossfadeGfxState[];
extern u32 gScriptStepCallbacks[];

/* Walk the four global object trees, bump the frame counter and crossfade
 * phase, invoke each tracked object's saved update handler, then clear the
 * actor's script-step action byte and dispatch its next script step. */
void updateObjectTreesAndAdvanceScript(u8 *actor)
{
    u8 *ws;
    u8 *treeA;
    u8 *frameCounter;
    u8 *treeB;
    u8 *phaseDst;
    u8 *phaseSrc;
    u8 *obj;
    void *t;
    ws = (u8 *) gMainWorkspace;
    updateObjectTree(*((void **) (ws + 0x1854)));
    treeA = ws + 0x1860;
    updateObjectTree(*((void **) treeA));
    frameCounter = ws + 0x1894;
    *((u32 *) frameCounter) += 1;
    treeB = ws + 0x1888;
    updateObjectTree(*((void **) treeB));
    if ((*((s32 *) (ws + 0x14C0))) >= 0)
    {
        struct
        {
            u8 _[8];
            u16 phase;
        } *gfx = (void *) gCrossfadeGfxState;
        gfx->phase += 2;
        if ((gfx->phase & 0xFFFF) != 0x10)
        {
            return;
        }
    }
    phaseDst = ws + 0x14B8;
    phaseSrc = ws + 0x14B4;
    *((u32 *) phaseDst) = ((*((u32 *) phaseSrc)) & 0x0F) | 0x80;
    updateObjectTree(*((void **) (ws + 0x184C)));
    updateObjectTree(*((void **) (ws + 0x185C)));
    updateObjectTree(*((void **) treeA));
    *((u32 *) frameCounter) += 1;
    updateObjectTree(*((void **) (ws + 0x1864)));
    t = *((void **) (ws + 0x1858));
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    t = *((void **) (ws + 0x1868));
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    t = *((void **) (ws + 0x186C));
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    t = *((void **) (ws + 0x1870));
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    t = *((void **) (ws + 0x1874));
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    t = *((void **) (ws + 0x1878));
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    t = *((void **) (ws + 0x187C));
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    t = *((void **) (ws + 0x1880));
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    t = *((void **) treeB);
    _call_via_r1((s32) t, *((s32 *) (((u8 *) t) + 0x24)));
    *((u8 *) ((actor + ((*((s16 *) (actor + 0x22))) * 2)) + 0x19)) = 0;
    {
        u32 *cb = gScriptStepCallbacks;
        _call_via_r3(actor + 0x18, actor + 0x22, 1, *cb);
    }
}
