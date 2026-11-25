/* Update one entity: keep its sprite in view, run its animation/state script
 * and motion, then store camera-relative screen coordinates on the sprite. */
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08013B5C(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_0866D6FC[];
extern u32 D_08671BDC;

struct SpriteFlags { u8 flag; };   /* sprite + 0x2A */
struct MotionFlags { u16 flag; };  /* motion + 0x00 */

void sub_0801CDCC(u8 *entity) {
    u8 *sprite;        /* display object at entity+0x38 (screen coords, flags) */
    u8 *motion;        /* physics object at entity+0x3C (world coords, flags) */
    u8 *motionState;   /* animation state at motion+0x34 */
    u8 *animEntry;     /* per-frame data at entity + index*2 */
    u8 *coordTable;    /* D_02021E90 */
    u8 *xCoordTable;   /* coordTable + 0x1278 */
    u8 *camState;      /* D_02025FF0 */
    u32 layer;         /* scroll/camera layer index */
    u32 camX;
    u32 camY;
    u32 stateByte;
    u8 *stateTable;    /* entity + 0x18 */
    s32 animOffset;
    u32 *scriptTable;  /* D_08671BDC */

    sprite = *(u8 **)(entity + 0x38);
    motion = *(u8 **)(entity + 0x3C);
    motionState = motion + 0x34;

    if (sub_0805F9B4(*(s32 *)(motion + 8), *(s32 *)(motion + 0xC)) == 1) {
        *(u8 *)((u8 *)*(void **)(motion + 0x28) + 1) = 0;
        ((struct SpriteFlags *)(sprite + 0x2A))->flag &= 0xBF;
    } else {
        *(u8 *)((u8 *)*(void **)(motion + 0x28) + 1) = 1;
        ((struct SpriteFlags *)(sprite + 0x2A))->flag |= 0x40;
    }

    if (*(u16 *)(entity + 0x64) & 1) {
        ((struct MotionFlags *)motion)->flag |= 1;
    }

    if (*(u16 *)motion & 1) {
        *(u8 *)((u8 *)*(void **)(motion + 0x28) + 1) = 0;
        if (*((u8 *)entity + *(s16 *)(entity + 0x22) * 2 + 0x1A) != 1) {
            *((u8 *)entity + *(s16 *)(entity + 0x22) * 2 + 0x1B) = 0;
            scriptTable = (u32 *)&D_08671BDC;
            sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 1, (s32)*scriptTable);
        }
    }

    if (sub_08013B5C(sprite, motion) != 0) goto common;

    *(u32 *)(entity + 0x14) = (u32)D_0866D6FC;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    animEntry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(animEntry + 0x19) = *(u8 *)(animEntry + 0x19) + 1;
    animOffset = *(s16 *)(entity + 0x22) * 2;
    stateTable = entity;
    stateTable += 0x18;
    stateByte = *(u8 *)((u32)stateTable + (u32)animOffset);
    sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + 0x14) + stateByte * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if (*(u16 *)(entity + 2) & 0x8000) return;
    sub_080113A8(sprite, motionState);
    sub_0801165C(motion, 0);

common:
    coordTable = D_02021E90;
    camState = D_02025FF0;
    camState += 0x18A8;
    layer = ((u32)*camState + 1) * 0x40;
    xCoordTable = coordTable + 0x1278;
    camX = *(u32 *)(xCoordTable + layer);
    *(u32 *)(sprite + 0x14) = *(u32 *)(motion + 8) - ((camX + 0x8000) & 0xFFFF0000);
    layer = ((u32)*camState + 1) * 0x40;
    coordTable += 0x127C;
    camY = *(u32 *)(coordTable + layer);
    *(u32 *)(sprite + 0x18) = *(u32 *)(motion + 0xC) - ((camY + 0xFFFF8000) & 0xFFFF0000);
}
