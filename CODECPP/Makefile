TARGET = main_exec
CXX = g++
LD = g++

# 编译选项
CCFLAGS += -std=c++11

# 链接选项
LDFLAGS += 

# 宏定义
GLOBAL_DEF += 
GLOBAL_DEF_F = $(addprefix -D, $(GLOBAL_DEF))

# 头文件路径
INCLUDES += ./
INCLUDES_F = $(addprefix -I, $(INCLUDES))

# 链接库文件
LIBS_FILES += pthread
LIBS_FILES_F = $(addprefix -l, $(LIBS_FILES))

# 链接库文件路径
LIBS_DIRS += ./
LIBS_DIRS_F = $(addprefix -L, $(LIBS_DIRS))

# 源文件
SRC_FILES += main.cpp
SRC_FILES += common.cpp
SRC_FILES += cpp_class.cpp
SRC_FILES += cpp_stl.cpp
SRC_FILES += file.cpp
OBJ_FILES = $(SRC_FILES:%.cpp=%.o)

# 链接生成目标文件
$(TARGET):$(OBJ_FILES)
	@echo LD $(notdir $@)
	$(LD) $(LDFLAGS) $(LIBS_FILES_F) $(LIBS_DIRS_F) $^ -o $(TARGET)

# 编译所有源文件
%.o: %.cpp
	@echo CC $(notdir $<)
	$(CXX) $(CCFLAGS) $(GLOBAL_DEF_F) $(INCLUDES_F) -c $<

# 清理
clean:
	$(RM) $(OBJ_FILES) $(TARGET) 