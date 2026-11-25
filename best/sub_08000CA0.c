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

s32 sub_08000CA0(M2C_UNK *arg0) {
    M2C_UNK *temp_r1;
    M2C_UNK *var_r2;
    M2C_UNK *var_r3;
    s32 temp_r0;

    temp_r1 = *arg0;
    if (temp_r1 == NULL) {
        return 0;
    }
    var_r3 = arg0;
    var_r2 = temp_r1;
    if (*var_r2 != NULL) {
        do {
            var_r3 = *var_r2;
            var_r2 = var_r3;
        } while (*var_r3 != NULL);
    }
    temp_r0 = M2C_FIELD(var_r2, s32 *, 4);
    M2C_FIELD(var_r2, s32 *, 4) = 0;
    *var_r3 = NULL;
    return temp_r0;
}
