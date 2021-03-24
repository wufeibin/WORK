# Git

[Git教程](https://github.com/luotf/Git/blob/master/Git%E6%95%99%E7%A8%8B.md)

- Git属于分布式版本控制系统，而SVN属于集中式。集中式版本控制只有中心服务器拥有一份代码，而分布式版本控制每个电脑上都有一份完整代码。GitHub就是中心服务器，用来交换每个用户的修改。
- Git仓库和GitHub中心服务器仓库的传输通过SSH加密。主目录中的.ssh目录下有id_rsa(私钥)和id_rsa.pus(公钥)两个文件，将公钥内容复制到GitHub的SSH Keys中用于传输。
- 工作流：新建一个仓库后，当前目录就成了**工作目录**，工作目录下有一个隐藏目录.git，它属于Git的版本库。Git版本库有一个称为Stage**暂存区**和History**版本库**。History版本库中存有所有的分支，使用一个HEAD指针指向当前分支。

- Git命令

```
工作目录 ----add/rm----> 缓存区 ----commit----> 本地仓库 ----push----> 远程仓库
工作目录 <----checkout---- 缓存区 <-------- 本地仓库 <----pull---- 远程仓库

git init 创建当前目录新仓库
git clone git@github.com:wufeibin/WORK.git 克隆创建仓库
git branch 查看分支
git branch <name> 创建分支
git branch -d <name> 删除分支
git checkout <name> 切换分支
git checkout -b <name> 创建并切换分支
git checkout -- <filename> 回退替换工作目录的文件
git status 查看仓库状态
git diff <filename>
git diff <source_branch> <target_branch>
git add <filename>
git commit -m "xxxx"
git log
git reset HEAD <filename> 回退缓存区的修改至工作目录
git reset --hard HEAD^ 回退至上个版本
git reset --hard <id> 回退至某个版本
git reset --hard origin/master
git pull 更新本地仓库
git pull origin <branch>
git push 推送改动至远端仓库
git push origin <branch>

git fetch origin
git merge <branch> 合并某分支到当前分支
```



# RESTful
[RESTful API 设计规范](https://github.com/godruoyi/restful-api-specification)


RESTful架构，就是目前最流行的一种互联网软件架构。它结构清晰、符合标准、易于理解、扩展方便，所以正得到越来越多网站的采用。REST，即Representational State Transfer，表现层状态转化。如果一个架构符合REST原则，就称它为RESTful架构。



**1.资源（Resources）**: 每种资源对应一个特定的URI(统一资源定位符),URI为每一个资源的地址或独一无二的识别符;

**2.表现层（Representation）**:把"资源"具体呈现出来的形式，叫做它的"表现层"，URI只代表"资源"的位置。它的具体表现形式，应该在HTTP请求的头信息中用Accept和Content-Type字段指定，这两个字段才是对"表现层"的描述。

**3.状态转化（State Transfer）**:客户端想要操作服务器，必须通过某种手段，让服务器端发生"状态转化"。而这种转化是建立在表现层之上的，所以就是"表现层状态转化"。客户端用到的手段就是HTTP协议里面，四个表示操作方式的动词：GET、POST、PUT、DELETE。它们分别对应四种基本操作：GET用来获取资源，POST用来新建资源（也可以用于更新资源），PUT用来更新资源，DELETE用来删除资源。

总结:

- 每一个URI代表一种资源；
- 客户端和服务器之间，传递这种资源的某种表现层；
- 客户端通过四个HTTP动词，对服务器端资源进行操作，实现"表现层状态转化"。



对于资源的具体操作类型，由HTTP动词表示。 常用的HTTP动词有下面五个

- GET（SELECT）：从服务器取出资源（一项或多项）。 
- POST（CREATE）：在服务器新建一个资源。
- PUT（UPDATE）：在服务器更新资源（客户端提供改变后的完整资源）。
- PATCH（UPDATE）：在服务器更新资源（客户端提供改变的属性）。
- DELETE（DELETE）：从服务器删除资源。

还有两个不常用的HTTP动词。

- HEAD：获取资源的元数据。
- OPTIONS：获取信息，关于资源的哪些属性是客户端可以改变的。

下面是一些例子。

> GET /zoos：列出所有动物园  
>  POST /zoos：新建一个动物园  
>  GET /zoos/ID：获取某个指定动物园的信息  
>  PUT /zoos/ID：更新某个指定动物园的信息（提供该动物园的全部信息）  
>  PATCH /zoos/ID：更新某个指定动物园的信息（提供该动物园的部分信息）  
>  DELETE /zoos/ID：删除某个动物园  
>  GET /zoos/ID/animals：列出某个指定动物园的所有动物  
>  DELETE /zoos/ID/animals/ID：删除某个指定动物园的指定动物  

针对不同操作，服务器向用户返回的结果应该符合以下规范。

> GET /collection：返回资源对象的列表（数组）  
> GET /collection/resource：返回单个资源对象  
> POST /collection：返回新生成的资源对象  
> PUT /collection/resource：返回完整的资源对象  
> PATCH /collection/resource：返回完整的资源对象  
> DELETE /collection/resource：返回一个空文档  



# POCO

https://github.com/pocoproject/poco

https://pocoproject.org/docs/index.html



# 视频编解码

视频编码就是指通过特定的压缩技术，将某个视频格式文件转换成另一种视频格式文件的方式。

视频封装格式：把编码后的音视频数据以一定格式封装到一个容器，封装格式有 MKV、AVI、TS 等 

视频编码格式：

- MPEG 【MPEG-2 、 MPEG-4】
- H.26X 【H.263 、 H.264/AVC 、 H.265/IEVC】

视频解码后的格式（原始数据格式）：YUV

- NV12与YV12视频格式，是YUV的主要格式

图片格式：PNG格式、JPEG格式、TIFF格式、BMP格式、GIF格式



CUDA

https://my.oschina.net/zhangxu0512/blog/711577

https://www.cnblogs.com/marsggbo/p/11838823.html#gpu%E5%9E%8B%E5%8F%B7%E5%90%AB%E4%B9%89





1. core调试详解
2. limit设置



# 正则表达式







encrypt、decrypt、plaintext、ciphertext

Alic、Bob：相互通信
Eve：窃听者
Mallory：主动攻击者