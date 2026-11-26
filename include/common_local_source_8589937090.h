/* context.h for DRACULA AGB1: shared by every function. Agents grow it with edit_context:
 * add a prototype or struct the moment you work one out, so the next function benefits. */

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

/* struct layout used by sub_08005AB0 (offsets from m2c):
 * 0x13: u8 counter
 * 0x14: u32 pointer
 * 0x16: u16 index
 * 0x19: u32 pointer
 */
struct Foo {
    u8 unk_0x13;
    u32 unk_0x14;
    u16 unk_0x16;
    u32 unk_0x19;
};

extern vu32 D_0200A260;
extern vu32 D_0200A258;
typedef volatile s32 vs32;
typedef int s32_bool;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

extern void *sub_080015E0(s32 mask, s32 object);
