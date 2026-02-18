#include "udf.h"

#define a 3.0 
#define b -1.0
#define DIFF_U 2e-9
#define DIFF_V 1e-8
#define L_x	0.058
#define L_y 0.058

DEFINE_SOURCE(u_source,c ,t ,dS , eqn)
{
real u=C_UDSI(c,t,0);
real v=C_UDSI(c,t,1);
real source= a*u-(u+b*v)*(u*u+v*v);

dS[eqn]=a-(3*u*u+b*u*2*v+v*v);
return source;


}

DEFINE_SOURCE(v_source,c ,t ,dS , eqn)
{
real u=C_UDSI(c,t,0);
real v=C_UDSI(c,t,1);
real source= a*v+(b*u-v)*(u*u+v*v);

dS[eqn]=a+2*v*b*u-u*u-3*v*v;
return source;


}



DEFINE_DIFFUSIVITY(uds_diff, c, t, i)
{
    if (i == 0) return DIFF_U;
    if (i == 1) return DIFF_V;
    return 0.0;
}



DEFINE_INIT(init_waves, d)
{
	
    Thread *t;
    cell_t c;
    real x[ND_ND];
    thread_loop_c(t, d)
    {
        begin_c_loop(c, t)
        {
            C_CENTROID(x, c, t);
           
            C_UDSI(c, t, 0) = sin(2*M_PI*x[0]/L_x)*sin(2*M_PI*x[1]/L_y);
            C_UDSI(c, t, 1) = 0.0;
            
			
        }
        end_c_loop(c, t)
        
    }
}





