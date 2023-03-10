#!/bin/sh

export TURTLEBOT_GAZEBO_MAP_FILE=$(rospack find my_robot)/maps/map.yaml

xterm -e " source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find my_robot)/worlds/myoffice.world" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch"
