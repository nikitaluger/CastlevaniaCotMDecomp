s32 sub_08014090(s16);
void sub_0801565C(u8 *, s32 *, s32 *);
void sub_0801572C(u8 *, s32 *, s32 *);

struct S_02025FF0 { u8 _0x000[0x189C]; u32 w; };
extern struct S_02025FF0 gMainWorkspace;

/* Update an entity's sprite attribute from its kind and countdown, clear a
 * flag on two related objects, then either report it available or run the
 * matching timed-cleanup helper. */
s32 sub_0801576C(u16 *gfx, u8 *entity, u8 *other1, u8 *other2, s32 *held1, s32 *held2) {
    if (*(u16 *)(entity + 0) & 1) return 0;
    if (*(u16 *)(entity + 0) & 0xC) {
        if (*(u16 *)(entity + 0) & 4) {
            if (*(s16 *)(entity + 0x1E) > 0x3C || !(gMainWorkspace.w & 2)) {
                *(u16 *)(gfx + 0) = (*(u16 *)(gfx + 0) & 0xFFF) | 0xD000;
            }
        } else {
            if (*(s16 *)(entity + 0x1E) > 0x3C || !(gMainWorkspace.w & 2)) {
                *(u16 *)(gfx + 0) = (*(u16 *)(gfx + 0) & 0xFFF) | 0xC000;
            }
        }
        if (other1 != 0) {
            other1[1] &= 0xFE;
        }
        if (other2 != 0) {
            other2[1] &= 0xFE;
        }
    }
    if (sub_08014090(*(s16 *)(entity + 0x1C)) == 1) {
        return 1;
    }
    if (*(u16 *)(entity + 0) & 0xC) {
        if (*(u16 *)(entity + 0) & 4) {
            sub_0801565C(entity, held1, held2);
        } else {
            sub_0801572C(entity, held1, held2);
        }
        return 1;
    }
    return 0;
}
