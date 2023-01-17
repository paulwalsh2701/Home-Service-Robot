#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <iostream> 
using namespace std;

double x_pose = -20.0;
double y_pose = -20.0;
bool first_goal_reached = false;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
  y_pose = (msg->pose.pose.position.x)*-1.0;
  x_pose = msg->pose.pose.position.y;

  //ROS_INFO("Odom Received");
  //ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  //cout << "x_pose is " << x_pose << endl;
  //cout << "y_pose is " << y_pose << endl;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom", 100, odomCallback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;
  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  while (ros::ok())
  {
    ros::spinOnce();

    cout << "x_marker is " << (marker.pose.position.x) << endl;
    cout << "y_marker is " << (marker.pose.position.y) << endl;
    cout << "x_pose is " << (x_pose) << endl;
    cout << "y_pose is " << (y_pose) << endl;
    
    float pos_tol = 0.3;

    if ( (abs(marker.pose.position.x - x_pose) > pos_tol) 
      && (abs(marker.pose.position.y - y_pose) > pos_tol) 
      && (first_goal_reached == false))
    {
    marker.pose.position.x = 1.0;
    marker.pose.position.y = 2.0;    
    marker.action = visualization_msgs::Marker::ADD;
    ROS_INFO("[Marker Not Picked Yet");
    } 
    if ( (abs(marker.pose.position.x - x_pose) < pos_tol) 
      && (abs(marker.pose.position.y - y_pose) < pos_tol) 
      && (first_goal_reached == false))
    {
    //cout << "x_pose is " << (x_pose) << endl;
    //cout << "y_pose is " << (y_pose) << endl;
    //cout << "x_marker is " << (marker.pose.position.x) << endl;
    //cout << "y_marker is " << (marker.pose.position.y) << endl;
    marker.action = visualization_msgs::Marker::DELETE;
    marker.pose.position.x = 2.0;
    marker.pose.position.y = 6.0;
    first_goal_reached = true;
    ROS_INFO("[Picked Marker");
    }
    if ( (abs(marker.pose.position.x - x_pose) < pos_tol) 
      && (abs(marker.pose.position.y - y_pose) < pos_tol) 
      && (first_goal_reached == true))
    {
    marker.action = visualization_msgs::Marker::ADD;
    ROS_INFO("[Delivered Marker");
    }

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    // Cycle between different shapes
    //switch (shape)
    //{
    //case visualization_msgs::Marker::CUBE:
      //shape = visualization_msgs::Marker::SPHERE;
      //break;
    //case visualization_msgs::Marker::SPHERE:
      //shape = visualization_msgs::Marker::ARROW;
      //break;
    //case visualization_msgs::Marker::ARROW:
      //shape = visualization_msgs::Marker::CYLINDER;
      //break;
    //case visualization_msgs::Marker::CYLINDER:
      //shape = visualization_msgs::Marker::CUBE;
      //break;
    //}
    
    marker.lifetime = ros::Duration();
    marker_pub.publish(marker);
    r.sleep();
  }
}
