#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.h>

ros::Publisher pub;

void pointCloudCallback(const sensor_msgs::PointCloud2ConstPtr& input)
{
    static tf2_ros::Buffer tf_buffer;
    static tf2_ros::TransformListener tf_listener(tf_buffer);

    geometry_msgs::TransformStamped transform_stamped;
    try
    {
        // 获取从 lidar_link 到 world 的变换
        transform_stamped = tf_buffer.lookupTransform("world", "uav1/lidar_link", ros::Time(0));
    }
    catch (tf2::TransformException &ex)
    {
        ROS_WARN("%s", ex.what());
        return;
    }

    // 创建一个用于存储转换后点云数据的对象
    sensor_msgs::PointCloud2 output;

    // 使用 tf2 将点云数据转换到 world 坐标系
    tf2::doTransform(*input, output, transform_stamped);

    // 设置输出点云的坐标系
    output.header.frame_id = "world";

    // 发布转换后的点云
    pub.publish(output);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pointcloud_transformer");
    ros::NodeHandle nh;

    // 订阅激光雷达的点云数据
    ros::Subscriber sub = nh.subscribe("/livox/lidar", 10, pointCloudCallback);

    // 创建发布器，用于发布转换后的点云数据
    pub = nh.advertise<sensor_msgs::PointCloud2>("/livox_pointcloud_world", 10);

    ros::Rate r(100.0);

    while(ros::ok())
    {
        //调用一次回调函数
        ros::spinOnce();
        r.sleep();
    }

    return 0;
}
