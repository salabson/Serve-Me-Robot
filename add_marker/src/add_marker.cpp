#include<ros/ros.h>
#include<visualization_msgs/Marker.h>

int main(int argc, char** argv){
        // initialize ros system
        ros::init(argc, argv, "add_maker");
        // Create node object
        ros::NodeHandle nh;
        // Create maker publisher
        ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker",1);
        ros::Rate r(1);

        // Set initial marker shape
        uint32_t shape = visualization_msgs::Marker::CUBE;

        while(ros::ok())
        {
        // Create marker object
        visualization_msgs::Marker marker;

        // set the marker frame id
        marker.header.frame_id ="map";
        marker.header.stamp = ros::Time::now();


        // set the type of the marker
        marker.type = shape;

        // set marker namespace and id
        marker.ns = "add_maker";
        marker.id = 0;

        // set the pose of the marker relative to the map in 6DOF
        marker.pose.position.x = 0;
        marker.pose.position.y = 0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        // set the scale(size)
        marker.scale.x = 1.0;
        marker.scale.y = 1.0;
        marker.scale.z = 1.0;

        // set color
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0f;

        // set marker action: ADD or DELETE
        marker.action = visualization_msgs::Marker::ADD;

        // set marker lifetime
        marker.lifetime = ros::Duration();

        // publish the marker if there's at least a subscriber
        if (marker_pub.getNumSubscribers() < 1){
                if(!ros::ok()){
                        return 0;
                }

                ROS_WARN_ONCE("Please create a subscriber to the marker");
        }
        marker_pub.publish(marker);

        // Change the type of the marker for the next iteration
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


        sleep(1);

        }

                       




}
