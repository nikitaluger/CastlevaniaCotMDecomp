void sub_0806A7AC(void *, void *, s32);
void sub_0806D2A0(void *, s32, s32, s32);
void sub_0806E114(void *, s32, s32, s32);
void sub_08086E28(void);

struct S_02025FF0 { u8 _0x000[0x14ED]; u8 b; };
extern struct S_02025FF0 gMainWorkspace;

/* Set animation 8 on animObj from srcObj, spawn a type-3 entity at pos, and,
   when the global state byte at gMainWorkspace+0x14ED is 0x37, sync it and run
   the extra state handler. */
void sub_0806B280(void *entity, void *srcObj, void *animObj, void *pos) {
    sub_0806A7AC(srcObj, animObj, 8);
    sub_0806E114(entity, 3, *(u32 *)pos, *(u32 *)((u8 *)pos + 4));
    if (gMainWorkspace.b == 0x37) {
        sub_0806D2A0(entity, 0x37, 0xA, 0x12);
        sub_08086E28();
    }
}
