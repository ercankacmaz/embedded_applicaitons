        MODULE  ?delay
        PUBWEAK __delay

        SECTION .text:CODE:NOROOT:REORDER(2)

        CALL_GRAPH_ROOT __delay, "interrupt"
        NOCALL __delay

;       Arg: Number of cycles (min 32)
__delay:
        LSRS    R1, R0, #3
        SUBS    R1, R1, #3

L1:	B       L2
L2:     B       L3
L3:     NOP
        SUBS    R1, R1, #1
        BNE     L1
        
        AND     R1, R0, #7
        TST     R1, #1
        BEQ     L4
        B       L4

L4:     TST     R1, #2
        BEQ     L5
        NOP
        B       L5

L5:     TST     R1, #4
        BEQ     L7
        NOP
        B       L6
L6:     B       L7

L7:     BX      LR

        END
