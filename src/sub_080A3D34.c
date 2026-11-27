/* machine draft (m2c) for agbcc -mthumb-interwork -O2, tried by autopilot */
#ifndef M2C_DEFINES
#define M2C_DEFINES
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif

extern void sub_08011650(s32);
extern void sub_08015974(void *);
extern void unlinkAndFreeObject(void *);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Actor destructor: free every sprite object it owns, then release the rest. */
void sub_080A3D34(void *arg0) {
    s32 sprite;
    void *info;
    void *fxBlock;

    sprite = M2C_FIELD(arg0, s32 *, 0x38);
    info = M2C_FIELD(arg0, void **, 0x3C);
    fxBlock = (u8 *)info + 0x48;
    if (M2C_FIELD(info, s32 *, 0x28) != 0) {
        unlinkAndFreeObject((void *)M2C_FIELD(info, s32 *, 0x28));
    }
    if (M2C_FIELD(fxBlock, s32 *, 0x50) != 0) {
        unlinkAndFreeObject((void *)M2C_FIELD(fxBlock, s32 *, 0x50));
    }
    if (M2C_FIELD(fxBlock, s32 *, 0x54) != 0) {
        unlinkAndFreeObject((void *)M2C_FIELD(fxBlock, s32 *, 0x54));
    }
    if (M2C_FIELD(fxBlock, s32 *, 0x58) != 0) {
        unlinkAndFreeObject((void *)M2C_FIELD(fxBlock, s32 *, 0x58));
    }
    sub_08011650(sprite);
    if (M2C_FIELD(info, s32 *, 0x2C) != 0) {
        sub_08015974((void *)M2C_FIELD(info, s32 *, 0x2C));
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, M2C_FIELD(info, s32 *, 0x24));
}
