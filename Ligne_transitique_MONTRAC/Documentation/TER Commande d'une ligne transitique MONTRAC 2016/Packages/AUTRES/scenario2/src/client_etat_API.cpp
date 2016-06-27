#include "ros/ros.h"
//#include "std_msgs/String.h"
#include <sstream>
#include <stdio.h>
#include "scenario1/Etat_API.h"
//#include <modbus/modbus.h>

uint16_t MASK(uint16_t registre,int voie);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "client_etat_API");

  ros::NodeHandle n;

  ros::ServiceClient client = n.serviceClient<scenario1::Etat_API>("etat_API");

  scenario1::Etat_API srv;
  srv.request.numero_API = atoll(argv[1]);
  if (client.call(srv))
  {
	ROS_INFO("~~~ ENTREES -> %d ~~~",srv.response.entrees);
	for(int i=0;i<=15;i++) ROS_INFO("Registre entrees, voie %d = %d",i,MASK(srv.response.entrees,i));
	ROS_INFO("\n");	

	ROS_INFO("~~~ SORTIES -> %d ~~~",srv.response.sorties);
	for(int i=0;i<=15;i++) ROS_INFO("Registre sorties, voie %d = %d",i,MASK(srv.response.sorties,i));
	ROS_INFO("\n");	
  }
  else
  {
    ROS_ERROR("Failed to call service etat_API");
    return 1;
  }
  return 0;
}


uint16_t MASK(uint16_t registre,int voie)
{
	return (registre & (uint16_t)pow(2,voie))/pow(2,voie);
}