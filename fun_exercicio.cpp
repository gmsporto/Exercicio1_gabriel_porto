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



MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
