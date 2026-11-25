#ifndef M2C_DEFINES
#define M2C_DEFINES
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#endif

s32 sub_08000CE4(M2C_UNK *arg0, s32 arg1) {
    M2C_UNK *temp_r0 = *arg0;
    M2C_UNK *var_r2, *var_r3;
    if (temp_r0 != NULL) goto setup;
    goto block_6;
found:
    *var_r3 = M2C_FIELD(var_r2, M2C_UNK **, 0);
    M2C_FIELD(var_r2, s32 *, 4) = 0;
    return 1;
setup:
    var_r3 = arg0;
    var_r2 = temp_r0;
loop:
    if (M2C_FIELD(var_r2, s32 *, 4) == arg1) goto found;
    var_r3 = var_r2;
    var_r2 = M2C_FIELD(var_r2, M2C_UNK **, 0);
    if (var_r2 != NULL) goto loop;
block_6:
    return 0;
}
