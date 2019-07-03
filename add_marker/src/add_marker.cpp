#include<ros/ros.h>
#include<visualization_msgs/Marker.h>
#include<string.h>

int main(int argc, char** argv){
        // intialize ROS system
        ros::init(argc, argv, "simple_marker");
        //Create nodehandle object to interact with ROS
        ros::NodeHandle nh;
        //Create publishier object that publish marker
        ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker",1);
        ros::Rate r(1);
  // set the initial shape of the marker
        uint32_t shape = visualization_msgs::Marker::CUBE;


                                 

              // Create marker msgs
              
                visualization_msgs::Marker marker;
               
                // set up frame relative to which you want to marker pose be interpreted
                marker.header.frame_id = "map";
                marker.header.stamp = ros::Time::now();

                // set up namespace and id of the marker
                marker.ns = "add_marker";
                marker.id = 0;


               // set the type of the marker e.g cube, sphere
               marker.type = shape;

               // set the action of the marker
               marker.action = visualization_msgs::Marker::ADD;

               // set how long the marker will stick around
               marker.lifetime = ros::Duration();

               // set the pose of the marker
               marker.pose.position.x = -6.741549;
               marker.pose.position.y = 0;
               marker.pose.position.z = 0;
               marker.pose.orientation.x = 0.0;
               marker.pose.orientation.y = 0.0;
               marker.pose.orientation.z = 0.0;
               marker.pose.orientation.w = -2.264534;

               // set color of the marker
               marker.color.r = 0.0f;
               marker.color.g = 0.0f;
               marker.color.b = 1.0f;
               marker.color.a = 1.0f;

               // set scale or size of the marker
               marker.scale.x = 0.2;
               marker.scale.y = 0.2;
               marker.scale.z = 0.2;
                // check if there's at least one subscriber available
               if(marker_pub.getNumSubscribers() < 1){
                       if(!ros::ok()){
                               return 0;
                       }

                       ROS_WARN_ONCE("Please create subscriber to the marker");
                       sleep(1);
               }


               marker_pub.publish(marker);

               std::string robot_state;






        while( ros::ok()){

               
               if( ros::param::get("/pick_objects/robot_state",robot_state)){
                         if(robot_state == "pick_up"){
              
                 marker.action = visualization_msgs::Marker::DELETE;
                 marker_pub.publish(marker);

                 ros::Duration(5.0).sleep();
                }


                              

                if(robot_state == "drop_off"){               
                
                marker.pose.position.x = 0.236172;
                marker.pose.orientation.w = 3.871257;
                marker.action = visualization_msgs::Marker::ADD;
                marker_pub.publish(marker);

                ros::Duration(5.0).sleep();

                }
     


               }
             

             
                
                r.sleep();
        }
              



}
