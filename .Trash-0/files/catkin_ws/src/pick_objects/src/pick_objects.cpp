#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal1;

  // set up the frame parameters
  goal1.target_pose.header.frame_id = "map";
  goal1.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal1.target_pose.pose.position.x = 1.0;
  goal1.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal 1");
  ac.sendGoal(goal1);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved to goal 1");
  else
    ROS_INFO("The base failed to move to goal 1 for some reason");

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for 5 secs after reaching the pickup zone");
  }

  move_base_msgs::MoveBaseGoal goal2;

  // set up the frame parameters
  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal2.target_pose.pose.position.x = -4.0;
  goal2.target_pose.pose.position.y = -4.0;
  goal2.target_pose.pose.orientation.w = 1.57;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal 2");
  ac.sendGoal(goal2);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved to goal 2");
  else
    ROS_INFO("The base failed to move to goal 2 for some reason");

  return 0;
}
