#include<ros/ros.h>
#include<visualization_msgs/Marker.h>


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

        while( ros::ok()){
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
               marker.pose.position.x = 0;
               marker.pose.position.y = 0;
               marker.pose.position.z = 0;
               marker.pose.orientation.x = 0.0;
               marker.pose.orientation.y = 0.0;
               marker.pose.orientation.z = 0.0;
               marker.pose.orientation.w = 1.0;

               // set color of the marker
               marker.color.r = 0.0f;
               marker.color.g = 1.0f;
               marker.color.b = 0.0f;
               marker.color.a = 1.0f;

               // set scale or size of the marker
               marker.scale.x = 1.0;
               marker.scale.y = 1.0;
               marker.scale.z = 1.0;

               // check if there's at least one subscriber available
               if(marker_pub.getNumSubscribers() < 1){
                       if(!ros::ok()){
                               return 0;
                       }

                       ROS_WARN_ONCE("Please create subscriber to the marker");
               }


                marker_pub.publish(marker);

                switch(shape){
                        case visualization_msgs::Marker::CUBE:
                             shape = visualization_msgs::Marker::SPHERE;
                             break;
                        case visualization_msgs::Marker::SPHERE:
                             shape = visualization_msgs::Marker::ARROW;
                             break;
                        case visualization_msgs::Marker::ARROW:
                             shape = visualization_msgs::Marker::CYLINDER;
                             break;
                        case visualization_msgs::Marker::CYLINDER:
                             shape = visualization_msgs::Marker::CUBE;
                             break;
     
     
     

                }
                r.sleep();
        }

}
