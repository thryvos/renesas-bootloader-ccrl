$INCLUDE "ftable.inc"

    .public _f1
_f1 .equ    (FLASH_TABLE + INTERRUPT_OFFSET + (0 * 4))
    .public _f2
_f2 .equ    (FLASH_TABLE + INTERRUPT_OFFSET + (1 * 4))