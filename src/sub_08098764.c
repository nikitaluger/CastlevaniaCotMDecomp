/* Update an object's world/screen position and state flags for its layer,
 * firing its callback when the state value changes. */
void postDisplaySprite(s32, s32, s32, s32, s32);
void sub_080988DC(void *);

struct FlagWord { u8 _0[2]; u16 flags; };
struct Position { u8 _0[8]; s32 x; s32 y; };
struct ChildState { u8 _0[0x58]; u8 state; };
struct Object {
    u8 _0[4];
    s32 f04[2];
    u8 _0C[4];
    void *callback;
    void *childA;
    void *childB;
    u8 layer;
    u8 _1D[0xC];
    s8 prevState;
    u8 _2A[2];
    s32 posX;
    s32 posY;
    u8 stateByte;
    s8 state;
};
struct S_02025FF0 { u8 _0[0x18A8]; u8 activeLayer; };
extern struct S_02025FF0 gMainWorkspace;
struct Entry90 { u32 x; u32 y; u8 _[0x38]; };
struct FlagRecord { u16 flag; u8 _[0x3E]; };
struct Flags90 { u8 _0[0x1260]; struct FlagRecord recs[1]; };
struct Entries90 { u8 _0[0x1278]; struct Entry90 entries[1]; };
extern u8 gCameraState[];

void sub_08098764(struct FlagWord *flagsOut, struct Position *src, struct Object *obj) {
    u32 t;
    s32 idx;

    obj->posX = src->x;
    obj->posY = src->y;

    if (obj->state == -1)
        flagsOut->flags &= 0xFFEF;
    else
        flagsOut->flags |= 0x10;

    if (obj->childA != NULL)
        ((struct ChildState *)obj->childA)->state = obj->stateByte;
    if (obj->childB != NULL)
        ((struct ChildState *)obj->childB)->state = obj->stateByte;

    if (obj->stateByte != 0) {
        u8 *base = gCameraState;
        ((struct Flags90 *)(base + (obj->layer << 6)))->recs[0].flag |= 0x2000;
        return;
    }
    {
        u8 *base = gCameraState;
        ((struct Flags90 *)(base + (obj->layer << 6)))->recs[0].flag &= 0xDFFF;
    }

    {
        s8 v35 = obj->state;
        if (v35 != obj->prevState) {
            t = (u32)~v35;
            idx = (((0u - t) | t) >> 31) << 2;
            {
                u8 *arr = (u8 *)obj + 4;
                idx = *(s32 *)(arr + idx);
            }
            if (idx != 0 && obj->callback != NULL) {
                postDisplaySprite(1, idx, (s32)obj->callback, 0x400, 0x10);
            }
            sub_080988DC(obj);
        }
    }
    *(u8 *)((u8 *)obj + 0x29) = *(u8 *)((u8 *)obj + 0x35);

    ((struct Entries90 *)gCameraState)->entries[obj->layer].x =
        (((struct Entries90 *)gCameraState)->entries[gMainWorkspace.activeLayer + 1].x + 0x8000 & 0xFFFF0000) - obj->posX + 0x400000;
    ((struct Entries90 *)gCameraState)->entries[obj->layer].y =
        (((struct Entries90 *)gCameraState)->entries[gMainWorkspace.activeLayer + 1].y + 0xFFFF8000 & 0xFFFF0000) - obj->posY + 0x400000;
}
