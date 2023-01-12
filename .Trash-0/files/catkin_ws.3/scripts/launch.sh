#!/bin/sh
xterm  -e  "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot world.launch" &
sleep 5
xterm  -e  "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot teleop.launch" & 
sleep 5
xterm  -e  "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot amcl.launch" 
