struct SceneState74B60 {
    u8 _0[0x10];
    u32 sceneFlags;
    u8 _1[0x14ED - 0x14];
    u8 counter;
    u8 _2[0x14FC - 0x14EE];
    u32 enableFlag;
    u8 _3[0x1728 - 0x1500];
    u32 primaryX;
    u32 primaryY;
    u8 _4[0x173A - 0x1730];
    u8 viewMode;
    u8 _5[0x174C - 0x173B];
    u32 secondaryX;
    u32 secondaryY;
    u8 _6[0x18C2 - 0x1754];
    u16 spriteAttrMask;
};
extern struct SceneState74B60 gMainWorkspace;

extern s32 sub_0806D450(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern s32 sub_08003740(void *, void *);
extern void sub_080C31E0(void *, u32);

/* One tick of a camera-followed entity: gated by sub_0806D450, syncs object
 * coordinates from the scene state, then despawns when the scene says so. */
void sub_08074B60(void *arg0) {
    void *self = arg0;
    u8 *object;
    u8 *objectData;
    u8 *sprite;
    u8 *objectDataSaved;

    object = *(u8 **)((u8 *)self + 0x6C);
    objectData = object + 4;
    sprite = *(u8 **)((u8 *)self + 0x38);
    objectDataSaved = objectData;
    if (sub_0806D450(self, sprite, objectData) != 0) return;

    if (object[0x55] == 0x33) {
        u32 v = *(u16 *)(sprite + 2) & 0xFFEF;
        *(u16 *)(sprite + 2) = (u16)v;
        {
            u8 *p = *(u8 **)((u8 *)self + 0x28);
            u8 *q = *(u8 **)(p + 0x38);
            *(u16 *)(sprite + 2) = (u16)((*(u16 *)(q + 2) & 0x10) | v);
        }
        *(u32 *)(object + 4) = gMainWorkspace.primaryX;
        *(u32 *)(objectData + 4) = gMainWorkspace.primaryY;
        if (gMainWorkspace.enableFlag == 0) {
            sub_080C31E0(self, *(u32 *)((u8 *)self + 0x24));
            return;
        }
    } else {
        *(u32 *)(object + 4) = gMainWorkspace.secondaryX;
        *(u32 *)(objectData + 4) = gMainWorkspace.secondaryY;
    }
    sub_0806D588(sprite, objectDataSaved);
    *(u16 *)sprite = (u16)(gMainWorkspace.spriteAttrMask | *(u16 *)((u8 *)self + 0x7C));
    if (sub_08003740(objectData + 0x1C, sprite) == 0) {
        sub_080C31E0(self, *(u32 *)((u8 *)self + 0x24));
        return;
    }
    if (gMainWorkspace.viewMode == 0x1C ||
        (gMainWorkspace.counter == 0 && gMainWorkspace.sceneFlags != 0)) {
        sub_080C31E0(self, *(u32 *)((u8 *)self + 0x24));
    }
}
