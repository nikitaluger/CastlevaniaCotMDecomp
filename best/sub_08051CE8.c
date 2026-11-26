/* machine draft (m2c) for agbcc -mthumb-interwork -O2 -fno-strength-reduce, tried by autopilot */
#ifndef M2C_DEFINES
#define M2C_DEFINES
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_BITS_F32(expr) (m2c_bits = (u32)(expr), *(f32 *)&m2c_bits)
extern u32 m2c_bits;
#define M2C_PTR_FROM_F32(type, expr) ((type)(m2c_fbits = (expr), *(u32 *)&m2c_fbits))
extern f32 m2c_fbits;
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif

void sub_08051CE8(void *arg0) {
  void *__repair_entry_temp_r0_2;
    
    void *temp_r0_2;
    void *temp_r4;
    void *var_r3;

    temp_r4 = M2C_FIELD(arg0, M2C_UNK **, 0x30);
    if (temp_r4 != NULL) {
        M2C_FIELD(temp_r4, s8 *, 0x70) = 1;
        __repair_entry_temp_r0_2 = M2C_FIELD(temp_r4, M2C_UNK **, 0x2C);
        var_r3 = __repair_entry_temp_r0_2;
        if (__repair_entry_temp_r0_2 != NULL) {
            do {
                __repair_entry_temp_r0_2 = temp_r0_2;
                do { M2C_FIELD(var_r3, s8 *, 0x70) = 1; } while (0);
                do { temp_r0_2 = M2C_FIELD(var_r3, M2C_UNK **, 0x2C); } while (0);
                do { var_r3 = __repair_entry_temp_r0_2; } while (0);
            } while (temp_r0_2 != NULL);
        }
    }
}
