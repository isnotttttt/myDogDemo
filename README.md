# myDogDemo
本项目基于UnitreeGO1EDU版本机械狗进行开发，开发系统使用基于arm指令集Ubuntu系统，编程语言使用c++开发，功能实现基于paddledetection预测框架（百度飞浆套件）、opencv视觉开发框架、unitree_legged_sdk四足机器人控制框架。

参考官方文档 https://www.yuque.com/ironfatty/nly1un/fscioc
需要ros基础知识，c++基础，python基础


编译环境配置
lcm
gstremer   依赖
opencv-4.1.1    cmake时记得查看是否含有gstreamer。没有就按照官方文档安装好
paddle_inference   预编译c++版本的paddle，部署狗上请使用arm版本  https://paddleinference.paddlepaddle.org.cn/master/user_guides/download_lib.html


需要修改内容
paddle_detection/CMakeLists.txt：
WITH_MKL  # 是否使用MKL or openblas，TX2需要设置为OFF
WITH_GPU  # gpu预测，可选
PADDLE_DIR  # 修改双引号内容为c++版本paddle路径
PADDLE_LIB_NAME paddle  # 预测库lib名称，由于不同平台不同版本预测库lib名称不同，请查看所下载的预测库中`paddle_inference/lib/`文件夹下`lib`的名称
CUDA_LIB  # cuda路径
CUDNN_LIB  # cudnn路径
TENSORRT_INC_DIR  # TensorRT 的include路径
TENSORRT_LIB_DIR  # TensorRT 的lib路径


tactile_paving/scripts/signalLampDetection.py：
第一行修改为本地python路径


编译步骤
1.mkdir ~/catkin_ws
2.解压本目录下的src到~/catkin_ws文件夹下
3.cd ~/catkin_ws 
4.catkin_make


功能包说明
face_light_sdk_nano  机器狗头部灯光
paddle_detection  飞桨目标识别c++版本
robot_voice  科大迅飞语言识别，仅供x86使用
slamware_ros_sdk、slamware_sdk  雷达发布话题
tactile_paving  导盲场景
unitree_legged_msgs、unitree_legged_real、unitree_legged_sdk-master  宇树机器狗控制功能包


主要运行命令
roslaunch slamware_ros_sdk slamware_ros_sdk_server_node.launch ip_address:=192.168.11.1  开启雷达
roslaunch tactile_paving Start_control.launch   导盲场景。自动开启寻迹、雷达避障、机器狗前灯
roslaunch tactile_paving start_voice.launch  语音控制


主要业务代码
tactile_paving/src/example_Tracing.cpp  寻迹场景
tactile_paving/src/lidar_node.cpp  雷达避障
tactile_paving/src/unitree_put_cmd.cpp  订阅/cmd_vel中Twist内容转为unitree发送高位控制
tactile_paving/scripts/signalLampDetection.py  python版本飞桨目标识别。有bug、检测速度慢。
robot_voice/src/voice_control.cpp  语音识别主要逻辑。
paddle_detection/src/main.cc  c++版本飞桨目标识别。
face_light_sdk_nano/src/main.cpp  狗头部灯光


tactile_paving/launch/Start_control.launch  可修改内容
