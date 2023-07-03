# IntelliCar

> 智能小车-中山大学电子线路开放性实验项目
>
> Copyright (c) GeorgeDong32. All rights reserved.

以STM32F103RCT6为核心的两驱超声波避障小车

## 项目结构

```bash
IntelliCar
├─CORE        #STM32 COre
├─FWLIB       #STM32 Firmware Library
│  ├─inc
│  └─src
├─HARDWARE    #外设文件
├─Listings    #list文件
├─Objects     #编译生成文件
└─USER        #主程序
```

> 其中CORE和FWLIB打包在Release中，Listings和Objects文件夹需自行在本地创建

## 实现功能

### 超声波避障

通过舵机和超声波模块实现对左前右三个方向的测距，并进行判断和行动操作。

## License

Repository is under CC BY-NC-SA License.

本作品采用 <a rel="license" href="https://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a> 进行许可。<br />
<a rel="license" href="https://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
