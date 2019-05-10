#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if(!client.call(srv))
    {
     ROS_INFO("Unable to call the drive bot service");
    }
}

int count_color_pixel(int start, int end,int pixel_color, const sensor_msgs::Image img)
{
    int num_of_white_pixel=0;
    
       for(int y=start; y<=img.height*end; y++)
       {
          if (img.data[y] == pixel_color)
          {
            num_of_white_pixel++;
          } 
       }
 
   return num_of_white_pixel;

}
 
// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    bool ballPresent = false;
    int num_of_white_pixel_left =0;
    int num_of_white_pixel_center =0;
    int num_of_white_pixel_right =0;
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    for(int i=0; i<img.height*img.step; i++)
    {
      if (img.data[i] == white_pixel)
      {
        ballPresent= true;
      }
    }
    
   if(ballPresent)
   {
    int side = img.step/3;
     num_of_white_pixel_left =count_color_pixel(0,side,white_pixel,img);
     num_of_white_pixel_center =count_color_pixel(side,side*2,white_pixel,img); 
     num_of_white_pixel_right=count_color_pixel(side*2,side*3,white_pixel,img);
     ROS_INFO("left: %d center: %d right: %d ", num_of_white_pixel_left, num_of_white_pixel_center, num_of_white_pixel_right);
     drive_robot(0.5,0.0);
   } else {drive_robot(0.0, 0.0 );}
}


int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}

