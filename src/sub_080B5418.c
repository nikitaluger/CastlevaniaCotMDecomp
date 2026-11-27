extern void forceAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_08102CAC[];
extern u8 gMainObjTimerCallbacks[];

/* Links or unlinks a companion entity: when linked, mirror its position and
 * shared sprite flags, select its graphics state, run the script command and
 * clear the script-state byte; when unlinked, clear those flags and bytes. */
void sub_080B5418(void *entity)
{
    void *world = entity;
    void *sprite = *((void **) (((u8 *) world) + 0x38));
    void *companion = *((void **) (((u8 *) world) + 0x3C));
    void *animDesc = 0x34 + companion;
    void *gfxSlot = companion + 0x48;
    void *sourceObj = *((void **) ((*((void **) (((u8 *) world) + 0x28))) + 0x3C));
    u8 linked = *(((u8 *) world) + 0x4C);

    if (linked != 0)
    {
        unsigned int t;
        u8 zero;
        u8 spriteFlags = *((u8 *) (((u8 *) sprite) + 0x2A));
        u32 newFlags = 0x40;
        newFlags |= spriteFlags;
        *((u8 *) (((u8 *) sprite) + 0x2A)) = (u8) newFlags;
        t = (*((u16 *) (((u8 *) sprite) + 0x02))) & 0xFFEF;
        zero = 0;
        *((u16 *) (((u8 *) sprite) + 0x02)) = t;
        *((u16 *) (((u8 *) sprite) + 0x02)) = (u16) (((*((u16 *) (((u8 *) (*((void **) ((*((void **) (((u8 *) world) + 0x28))) + 0x38)))) + 0x02))) & 0x10) | t);
        *((s32 *) (((u8 *) companion) + 0x08)) = *((s32 *) (((u8 *) sourceObj) + 0x08));
        *((s32 *) (((u8 *) companion) + 0x0C)) = *((s32 *) (((u8 *) sourceObj) + 0x0C));
        *((u8 *) ((*((void **) (((u8 *) companion) + 0x28))) + 1)) = D_08102CAC[0];
        *((u8 *) ((*((void **) (((u8 *) companion) + 0x48))) + 1)) = D_08102CAC[1];
        *((u8 *) ((*((void **) (((u8 *) gfxSlot) + 0x04))) + 1)) = D_08102CAC[2];
        t = 2;
        forceAnimationFrame(sprite, animDesc, 0x78, 0);
        *((s8 *) ((((u8 *) world) + ((s32) ((*((s16 *) (((u8 *) world) + 0x22))) * 2))) + 0x19)) = zero;
        { void **fnaddr = (void **) gMainObjTimerCallbacks; sub_080C31E4(((u8 *) world) + 0x18, ((u8 *) world) + 0x22, (s32) (*fnaddr)); }
    }
    else
    {
        *((u8 *) (((u8 *) sprite) + 0x2A)) = (*((u8 *) (((u8 *) sprite) + 0x2A))) & 0xBF;
        *((u8 *) ((*((void **) (((u8 *) companion) + 0x28))) + 1)) = 0;
        *((u8 *) ((*((void **) (((u8 *) companion) + 0x48))) + 1)) = 0;
        *((u8 *) ((*((void **) (((u8 *) gfxSlot) + 0x04))) + 1)) = 0;
    }
}
