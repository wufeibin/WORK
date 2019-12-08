## grep 搜索数据

grep [options] pattern [file]

- grep xxx file
- grep -v xxx file 反向搜索，输出不匹配的行
- grep -n xxx file 显示行号
- grep -c xxx file 显示匹配的行数
- grep -e xxx -e yyy file 指定多个匹配模式，输出匹配xxx或yyy的行



* **ps** 显示某刻系统的进程信息
* **top** 动态显示显示系统的进程信息  
* **cat proc/500/maps** 查看进程的虚拟地址空间使用情况
* **cat proc/500/status** 查看进程的状态信息
* **cat proc/meminfo** 查看操作系统的内存使用情况

```
MemTotal:         171284 kB	//总物理内存大小
MemFree:            6632 kB	//空闲物理内存大小
Buffers:           10660 kB //文件的缓存的大小
Cached:            83580 kB //高速缓存存储器的大小
```
* **free** 查看系统内存使用情况
```
             total       used       free     shared    buffers     cached
Mem:     131916676  130603592    1313084    1539580    3569100   42805216
-/+ buffers/cache:   84229276   47687400

total：总物理内存
used：已使用物理内存
free：未使用物理内存
buffer/cache：缓存

total = used1 + free1
total = used2 + free2
used1 - used2 = buffer + cache
free2 - free1 = buffer + cache
```