#!/bin/sh

xterm -e " source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find my_robot)/worlds/myoffice.world" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find my_robot)/maps/map.yaml" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e " source devel/setup.bash; rosrun add_markers add_markers_VO"
