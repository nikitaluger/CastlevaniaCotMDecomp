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

s32 sub_08000CC8(void **arg0, s32 arg1) {
    void *var_r2;

    var_r2 = *arg0;
    if (var_r2 != NULL) {
loop_1:
        if (M2C_FIELD(var_r2, s32 *, 4) == arg1) {
            return 1;
        }
        var_r2 = M2C_FIELD(var_r2, void **, 0);
        if (var_r2 == NULL) {
            goto block_4;
        }
        goto loop_1;
    }
block_4:
    return 0;
}
