;������� n ���������, ���� ������� ����� a1, a2,�,aN (����� ����� �� 1 �� 10^8). 
;������� �� ��� ����� ������������, ����� �� ��� ��� ����� ��������� ����� M,
;���� �������, ��� ������ ������������ �� ����������. N �� ��������� 30.
include H:\masm32\include\masm32rt.inc
 
NUM_THREADS=4                                   ;����� ����������� �������
;-����������----------------------------------------------;
.data                                           ;������ �������� ������
    fmt_int BYTE "%d ", 0                       ;������ ������� ��� ����� ����� ����� ������
    infmt_int BYTE "%d", 0                      ;������ ������� ��� ������ ����� �����
    fmt_str BYTE "%s", 0                        ;������ ������� ��� ������ �����
    fmt_strd BYTE "d %s", 0                     ;������ ������� ��� ������ ������ �� ����� ���������� ������
    fmt_strc BYTE "c %s", 0                     ;������ ������� ��� ������ ������ �� ����� �������� ������
    fmt_strb BYTE "b %s", 0                     ;������ ������� ��� ������ ������ �� ����� ������� ������
    fmt_stra BYTE "a %s", 0                     ;������ ������� ��� ������ ������ �� ����� ������� ������
    MsgOk BYTE "OK!", 13, 10, 0                 ;��������� �� �������� ������
    MsgFail BYTE "Fail!", 13, 10, 0             ;��������� � ���������� ������
    nextline BYTE 13, 10, 0                     ;������ ��� �������� ������
    threadHandles DWORD NUM_THREADS DUP (0)     ;������ ��� ���������� ������������ �������
    A DWORD 30 DUP (0)                          ;������ ��� ������ � ���� ���������
    N DWORD 0                                   ;���������� ���������
    M DWORD 0                                   ;������� ��� ������ ���������
    K DWORD 1                                   ;����� ����� 2^N
 
ARGS STRUCT                                     ;��� ������ � ����������� ��� ��������� ������
    first DWORD ?                               ;���������� ��������� ��������
    last DWORD ?                                ;������� ������� ��������
    res DWORD ?                                 ;��������� ��������
ARGS ENDS                                       ;
 
arguments ARGS NUM_THREADS DUP (<>)             ;������ ������� � ����������� ��� ��������� ������
 
.code                                           
 
Shift PROC, s:DWORD                             ;������� �������� ������� ��������� ��������
    mov eax, s                                  ;�������� ��������� � ������� eax
    mov ecx, 0                                  ;���������� 0 � ecx
    n1:                                         ;
        bt eax, ecx                             ;��������� ��������� ���� ecx � eax
        jc n2                                   ;���� ��� 1 ��������� � ����� n2
        inc ecx                                 ;����� ����������� ecx
        jmp n1                                  ;��������� � n1
    n2:                                         ;
        btr eax, ecx                            ;���������� ���
        jnc n3                                  ;���� ��� �� ��� 1 ��������� � n3
        inc ecx                                 ;����� ����������� ecx
        jmp n2                                  ;��������� � n2
    n3:                                         ;
    bts eax, ecx                                ;������������� ���
    ret                                     
Shift ENDP                      
 
 
threadProc PROC pArgs: DWORD                    ;������� �������� ��������� �� ��������� � ����������� ���������
    mov esi, pArgs                              ;�������� ��������� �� ������ � ����������� � esi
    mov eax, (ARGS PTR [esi]).first             ;�������� ��������� ����� � eax
    mov ebx, (ARGS PTR [esi]).last              ;�������� �������� ����� � ebx
    .WHILE eax < ebx                            ;���� eax < ebx
        lea edi, A                              ;�������� � edi ����� ������� ������
        mov edx, 0                              ;�������� edx, � �� ����� ��������� ����� ����� ���������� ������
        mov ecx, 0                              ;�������� ecx, �� ����� ��������� ����� ��� ��������
        .WHILE ecx < N                          ;���� ecx ������ ���������� ��������� � ����� ������
            bt eax, ecx                         ;��������� ��� ecx � eax
            jnc notc                            ;���� �� 0, �� ������� � notc
                add edx, DWORD PTR [edi]        ;����� ���������� ����� �������� � ����� ����� ������������ ������
            notc:                               ;
            inc ecx                             ;����������� ecx
            add edi, SIZEOF DWORD               ;���������� ��������� edi � ���������� �������� �������
        .ENDW                                   ;
        .IF edx == M                            ;���� ����� ������������ ������ ����� �������
            mov (ARGS PTR [esi]).res, eax       ;�������� ����� � �������� res ������� ���������
            ret                                 ;�������
        .ELSEIF edx > M                         ;�����, ���� ����� ������������ ������ ������ �������
            invoke Shift, eax                   ;�������� ��������� ����������� �������
        .ELSE                                   ;�����
            inc eax                             ;������ ����������� ecx
        .ENDIF                                  ;
    .ENDW                                       ;
    mov eax, -1                                 ;���� ������ �� �������, �� ��� �������� ��� ������
    mov (ARGS PTR [esi]).res, eax               ;����� ��� � ���������
    ret                                         
threadProc ENDP                             
    
 
PrintResult PROC, r:DWORD                       ;������� ��������, �������������� �����
    lea edi, A                                  ;��������� ����� ������� ������ � edi
    mov ecx, 0                                  ;�������� ecx
    mov eax, r                                  ;�������� � eax �������������� �����
    .WHILE ecx < N                              ;���� ecx ������ ����� ��������� ������ ������
        bt eax, ecx                             ;��������� ��� ecx � eax
        jnc notc                                ;���� ��� �� ����� 1, �� ������� � notc
            pushad                              ;����� ��������� ���������� ��������� � ����� ����� ������� crt_printf
            invoke crt_printf, ADDR fmt_int, DWORD PTR [edi]    ;�������� �������
            popad                               ;��������������� �������� �� �����
        notc:                                   ;
        inc ecx                                 ;����������� ecx
        add edi, SIZEOF DWORD                   ;���������� ��������� edi � ���������� �������� �������
    .ENDW                                       
    ret                                         
PrintResult ENDP
 
 
main PROC                                   
 
    invoke crt_scanf, ADDR infmt_int, ADDR N    
    lea esi, A                                  
    mov ecx, 0                                  
    mov edi, K                                  
    .WHILE ecx < N                              
        push ecx                                ;��������� �������� ecx
        invoke crt_scanf, ADDR infmt_int, esi   ;������ ����� � ����� ��� �� ������ � esi
        add esi, SIZEOF DWORD                   ;���������� ��������� ������� � ���������� ��������
        shl edi, 1                              ;�������� edi �� 2
        pop ecx                                 ;��������������� ecx
        inc ecx                         
    .ENDW                                       
    mov K, edi                                  
    invoke crt_scanf, ADDR infmt_int, ADDR M    
 
;������ ������������ ������ � ���������� NUM_THREADS ����
    mov ecx, NUM_THREADS                        
    mov eax, OFFSET arguments                   ;����� ����� ������ � ����������� ��� ���������� ������ � eax
    mov esi, OFFSET threadHandles               ;����� �����, ���� ����� ������� ���������� ���������� ���������� ������ � esi
    mov ebx, 0                                  ;� ebx ��������� �������� ��������
    mov edx, K                                  ;� edx ����� 2^N
    shr edx, 1                                  ;� ����� �������, ��� ����� �������� �������� �������� (����� �� 4 �����)
    shr edx, 1
    shr edx, 1
    @mk_threads:                                ;
        mov (ARGS PTR [eax]).first, ebx         ;������ �������� ��� ��������� ������
        mov (ARGS PTR [eax]).last, edx          ;������ �������� ��� ��������� ������
        mov (ARGS PTR [eax]).res, 0             ;�������� ���������
        pushad                                  ;��������� �������� � �����
        invoke CreateThread, 0, 0, threadProc, eax, 0, 0    ;��������� �����
        mov [esi], eax                          ;��������� ���������� (handle)
        popad                                   ;��������������� �������� �� �����
        add esi, SIZEOF DWORD                   ;����� ������ ��� ���������� ���������� �����������
        add eax, SIZEOF ARGS                    ;��������� � ������ ��������� ������ � �����������
        add ebx, edx                            ;��������� �������� �������� ��������
        shl edx, 1                              ;�������� ����������� �����
    loop @mk_threads                            ;������ ��� 4 ����
    
;������������ ������� ����� �� �������, ���� �� ���������� ��� ���������� ������
    invoke WaitForMultipleObjects, NUM_THREADS, OFFSET threadHandles, TRUE, INFINITE    ;��� ���������� ���� ��������� �������
    
;-��������-���������----------------------------;
    mov esi, OFFSET arguments                   ;� esi ����� ��������� �� ������ ���������� �������
    mov eax, (ARGS PTR [esi]).res               ;� eax ���������� �������� ���������� ��������� �������
    .IF eax != -1                               ;���� ������ ����� ����� ������������� ���������
        invoke PrintResult, eax                 ;�������� ��������� ������ ��� ��� ����������
        invoke crt_printf, ADDR fmt_stra, ADDR MsgOk    ;� ��������� ��� �� OK
        exit                                    ;������� �� ���������
    .ENDIF                                      ;
    add esi, SIZEOF ARGS                        ;�����, ����������� ��������� � ���������� ��������
    mov eax, (ARGS PTR [esi]).res               ;�������� ��� ��������� � eax
    .IF eax != -1                               ;���� ��������� �������������
        invoke PrintResult, eax                 ;�������� ���
        invoke crt_printf, ADDR fmt_strb, ADDR MsgOk    ;������� ��
        exit                                    ;��������� ���������
    .ENDIF
    
    add esi, SIZEOF ARGS                        ;�����, ����������� ��������� � ���������� ��������
    mov eax, (ARGS PTR [esi]).res               ;�������� ��� ���������� � eax
    .IF eax != -1                               ;���� ��������� �������������
        invoke PrintResult, eax                 ;�������� ���
        invoke crt_printf, ADDR fmt_strc, ADDR MsgOk    ;������� ��
        exit                                    ;��������� ���������
    .ENDIF  
    add esi, SIZEOF ARGS                        ;�����, ����������� ��������� � ���������� ��������
    mov eax, (ARGS PTR [esi]).res               ;�������� ��� ���������� � eax
    .IF eax != -1                               ;���� ��������� �������������
        invoke PrintResult, eax                 ;�������� ���
        invoke crt_printf, ADDR fmt_strd, ADDR MsgOk    ;������� ��
        exit                                    ;������� �� ���������
    .ENDIF  
    
    invoke crt_printf, ADDR fmt_str, ADDR MsgFail   ;����� ��������� ����� �� ����� �����, ������� FAIL
    exit                                        ;������� �� ���������
main ENDP                                       ;
;-----------------------------------------------;
END main                                        ;
;-----------------------------------------------;