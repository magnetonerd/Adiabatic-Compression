#include <stdio.h>
#include <math.h>

#define PI               acos(-1.0)
#define TUBE_LENGTH      0.20
#define TUBE_RADIUS      0.05
#define DENSITY_AIR      1.225
#define TEMPERATURE_INIT 300.0
#define PRESSURE_INIT    100000.0
#define Cv               20.9
#define GAMMA            1.3923444976

double TEMP(double VOLUME_INIT, double VALUE, double VOLUME_F);
double VOLUME(double x);
double MASS_AIR(double x);
double FORCE_AIR(double VOLUME_INIT, double x);
		   
int main()
{
  double VOLUME_INIT = (PI*pow(TUBE_RADIUS,2.0))*TUBE_LENGTH;
  double VALUE = PRESSURE_INIT*pow(VOLUME_INIT,GAMMA)/(Cv*(GAMMA-1));
  double t, t_guess, dt, x_init, v_init, velocity, air_pos_x;
  
  t = 0.0;
  t_guess = 0.0;
  dt = 0.0000001;
  x_init = 0.01;
  v_init = 0.0;
  velocity = 331.0;//0.0;
  air_pos_x = x_init;
  
  double force, force_guess, velocity_guess, air_guess;
  int n = 0;
  
  while((air_pos_x < TUBE_LENGTH) && (TEMP(VOLUME_INIT,VALUE,VOLUME(TUBE_LENGTH-air_pos_x)) < 800.0)){
    t = t + dt;
    t_guess = t_guess;
   
    printf("Temperature: %5f K, Barrier Position: %5f m, velocity: %5f\n",TEMP(VOLUME_INIT,VALUE,VOLUME(TUBE_LENGTH-air_pos_x)), air_pos_x,velocity);
    force = FORCE_AIR(VOLUME_INIT,air_pos_x);
    //printf("Force: %5f\n", force);
    air_guess = air_pos_x + velocity*dt;
    velocity_guess = velocity + force*dt/MASS_AIR(air_guess);
    force_guess = FORCE_AIR(VOLUME_INIT,air_guess);
    air_pos_x = air_pos_x + (velocity + velocity_guess)*dt/2.0;
    velocity = velocity + (force + force_guess)*dt/(2.0*MASS_AIR(air_pos_x));
    //printf("%5f %5f %5f %5f %5f\n",force,air_guess,velocity_guess,force_guess,velocity);
    ++n;
  }
  return 0;
}

double TEMP(double VOLUME_INIT, double VALUE, double VOLUME_F)
{
  return VALUE*((VOLUME_F/pow(VOLUME_F,GAMMA))-(VOLUME_INIT/pow(VOLUME_INIT,GAMMA))) + TEMPERATURE_INIT;
}

double VOLUME(double x)
{
  return (PI*pow(TUBE_RADIUS,2.0))*x;
}

double MASS_AIR(double x)
{
  return DENSITY_AIR*VOLUME(x);
}

double FORCE_AIR(double VOLUME_INIT, double x)
{
  return (PRESSURE_INIT*pow(VOLUME_INIT,GAMMA))*(PI*pow(TUBE_RADIUS,2.0))/pow(VOLUME(x),GAMMA);
}
