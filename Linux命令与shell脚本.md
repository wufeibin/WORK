# 一、Linux命令

[Linux命令大全](https://man.linuxde.net/)

### grep 搜索数据

- grep -n xxx file 【显示行号】
- grep -v xxx file 【反向搜索，输出不匹配的行】
- grep -c xxx file 【显示匹配的行数】
- grep -A 2 xxx file 【显示匹配内容和后2行】
- grep -B 2 xxx file 【显示匹配内容和前2行】
- grep -C 2 xxx file 【显示匹配内容和前后2行】
- grep -e xxx -e yyy file, grep -E 'xxx|yyy' file, egrep 'xxx|yyy' file 【或匹配】

### find 递归查找文件
- find [path] -name file
- find [path] -type f -name "*.txt" 【f 普通文件，d 目录】
- find . -type f -name "*.txt" -exec printf "File: %s\n" {} \;

### tail 显示文件末尾内容 

- tail -f file 【循环显示文件末尾内容】

### tar 归档

- tar -xzvf xxx.tar.gz 
- tar -czvf xxx.tar.gz [path]

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

### netstat 查看网络端口

- netstat -anp

### nm 查看文件中的符号

### ldd 查看程序/库依赖的共享库列表



### 

### xargs 

- find . -name "1.txt" | xargs ls 【与管道配合使用，将标准输出转化为参数】

### sed 流编辑器

- echo this is xxx | sed 's/xxx/yyy/'
- sed 's/xxx/yyy/' file 【替换文本中的字符串】
- sed 's/xxx/yyy/g' file 【/g 替换每一行中的所有匹配】
- sed -n 's/xxx/yyy/p' file 【-n选项和p命令一起使用，只打印那些发生替换的行】
- sed -e 's/brown/green/p; s/dog/cat/' file 【-e选项，同一行里执行多条命令】
- sed -f script.sed file

### awk|gawk

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

- 用分号将多个命令串起来执行
- 将命令输出赋给变量：`` 或 $()
- date +%y%m%d
- 输出重定向：将命令的结果输出到文件，而不是标准输出
  - \> 写入覆盖文件
  - \>> 追加到文件末尾
  - 永久重定向 exec 1>abc.txt
- 管道：| 将一个命令的输出作为另外一个命令的输入
- 退出码：exit 1、查看退出码：echo $？
- 布尔运算符
  - [ condition1 ] && [ condition2 ]
  - [ condition1 ] || [ condition2 ]

| 数值比较  |              |
| --------- | ------------ |
| n1 -eq n2 | n1等于n2     |
| n1 -ne n2 | n1不等于n2   |
| n1 -ge n2 | n1大于等于n2 |
| n1 -gt n2 | n1大于n2     |
| n1 -le n2 | n1小于等于n2 |
| n1 -lt n2 | n1小于n2     |
| **字符串比较** |                 |
| str1 = str2  | str1和str2相同  |
| str1 != str2 | str1和str2不同  |
| str1 < str2  | str1比str2小    |
| str1 > str2  | str1比str2大    |
| -n str1      | str1的长度不为0 |
| -z str1      | str1的长度为0   |

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


