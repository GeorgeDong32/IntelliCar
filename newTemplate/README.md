# STM32项目模板

## 项目模板文件结构

```
├─CORE					存放核心文件，包含启动文件和core_cm3
│  └─startup 			 存放启动文件，按需选择类型
├─FWLIB					FWLib
│  ├─inc
│  └─src
├─HARDWARE				外设文件
└─USER					用户文件
```

## 配置

### 应用模板

将本文件夹中的所有文件移动到目标项目文件夹下，在项目文件夹中新建项目

### 配置项目

选择合适芯片新建项目并分组，向各组中添加文件，其中CORE中只能添加一个`.s`启动文件。主义在USER组中不要选择`system_stm32f10x.c`

在编译设置中选择C/C++编译选项

* 在Define栏填入

  ```
  USE_STDPERIPH_DRIVER
  ```

* 将所有含有头文件的文件夹添加到`Include Paths`中

* 勾选C99 Mode

在Debug中配置调试器选项

完成配置

