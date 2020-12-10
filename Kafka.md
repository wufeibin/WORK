[TOC]

# Kafka

## 1.简介

Kafka 是由 Linkedin 公司开发的，它是一个分布式的，支持多分区、多副本，基于 Zookeeper 的分布式消息流平台，它同时也是一款开源的**基于发布订阅模式的消息引擎系统**。

[Kafka源码](https://github.com/apache/kafka)

- **Producer**：生产者，push 消息到 Kafka 集群中的 broker 中；
- **Broker**：Kafka 集群由多个 Kafka 实例（server） 组成；
- **Topic**：producer 向 kafka 集群 push 的消息会被归于某一类别，即Topic，这本质上只是一个逻辑概念，面向的对象是 producer 和 consumer，producer 只需要关注将消息 push 到哪一个 Topic 中，而 consumer 只需要关心自己订阅了哪个 Topic；
- **Partition**：每一个 Topic 又被分为多个 Partitions，即物理分区；出于负载均衡的考虑，同一个 Topic 的 Partitions 分别存储于 Kafka 集群的多个 broker 上；而为了提高可靠性，这些 Partitions 可以由 Kafka 机制中的 replicas 来设置备份的数量；
- **Consumer**：消费者，从 Kafka 集群的 broker 中 pull 消息；

![enter image description here](https://images.gitbook.cn/e49bc290-cf95-11e8-8388-bd48f25029c6)



一个典型的 Kafka 体系架构包括若干 Producer，若干 broker（ Kafka 节点的服务器），若干 Consumer，以及一个 ZooKeeper 集群。Kafka通过 ZooKeeper 管理集群配置、选举 Leader 以及在 consumer group 发生变化时进行 Rebalance。Producer 使用 push模式将消息发布到 broker，Consumer 使用 pull模式从 broker 订阅并消费消息。

- 一个 topic 可以认为是一类消息，每个 topic 将被分成多个 partition，每个 partition 在存储层面是 append log 文件。任何发布到此 partition 的消息都会被追加到log文件的尾部，每条消息在文件中的位置称为 offset（偏移量）

- Topic 只是逻辑概念，面向的是 producer 和 consumer；而 Partition 则是物理概念。如果 Topic 不进行分区，而将 Topic 内的消息存储于一个 broker，那么关于该 Topic 的所有读写请求都将由这一个 broker 处理，吞吐量很容易陷入瓶颈。

  **Partiton 机制**可以极大的提高**吞吐量**，并且使得系统具备良好的**水平扩展**能力。假设一个 Topic 被分为 10 个 Partitions，Kafka 会根据一定的算法将 10 个 Partition 尽可能均匀的分布到不同的 broker（服务器）上，当 producer 发布消息时，producer 客户端可以采用算法选定目标 partition。在发送一条消息时，可以指定这个消息的 key，producer 根据这个 key 和 partition 机制来判断这个消息发送到哪个partition。

- 一个 partition 上由多个 segment 组成；segment 文件由两部分组成，分别为 “.index” 文件和 “.log” 文件，分别表示为 segment 索引文件和数据文件。

## 2.librdkafka

librdkafka 是一个C实现的高性能 Apache Kafka 客户端，为生产环境提供了一个可靠和高性能的客户端。librdkafka 同样也提供了传统的 C++ 接口。

- 创建kafka配置：rd_kafka_conf_new()
- 配置kafka参数：rd_kafka_conf_set()
- 设置回调函数：rd_kafka_conf_set_dr_msg_cb()
- 创建topic：rd_kafka_topic_new()
- 配置topic参数：rd_kafka_topic_conf_set()
- 销毁topic：rd_kafka_topic_destroy()
- 创建producer实例：rd_kafka_new()
- 销毁producer实例：rd_kafka_destroy()
- 异步发送消息：rd_kafka_produce()
- 同步发送消息：rd_kafka_poll()
- 添加brokerlist：rd_kafka_brokers_add()
- 开启consumer订阅：rd_kafka_subscribe()
- 轮询消息或事件，调用回调函数：rd_kafka_consumer_poll()
- 关闭consumer实例：rd_kafka_consumer_close()

## 3.ZooKeeper

ZooKeeper 是一个分布式的、开放源码的**分布式应用程序协调服务**，是 Google 的 Chubby 一个开源的实现。分布式应用程序可以基于它实现统一命名服务、状态同步服务、集群管理、分布式应用配置项的管理等工作。

在基于 Kafka 的分布式消息队列中，ZooKeeper 的作用有：broker 注册、topic 注册、producer 和 consumer 负载均衡、维护 partition 与 consumer 的关系、记录消息消费的进度以及 consumer 注册等。

 

# Protobuf

## 1.简介

protobuf（Protocol Buffers ）是 Google 的开源项目，是 Google 中立于语言、平台，可扩展的用于序列化结构化数据的解决方案。简单地说，protobuf 是用来对数据进行序列化和反序列化。

[Protobuf源码](https://github.com/protocolbuffers/protobuf)

[官方文档](https://developers.google.com/protocol-buffers)

## 2.使用

1. 定义proto文件，为需要序列化的数据结构添加一个消息（message），为消息中的每一个字段指定一个名字和类型。
2. 通过编译器编译proto文件，生成对应头文件（.pb.h ）和源文件（.pb.cc）
3. 使用生成的API读写消息

## 3.示例

- **tutorial.proto**

```
package tutorial;

message Person {
  required string name = 1;
  required int32 id = 2;
  optional string email = 3;

  enum PhoneType {
    MOBILE = 0;
    HOME = 1;
    WORK = 2;
  }

  message PhoneNumber {
    required string number = 1;
    optional PhoneType type = 2 [default = HOME];
  }

  repeated PhoneNumber phone = 4;
}

message AddressBook {
  repeated Person person = 1;
}
```

| proto 类型 | C++ 类型 |
| :--------- | :------- |
| double     | double   |
| float      | float    |
| int32      | int32    |
| uint32     | uint32   |
| int64      | int64    |
| uint64     | uint64   |
| sint32     | int32    |
| sint64     | int64    |
| fixed32    | uint32   |
| fixed64    | uint64   |
| sfixed32   | int32    |
| sfixed64   | int64    |
| bool       | bool     |
| string     | string   |
| bytes      | string   |

> - 文件以一个 package 声明开始，可以避免不同项目的命名冲突。
> - 字段尾部的序号，用于二进制编码的唯一"标签"。
> - required：必须提供字段值，否则会引起未初始化错误，序列化未初始化的消息会造成断言错误。
> - optional：可选提供字段值，当字段未被设置时取默认值。
> - repeated：可重复字段，类似于动态数组。

- 在proto文件扩展修改过程中，考虑到兼容性问题，需注意以下几点

> - 不可以修改任何已存在字段的标签数字
> - 不可以添加或删除任何 required 字段
> - 可以删除 optional 或 repeated 字段
> - 添加新的 optional 或 repeated 字段时，必须使用新的标签数字

- protoc编译器：`protoc -I$SRC_DIR --cpp_out=$DST_DIR tutorial.proto`
- **tutorial.pb.h**

```c++
Person类
// name
inline bool has_name() const;
inline void clear_name();
inline const ::std::string& name() const;
inline void set_name(const ::std::string& value);
inline void set_name(const char* value);
inline ::std::string* mutable_name();

// id
inline bool has_id() const;
inline void clear_id();
inline int32_t id() const;
inline void set_id(int32_t value);

// email
inline bool has_email() const;
inline void clear_email();
inline const ::std::string& email() const;
inline void set_email(const ::std::string& value);
inline void set_email(const char* value);
inline ::std::string* mutable_email();

// phone
inline int phone_size() const;
inline void clear_phone();
inline const ::google::protobuf::RepeatedPtrField< ::tutorial::Person_PhoneNumber >& phone() const;
inline ::google::protobuf::RepeatedPtrField< ::tutorial::Person_PhoneNumber >* mutable_phone();
inline const ::tutorial::Person_PhoneNumber& phone(int index) const;
inline ::tutorial::Person_PhoneNumber* mutable_phone(int index);
inline ::tutorial::Person_PhoneNumber* add_phone();
```

```c++
bool SerializeToString(string* output) const;	//序列化消息写到字符串
bool ParseFromString(const string& data);	//从字符串解析消息
bool SerializeToArray(void * data, int size) const;	//序列化消息至数组
bool ParseFromArray(const void * data, int size);	//从数组解析消息
bool SerializeToOstream(ostream* output) const;	//序列化消息至ostream
bool ParseFromIstream(istream* input);	//从istream解析消息
```

- **读写消息**

```c++
#include <iostream>
#include <fstream>
#include <string>
#include "tutorial.pb.h"
using namespace std;

void PromptForAddress(tutorial::Person* person) {
	person->mutable_name();
	person->set_id(1);
  person->set_email("xxx");
  tutorial::Person::PhoneNumber* phone_number = person->add_phone();
  phone_number->set_number("xxx");
  phone_number->set_type(tutorial::Person::MOBILE);
}

int main(int argc, char* argv[]) {
  // 在使用 C++ Protocol Buffer 库之前执行该宏。它可以保证避免不小心链接到一个与编译的头文件版本不兼容的库版本。如果被检查出来版本不匹配，程序将会终止。注意，每个 .pb.cc 文件在初始化时会自动调用这个宏。
  GOOGLE_PROTOBUF_VERIFY_VERSION;

	tutorial::AddressBook address_book;
  //写消息
  tutorial::Person* person;
  for(...) {
    person = address_book.add_person();
    person->mutable_name();
    person->set_id(1);
    person->set_email("xxx");
    tutorial::Person::PhoneNumber* phone_number = person->add_phone();
    phone_number->set_number("xxx");
    phone_number->set_type(tutorial::Person::MOBILE);   
  }
  fstream output(...);
  if (!address_book.SerializeToOstream(&output)) {
    cerr << "Failed to write address book." << endl;
    return -1;
  }
  
  //读消息
  fstream input(...);
  if (!address_book.ParseFromIstream(&input)) {
    cerr << "Failed to parse address book." << endl;
    return -1;
  }
  const tutorial::Person& person
  for (int i = 0; i < address_book.person_size(); i++) {
    person = address_book.person(i);
		person.id();
    person.name();
    person.has_email();
  }

  // 可选：释放 Protocol Buffer 库申请的所有全局对象
  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}
```
