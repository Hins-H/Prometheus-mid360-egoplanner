基于阿木实验室的[Prometheus项目](https://github.com/amov-lab/Prometheus)，做了一些修改：
- 完成了 Prometheus + mid360 + Fast_LIO + ego-planner
- 加上了mid360的模型，修改了mid360的驱动程序，使mid360能发布符合Fast_lio算法要求点云的类型，并能在.sdf文件中指定雷达坐标系。
- Prometheus项目中对ego-planner进行了修改，生成的三维膨胀地图是二维膨胀地图在竖直方向上的延伸，不是真实的障碍物膨胀地图，故将Prometheus中的ego-planner和原版ego-planner进行了融合，最后能生成实际的三维地图。
- 修改了Fast_LIO的代码，能够在参数文件中设定其发布的两个坐标系（原版将坐标系固定为camera_init和body）。
