extern void updateObjectTree(void *p);
extern void sub_080C31E0(void *a, void *b);

/* Advances a global phase counter and, when it wraps to 0x10, despawns the
 * effect's tracked sub-objects along with the object itself. */
/* Advances the global crossfade phase: updates three effect-tree roots and bumps the frame counter at gMainWorkspace+0x1894, then adds 0x40 (mode 2) or 0x100 to the phase accumulator at +0x14A8 and publishes (phase >> 8) as u16 to gCrossfadeGfxState+8. When the phase reaches 0x10 the effect has faded out, so invoke the cleanup callback at +0x24 of each of the 15 tracked sub-objects (gMainWorkspace+0x184C..+0x1888, stride 4) and finally of the effect itself. */ void advanceCrossfadePhase(void *effect)
{
    u8 *ws = (u8*)0x02025FF0;
    u8 *gfx;
    u32 phase;

    updateObjectTree(*(void**)(ws + 0x1854));
    updateObjectTree(*(void**)(ws + (0xC3 << 5)));
    (*(u32*)(ws + 0x1894))++;
    updateObjectTree(*(void**)(ws + 0x1888));

    if (*(s32*)(ws + 0x0C) == 2) {
        *(u32*)(ws + 0x14A8) += 0x40;
    } else {
        *(u32*)(ws + 0x14A8) += 0x100;
    }

    gfx = (u8*)0x03000830;
    ws = (u8*)0x02025FF0;
    phase = *(u32*)(ws + 0x14A8) >> 8;
    *(u16*)(gfx + 8) = (u16)phase;
    if ((u16)phase == 0x10) {
        void *p;
        p = *(void**)(ws + 0x184C); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1850); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1854); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1858); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x185C); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + (0xC3 << 5)); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1864); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1868); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x186C); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1870); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1874); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1878); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x187C); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + (0xC4 << 5)); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(ws + 0x1888); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        sub_080C31E0(effect, *(void**)((u8*)effect + 0x24));
    }
}
