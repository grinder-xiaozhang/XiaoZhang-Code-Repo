# 25 年云台追踪工程

基于 STM32F4 的云台追踪固件工程，包含应用程序、外设驱动、STM32 标准外设库和 Keil 工程配置。

## 获取源码

点击仓库右上方 **Code → Download ZIP** 下载全部文件，或使用 Git：

```bash
git clone https://github.com/zjh19117327745-cmyk/XiaoZhang-Code-Repo.git
```

源码已直接展开在仓库中，可在线查看。最初上传的 ZIP 作为原始归档保留；后续修改以展开后的源码为准。

## 目录

| 路径 | 内容 |
| --- | --- |
| `USER/main.c` | 应用程序入口及控制逻辑 |
| `USER/Template.uvprojx` | Keil uVision 工程文件 |
| `USER/` | 板级配置、电机控制、串口及相关模块 |
| `SYSTEM/` | 延时、定时器、编码器、OLED、PID 等驱动模块 |
| `CORE/` | Cortex-M4 内核头文件和启动汇编 |
| `FWLIB/` | STM32F4 标准外设库 |
| `README/README.txt`、`readme.txt` | 原工程附带说明，部分内容来自初始模板 |

## 开发环境与编译

原工程配置如下：

- 芯片：STM32F407ZG（Cortex-M4）。
- 工具：Keil MDK / uVision 5。
- 编译器：ARM Compiler 5.06 update 7（build 960）。
- 设备包：Keil.STM32F4xx_DFP 3.1.1。
- 编译目标：`Template`。
- 工程宏：`STM32F40_41xxx`、`USE_STDPERIPH_DRIVER`。

1. 安装上述开发工具、编译器和设备包。
2. 打开 `USER/Template.uvprojx`，确认工程已选用 ARM Compiler 5。
3. 在 Keil 中执行 **Rebuild**；工程配置的输出目录为 `OBJ/`。
4. 根据实际开发板、下载器和接线配置调试与下载选项，再烧录固件。

接线信息可参考 `USER/引脚.txt` 和源码中的配置；使用前请核对实际硬件。VS Code/EIDE 等辅助配置中的本机工具路径需要按自己的安装位置调整。

## 版本管理

仓库跟踪源码和工程配置，编译输出及本机调试缓存通过 `.gitignore` 排除。修改代码后，将所需文件暂存、提交并推送即可更新项目。

本次整理保留了原始源码内容，并核对了 Keil 工程中引用的 64 个文件均已包含；尚未重新编译或进行硬件验证。

## 授权说明

第三方代码保留其原有版权和授权声明。原创部分尚未指定单独的开源许可证，后续由作者明确授权范围。
