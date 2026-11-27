extern void moveEntityWithCollision(void *, s32);
extern void copyPoseAttrs(void *, void *);
extern void setAnimationFrame(s32, void *, u16, u8);
extern void stepAnimationTrack(s32, void *);
extern void sub_0803C674(u16 *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_080CF2D8[];

void sub_0803C048(u8 *self) {
    s32 parent = *(s32 *)(self + 0x38);
    u8 *obj = *(u8 **)(self + 0x3C);
    u8 *objSub = obj + 0x34;
    u8 *objState = obj + 0x48;
    s32 *handlerTable;

    moveEntityWithCollision(obj, 0x16C1);
    if (*(u16 *)(obj + 2) & 4) {
        *(u8 *)(objState + 4) = 2;
        {
            void *dst = *(void **)(obj + 0x28);
            u8 *poseTable = D_080CF2D8;
            copyPoseAttrs(dst, poseTable + 0x10);
        }
        setAnimationFrame(parent, objSub, 7, 0);
    }
    stepAnimationTrack(parent, objSub);
    if (*(u8 *)objSub & 2) {
        *(u8 *)(objState + 4) = 3;
        setAnimationFrame(parent, objSub, 10, 0);
        if (*(u16 *)((u8 *)parent + 2) & 0x10) {
            *(s32 *)(obj + 8) += 0x210000;
        } else {
            *(s32 *)(obj + 8) -= 0x210000;
        }
        *(s32 *)(objState + 8) = *(s32 *)(obj + 8);
        copyPoseAttrs(*(void **)(obj + 0x28), (void *)(D_080CF2D8 + *(u8 *)(objState + 4) * 8));
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        handlerTable = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *handlerTable);
    }
    sub_0803C674((u16 *)parent, obj, objState);
}
