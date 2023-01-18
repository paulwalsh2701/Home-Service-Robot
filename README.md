# Home-Service-Robot
----
 The home service robot project can be run by sourcing setup.bash and then running the home_service script in the catkin_ws folder
 The script initiates launch files and packages as explained below.
 
--------
 
* turtlebot_world.launch
    * Starts the gazebo simulation software
    * A robot is added to the environment using the urdf file as a basis
    * my_office world is used by specifying for the launch file which world file to use in the script
* amcl_demo.launch
    * Starts up the amcl_demo node and move_base node. 
    * Parameters are set including critically, the initial pose of the robot which give the robot a helping hand in localization.
    * the map file (map.yaml) that amcl.launch should use is specified in the script also.
    * amcl node
        * The amcl node uses Adaptive Monte Carlo Localization as the basis for an algorithm for state estimation.
        * Monte Carlo localization uses particles and a filter to estimate the pose of the robot 
        * AMCL needs a map to perform its localization and it publishes this on the /map topic.
    * move_base node
        * The move_base node provide the capability to set goals for the robot and give the capbility for it to navigate to it
        * It will perform recovery behaviours if stuck and notify the user if cannot reach the goal
* view_navigation.launch
    * This launch file starts the Rviz visualization tool
    * It uses the rviz configuration file that was previously defined in the turtlebot package and adds the markers to it also.
* pick_objects
    * The pick_objects node communicates with ROS navigation stack.
    * It sends 2 goals for the robot to reach which include a position and orientation.
    * It then checks to see if the robot has reached its goals and will provide a message if not.
    * The robot stops using a ros::duration line to wait for 5 seconds once the first goal is reached before navigating to goal 2.
* add_markers
    * The add_markers node allows the modelling of virtual objects in rviz.
    * In this case it is used to display a marker at the first goal (pick-up) until the robot arrives. The marker will then disappear representing a pick and finally reappear at the 2nd goal (drop-off) when the robot arrives there.
    * It subscribes to the odom topic to track the robot position and compares this to the goals to determine when to display or delete the markers at each goal.
----
Robot Ready
---
![Robot Ready](https://user-images.githubusercontent.com/97263488/212975078-a75d9962-a11f-40be-8439-f7cd803037dc.png)
1st Goal Reached & Marker Picked
---
![1st Goal Reached - Marker Picked](https://user-images.githubusercontent.com/97263488/212975103-afd2a6d6-df39-497f-a5c6-874e23cd7ad2.png)
Robot navigating to drop off
---
![1st Goal To 2nd Goal - Marker Picked](https://user-images.githubusercontent.com/97263488/212975130-ab496df8-c43d-4577-b32c-4d29b8f372b5.png)
Robot At Final Location Having "Delivered" Marker
---
![Marker Delivered](https://user-images.githubusercontent.com/97263488/212975174-2f833afa-48c0-4a2a-83fe-00cc9153e5d0.png)
gif of home_service.sh script initiating all the packages and launch files and showing the robot nvaigating to each goal.
---
![2023-01-17-17-44-31](https://user-images.githubusercontent.com/97263488/212983871-b1990227-6ecb-471d-bfd2-60c5a269cc83.gif)
