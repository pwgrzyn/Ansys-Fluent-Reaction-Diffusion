#include "udf.h"

#define a 1
#define b 1 
#define epsilon 0.035
#define epsilon_2 0.008
#define h 0.3
#define f 0.9
#define q 0.05
#define D_u 6.075e-9
#define D_v 3.4425e-9
#define D_w 6.885e-9

DEFINE_SOURCE(u_source,c,t,dS,eqn)
{
	real u=C_UDSI(c,t,0);
	real v=C_UDSI(c,t,1);
	real w=C_UDSI(c,t,2);
	
	real source= (0.5*h*h*w-u*w*h+u*h-1.0*q*u*u)/epsilon;
	
	dS[eqn]=(-w*h+h-2.0*q*u)/epsilon;
	
	return source;
	


}
DEFINE_SOURCE(v_source,c,t,dS,eqn)
{
	real u=C_UDSI(c,t,0);
	real v=C_UDSI(c,t,1);
	real w=C_UDSI(c,t,2);
	real source=u*h-v;
	
	dS[eqn]=-1	;
	return source;
	
}


DEFINE_SOURCE(w_source,c,t,dS,eqn)
{
	real u=C_UDSI(c,t,0);
	real v=C_UDSI(c,t,1);
	real w=C_UDSI(c,t,2);
	real source=1.0/epsilon_2*(-q*w*h*h-2*q*u*w*h+2*q*f*v);
	
	dS[eqn]=1.0/epsilon_2*(-q*h*h-2*q*u*h);
	return source;
	
}


DEFINE_DIFFUSIVITY(uds_diff, c, t, i)
{

    if (i == 0) return D_u;
    if (i == 1) return D_v;
    if( i== 2) return D_w;
    return 0.0;
}


DEFINE_INIT(init_double_spiral, d)
{
    Thread *t;
    cell_t c;
    real x[ND_ND];

    thread_loop_c(t, d) {
        begin_c_loop(c, t) {
            C_CENTROID(x, c, t);
            
            C_UDSI(c, t, 0) = 0.0; 
            C_UDSI(c, t, 1) = 0.0;
            C_UDSI(c, t, 2) = 0.0;
          if(x[0] >= -0.000125 && x[0] <= 0.000125 && x[1] >= 0.0 && x[1] <= 0.00375)
{
    C_UDSI(c,t,0) = 0.8;
}

if(x[0]<-0.0125 && x[0]>=-0.012750 && x[1] >= 0.0 && x[1] <= 0.00375)
{
	C_UDSI(c,t,0) = 0.8;
}
if(x[0]>0.0192 && x[0]<=0.01977 && x[1]>=0.0025 && x[1]<=0.0031)
{C_UDSI(c,t,0)=0.8;
}
if(x[0]>=0.0135 && x[0]<= 0.01389 && x[1]<=-0.0249 && x[1]>=-0.0276)
{C_UDSI(c,t,0)=0.8;
}
if(x[0]>=-0.0167 && x[0]<=-0.0164 && x[1]>=-0.021 && x[1]<=-0.0194)
{C_UDSI(c,t,0)=0.8;
}
}
        end_c_loop(c, t)
    }
}
