#include "udf.h"

#define F_RATE 0.055 //feedrate adding u to the cell
#define K_RATE 0.062 //killrate substracting v from the cell with reaction V->P 
#define DIFF_U 2e-8
#define DIFF_V 1e-8

DEFINE_SOURCE(u_source,c ,t ,dS , eqn)
{
real u=C_UDSI(c,t,0);
real v=C_UDSI(c,t,1);
real source= -u*v*v+(F_RATE)*(1.0-u);

dS[eqn]=-v*v-F_RATE;
return source;


}

DEFINE_SOURCE(v_source,c ,t ,dS , eqn)
{
real u=C_UDSI(c,t,0);
real v=C_UDSI(c,t,1);
real source= u*v*v-(F_RATE+K_RATE)*v;

dS[eqn]=2.0*u*v-(F_RATE+K_RATE);
return source;


}



DEFINE_DIFFUSIVITY(uds_diff, c, t, i)
{
    if (i == 0) return DIFF_U;
    if (i == 1) return DIFF_V;
    return 0.0;
}



DEFINE_INIT(init_gray_scott, d)
{
	//just initializing square in the middle for potentially interesting non symmetric patterns
	//do random 
    Thread *t;
    cell_t c;
    real x[ND_ND];
    thread_loop_c(t, d)
    {
        begin_c_loop(c, t)
        {
            C_CENTROID(x, c, t);
           
            C_UDSI(c, t, 0) = 1.0;
            C_UDSI(c, t, 1) = 0.0;

         //this is roughly middle of the square
           //if ((x[0] > 0.014 && x[0] < 0.028 && x[1] > 0.014 && x[1] < 0.028) || (x[0] < -0.014 && x[0] > -0.028 && x[1] < -0.014 && x[1] > -0.028) )
           //if(x[0]>-0.014 && x[0]<0.014 && x[1]>-0.014 && x[1]<0.014)
           if( x[0]>-0.004 && x[0]<0.004 && x[1]>-0.004 && x[1]<0.004 )
{
    C_UDSI(c, t, 0) = 0.50;
    C_UDSI(c, t, 1) = 0.25;
}
        }
        end_c_loop(c, t)
        
    }
}





