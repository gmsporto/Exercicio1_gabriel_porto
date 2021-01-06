//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words


EQUATION("X")
/*
X (t) = X (t-1) + ruido branco   
*/
v[0] = VL("X",1);
v[1] = norm(0, 2.5); 
v[2] = v[0]+v[1];
RESULT(v[2])

EQUATION("X_Sum")
/*
Variável do Setor
Equivalente macro: RESULT(SUM("X"))
*/
v[0]=0;
CYCLE(cur, "FIRM")
{
		v[1]=VS(cur,"X");
		v[0]=v[0]+v[1];
}
RESULT(v[0])

EQUATION("X_Ave")
/*
Variável do Setor
*/
RESULT(AVE("X"))

EQUATION ("X_Max")
/*
Variável do Setor
*/
RESULT(MAX("X"))



MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
