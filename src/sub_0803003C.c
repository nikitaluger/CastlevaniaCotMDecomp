extern void sub_08011368(void *, void *, s32, s32);
extern void sub_0803010C(void *, void *, s32);
extern void sub_080C31E0(void *, s32);

struct SubObj { u8 _p[0x6C]; u16 flags; };
struct Work { u8 _p0[0x48]; struct SubObj *partA; struct SubObj *partB; };

// Attack animation step: set a flag on both sub-objects, play animation frame
// 0x1F, spawn effects at fixed points in the animation, and on animation end
// switch the entity to its next script state.
void sub_0803003C(void *entity) {
    void *sprite = *(void **)((u8 *)entity + 0x38);
    struct Work *work = *(struct Work **)((u8 *)entity + 0x3C);
    void *animator = (u8 *)work + 0x34;
    work->partA->flags = (u16)(work->partA->flags | 0x20);
    work->partB->flags = (u16)(work->partB->flags | 0x20);
    sub_08011368(sprite, animator, 0x1F, 0);
    if (*(s32 *)((u8 *)animator + 0x04) == 1) {
        switch (*(u8 *)((u8 *)animator + 0x01) - 1) {
            case 2:
                sub_0803010C(sprite, work, 0);
                break;
            case 3:
                sub_0803010C(sprite, work, 1);
                sub_0803010C(sprite, work, 2);
                break;
        }
    }
    if (*(u8 *)animator & 0x02) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
