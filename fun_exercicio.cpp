//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words


EQUATION("X") //Sim1
/*
LEVEL: FIRM
*/
	v[0] = VL("X",1);
	v[1] = V("Max"); 
	v[2] = V("Min");
	v[3] = v[0]+uniform(v[1],v[2]);
	RESULT(v[3])

EQUATION("X_Sum")  //Sim2
/*
LEVEL: SECTOR
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
LEVEL: SECTOR
*/
	v[0]=0;
	CYCLE(cur, "FIRM")
	{
			v[1]=VS(cur,"X");
			v[0]=v[0]+v[1];
			v[2]= COUNT_ALLS(cur,"FIRM");  
	}
	RESULT(v[0]/v[2])


EQUATION ("X_Max")
/*
LEVEL: SECTOR
*/
	v[0]=0;
	CYCLE(cur, "FIRM")
	{
			v[1]=VS(cur, "X");
			if (v[1]>v[0])   
			{v[0]=v[1];}
			else 
			{v[0]=v[0];}
	}
	RESULT(v[0])


EQUATION("MktSh") //Sim3
/*
LEVEL: FIRM
*/
	v[0]=V("X");
	v[1]=V("X_Sum");
	RESULT(v[0]/v[1])


EQUATION("Sum_MktSh")
/*
LEVEL:SECTOR
*/
	v[0]=0;
	CYCLE(cur,"FIRM")
	{
			v[1]=VS(cur,"MktSh");
			v[0]=v[0]+v[1];
	}
	RESULT(v[0])


EQUATION("Leader") // DESAFIO
/*
LEVEL: SECTOR
*/
	v[0]=0;
	v[1]=0;
	CYCLE(cur, "FIRM")
	{
			v[2]=VS(cur, "X");
			v[3]=VS(cur,"IdFirm");
			if (v[2]>v[0])   
			{v[0]=v[2]; v[1]=v[3];}
			else 
			{v[0]=v[0]; v[1]=v[1];}
	}
	RESULT(v[1]) 


EQUATION("Rank") // Sim4
/*
LEVEL: SECTOR
*/
	v[0]=1;
	CYCLE(cur, "FIRM")
	{
			cur1=SORT("FIRM", "X", "DOWN");
			CYCLE(cur, cur1)
			{
					WRITES(cur, "firm_rank", v[0]);
					v[0]=v[0]+1;	
			}				
	}

/*
v[0]=1;
	cur1=SORT("FIRM", "X", "DOWN");
	CYCLE(cur, cur1)
	{
			WRITES(cur, "firm_rank", v[0]);
			v[0]=v[0]+1;				
	}
*/

RESULT(v[0])

MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
