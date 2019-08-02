#! /bin/bash
source /opt/ros/kinetic/setup.bash
source /home/vkrobot/hexbot_ws/devel/setup.bash
source /home/vkrobot/.bashrc

roscore &
sleep 5s
gnome-terminal -x rosrun hexbot_teleop_joy controller
sleep 5s
roslaunch rplidar_ros rplidar.launch &
sleep 5s
roslaunch rplidar_ros hector_mapping_demo.launch &
sleep 5s
gnome-terminal -x bash -c "cd /home/vkrobot/hexbot_ws/src/hexbot_camera && python3 server.py"
sleep 5s
roslaunch rosbridge_server rosbridge_websocket.launch


