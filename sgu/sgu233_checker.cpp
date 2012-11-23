#include<stdio.h>
#include<math.h>
inline double dist(double,double,double,double);
int Main();
int main()
{
	    return Main();
}
int Main()
{
	    int n,i;
				    scanf("%d",&n);
					    for(i=0;i<n;++i)
							    {
									        double xo2,yo2,r,xa2,ya2,xb2,yb2;
											        scanf("%lf%lf%lf%lf%lf%lf%lf",&xo2,&yo2,&r,&xa2,&ya2,&xb2,&yb2);
													        if(fabs(xo2-xa2)<1e-8&&fabs(yo2-ya2)<1e-8)
																        {
																			            double t=xa2;
																						            xa2=xb2,xb2=t;
																									            t=ya2,ya2=yb2,yb2=t;
																												        }
																														        double ofx=(xa2+xo2)/2.0,ofy=(ya2+yo2)/2.0;
																																        xo2-=ofx,yo2-=ofy,xa2-=ofx,ya2-=ofy,xb2-=ofx,yb2-=ofy;
																																		        double d=dist(xo2,yo2,xa2,ya2),sinc=-ya2/d*2.0,cosc=xa2/d*2.0,
																																				               xo=xo2*cosc-yo2*sinc,yo=xo2*sinc+yo2*cosc,
																																							                  xa=xa2*cosc-ya2*sinc,ya=xa2*sinc+ya2*cosc,
																																											                 xb=xb2*cosc-yb2*sinc,yb=xb2*sinc+yb2*cosc,
																																															                
																																																			               aa=r*r/4,bb=aa-d*d/4,
																																																						                  x0=(xa+xb)/2.0,y0=(ya+yb)/2.0,dx=yb-ya,dy=xa-xb,
																																																										                 
																																																														                a=bb*dx*dx+aa*dy*dy,
																																																																		               b=2*x0*dx*bb+2*y0*dy*aa,
																																																																					                  c=x0*x0*bb+y0*y0*aa-aa*bb,
																																																																									                 delta=sqrt(b*b-4*a*c),
																																																																													                
																																																																																	               k1=(-b+delta)/2.0/a,k2=(-b-delta)/2.0/a,
																																																																																				                  xp1=x0+k1*dx,xp2=x0+k2*dx,
																																																																																								                 yp1=y0+k1*dy,yp2=y0+k2*dy,
																																																																																												                dop1=dist(xo,yo,xp1,yp1),dop2=dist(xo,yo,xp2,yp2),
																																																																																																               xd1=xo+(xp1-xo)*(r/dop1),xd2=xo+(xp2-xo)*(r/dop2),
																																																																																																			                  yd1=yo+(yp1-yo)*(r/dop1),yd2=yo+(yp2-yo)*(r/dop2),
																																																																																																							                 
																																																																																																											                da1=dist(xa,ya,xd1,yd1),da2=dist(xa,ya,xd2,yd2),
																																																																																																															               db1=dist(xb,yb,xd1,yd1),db2=dist(xb,yb,xd2,yd2),
																																																																																																																		                  dd=dist(xa,ya,xb,yb),
																																																																																																																						                 cosd1=(da1*da1+db1*db1-dd*dd)/(2.0*da1*db1),
																																																																																																																										                cosd2=(da2*da2+db2*db2-dd*dd)/(2.0*da2*db2);
																																																																																																																														        
																																																																																																																																        if(cosd2<cosd1)
																																																																																																																																			            xd1=xd2,yd1=yd2;
																																																																																																																																						        sinc=-sinc,
																																																																																																																																								        xd2=xd1*cosc-yd1*sinc,yd2=xd1*sinc+yd1*cosc,
																																																																																																																																										        xd2+=ofx,yd2+=ofy;
																																																																																																																																												        printf("%.6lf %.6lf\n",xd2,yd2);
																																																																																																																																														    }
																																																																																																																																															    return 0;
}
inline double dist(double x1,double y1,double x2,double y2)
{
	    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}


