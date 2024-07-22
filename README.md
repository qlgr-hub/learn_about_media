## 音视频开发学习
### learn about media (简称lam) 
* 一套简单的音视频处理接口
* 可以用多种开源框架实现这套接口，且应用不需要直接依赖这些开源框架的api（也就是可以灵活切换不同的实现）
* 目前初步用ffmpeg实现了，format\codec 的基础代码，进一步的扩展开发和相关测试、例子等还在继续...
### 环境
* docker/ 目录下是我自己使用的环境的配置，可以根据个人的需要进行调整使用
* scripts/ 目录下是我用编译 ffmpeg 时使用的脚本（仅供参考）
### Diagram
![Class Diagram](http://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/qlgr-hub/learn_about_media/main/learn_about_media/uml/basic_structure.puml)
### References
* https://ffmpeg.org/download.html#get-sources
* https://ffmpeg.org/doxygen/trunk/examples.html
* https://zhuanlan.zhihu.com/p/672431324
* 《深入理解FFmpeg》 刘歧，赵军，杜金房，赵文杰，宋韶颍