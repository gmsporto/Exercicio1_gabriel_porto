//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words


EQUATION("X") 
//LEVEL: FIRM
	v[1]=V("quali");
	v[2]=V("p"); 
	v[3]=V("X_quali");					// par�metro de calibragem
	v[4]=V("X_p");							// par�metro de calibragem
	if (v[2]!=0) {v[5]=norm(0, 2)+pow(v[1],v[3])/pow(v[2],v[4]);}
	else {v[5]=VL("X",1);}
RESULT(max(v[5],0))


EQUATION("p")
//LEVEL: FIRM
	v[0]=VL("p",1);
	v[1]=VL("MktSh",1)-VL("MktSh",2);
	v[2]=V("p_MktSh"); 			   		 // par�metro de calibragem
	v[3]=v[0]+v[2]*v[1];
RESULT(max(v[3],0))


EQUATION("quali")
//LEVEL: FIRM
	v[0]=VL("quali",1);
	v[1]=V("quali_med"); 						//par�metro de calibragem
	v[2]=V("quali_desvpad");				//par�metro de calibragem
	v[3]=norm(v[1],v[2]);
	if (v[3]>0) {v[4]=v[0]+v[3];}
	else {v[4]=v[0];}
RESULT(v[4])

EQUATION("HHIinv")
//Level: SECTOR
	v[0]=0;
	CYCLE(cur,"FIRM")
	{
		v[1]=pow(VS(cur,"MktSh"),2);
		v[0]+=v[1];
	}
RESULT(1/v[0])

//  ** EXERC�CIOS ANTERIORES **

EQUATION("X_Sum")  
//LEVEL: SECTOR
	v[0]=0;
	CYCLE(cur, "FIRM")
	{
			v[1]=VS(cur,"X");
			v[0]=v[0]+v[1];
	}
RESULT(v[0])

EQUATION("X_Ave")
//LEVEL: SECTOR
	v[0]=0;
	CYCLE(cur, "FIRM")
	{
			v[1]=VS(cur,"X");
			v[0]=v[0]+v[1];
			v[2]= COUNT_ALLS(cur,"FIRM");  
	}
RESULT(v[0]/v[2])


EQUATION ("X_Max")
//LEVEL: SECTOR
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


EQUATION("MktSh")
//LEVEL: FIRM
	v[0]=V("X");
	v[1]=V("X_Sum");
	if (v[1]!=0) {v[2]=v[0]/v[1];}
	else {v[2]=0;}
RESULT(v[2])


EQUATION("Sum_MktSh")
//LEVEL:SECTOR
	v[0]=0;
	CYCLE(cur,"FIRM")
	{
			v[1]=VS(cur,"MktSh");
			v[0]=v[0]+v[1];
	}
RESULT(v[0])


EQUATION("Leader") 
//LEVEL: SECTOR
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


EQUATION("Rank") 
//LEVEL: SECTOR
SORT("FIRM", "X", "DOWN");
	v[0]=0;
	CYCLE(cur, "FIRM")
	{
			v[0]++;
			WRITES(cur, "firm_rank", v[0]);
	}
RESULT(0)

/*
EQUATION("EntryExit")
//LEVEL: SECTOR
	v[0]=V("switch_entry")
	if(v[0]==1)
	{
			cur=SEARCH_CND("firm_rank",10);
			DELETE(cur);
			cur1=SEARCH_CND("firm_rank",5);
			ADDOBJ_EX("FIRM", cur1);
	}
RESULT(0)
*/

MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
