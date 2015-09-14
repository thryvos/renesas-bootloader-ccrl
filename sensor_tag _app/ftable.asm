$INCLUDE "ftable.inc"
        .EXTERN _start
;        .EXTERN _f1
;       .EXTERN _f2
.jtext  .CSEG AT FLASH_TABLE                    ; Vector Name            Vector Address Relocated Vector Address
                                                ;-------------           -------------- ------------------------ 
         BR     !!_start                        ; RESET                         ;0x0000 ;0x0000
        .DB4    0xffffffff                      ; Reserved                      ;0x0002 ;0x0004
        .DB4    0xffffffff                      ; INTWDTI                       ;0x0004 ;0x0008
        .DB4    0xffffffff                      ; INTLVI                        ;0x0006 ;0x000C
         BR     !!_r_intc0_interrupt            ; INTP0                         ;0x0008 ;0x0010
        .DB4    0xffffffff                      ; INTP1                         ;0x000A ;0x0014
         BR     !!_r_intc2_interrupt            ; INTP2                         ;0x000C ;0x0018
        .DB4    0xffffffff                      ; INTP3                         ;0x000E ;0x001C
         BR     !!_r_intc4_interrupt            ; INTP4                         ;0x0010 ;0x0020
        .DB4    0xffffffff                      ; INTP5                         ;0x0012 ;0x0024
         BR     !!_r_uart2_interrupt_send       ; INTST2/INTCSI20/INTIIC20      ;0x0014 ;0x0028
         BR     !!_r_uart2_interrupt_receive    ; INTSR2                        ;0x0016 ;0x002C
        .DB4    0xffffffff                      ; INTSRE2                       ;0x0018 ;0x0030
        .DB4    0xffffffff                      ; INTDMA0                       ;0x001A ;0x0034
        .DB4    0xffffffff                      ; INTDMA1                       ;0x001C ;0x0038
        .DB4    0xffffffff                      ; INTCSI00/INTIIC00/INTST       ;0x001E ;0x003C
        .DB4    0xffffffff                      ; INTSR0                        ;0x0020 ;0x0040
        .DB4    0xffffffff                      ; INTSRE0/INTTM01H              ;0x0022 ;0x0044
         BR     !!_r_uart1_interrupt_send       ; INTST1                        ;0x0024 ;0x0048
         BR     !!_r_uart1_interrupt_receive    ; INTCSI11/INTIIC11/INTSR1      ;0x0026 ;0x004C
         BR     !!_r_uart1_interrupt_error      ; INTSRE1/INTTM03H              ;0x0028 ;0x0050
        .DB4    0xffffffff                      ; INTIICA0                      ;0x002A ;0x0054
         BR     !!_r_tau0_channel0_interrupt    ; INTTM00                       ;0x002C ;0x0058
         BR     !!_r_tau0_channel1_interrupt    ; INTTM01                       ;0x002E ;0x005C
         BR     !!_r_tau0_channel2_interrupt    ; INTTM02                       ;0x0030 ;0x0060
         BR     !!_r_tau0_channel3_interrupt    ; INTTM03                       ;0x0032 ;0x0064
        .DB4    0xffffffff                      ; INTAD                         ;0x0034 ;0x0068
        .DB4    0xffffffff                      ; INTRTC                        ;0x0036 ;0x006C
        .DB4    0xffffffff                      ; INTIT                         ;0x0038 ;0x0070
        .DB4    0xffffffff                      ; Reserved                      ;0x003A ;0x0074
        .DB4    0xffffffff                      ; Reserved                      ;0x003C ;0x0078
        .DB4    0xffffffff                      ; Reserved                      ;0x003E ;0x007C
        .DB4    0xffffffff                      ; Reserved                      ;0x0040 ;0x0080
         BR     !!_r_tau0_channel4_interrupt    ; INTTM04                       ;0x0042 ;0x0084
        .DB4    0xffffffff                      ; INTTM05                       ;0x0044 ;0x0088
        .DB4    0xffffffff                      ; INTTM06                       ;0x0046 ;0x008C
        .DB4    0xffffffff                      ; INTTM07                       ;0x0048 ;0x0090
        .DB4    0xffffffff                      ; Reserved                      ;0x004A ;0x0094
        .DB4    0xffffffff                      ; Reserved                      ;0x004C ;0x0098
        .DB4    0xffffffff                      ; Reserved                      ;0x004E ;0x009C
        .DB4    0xffffffff                      ; Reserved                      ;0x0050 ;0x00A0
        .DB4    0xffffffff                      ; Reserved                      ;0x0052 ;0x00A4
        .DB4    0xffffffff                      ; Reserved                      ;0x0054 ;0x00A8
        .DB4    0xffffffff                      ; Reserved                      ;0x0056 ;0x00AC
        .DB4    0xffffffff                      ; Reserved                      ;0x0058 ;0x00B0
        .DB4    0xffffffff                      ; Reserved                      ;0x005A ;0x00B4
        .DB4    0xffffffff                      ; Reserved                      ;0x005C ;0x00B8
        .DB4    0xffffffff                      ; INTMD                         ;0x005E ;0x00BC
        .DB4    0xffffffff                      ; Reserved                      ;0x0060 ;0x00C0
        .DB4    0xffffffff                      ; INTFL                         ;0x0062 ;0x00C4
        .DB4    0xffffffff                      ; BRK                           ;0x007E ;0x00C8

;            ~ Omitted ~
;.jtext2 .CSEG AT FLASH_TABLE+INTERRUPT_OFFSET
;         BR     !!_f1
;         BR     !!_f2
         