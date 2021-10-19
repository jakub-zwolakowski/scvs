# TrustInSoft results

## accfree

### accfree_e01

OK (UB detected)

### accfree_e02

OK (UB detected)

### accfree_e03

OK (UB detected)

## accsig

### accsig_e01

SKIP - CONCURRENT - SIGNALS

## addrescape

### addrescape_e01

MISPLACED UB

### addrescape_e02

MISPLACED UB

### addrescape_e03

NO UB (escaping address not used)

## alignconv

### alignconv_e01

NIY (pointer alignment)

### alignconv_e02

OK (no false positive)

## argcomp

### argcomp_e01

OK (UB detected)

### argcomp_e02

OK (UB detected)

### argcomp_e03

OK (UB detected)

### argcomp_e04

OK (UB detected)

## asyncsig

### asyncsig_e01

SKIP - CONCURRENT - SIGNALS

### asyncsig_e02

SKIP - CONCURRENT - SIGNALS

### asyncsig_e03

SKIP - CONCURRENT - SIGNALS

## boolasgn

### boolasgn_e01

NO UB (infinite loop)

### boolasgn_e02

NO UB (infinite loop)

### boolasgn_e03

OK (no false positive)

### boolasgn_e04

OK (no false positive)

### boolasgn_e05

OK (no false positive)

### boolasgn_e06

NO UB

### boolasgn_e07

OK (no false positive)

## chreof

### chreof_e01

CHECK

### chreof_e02

CHECK

## chrsgnext

### chrsgnext_e01

CHECK

## dblfree

### dblfree_e01

NO UB ('free(NULL)' does nothing - we can repeat it as many times as we want)

### dblfree_e02

NO UB (no double free happening in any possible program execution, see https://cigix.me/c17#7.22.3.5.p3)

## diverr

### diverr_e01

OK (UB detected)

### diverr_e02

OK (UB detected)

### diverr_e03

OK (UB detected)

### diverr_e04

OK (UB detected)

## fileclose

### fileclose_e01

CHECK (not closing a file is not UB)

### fileclose_e02

NO UB (resource leak is not UB), STILL: DETECTED IN THE LOG

## filecpy

### filecpy_e01

TODO

## funcdecl

### funcdecl_e01

OK (UB detected)

### funcdecl_e02

OK (UB detected)

### funcdecl_e03

OK (UB detected)

### funcdecl_e04

CHECK

### funcdecl_ex1

OK (no false positive)

## intoflow

### intoflow_e01

NO UB (TYPO?... There cannot be a signed overflow on an 'unsigned int' value.)

OK (UB detected), NOTE: changed 'add(unsigned int ui)' to 'add(int ui)'

### intoflow_e02

OK (no false positive)

### intptrconv_005

OK (detected a different UB)

MISPLACED UB

## intptrconv

### intptrconv_e01

OK (detected a different UB)

MISPLACED UB

### intptrconv_e02

NO UB (pointer created, but not used)

CHECK

### intptrconv_ex1

OK (no false positive)

### intptrconv_ex2

OK (no false positive)

## inverrno

### inverrno_e01

### inverrno_e02

### inverrno_e03

### invfmtstr_002

OK (UB detected)

## invfmtstr

### invfmtstr_e01

OK (UB detected)

## invptr

### invptr_e01

OK (UB detected)

### invptr_e02

OK (no false positive)

### invptr_e03

OK (no false positive)

### invptr_e04

OK (found the UB)

MISPLACED UB

OK (found the UB), NOTE: made the test abstract to find the desired UB

### invptr_e05

OK (no false positive)

### invptr_e06

OK (UB detected)

### invptr_e07

OK (no false positive)

### invptr_e08

OK (UB detected)

### invptr_e09

OK (no false positive)

### invptr_e10

OK (UB detected)

### invptr_e11

OK (no false positive)

### invptr_e12

TODO

## ioileave

### ioileave_e01

NIY (interleaving reads and writes to a file)

## liberr

### liberr_e01

CHECK

### liberr_e02

OK (no false positive)

### liberr_ex1

OK (no false positive)

### liberr_ex2

OK (no false positive)

## libmod

### libmod_e01

NIY (modifying the string returned from setlocale)

### libmod_e02

NIY (modifying the string returned from localeconv)

### libmod_e03

NIY (modifying the string returned from getenv)

### libmod_e04

NIY (modifying the string returned from strerror)

## libptr

### libptr_e01

OK (UB detected)

### libptr_e02

### libptr_e03

### libptr_e04

OK (UB detected)

### libptr_e05

## libuse

### libuse_e01

### libuse_e02

### libuse_e03

## nonnullstr

### nonnullstr_e01

OK (UB detected)

### nonnullstr_e02

MISPLACED UB (reading uninitialized memory)

### nonnullstr_e03

MISPLACED UB (reading uninitialized memory)

## nullref

### nullref_e01

OK (UB detected)

## padcomp

### padcomp_e01

CHECK

## ptrcomp

### ptrcomp_e01

OK (UB detected in the log)

## ptrobj

### ptrobj_e01

OK (UB detected)

### ptrobj_ex1

OK (no false positive)

### ptrobj_ex2

TYPO! (there is a typo in the example - 'subrtact')

OK (no false positive), NOTE: there was a typo in the example! s/'subrtact'/'subtract'/g

## resident

### resident_e01

NIY (defining reserved identifier errno)

### resident_e02

NIY (defining reserved symbol _RESIDENT_HEADER_H)

### resident_e03

OK (no false positive)

### resident_e04

NIY (defining reserved file scope identifier _limit)

### resident_e05

OK (no false positive)

### resident_e06

HALF! OK (detected reusing identifier SIZE_MAX), NIY (defining reserved identifier INTFAST16_LIMIT_MAX)

### resident_e07

OK (no false positive)

### resident_e08

NIY (defining reserved identifier 'malloc()' and 'free()')

### resident_e09

OK (no false positive)

## restrict

### restrict_e01

NO UB (the memory zones passed to memcpy do not overlap)

CHECK

OK (UB detected), NOTE: the memory zones passed to memcpy made to overlap

### restrict_e02

NIY (qualifier 'restrict')

## sigcall

### sigcall_e01

SKIP - CONCURRENT - SIGNALS

## signconv

### signconv_e01

CHECK

## sizeofptr

### sizeofptr_e01

CHECK

## strmod

### strmod_e01

OK (UB detected)

### strmod_e02

OK (no false positive)

### strmod_e03

OK (UB detected)

### strmod_e04

OK (UB detected)

### strmod_e05

OK (UB detected)

### strmod_e06

OK (no false positive)

## swtchdflt

### swtchdflt_e01

## syscall

### syscall_e01

SKIP

system()

### syscall_e02

SKIP

system()

## taintformatio

### taintformatio_e01

OK (UB detected)

### taintformatio_e02

OK (UB detected)

## taintnoproto

### taintnoproto_e01

NO UB (maybe the behavior is unexpected, but this code is correct - the type of 'int array[]' is complete, so can be used as an argument to 'sizeof' - see https://cigix.me/c17#6.7.6.2.p4)

CHECK

## taintsink

### taintsink_e01

OK (UB detected)

### taintsink_e02

OK (UB detected)

## taintstrcpy

### taintstrcpy_e01

OK (UB detected)

## uninitref

### uninitref_e01

OK (UB detected)

### uninitref_e02

OK (UB detected)

### uninitref_e03

OK (UB detected)

### uninitref_e04

OK (UB detected)

MISPLACED UB

## usrfmt

### usrfmt_e01

### usrfmt_e02

### usrfmt_e03

OK (UB detected), NOTE: there is more than one problem here

### usrfmt_e04

OK (no false positive)

### xfilepos_002

NIY (checking if 'fsetpos' argument always comes from 'fgetpos')

## xfilepos

### xfilepos_e01

NIY (checking if 'fsetpos' argument always comes from 'fgetpos')

## xfree

### xfree_e01

### xfree_e02
