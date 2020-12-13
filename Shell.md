# 一、Linux命令

[Linux命令大全](https://man.linuxde.net/)

### grep 搜索数据

- grep -n xxx file 【显示行号】
- grep -r xxx path 【递归查找目录文件】
- grep -v xxx file 【反向搜索，输出不匹配的行】
- grep -w xxx file 【显示全词匹配的行】
- grep -c xxx file 【显示匹配的行数】
- grep -l xxx * 【显示匹配的文件名】
- grep -A 2 xxx file 【显示匹配内容和后2行】
- grep -B 2 xxx file 【显示匹配内容和前2行】
- grep -C 2 xxx file 【显示匹配内容和前后2行】
- grep -e xxx -e yyy file, grep -E 'xxx|yyy' file, egrep 'xxx|yyy' file 【或匹配】
- grep   '2020-08-3[0-9]' file

### find 递归查找文件
- find [path] -name file
- find [path] -type f -name "*.txt" 【f 普通文件，d 目录】
- find . -type f -name "*.txt" -exec printf "File: %s\n" {} \;

### tail 显示文件末尾内容

- tail -f file 【循环显示文件末尾内容】
- tail -n 10 【显示文件末尾n行内容】

### tar 归档

- tar -xzvf xxx.tar.gz -C [path] 【解压缩文件】
- tar -czvf xxx.tar.gz [file] 【打包压缩文件】

### zip/unzip 压缩/解压zip文件
- zip -r xxx.zip ./*
- unzip -d /home xxx.zip

### gzip/gunzip 压缩/解压gz文件
- gzip -c -r xxx >xxx.gz
- gunzip -c xxx.gz >xxx

### ln 创建链接文件
- ln -snf 【生成文件的软连接】

### du 查看目录的硬盘使用情况
- du -h -c path
- du -sh *

### netstat 查看网络端口

- netstat -anp

### nm 查看目标文件的符号表

### ldd 查看程序/库依赖的共享库
- ldd -r xxx.so 【-r选项，数据对象和函数的重定位】

### readelf 查看elf目标文件信息

- readelf -sD xxx.so 【查看elf文件的动态符号表】

### objdump 查看目标文件的构成

### xargs 配合管道｜使用

- find . -name "1.txt" | xargs ls 【与管道配合使用，将标准输出转化为参数】

### sed 流编辑器

- echo this is xxx | sed 's/xxx/yyy/'
- sed 's/xxx/yyy/' file 【替换文本中的字符串】
- sed 's/xxx/yyy/g' file 【/g 替换每一行中的所有匹配】
- sed -n 's/xxx/yyy/p' file 【-n选项和p命令一起使用，只打印那些发生替换的行】
- sed -e 's/brown/green/; s/dog/cat/' file 【-e选项，同一行里执行多条命令】
- sed -f script.sed file
- sed -n '/2020-08-30-15-38-[0-9]/,/2020-08-30-15-50-[0-9]/p' file 【,选项，选定行范围】

### awk

- awk 'BEGIN{ commands } pattern{ commands } END{ commands }'
  - 第一步：执行`BEGIN{ commands }`语句
  - 第二步：从文件或标准输入逐行读取，执行`pattern{ commands }`语句
  - 第三步：执行`END{ commands }`语句

- echo -e "A line 1\nA line 2" | awk 'BEGIN{ print "Start" } { print; print $1 } END{ print "End" }'
  - $0 整行内容
  - $n 第n个字段
  - NF 字段数

- awk -F: '{print $1}' data.txt 【-F指定分隔符 : 】



### top 查看系统的实时运行情况

### free 查看系统内存使用情况

```
             total       used       free     shared    buffers     cached
Mem:     131916676  130603592    1313084    1539580    3569100   42805216
-/+ buffers/cache:   84229276   47687400

total：总物理内存 used：已使用物理内存 free：未使用物理内存 buffer/cache：缓存
total = used + free
```



- cat proc/500/maps 查看进程的虚拟地址空间使用情况
- cat proc/500/status 查看进程的状态信息
- cat proc/meminfo 查看操作系统的内存使用情况





# 二、Shell脚本

| 数值比较  |              |
| --------- | ------------ |
| n1 -eq n2 | n1等于n2     |
| n1 -ne n2 | n1不等于n2   |
| n1 -ge n2 | n1大于等于n2 |
| n1 -gt n2 | n1大于n2     |
| n1 -le n2 | n1小于等于n2 |
| n1 -lt n2 | n1小于n2     |


| 字符串比较  |              |
| --------- | ------------ |
| str1 = str2  | str1和str2相同  |
| str1 != str2 | str1和str2不同  |
| str1 < str2  | str1比str2小    |
| str1 > str2  | str1比str2大    |
| -n str1      | str1的长度不为0 |
| -z str1      | str1的长度为0   |


| 文件比较 |                              |
| -------- | ---------------------------- |
| -e file  | 检查file是否存在             |
| -f file  | 检查file是否存在并是一个文件 |
| -d file  | 检查file是否存在并是一个目录 |
| -r file  | 检查file是否存在并可读       |
| -s file  | 检查file是否存在并非空       |
| -w file  | 检查file是否存在并可写       |
| -x file  | 检查file是否存在并可执行     |

 


- if | case

```
#!bin/bash
str="yyy"
if [ $str = "xxx" ]; then
    echo "xxx"
elif [ $str = "yyy" ]; then
    echo "yyy"
else
    echo "zzz"
fi
```

```
#!bin/bash
case $1 in
jack | lisa)
    echo "Welcome, $1"
    echo "Please";;
mike)
    echo "xxx";;
james)
    echo "yyy";;
*)
    echo "zzz";;
esac
```

- for | while | until | break | continue

```
#!/bin/bash
for file in `pwd`/*
do
    echo "file : $file"
done

for (( a=1, b=10; a <= 10; a++, b-- ))
do
    echo "$a - $b"
done
```

```
var=10
while [ $var -gt 0 ]
do
    echo $var
    var=$[ $var - 1 ]
done
```

```
var=10
until [ $var -eq 0 ]
do
    echo $var
    var=$[ $var - 1 ]
done
```

- function

```
function name {
	commands
}

name() {
	commands
}
```



**内置变量**

- $0：脚本文件名称

- $1：第1个位置参数

- $#：位置参数个数

- $@/*：所有的位置参数

- $?：退出状态码

- $PATH：可执行文件的搜索路径

- $PWD：当前工作目录




## Shell实例

- 菜单脚本

```shell
#!/bin/bash

echo "Tool Menu"
PS3="Please choose your option: "
select option in "Option1" "Option2" "Option3" "Test" "Exit"
do
    case $option in
        "Option1")
            echo "option 1";;
        "Option2")
            echo "option 2";;
        "Option3")
            ls;;
        "Test")
            pwd;;
        "Exit")
            break ;;
        *)
            echo "invalid option"
            break ;;
    esac
done
```

- 输入一个数字，运行对应的一个命令。

```shell
#!/bin/bash
echo "1:date; 2:ls 3:who 4:pwd"
read -p "Please input a number: " n
echo ${n:=1}	# 默认值为1
if [ -z "$n" ]
then
    echo "请输入一个纯数字,范围1-4."
    exit
fi

${n=1}
case $n in 
    1)
      date
      ;;
    2)
      ls
      ;;
    3)
      who
      ;;
    4)
      pwd
      ;;
    *)
      echo "请输入1-4的数字"
      ;;
esac
```

- 以 2017-12-20.log 格式每日生成一个文件，并删除一年以前的文件。

```shell
#!/bin/bash
#时间格式：date +%F、date +%y%m%d、date +%Y-%m-%d-%H-%M-%S
d=`date +%F` #将命令输出赋给变量：`` 或 $()
dir=/data/logs/disklog
if [ ! -d $dir ]
then
    mkdir -p $dir
fi
df -h > $dir/$d.log #输出重定向，写入覆盖文件：>；追加到文件末尾：>> 
find $dir/ -mtime +365 |xargs rm
```

- 找到/123目录下所有后缀名为.txt的文件，打包压缩为123.tar.gz

```shell
#!/bin/bash
find /123/ -type f -name "*.txt" > /tmp/txt.list
tar -czvf 123.tar.gz `cat /tmp/txt.bak.list |xargs`
```

- 把一个文本文档的前5行中包含字母的行删除掉，同时把6到10行中的全部字母删除掉。

```shell
#!/bin/bash
sed -n '1,5'p 1.txt |sed '/[a-zA-Z]/d' #把一个文本文档的前5行中包含字母的行删除掉
sed '1,5d' 1.txt |sed '1,5s/[a-zA-Z]//g' ##把6到10行中的全部字母删除掉。
```

- 当时间是0点和12点时，需要将目录/data/log/下的文件全部清空，而其他时间统计每个文件的大小，一个文件一行，输出到一个按日期和时间为名字的日志里。

```shell
#!/bin/bash
dir=/tmp/log_stat
t=`date +%d%H`
t1=`date +%H`
logdir=/data/log

[ -d $dir ] || mkdir $dir #或运算符，同-o
[ -f $dir/$t.log ] && rm -f $dir/$t.log #与运算符，同-a

if [ $t == "00" -o $t1 == "12" ]
then
    for f in `find $logdir/ -type f`
    do
      > $f
    done
else
    for f in `find $logdir/ -type f`
    do
      du -sh $f >> $dir/$t.log
    done
fi
```

- 把文本里面每三行内容合并到一行

```shell
#!/bin/bash
n=1
cat $1 |while read line #逐行遍历
do
    n1=$[$n%3]
    if [ $n1 -eq 0 ]
    then
      echo "$line"
    else
      echo -n "$line " #不换行
    fi
      n=$[$n+1]
done
```

