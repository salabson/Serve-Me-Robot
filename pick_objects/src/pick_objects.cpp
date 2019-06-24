#include<ros/ros.h>
#include<move_base_msgs/MoveBaseAction.h>
#include<actionlib/client/simple_action_client.h>

// Create move_base simple action client type
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
// intialize ros node
ros::init(argc, argv, "pick_objects");
//1. start the server


// call move_base action server and tell it to spin (start action server)
MoveBaseClient ac("move_base", true);

// wait for 5 second for move_base action server to come up
while(!ac.waitForServer(ros::Duration(5.0))){
	ROS_INFO("Waiting for move_base action server to come up");

}

//2. set the goal target

// Create move base goal object or service
move_base_msgs::MoveBaseGoal goal;

// setup frame parameters
goal.target_pose.header.frame_id = "map"; 
goal.target_pose.header.stamp = ros::Time::now();

//Define pick up goal position and orientation for the robot to be reached
goal.target_pose.pose.position.x =-6.741549;
goal.target_pose.pose.orientation.w =-2.264534;



//3. send robot to goal target

// send the goal for pick up zone
ROS_INFO("Sending goal pick up zone");
ac.sendGoal(goal);

// wait for infinite for result
ac.waitForResult();


// Check to see if goal has been reached by the robot
if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	ROS_INFO("Hurray the Robot has sucessfully reached the pick up zone");
else
	ROS_INFO("Ayya! the robot failed to reached the goal location for some reasons");

ros::Duration(5.0).sleep();


// Define dropoff goal position and orientation for the robot to be reached
goal.target_pose.pose.position.x =0.236172;
goal.target_pose.pose.orientation.w =3.871257;


ROS_INFO("Sendin goal for drop off zone");
ac.sendGoal(goal);

// wait fir infine time for result
ac.waitForResult();


// check if robot reached the dropoff goal or not
if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	ROS_INFO("Congratulations! robot has successful reached the dropoff zone");
else
	ROS_INFO("Ayya! robot failed to reached the drop off zone");

return 0;



}
