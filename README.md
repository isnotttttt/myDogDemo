---

# 🐕 myDogDemo

本项目基于 **Unitree GO1 EDU 机械狗** 开发，运行环境为 **ARM 指令集 Ubuntu 系统**，使用 **C++** 编程。
主要功能实现依赖以下框架与工具：

* [PaddleDetection](https://github.com/PaddlePaddle/PaddleDetection) —— 百度飞桨目标检测框架
* [OpenCV](https://opencv.org/) —— 计算机视觉开发框架
* [unitree\_legged\_sdk](https://github.com/unitreerobotics/unitree_legged_sdk) —— 宇树四足机器人控制框架

参考官方文档 👉 [铁胖子的宇树笔记](https://www.yuque.com/ironfatty/nly1un/fscioc)
需要具备 **ROS 基础知识、C++ 基础、Python 基础**。

---

## 📑 目录

* [⚙️ 编译环境依赖](#️-编译环境依赖)
* [🔧 需要修改的配置](#-需要修改的配置)
* [🛠️ 编译步骤](#️-编译步骤)
* [📦 功能包说明](#-功能包说明)
* [🚀 主要运行命令](#-主要运行命令)
* [📂 主要业务代码](#-主要业务代码)
* [🔍 可修改配置](#-可修改配置)
* [📖 TODO / 已知问题](#-todo--已知问题)

---

## ⚙️ 编译环境依赖

请确保系统安装以下依赖：

* [LCM](https://lcm-proj.github.io/)
* [GStreamer](https://gstreamer.freedesktop.org/)
* [OpenCV 4.1.1](https://opencv.org/)

  * ⚠️ 编译时检查是否包含 GStreamer，没有则需根据官方文档安装
* [Paddle Inference C++ 预测库](https://paddleinference.paddlepaddle.org.cn/master/user_guides/download_lib.html)

  * ARM 部署请选择 **ARM 版本**

---

## 🔧 需要修改的配置

### `paddle_detection/CMakeLists.txt`

* `WITH_MKL` — 是否使用 MKL 或 OpenBLAS，TX2 必须设为 `OFF`
* `WITH_GPU` — 是否开启 GPU 预测（可选）
* `PADDLE_DIR` — C++ Paddle 路径
* `PADDLE_LIB_NAME` — Paddle 预测库名称，请在 `paddle_inference/lib/` 中确认实际名称
* `CUDA_LIB` — CUDA 路径
* `CUDNN_LIB` — cuDNN 路径
* `TENSORRT_INC_DIR` — TensorRT 头文件路径
* `TENSORRT_LIB_DIR` — TensorRT 库路径

### `tactile_paving/scripts/signalLampDetection.py`

* 修改第一行为本地 **Python 路径**

---

## 🛠️ 编译步骤

```bash
# 创建工作空间
mkdir ~/catkin_ws

# 解压项目源码到 src 目录
tar -zxvf src.tar.gz -C ~/catkin_ws/

# 进入工作空间
cd ~/catkin_ws

# 编译
catkin_make
```

---

## 📦 功能包说明

| 功能包                                                                         | 说明                |
| --------------------------------------------------------------------------- | ----------------- |
| `face_light_sdk_nano`                                                       | 控制机械狗头部灯光         |
| `paddle_detection`                                                          | 飞桨目标检测 C++ 版本     |
| `robot_voice`                                                               | 科大讯飞语音识别（仅支持 x86） |
| `slamware_ros_sdk` / `slamware_sdk`                                         | 雷达数据发布            |
| `tactile_paving`                                                            | 导盲场景逻辑            |
| `unitree_legged_msgs` / `unitree_legged_real` / `unitree_legged_sdk-master` | 宇树机器人控制功能包        |

---

## 🚀 主要运行命令

```bash
# 启动雷达
roslaunch slamware_ros_sdk slamware_ros_sdk_server_node.launch ip_address:=192.168.11.1

# 导盲场景（包含寻迹、雷达避障、头灯）
roslaunch tactile_paving Start_control.launch

# 语音控制
roslaunch tactile_paving start_voice.launch
```

---

## 📂 主要业务代码

| 文件路径                                            | 功能                             |
| ----------------------------------------------- | ------------------------------ |
| `tactile_paving/src/example_Tracing.cpp`        | 寻迹场景                           |
| `tactile_paving/src/lidar_node.cpp`             | 雷达避障                           |
| `tactile_paving/src/unitree_put_cmd.cpp`        | 订阅 `/cmd_vel` 并转为 Unitree 控制指令 |
| `tactile_paving/scripts/signalLampDetection.py` | Python 版本飞桨目标识别（有 bug，速度慢）     |
| `robot_voice/src/voice_control.cpp`             | 语音识别主逻辑                        |
| `paddle_detection/src/main.cc`                  | C++ 版本飞桨目标识别                   |
| `face_light_sdk_nano/src/main.cpp`              | 控制狗头部灯光                        |

---

## 🔍 可修改配置

* `tactile_paving/launch/Start_control.launch`
  👉 可在此修改场景启动配置

---

## 📖 TODO / 已知问题

* [ ] `signalLampDetection.py` 检测速度慢，需要优化
* [ ] Jetson TX2 平台需注意 `WITH_MKL=OFF`

---
