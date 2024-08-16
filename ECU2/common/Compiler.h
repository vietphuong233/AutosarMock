/**
 *
 * \brief Electric Memory Seat
 * \author Group1B
 *
 */

#ifndef COMPILER_H
#define COMPILER_H

#include <Compiler_Cfg.h>

/* Definitions */
#define AUTOMATIC             // COMPILER040
#define TYPEDEF               // COMPILER040
#define STATIC static
#define NULL_PTR ((void *)0)  // COMPILER051
#define INLINE                // COMPILER057
#define LOCAL_INLINE          // COMPILER060

/* Macros */
#define FUNC(rettype, memclass) rettype                                    // COMPILER001
#define FUNC_P2CONST(rettype, ptrclass, memclass) const rettype *          // COMPILER061
#define FUNC_P2VAR(rettype, ptrclass, memclass) rettype *                  // COMPILER063
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *                       // COMPILER006
#define P2CONST(ptrtype, memclass, ptrclass) ptrtype const *               // COMPILER013
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const            // COMPILER031
#define CONSTP2CONST(ptrtype, memclass, ptrclass) ptrtype const * const    // COMPILER032
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const ptrclass fctname) // COMPILER065
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname) ptrclass     // COMPILER039

#define CONST(consttype, memclass) const consttype                         // COMPILER023
#define VAR(vartype, memclass) vartype                                     // COMPILER026
#endif /* COMPILER_H */