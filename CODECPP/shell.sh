#!/bin/bash
# -------------------------------------------------------------------------------
# Date         : 2020/12/31
# Author       : wufeibin
# Description  : 实例练习&总结

# 1、控制语句：if | case ｜ for | while | until | break | continue
# 2、内置变量
#    $0：脚本文件名称
#    $1：第1个位置参数
#    $#：位置参数个数
#    $@/*：所有的位置参数
#    $?：退出状态码
#    $PATH：可执行文件的搜索路径
#    $PWD：当前工作目录
# 3、数值比较：-eq、-ne、-ge、-gt、-le、-lt
# 4、字符串比较：=、!=、>、<、-n(长度不为0)、-z(长度为0)
# 5、文件比较：-e、-f、-d、-s、-r、-w、-x

# -------------------------------------------------------------------------------

function PrintColor {
    # 字体颜色码：重置=0，黑色=30，红色=31，绿色=32，黄色=33，蓝色=34，洋红=35，青色=36，白色=37
    echo "\033[31m This is Red Color \033[0m"

    # 背景颜色码：重置=0，黑色=40，红色=41，绿色=42，黄色=43，蓝色=44，洋红=45，青色=46，白色=47
    echo "\033[41m This is Red Background \033[0m"

    # 其他数字参数：0 关闭所有属性、1 设置高亮度（加粗）、4 下划线、5 闪烁、7 反显、8 消隐
    echo "\033[32;47;1;5m This is Test \033[0m"
}

# 文件替换/备份
function ReplaceBak {
    
}


Birthday() {
    read -p "Pleas input your birthday (MMDD, ex> 0709): " bir

    #获取目前的时间，输出格式为MMDD
    now=`date +%m%d`

    #判断当前的时间与输入的时间是否一致
    if [ "$bir" == "$now" ]; then
            echo "Happy Birthday to you!!!"
    #判断输入的日期是否大于当前日期
    elif [ "$bir" -gt "$now" ]; then
            year=`date +%Y`
            # +%s参数：自UTC 时间 1970-01-01 00:00:00 以来所经过的秒数
            # 两个相减得到多的秒数，除以60，60，24最终得到离生日的天数
            total_d=$(($((`date --date="$year$bir" +%s`-`date +%s`))/60/60/24))
            echo "Your birthday will be $total_d later"
    else
            year=$((`date +%Y`+1))
            total_d=$(($((`date --date="$year$bir" +%s`-`date +%s`))/60/60/24))
            echo "Your birthday will be $total_d later"
    fi
}

# 查看cpu信息
CpuInfo() {
    echo "Frequency : `cat /proc/cpuinfo | grep "model name" | uniq | awk -F ':' '{print $2}'`"
    echo "CPU cores : `cat /proc/cpuinfo | grep "cpu cores" | uniq |awk -F ':' '{print $2}'`"
    echo "Logic Count : `cat /proc/cpuinfo | grep "processor" | sort -u | wc -l `"
    echo "CPU cores : `cat /proc/cpuinfo | grep "Physical" | sort -u | wc -l `"
    echo "CPU cores : `cat /proc/cpuinfo | grep "cache size" | uniq |awk -F ':' '{print $4,$5}'`"
}

# 根据压缩文件的格式正确选择解压方式
compress() {
    case ${1##*.} in
        bz2)
            tar jzxf $1
            ;;
        gz)
            tar zxvf $1
            ;;
        bz)
            tar xjvf $1
            ;;
        tar)
            tar xvf $1
            ;;
        tgz)
            tar xzf $1
            ;;
        zip)
            unzip $1
            ;;
        *)
            echo "wrong file type"
    esac
}

# 以 2017-12-20.log 格式每日生成一个文件，并删除一年以前的文件。
function1() {
    #时间格式：date +%F、date +%y%m%d、date +%Y-%m-%d-%H-%M-%S
    d=`date +%F` #将命令输出赋给变量：`` 或 $()
    dir=/data/logs/disklog
    if [ ! -d $dir ]
    then
        mkdir -p $dir
    fi
    df -h > $dir/$d.log #输出重定向，写入覆盖文件：>；追加到文件末尾：>> 
    find $dir/ -mtime +365 |xargs rm
}

# 找到/123目录下所有后缀名为.txt的文件，打包压缩为123.tar.gz
function2() {
    find /123/ -type f -name "*.txt" > /tmp/txt.list
    tar -czvf 123.tar.gz `cat /tmp/txt.bak.list |xargs`
}

# 把一个文本文档的前5行中包含字母的行删除掉，同时把6到10行中的全部字母删除掉。
function3() {
    sed -n '1,5'p 1.txt |sed '/[a-zA-Z]/d' #把一个文本文档的前5行中包含字母的行删除掉
    sed '1,5d' 1.txt |sed '1,5s/[a-zA-Z]//g' #把6到10行中的全部字母删除掉。
}

# 把文本里面每三行内容合并到一行
function4() {
    n=1
    cat $1 | while read line #逐行遍历
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
}

# 当时间是0点和12点时，需要将目录/data/log/下的文件全部清空，而其他时间统计每个文件的大小，一个文件一行，输出到一个按日期和时间为名字的日志里。
function5() {
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
}

echo "\033[32;47;1;5mTool Menu\033[0m"
PS3="Please choose your option: "
select option in "Option1" "Option2" "Option3" "Test" "Exit"
do
    case $option in
        "Option1")
            Birthday;
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


