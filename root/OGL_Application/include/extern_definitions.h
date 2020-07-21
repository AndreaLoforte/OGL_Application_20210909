#ifndef GLOBAL_H
#define GLOBAL_H
namespace globalNS {



static const std::string OBJECTGUNCOLLECTOR{ "GUNCOLLECTOR" };
static float DURATION = 0.033;

/*fattore utile a scalare alcuni parametri come
RigidBody::motion , che regola quando un corpo 
viene settato a "can sleep". 
Questo accade perchè la scala del mondo che ho creato
è troppo grande rispetto a quella per cui è stato 
progettato il motore fisico*/
static constexpr float WORLDSCALINGFACTOR = 1;

}



#endif