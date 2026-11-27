extern void uploadPendingSpriteGraphic(void *, void *);
extern s32 sub_08014328(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866DD28[];

/* Update the entity's sprite pose from its motion state: set graphic flags,
 * take the disabled path or advance the script when idle, then apply
 * table-driven coordinate offsets. */
void sub_080336B4(u8 *entity)
{
    u32 tableX;
    u32 tableY;
    u8 *sprite;
    u8 *motion;
    unsigned int index2;
    u8 *posePtr;

    sprite = *((u8 **)(entity + 0x38));
    motion = *((u8 **)(entity + 0x3C));

    *((u16 *)sprite) = (*((u16 *)sprite) & 0xFFF) | (((*((u16 *)(motion + 0x22))) + 8) << 12);

    if (*((u8 *)(entity + 0x80)) == 0)
    {
        struct Z { u32 w; u8 b; } z = {0, 0};
        u8 *attrPtr = *((u8 **)(motion + 0x28));
        *((u8 *)(attrPtr + 1)) = z.b;
        *((u8 *)(sprite + 0x2A)) &= 0xBF;
        return;
    }

    uploadPendingSpriteGraphic((void *)*((u32 *)(entity + 0x28)), (void *)*((u32 *)(motion + 0x28)));

    posePtr = entity + 0x22;
    if (sub_08014328((void *)*((u32 *)(entity + 0x28)), sprite, motion) == 0)
    {
        s16 poseIndex;
        s32 byteOffset;
        u8 *poseBase;

        *((u32 *)(entity + 0x14)) = (u32)D_0866DD28;
        *((u16 *)(entity + 0x22)) = (*((u16 *)posePtr)) + 1;
        poseIndex = *((s16 *)posePtr);
        *((u8 *)((entity + (poseIndex * 2)) + 0x19)) += 1;
        poseIndex = *((s16 *)posePtr);
        byteOffset = poseIndex * 2;
        poseBase = entity + 0x18;
        sub_080C31E0(entity, *((void **)((*((u32 *)(entity + 0x14))) + ((2 * (*((u8 *)(poseBase + byteOffset)))) * 2))));
        *((u16 *)posePtr) = (*((u16 *)posePtr)) - 1;
    }

    {
        u8 *pt = gCameraState;
        u8 *pb = gMainWorkspace;
        u8 *pt1;
        u32 idx;
        u32 v1;

        pb += 0x18A8;
        idx = (((u32)(*pb)) + 1) << 6;
        pt1 = pt + 0x1278;
        v1 = *((u32 *)(pt1 + idx));
        tableX = v1;
        *((u32 *)(sprite + 0x14)) = (*((u32 *)(motion + 0x08))) - ((tableX + 0x8000) & 0xFFFF0000);

        index2 = (1 + ((u32)(*pb))) << 6;
        idx = index2;
        pt += 0x127C;
        v1 = (tableY = *((u32 *)(pt + idx)));
        *((u32 *)(sprite + 0x18)) = (*((u32 *)(motion + 0x0C))) - ((v1 + 0xFFFF8000) & 0xFFFF0000);
    }
}
