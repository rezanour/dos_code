

     
     
     
     
     
     
     

   
   
   
   
   
   
   
   
   

   
   
   
   
   
   
   
   
   
   
   

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   

;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;%       Copyright (C) 1991, by WATCOM Systems Inc. All rights     %
;%       reserved. No part of this software may be reproduced      %
;%       in any form or by any means - graphic, electronic or      %
;%       mechanical, including photocopying, recording, taping     %
;%       or information storage and retrieval systems - except     %
;%       with the written permission of WATCOM Systems Inc.        %
;%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
;
; startup code for WATCOM C 386 Version 8.5
;
;       This must be assembled using the following command:
;               386asm cstart
;
;   NOTE: All C library data should be defined in CRWDATA.ASM -- That way
;         it's also available to ADS applications (who use ADSSTART.ASM).
;
        name    cstart

.387
.386p
        assume  nothing

        extrn   __CMain         : near
        extrn   __DOSseg__      : near

        extrn   _edata          : byte          ; end of DATA (start of BSS)
        extrn   _end            : byte          ; end of BSS (start of STACK)

        extrn    _dynend        : dword
        extrn    _curbrk        : dword
        extrn    _psp           : word
        extrn    _osmajor       : byte
        extrn    _osminor       : byte
        extrn    _STACKLOW      : dword
        extrn    _STACKTOP      : dword
        extrn    _child         : dword
        extrn   __no87          : word
        extrn    _Extender      : byte
        extrn    _Envptr        : dword
        extrn    _Envseg        : word
        extrn   __FPE_handler   : dword
        extrn  ___FPE_handler   : dword

DGROUP group _NULL,_AFTERNULL,CONST,_DATA,DATA,_emu_inits,_emu_init,_emu_inite,EXEC_S,EXEC,EXEC_E,XIB,XI,XIE,_BSS,STACK

; this guarantees that no function pointer will equal NULL
; (WLINK will keep segment 'BEGTEXT' in front)
; This segment must be at least 4 bytes in size to avoid confusing the
; signal function.

BEGTEXT  segment use32 word public 'CODE'
        assume  cs:BEGTEXT
forever: jmp    short forever
        nop
        nop
        nop
        nop
        assume  cs:nothing
BEGTEXT  ends

_TEXT   segment use32 word public 'CODE'

        assume  ds:DGROUP

_NULL   segment para public 'BEGDATA'
__nullarea label word
        db      01h,01h,01h,00h
        public  __nullarea
_NULL   ends

_AFTERNULL segment word public 'BEGDATA'
_AFTERNULL ends

CONST   segment word public 'DATA'
CONST   ends

_emu_inits      segment word public 'DATA'
_emu_start      label   word
_emu_inits      ends

_emu_init segment word public 'DATA'
__emulator      label   word
;;      dd      __init87emu
;;      dd      __fini87emu
_emu_init ends

_emu_inite    segment word public 'DATA'
_emu_end        label   word
_emu_inite    ends

EXEC_S  segment word public 'DATA'
EXEC_S  ends

EXEC    segment word public 'DATA'
EXEC    ends

EXEC_E  segment word public 'DATA'
EXEC_E  ends

XIB     segment word public 'DATA'
xistart label   byte
XIB     ends
XI      segment word public 'DATA'
XI      ends
XIE     segment word public 'DATA'
xiend   label   byte
XIE     ends


_DATA    segment word public 'DATA'
X_ERGO          equ     0
X_RATIONAL      equ     1
X_PHARLAP_V2    equ     2
X_PHARLAP_V3    equ     3
X_PHARLAP_V4    equ     4
X_INTEL         equ     5
__GDAptr   dd 0                 ; IGC and Intel Code Builder GDA address
__D16Infoseg   dw       0020h   ; DOS/4G kernel segment

        public  __GDAptr
        public  __D16Infoseg
_DATA    ends


DATA    segment word public 'DATA'
DATA    ends

_BSS          segment word public 'BSS'
_BSS          ends

STACK_SIZE      equ     1000h

STACK   segment para stack 'STACK'
        db      (STACK_SIZE) dup(?)
STACK   ends


        assume  nothing
        public  _cstart_
        public   __exit

        assume  cs:_TEXT

_cstart_ proc near
        jmp     short around

;
; copyright message
;
        db      "WATCOM C 386 Run-Time system. "
        db      "(c) Copyright by WATCOM Systems Inc. 1989, 1991."
        db      " All rights reserved."
;
; miscellaneous code-segment messages
;
ConsoleName     db      "con",00h
__saved_DS  dw  0               ; save area for DS for interrupt routines

around: sti                             ; enable interrupts

        assume  ds:DGROUP

PSP_SEG equ     24h
ENV_SEG equ     2ch

        and     esp,0fffffffch          ; make sure stack is on a 4 byte bdry
        mov     ebx,esp                 ; get sp
        mov      _STACKTOP,ebx          ; set stack top
        mov      _curbrk,ebx            ; set first available memory location
        mov     ax,PSP_SEG              ; get segment address of PSP
        mov      _psp,ax                ; save segment address of PSP
;
;       get DOS & Extender version number
;
        mov     ebx,'PHAR'              ; set ebx to 0
        sub     eax,eax                 ; set eax to 0
        mov     ah,30h
        int     21h                     ; modifies eax,ebx,ecx,edx
        mov      _osmajor,al
        mov      _osminor,ah
        mov     ecx,eax                 ; remember DOS version number
        sub     esi,esi                 ; offset 0 for environment strings
        mov     edi,81H                 ; DOS command buffer es:edi
        shr     eax,16                  ; get top 16 bits of eax
        cmp     ax,'DX'                 ; if top 16 bits = "DX"
        jne     not_pharlap             ; then its pharlap
        sub     bl,'0'                  ; - save major version number
        mov     al,bl                   ; - (was in ascii)
        mov     bx,14h                  ; - get value of Phar Lap data segment
        mov     cx,ENV_SEG              ; - PharLap environment segment
        jmp     short know_ext1         ; else
not_pharlap:                            ; - see if Intel Code Builder
        cmp     ax,'BC'                 ; - if Intel Code Builder
        jne     not_Intel               ; - ... then
GDA_PSPA equ    16                      ; - offset into GDA to PSP address
GDA_LDPT equ    28                      ; - offset into GDA to load address
        mov     __GDAptr,edx            ; - save address of GDA
        mov     esi,edx                 ; - get address of GDA
        mov     edx,GDA_LDPT[esi]       ; - get application load point address
        mov     ebx,esp                 ; - calc amount of memory to keep
        sub     ebx,edx                 ; - ...
        mov     ah,4Ah                  ; - resize to minimum memory
        int     21h                     ; - ...
        mov     bx,ds                   ; - just use ds (FLAT model)
        mov      _psp,ds                ; - save segment address of PSP
        mov     eax,GDA_PSPA[esi]       ; - get address of PSP
        add     edi,eax                 ; - add address of PSP
        sub     esi,esi                 ; - zero esi
        mov     si,02ch[eax]            ; - get environment segment into si
        shl     esi,4                   ; - convert to flat address
        mov     cx,ds                   ; - segment to access environment area
        mov     al,X_INTEL              ; - indicate Intel Code Builder
know_ext1:jmp   short know_extender     ; else
not_Intel:                              ; -
        mov     dx,78h                  ; - see if Rational DOS/4G
        mov     ax,0FF00h               ; - ...
        int     21h                     ; - ...
        cmp     al,0                    ; - ...
        je      short not_DOS4G         ; - quit if not Rational DOS/4G
        mov     ax,gs                   ; - get segment address of kernel
        cmp     ax,0                    ; - if not zero
        je      short rat9              ; - then
        mov     __D16Infoseg,ax         ; - - remember it
rat9:                                   ; - endif
        mov     al,X_RATIONAL           ; - indicate Rational 32-bit Extender
        mov     bx,ds                   ; - just use ds (FLAT model)
        mov      _psp,es                ; - save segment address of PSP
        mov     cx,es:[02ch]            ; - get environment segment into cx
        jmp     short know_extender     ; else
not_DOS4G:                              ; -
        mov     dx,ds                   ; - save ds
        mov     cx,PSP_SEG              ; - get PSP segment descriptor
        mov     ds,cx                   ; - ... into ds
        mov     cx,ds:[02ch]            ; - get environment segment into cx
        mov     ds,dx                   ; - restore ds
        mov     bx,17h                  ; - get writeable code segment for Ergo
        mov     al,X_ERGO               ; - indicate Ergo OS/386
know_extender:                          ; endif
        mov      _Extender,al           ; record extender type
        mov     es,bx                   ; get access to code segment
        mov     es:__saved_DS,ds        ; save DS value
        mov      _Envptr,esi            ; save address of environment strings
        mov      _Envseg,cx             ; save segment of environment area
        push    esi                     ; save address of environment strings
;
;       copy command line into bottom of stack
;
        mov     es, _psp                ; point to PSP
        mov     edx,offset DGROUP:_end
        add     edx,0FH
        and     dl,0F0H
        sub     ecx,ecx
        mov     cl,es:[edi-1]           ; get length of command
        cld                             ; set direction forward
        mov     al,' '
        rep     scasb
        lea     esi,-1[edi]
        mov     edi,edx
        mov     bx,es
        mov     dx,ds
        mov     ds,bx
        mov     es,dx                   ; es:edi is destination
        je      noparm
        inc     ecx
        rep     movsb
noparm: sub     al,al
        stosb                           ; store NULLCHAR
        stosb                           ; assume no pgm name
        pop     esi                     ; restore address of environment strings
        dec     edi                     ; back up pointer 1
        push    edi                     ; save pointer to pgm name
        push    edx                     ; save ds(stored in dx)
        mov     ds,es: _Envseg          ; get segment addr of environment area
        sub     ebp,ebp                 ; assume "no87" env. var. not present
L1:     mov     eax,[esi]               ; get first 4 characters
        or      eax,20202020h           ; map to lower case
        cmp     eax,'78on'              ; check for "no87"
        jne     short L2                ; skip if not "no87"
        cmp     byte ptr 4[esi],'='     ; make sure next char is "="
        jne     short L2                ; no
        inc     ebp                     ; - indicate "no87" was present
L2:     cmp     byte ptr [esi],0        ; end of string ?
        lodsb
        jne     L2                      ; until end of string
        cmp     byte ptr [esi],0        ; end of all strings ?
        jne     L1                      ; if not, then skip next string
        lodsb
        inc     esi                     ; point to program name
        inc     esi                     ; . . .
;
;       copy the program name into bottom of stack
;
L3:     cmp     byte ptr [esi],0        ; end of pgm name ?
        movsb                           ; copy a byte
        jne     L3                      ; until end of pgm name
        pop     ds                      ; restore ds
        pop     esi                     ; restore address of pgm name
        mov     ebx,esp                 ; end of stack in data segment

        assume  ds:DGROUP
        mov     __no87,bp               ; set state of "no87" enironment var
        mov      _STACKLOW,edi          ; save low address of stack
        mov      _dynend,ebx            ; set top of dynamic memory area

        mov     ecx,offset DGROUP:_end  ; end of _BSS segment (start of STACK)
        mov     edi,offset DGROUP:_edata; start of _BSS segment
        sub     ecx,edi                 ; calc # of bytes in _BSS segment
        mov     dl,cl                   ; save bottom 2 bits of count in edx
        shr     ecx,2                   ; calc # of dwords
        sub     eax,eax                 ; zero the _BSS segment
        rep     stosd                   ; ...
        mov     cl,dl                   ; get bottom 2 bits of count
        and     cl,3                    ; ...
        rep     stosb                   ; ...

        mov     eax,offset DGROUP:_emu_start
        mov     edx,offset DGROUP:_emu_end
        cmp     edx,eax                 ; if 387 emulator present
        je      short no_emu            ; then
          call  [eax]                   ; - initialize emulator
no_emu:                                 ; endif
        call    initrtns                ; call initializer routines
        mov     eax,offset DGROUP:_end  ; cmd buffer pointed at by EAX
        add     eax,0FH
        and     al,0F0H
        mov     edx,esi                 ; point EDX at program name
	sub	ebp,ebp			; ebp=0 indicate end of ebp chain
        call    __CMain
_cstart_ endp

;       don't touch AL in __exit_, it has the return code

 __exit  proc near
        jmp     short   ok

        public   __exit_with_msg

; input: EAX - pointer to message to print
;        EDX - exit code

 __exit_with_msg:
        push    edx                     ; save return code
        push    eax                     ; save address of msg
        mov     edx,offset ConsoleName
        mov     ax,03d01h               ; write-only access to screen
        int     021h
        mov     bx,ax                   ; get file handle
        pop     edx                     ; restore address of msg
        mov     esi,edx                 ; get address of msg
        cld                             ; make sure direction forward
L4:     lodsb                           ; get char
        cmp     al,0                    ; end of string?
        jne     L4                      ; no
        mov     ecx,esi                 ; calc length of string
        sub     ecx,edx                 ; . . .
        dec     ecx                     ; . . .
        mov     ah,040h                 ; write out the string
        int     021h                    ; . . .
        pop     eax                     ; restore return code
ok:
        push    eax                     ; save return code
        mov     eax,offset DGROUP:_emu_start
        mov     edx,offset DGROUP:_emu_end
        cmp     edx,eax                 ; if 387 emulator present
        je      no_emu1                 ; then
          call  4[eax]                  ; - finalize emulator
no_emu1:                                ; endif
        pop     eax                     ; restore return code
        mov     ah,04cH                 ; DOS call to exit with return code
        int     021h                    ; back to DOS
 __exit  endp

initrtns proc   near
        push    esi                     ; save esi
        mov     esi,offset DGROUP:xistart; get start addr of table
        mov     edi,offset DGROUP:xiend  ; get end   addr of table
init1:    cmp   esi,edi                 ; loop through the table
          jae   init9                   ; - quit if done
          sub   edi,4                   ; - point to start of entry
          mov   eax,[edi]               ; - get address of routine
          or    eax,eax                 ; - check for null entry
          je    init1                   ; - try next one if it is null
          call  eax                     ; - call initializer routine
        jmp     init1                   ; endloop
init9:  pop     esi                     ; restore esi
        ret                             ; return
initrtns endp


        public  __GETDS
__GETDS proc    near
        mov     ds,cs:__saved_DS        ; load saved DS value
        ret                             ; return
__GETDS endp

_TEXT   ends

        end     _cstart_
