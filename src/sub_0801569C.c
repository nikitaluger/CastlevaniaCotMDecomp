void *sub_08015914(void);

struct Work_1569C {
    u16 field_0;
    u8 _pad[0x16];
    void *field_18;
    u8 _pad2[2];
    u16 field_1E;
};

/* Lazily allocate a small sub-object from the pool and fill its header from
 * the given 16-bit parameters; on failure clear the work flag and the
 * sub-object pointer. */
s32 sub_0801569C(void *self, void *volatile *subObjPtr, u16 field4, u16 field6, u16 field8, u16 fieldA)
{
    struct Work_1569C *work = *(struct Work_1569C **)((u8 *)self + 0x3C);
    if (*subObjPtr == NULL) {
        void *allocated = sub_08015914();
        *subObjPtr = allocated;
        if (allocated == NULL) {
            work->field_0 = (work->field_0 & 0xFFF7) | 1;
            work->field_18 = NULL;
            return 0;
        }
    }
    {
        u8 *sub = (u8 *)*subObjPtr;
        u16 zero = 0;
        sub[1] = 1;
        *(u16 *)((u8 *)*subObjPtr + 2) = zero;
    }
    *(u16 *)((u8 *)*subObjPtr + 4) = field4;
    *(u16 *)((u8 *)*subObjPtr + 6) = field6;
    *(u16 *)((u8 *)*subObjPtr + 8) = field8;
    *(u16 *)((u8 *)*subObjPtr + 0xA) = fieldA;
    *(void **)((u8 *)*subObjPtr + 0xC) = self;
    work->field_1E = 0x12C;
    return 1;
}
