#!/bin/bash
# 脚本描述： 无人机绕圆飞行，找相应的二维码，并前往相应二维码进行降落

gnome-terminal -- bash -c "roslaunch prometheus_demo find_aruco_marker_all_P600.launch; exec bash"

echo “prometheus_find_aruco_marker  successfully started”
# 两个roslauch之间需要间隔一段时间，否则会相互抢占roscore,导致其中一个roslaunch失败,报runid错误
sleep 0.7s  

gnome-terminal -- bash -c "roslaunch spirecv_ros aruco_detection_with_rostopic.launch; exec bash"

echo “spirecv_aruco_detection  successfully started”

