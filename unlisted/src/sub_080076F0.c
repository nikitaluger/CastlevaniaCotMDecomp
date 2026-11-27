extern void updateObjectTree(void *p);
extern void sub_080C31E0(void *a, void *b);

/* Advances a global phase counter and, when it wraps to 0x10, despawns the
 * effect's tracked sub-objects along with the object itself. */
void sub_080076F0(void *obj)
{
    u8 *state = (u8*)0x02025FF0;
    u8 *reg;
    u32 phase;

    updateObjectTree(*(void**)(state + 0x1854));
    updateObjectTree(*(void**)(state + (0xC3 << 5)));
    (*(u32*)(state + 0x1894))++;
    updateObjectTree(*(void**)(state + 0x1888));

    if (*(s32*)(state + 0x0C) == 2) {
        *(u32*)(state + 0x14A8) += 0x40;
    } else {
        *(u32*)(state + 0x14A8) += 0x100;
    }

    reg = (u8*)0x03000830;
    state = (u8*)0x02025FF0;
    phase = *(u32*)(state + 0x14A8) >> 8;
    *(u16*)(reg + 8) = (u16)phase;
    if ((u16)phase == 0x10) {
        void *p;
        p = *(void**)(state + 0x184C); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1850); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1854); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1858); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x185C); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + (0xC3 << 5)); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1864); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1868); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x186C); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1870); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1874); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1878); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x187C); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + (0xC4 << 5)); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        p = *(void**)(state + 0x1888); sub_080C31E0(p, *(void**)((u8*)p + 0x24));
        sub_080C31E0(obj, *(void**)((u8*)obj + 0x24));
    }
}
