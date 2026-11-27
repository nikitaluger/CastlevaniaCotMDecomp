void setEntityForm(void *, void *, s32);
void spawnEntity(void *, s32, s32, s32);
void spawnKind2CEntity(void *, s32, s32, s32);
void sub_08086E28(void);

struct S_02025FF0 { u8 _0x000[0x14ED]; u8 b; };
extern struct S_02025FF0 gMainWorkspace;

/* Set animation 8 on animObj from srcObj, spawn a type-3 entity at pos, and,
   when the global state byte at gMainWorkspace+0x14ED is 0x37, sync it and run
   the extra state handler. */
void sub_0806B280(void *entity, void *srcObj, void *animObj, void *pos) {
    setEntityForm(srcObj, animObj, 8);
    spawnKind2CEntity(entity, 3, *(u32 *)pos, *(u32 *)((u8 *)pos + 4));
    if (gMainWorkspace.b == 0x37) {
        spawnEntity(entity, 0x37, 0xA, 0x12);
        sub_08086E28();
    }
}
