# TrustInSoft results

## accfree

### accfree_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### accfree_e02

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### accfree_e03

MISPLACED "REQUIRED DIAGNOSTIC"

TrustInSoft correctly detects another Undefined Behavior before reaching the "diagnostic required" line in this example. The call to `realloc()` is invalid, as `c_str1` is not a reallocable address (the declaration is `char s[MAX_LEN];`, then `s` is passed through the `c_str1` argument). See detailed results either with the GUI (click on the *Inspect with TrustInSoft Analyzer* button in the *Summary* tab) or look directly in the Analyzer Log tab:

```bash
tests/accfree/accfree_e03.c:76:[kernel] warning: Unclassified alarm: assert \warning("free expects a free-able address");
                  possibly invalid address {{ &s }} for free.
                  stack: realloc :: tests/accfree/accfree_e03.c:76 <-
                         f :: tests/accfree/accfree_e03.c:71 <-
                         main
```

Now, if we correct this Undefined Behavior, we stumble at another problem - the expected Undefined Behavior, as described in the test, actually does not exist. There is no possible execution of this program where a double free happens. This is the decription in the example:

```C
 * Rule: [accfree]
 * Description: diagnostic is required because realloc may free c_str1 
 *              when it returns NULL, resulting in c_str1 being freed 
 *              twice.
 * Diagnostic: required on line 78
```

But in the [C17 section *The realloc function* in paragraph 3](https://cigix.me/c17#7.22.3.5.p3), we can read:
> If size is nonzero and memory for the new object is not allocated, the old object is not deallocated.

The example's description directly contradicts the C17 standard, which states that if this call to `realloc` returns `NULL` then it cannot free `c_str1` in the same time.

SIDE NOTE: Possible confusion may have been caused by the following statement in the C17 standard:
> If size is zero and memory for the new object is not allocated, it is implementation-defined whether the old object is deallocated.

For comparison an example with `size` equal zero was added and analyzed. In this case however TrustInSoft warns about yet another Undefined Behavior, caused by calling `realloc` with `size` equal zero - this is explicitly considered Undefined Behavior in the upcoming C2X standard.

## accsig

Signal handling is out of scope.

### accsig_e01

OUT OF SCOPE

TrustInSoft does not handle signals.

## addrescape

### addrescape_e01

MISPLACED "REQUIRED DIAGNOSTIC"

What happens at the "diagnostic required" line - assigning an *escaping address* to a global variable - is not Undefined Behavior.

TrustInSoft correctly detects Undefined Behavior here when the *escaping address* is actually used - on line 72 in the statement `puts(p);`.

### addrescape_e02

MISPLACED "REQUIRED DIAGNOSTIC"

What happens at the "diagnostic required" line - returning an *escaping address* from a function - is not Undefined Behavior.

TrustInSoft correctly detects Undefined Behavior here when the *escaping address* is actually used - on line 65 in the expression `!init_array()`.

### addrescape_e03

NO UB

Holding an *escaping address* in a local variable is not Undefined Behavior. As this *escaping address* is never actually used, there is no Undefined Behavior in this example.

## alignconv

### alignconv_e01

NOT IMPLEMENTED YET

This is Undefined Behavior according to the C Standard - indeed there is no guarantee neither that `(int *)&c != 0` nor that `(char*)(int*)&c == &c`.

Expert quote:

> Ils ont raison, le premier exemple est UB d'après le standard, il n'y a pas de garantie que `(int*)&c != 0` ou que `(char*)(int*)&c == &c`. Par contre dans une discussion avec un développeur de GCC j'ai appris que c'était “presque comme si c'était documenté” (çad c'est documenté mais la documentation est une réponse à un bug report ou une discussion dans la mailing list des développeurs GCC) que GCC, pour les cibles qu'il vise, a une représentation uniforme des pointeurs et garantit exactement les deux propriétés dont il est question.

### alignconv_e02

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

## argcomp

### argcomp_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### argcomp_e02

OK : TRUE POSITIVE

Incompatible Declaration detected as expected.

### argcomp_e03

OK : TRUE POSITIVE

Incompatible Declaration detected as expected.

### argcomp_e04

OK : TRUE POSITIVE

Incompatible Declaration detected as expected.

## asyncsig

Signal handling is out of scope.

### asyncsig_e01

OUT OF SCOPE

TrustInSoft does not handle signals.

### asyncsig_e02

OUT OF SCOPE

TrustInSoft does not handle signals.

### asyncsig_e03

OUT OF SCOPE

TrustInSoft does not handle signals.

## boolasgn

### boolasgn_e01

NO UB (infinite loop)

Using an assignment expression (i.e. `x = y`) as a loop controlling expression is usually a typo and may cause unexpected behavior, but it is not Undefined Behavior.

Moreover, both `gcc` and `clang` find this kind of possible typos and suggest adding parentheses around the assingment expression if it was really intended to be an assignment and not a comparison.

### boolasgn_e02

NO UB (infinite loop)

Exactly the same explanation as in the previous case - `boolasgn_e01`.

### boolasgn_e03

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### boolasgn_e04

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### boolasgn_e05

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### boolasgn_e06

NO UB

CHECK

### boolasgn_e07

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

## chreof

### chreof_e01

NO UB

WRITE THE EXPLANATION

### chreof_e02

NO UB

WRITE THE EXPLANATION

## chrsgnext

### chrsgnext_e01

NO UB

TrustInSoft detects no Undefined Behavior here, because in this example all the values passed to `isspace()` are valid - they are representable as an `unsigned char`.

For comparison, I have added a second test where we pass the invalid value `-2` to `isspace()` and we can see that TrustInSoft correctly detects an Undefined Behavior.

NOTE: in `glibc`, the lookup table which is used inside the implementation of the `isspace()` function is defined in such a way that both `char` and `unsigned char` values are accepted - the valid range is between `-128` and `255`.

## dblfree

### dblfree_e01

NO UB

Calling `free()` with null pointer as argument does nothing. We can repeat it as many times as we want - this is not Undefined Behavior. There is no possible execution of this program where a double free happens.

### dblfree_e02

NO UB

(Note that this is similar to `accfree_e03`.)

There is no possible execution of this program where a double free happens.

This is the decription in the example:

```C
 * Rule: [dblfree]
 * Description: diagnostic is required because realloc may free c_str1 
 *              when it returns NULL, resulting in c_str1 being freed twice
 * Diagnostic: required on line 88
```

But in the [C17 section *The realloc function* in paragraph 3](https://cigix.me/c17#7.22.3.5.p3), we can read:
> If size is nonzero and memory for the new object is not allocated, the old object is not deallocated.

The description contradicts the C17 standard, which states that if this call to `realloc` returns `NULL` then it cannot free `c_str1` in the same time.

## diverr

### diverr_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### diverr_e02

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### diverr_e03

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### diverr_e04

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

## fileclose

### fileclose_e01

NO UB

Leaving a file open when program exits is technically not Undefined Behavior. However, as certain execution environments do not guarantee the open files to be in a coherent state after the program exits without closing them properly, this feature is in TrustInSoft's roadmap.

### fileclose_e02

NO UB

Memory leak is not Undefined Behavior. Still, TrustInSoft is capable of detecting such issues - the appropriate warning can be found in the *Analyzer Log* tab:

```bash
tests/fileclose/fileclose_e02.c:78:[value] warning: memory leak detected for {__malloc_fun_l84}
```

## filecpy

### filecpy_e01

TODO

## funcdecl

### funcdecl_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### funcdecl_e02

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### funcdecl_e03

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### funcdecl_e04

OUT OF SCOPE

TrustInSoft expects that the compiler will not truncate variable names at 8 characters.

### funcdecl_ex1

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

## intoflow

### intoflow_e01

NO UB

Is this a typo? The test's description talks about integer overflow:

```C
 * Rule: [intoflow]
 * Description: diagnostic is required on implementations that trap on 
 *              signed integer overflow because the expression x + 1 may 
 *              result in signed integer overflow
 * Diagnostic: required on line 79
```

However, the only variables that get incremented in this program ar `i` and `ui`:

* The variable `i` only goes from 1 to 10. So there cannot be a be a overflow here.
* And the variable `ui` is not a signed integer but an `usigned int`. There cannot be a signed overflow on an `unsigned int` value.

Added a corrected version - changed `add(unsigned int ui)` to `add(int ui)` and now TrustInSoft detects this Undefined Behavior as expected.

### intoflow_e02

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### intptrconv_005

OK (detected a different UB)

MISPLACED "REQUIRED DIAGNOSTIC"

## intptrconv

### intptrconv_e01

OK (detected a different UB)

MISPLACED "REQUIRED DIAGNOSTIC"

### intptrconv_e02

NO UB (pointer created, but not used)

CHECK

### intptrconv_ex1

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### intptrconv_ex2

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

## inverrno

### inverrno_e01

Not setting `errno` to zero before calling a library function is not Undefined Behavior.

Although the usual coding pattern is to set `errno` before calling a library function that modifies `errno` upen encountering an error, doing things differently is not always an error. Another common pattern is also chaining calls to multiple library functions one after another without checking the `errno` value in between. As no library function is allowed to set `errno` to zero upon successful completion, this way we can check its value just one at the end of such a chain and know if an error occured somewhere on the way.

Moreover, as `errno` is always initialized to zero, in this particular example it is actually still equal zero when the library function `strtoul` is called, so no problem can occur - therefore no misunderstanding can occur here.

### inverrno_e02

Not checking the return value of `signal()` before checking the value of `errno` is not Undefined Behavior.

As in the previous case: although the usual coding pattern in case of functions like `signal()`, which can indicate an error using their return value, is to check the return value before checking the `errno` value (because if `signal()` succeeds it does not modify the `errno` value, so it could possibly be set by some previous library function call), doing things differently is not always an error. Again, the chaining multiple library calls pattern is a good example when this is OK.

Moreover, as `errno` is always initialized to zero and `signal()` is the only function that can modify `errno` in this particular example, so no previous function could have set it already - therefore, again, no misunderstanding can occur here.

### inverrno_e03

Checking the value of `errno` after a call to `setlocale()` is not Undefined Behavior.

Although `setlocale()` does not modify `errno` upon encountering an error, checking the value of `errno` after such a call is not forbidden and might have sense in certain situations.

Note, that in this particular example TrustInSoft can find that the `if` branch where `errno` is not equal zero is dead code and will show it in red in the GUI (the *Inspect with TrustInSoft Analyzer* button in the *Summary* tab).

### invfmtstr_002

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

## invfmtstr

### invfmtstr_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

## invptr

### invptr_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### invptr_e02

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### invptr_e03

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### invptr_e04

OK (found the UB)

MISPLACED "REQUIRED DIAGNOSTIC"

OK (found the UB), NOTE: made the test abstract to find the desired UB

### invptr_e05

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### invptr_e06

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### invptr_e07

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### invptr_e08

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### invptr_e09

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### invptr_e10

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### invptr_e11

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### invptr_e12

TODO

## ioileave

### ioileave_e01

NIY (interleaving reads and writes to a file)

## liberr

### liberr_e01

CHECK

### liberr_e02

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### liberr_ex1

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### liberr_ex2

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

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

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### libptr_e02

NO UB

In this example Undefined Behavior only happens if the size of `int` is larger than the size of `float`. Unfortunately on all the architectures that TrustInSoft currently handles the size of `int` is smaller or equal than the size of `float`. Therefore the call to `memset` is always vald - it will never go out of the array's bounds.

### libptr_e03

### libptr_e04

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### libptr_e05

## libuse

### libuse_e01

### libuse_e02

### libuse_e03

## nonnullstr

### nonnullstr_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### nonnullstr_e02

MISPLACED "REQUIRED DIAGNOSTIC" (reading uninitialized memory)

### nonnullstr_e03

MISPLACED "REQUIRED DIAGNOSTIC" (reading uninitialized memory)

## nullref

### nullref_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

## padcomp

### padcomp_e01

CHECK

## ptrcomp

### ptrcomp_e01

OK (UB detected in the log)

## ptrobj

### ptrobj_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### ptrobj_ex1

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### ptrobj_ex2

TYPO! (there is a typo in the example - 'subrtact')

OK (no false positive), NOTE: there was a typo in the example! s/'subrtact'/'subtract'/g

## resident

OUT OF SCOPE

Checking for reserved identifiers is out of scope of TrustInSoft.

### resident_e01

NIY (defining reserved identifier errno)

### resident_e02

NIY (defining reserved symbol _RESIDENT_HEADER_H)

### resident_e03

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### resident_e04

NIY (defining reserved file scope identifier _limit)

### resident_e05

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### resident_e06

HALF! OK (detected reusing identifier SIZE_MAX), NIY (defining reserved identifier INTFAST16_LIMIT_MAX)

### resident_e07

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### resident_e08

NIY (defining reserved identifier 'malloc()' and 'free()')

### resident_e09

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

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

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### strmod_e02

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### strmod_e03

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### strmod_e04

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### strmod_e05

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### strmod_e06

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

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

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### taintformatio_e02

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

## taintnoproto

### taintnoproto_e01

NO UB (maybe the behavior is unexpected, but this code is correct - the type of 'int array[]' is complete, so can be used as an argument to 'sizeof' - see https://cigix.me/c17#6.7.6.2.p4)

CHECK

## taintsink

### taintsink_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### taintsink_e02

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

## taintstrcpy

### taintstrcpy_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

## uninitref

### uninitref_e01

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### uninitref_e02

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### uninitref_e03

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

### uninitref_e04

OK : TRUE POSITIVE

Undefined Behavior detected as expected.

MISPLACED "REQUIRED DIAGNOSTIC"

## usrfmt

### usrfmt_e01

### usrfmt_e02

### usrfmt_e03

OK (UB detected), NOTE: there is more than one problem here

### usrfmt_e04

OK : TRUE NEGATIVE

No Undefined Behavior detected, as expected.

### xfilepos_002

NIY (checking if 'fsetpos' argument always comes from 'fgetpos')

## xfilepos

### xfilepos_e01

NIY (checking if 'fsetpos' argument always comes from 'fgetpos')

## xfree

### xfree_e01

### xfree_e02
