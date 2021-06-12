;Имеется n предметов, веса которых равны a1, a2,…,aN (целые числа от 1 до 10^8). 
;Выбрать из них такое подмножество, чтобы их вес был равен заданному числу M,
;либо сказать, что такого подмножества не существует. N не превышает 30.
include H:\masm32\include\masm32rt.inc
 
NUM_THREADS=4                                   ;число порождаемых потоков
;-переменные----------------------------------------------;
.data                                           ;начало сегмента данных
    fmt_int BYTE "%d ", 0                       ;строка формата для вывод целых через пробел
    infmt_int BYTE "%d", 0                      ;строка формата для чтения целых чисел
    fmt_str BYTE "%s", 0                        ;строка формата для вывода строк
    fmt_strd BYTE "d %s", 0                     ;строка формата для вывода строки от имени четвертого потока
    fmt_strc BYTE "c %s", 0                     ;строка формата для вывода строки от имени третьего потока
    fmt_strb BYTE "b %s", 0                     ;строка формата для вывода строки от имени второго потока
    fmt_stra BYTE "a %s", 0                     ;строка формата для вывода строки от имени первого потока
    MsgOk BYTE "OK!", 13, 10, 0                 ;сообщение об успешном поиске
    MsgFail BYTE "Fail!", 13, 10, 0             ;сообщение о неуспешном поиске
    nextline BYTE 13, 10, 0                     ;строка для перевода строки
    threadHandles DWORD NUM_THREADS DUP (0)     ;массив для сохранения дескрипторов потоков
    A DWORD 30 DUP (0)                          ;массив для данных о весе предметов
    N DWORD 0                                   ;количество предметов
    M DWORD 0                                   ;искомый вес набора предметов
    K DWORD 1                                   ;здесь будет 2^N
 
ARGS STRUCT                                     ;тип записи с аргументами для процедуры потока
    first DWORD ?                               ;начальнное состояние перебора
    last DWORD ?                                ;верхняя граница перебора
    res DWORD ?                                 ;результат перебора
ARGS ENDS                                       ;
 
arguments ARGS NUM_THREADS DUP (<>)             ;массив записей с аргументами для процедуры потока
 
.code                                           
 
Shift PROC, s:DWORD                             ;входной параметр текущее состояние перебора
    mov eax, s                                  ;помещаем состояние в регистр eax
    mov ecx, 0                                  ;записываем 0 в ecx
    n1:                                         ;
        bt eax, ecx                             ;проверяем состояние бита ecx в eax
        jc n2                                   ;если бит 1 переходим к метке n2
        inc ecx                                 ;иначе увеличиваем ecx
        jmp n1                                  ;переходим к n1
    n2:                                         ;
        btr eax, ecx                            ;сбрасываем бит
        jnc n3                                  ;если бит не был 1 переходим к n3
        inc ecx                                 ;иначе увеличиваем ecx
        jmp n2                                  ;переходим к n2
    n3:                                         ;
    bts eax, ecx                                ;устанавливаем бит
    ret                                     
Shift ENDP                      
 
 
threadProc PROC pArgs: DWORD                    ;входной параметр указатель на структуру с аргументами процедуры
    mov esi, pArgs                              ;помещаем указатель на запись с аргументами в esi
    mov eax, (ARGS PTR [esi]).first             ;помещаем начальное число в eax
    mov ebx, (ARGS PTR [esi]).last              ;помещаем конечное число в ebx
    .WHILE eax < ebx                            ;пока eax < ebx
        lea edi, A                              ;помещаем в edi адрес массива данных
        mov edx, 0                              ;обнуляем edx, в нём будет храниться общая масса выбранного набора
        mov ecx, 0                              ;обнуляем ecx, он будет счётчиком битов при переборе
        .WHILE ecx < N                          ;пока ecx меньше количества предметов в общем наборе
            bt eax, ecx                         ;проверяем бит ecx в eax
            jnc notc                            ;если он 0, то переход к notc
                add edx, DWORD PTR [edi]        ;иначе добавление массы элемента к общей массе проверяемого набора
            notc:                               ;
            inc ecx                             ;увеличиваем ecx
            add edi, SIZEOF DWORD               ;продвигаем указатель edi к следующему элементу массива
        .ENDW                                   ;
        .IF edx == M                            ;если сумма проверяемого набора равна искомой
            mov (ARGS PTR [esi]).res, eax       ;помещаем набор в параметр res входной структуры
            ret                                 ;возврат
        .ELSEIF edx > M                         ;иначе, если сумма проверяемого набора больше искомой
            invoke Shift, eax                   ;вызываем процедуру сокращающую перебор
        .ELSE                                   ;иначе
            inc eax                             ;просто увеличиваем ecx
        .ENDIF                                  ;
    .ENDW                                       ;
    mov eax, -1                                 ;если ничего не нашлось, то код возврата для потока
    mov (ARGS PTR [esi]).res, eax               ;пишем его в структуру
    ret                                         
threadProc ENDP                             
    
 
PrintResult PROC, r:DWORD                       ;входной параметр, результирующий набор
    lea edi, A                                  ;загружаем адрес массива данных в edi
    mov ecx, 0                                  ;обнуляем ecx
    mov eax, r                                  ;помещаем в eax результирующий набор
    .WHILE ecx < N                              ;пока ecx меньше числа элементов общего набора
        bt eax, ecx                             ;проверяем бит ecx в eax
        jnc notc                                ;если бит не равен 1, то переход к notc
            pushad                              ;иначе сохраняем содержимое регистров в стеке перед вызовом crt_printf
            invoke crt_printf, ADDR fmt_int, DWORD PTR [edi]    ;печатаем элемент
            popad                               ;восстанавливаем регистры из стека
        notc:                                   ;
        inc ecx                                 ;увеличиваем ecx
        add edi, SIZEOF DWORD                   ;продвигаем указатель edi к следующему элементу массива
    .ENDW                                       
    ret                                         
PrintResult ENDP
 
 
main PROC                                   
 
    invoke crt_scanf, ADDR infmt_int, ADDR N    
    lea esi, A                                  
    mov ecx, 0                                  
    mov edi, K                                  
    .WHILE ecx < N                              
        push ecx                                ;сохраняем значение ecx
        invoke crt_scanf, ADDR infmt_int, esi   ;читаем число и пишем его по адресу в esi
        add esi, SIZEOF DWORD                   ;продвигаем указатель массива к следующему элементу
        shl edi, 1                              ;умножаем edi на 2
        pop ecx                                 ;восстанавливаем ecx
        inc ecx                         
    .ENDW                                       
    mov K, edi                                  
    invoke crt_scanf, ADDR infmt_int, ADDR M    
 
;Создаём параллельные потоки в количестве NUM_THREADS штук
    mov ecx, NUM_THREADS                        
    mov eax, OFFSET arguments                   ;пишем адрес записи с аргументами для очередного потока в eax
    mov esi, OFFSET threadHandles               ;пишем адрес, куда будет помещен дескриптор очередного созданного потока в esi
    mov ebx, 0                                  ;в ebx стартовое значение перебора
    mov edx, K                                  ;в edx пишем 2^N
    shr edx, 1                                  ;и делим пополам, это будет конечное значение перебора (итого на 4 части)
    shr edx, 1
    shr edx, 1
    @mk_threads:                                ;
        mov (ARGS PTR [eax]).first, ebx         ;первый аргумент для процедуры потока
        mov (ARGS PTR [eax]).last, edx          ;второй аргумент для процедуры потока
        mov (ARGS PTR [eax]).res, 0             ;обнуляем результат
        pushad                                  ;сохраняем регистры в стеке
        invoke CreateThread, 0, 0, threadProc, eax, 0, 0    ;запускаем поток
        mov [esi], eax                          ;сохраняем дескриптор (handle)
        popad                                   ;восстанавливаем регистры из стека
        add esi, SIZEOF DWORD                   ;адрес ячейки для сохранения следующего дескриптора
        add eax, SIZEOF ARGS                    ;переходим к адресу следующей записи с аргументами
        add ebx, edx                            ;стартовое значение заменяем конечным
        shl edx, 1                              ;конечное увеличиваем вдвое
    loop @mk_threads                            ;делаем так 4 раза
    
;приостановим главный поток до момента, пока не завершатся все запущенные потоки
    invoke WaitForMultipleObjects, NUM_THREADS, OFFSET threadHandles, TRUE, INFINITE    ;ждём завершения всех вызванных потоков
    
;-печатаем-результат----------------------------;
    mov esi, OFFSET arguments                   ;в esi пишем указатель на массив аргументов потоков
    mov eax, (ARGS PTR [esi]).res               ;в eax записываем значение результата выданного потоком
    .IF eax != -1                               ;если первый поток выдал положительный результат
        invoke PrintResult, eax                 ;вызываем процедуру печати для его результата
        invoke crt_printf, ADDR fmt_stra, ADDR MsgOk    ;и сообщение что всё OK
        exit                                    ;выходим из программы
    .ENDIF                                      ;
    add esi, SIZEOF ARGS                        ;иначе, передвигаем указатель к следующему элементу
    mov eax, (ARGS PTR [esi]).res               ;помещаем его результат в eax
    .IF eax != -1                               ;если результат положительный
        invoke PrintResult, eax                 ;печатаем его
        invoke crt_printf, ADDR fmt_strb, ADDR MsgOk    ;говорим ОК
        exit                                    ;выходимиз программы
    .ENDIF
    
    add esi, SIZEOF ARGS                        ;иначе, передвигаем указатель к следующему элементу
    mov eax, (ARGS PTR [esi]).res               ;помещаем его результата в eax
    .IF eax != -1                               ;если результат положительный
        invoke PrintResult, eax                 ;печатаем его
        invoke crt_printf, ADDR fmt_strc, ADDR MsgOk    ;говорим ОК
        exit                                    ;выходимиз программы
    .ENDIF  
    add esi, SIZEOF ARGS                        ;иначе, передвигаем указатель к следующему элементу
    mov eax, (ARGS PTR [esi]).res               ;помещаем его результата в eax
    .IF eax != -1                               ;если результат положительный
        invoke PrintResult, eax                 ;печатаем его
        invoke crt_printf, ADDR fmt_strd, ADDR MsgOk    ;говорим ОК
        exit                                    ;выходим из программы
    .ENDIF  
    
    invoke crt_printf, ADDR fmt_str, ADDR MsgFail   ;иначе программа дошла до этого места, говорим FAIL
    exit                                        ;выходим из программы
main ENDP                                       ;
;-----------------------------------------------;
END main                                        ;
;-----------------------------------------------;