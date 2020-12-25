Python API tutorial
=====================

## 1. Background

The core functions of Cyber RT are developed in C++. We also provide more python interfaces to help developers build their own utilities for specific projects.

## 2. Cyber RT Python Interfaces

The python interfaces of Cyber RT are wrapper the corresponding C++ interfaces. The implementation doesn't rely on other third-party tools, e.g. swig, which makes it easier to maintain.

## 3. Overview of Python Interfaces in Cyber RT

So far, the python interfaces covers:

* access the information of channels
* server/client communication
* query informatoin in record files
* read and write from/to record files
* Time/Duration/Rate related operations
* Timer

### 3.1 Read/Write of Channels

Steps shown as below:
  1. First create a Node；
  2. Create corresponding reader or writer;
  3. If write to a channel, use write interface in writer.
  4. If read from a channel, use the spin interface in the node, and process the messages in your callback function

The interfaces are shown below:

```python
class Node:
    """
    Class for cyber Node wrapper.
    """

    def create_writer(self, name, data_type, qos_depth=1):
        """
        create a topic writer for send message to topic.
        @param self
        @param name str: topic name
        @param data_type proto: message class for serialization
        """

   def create_reader(self, name, data_type, callback, args=None):
        """
        create a topic reader for receive message from topic.
        @param self
        @param name str: topic name
        @param data_type proto: message class for serialization
        @callback fn: function to call (fn(data)) when data is
                   received. If args is set, the function must
                   accept the args as a second argument,
                   i.e. fn(data, args)
        @args any: additional arguments to pass to the callback
        """
	def create_client(self, name, request_data_type, response_data_type):
	"""
	"""
	def create_service(self, name, req_data_type, res_data_type, callback, args=None):

    def spin(self):
        """
        spin in wait and process message.
        @param self
        """

class Writer(object):
    """
    Class for cyber writer wrapper.
    """
    def write(self, data):
        """
        writer msg string
        """
```

### 3.2 Record Interfaces

Read from record：

1. Create a RecordReader;
2. Read messages from Record;

Write to record：

1. Create a RecordWriter
2. Write messages to record；

The interfaces are shown below:

```python
class RecordReader(object):
    """
    Class for cyber RecordReader wrapper.
    """
    def read_messages(self, start_time=0, end_time=18446744073709551615):
        """
        read message from bag file.
        @param self
        @param start_time:
        @param end_time:
        @return: generator of (message, data_type, timestamp)
        """
	def get_messagenumber(self, channel_name):
        """
        return message count.
        """
	def get_messagetype(self, channel_name):
        """
        return message type.
        """
	def get_protodesc(self, channel_name):
        """
        return message protodesc.
        """
	def get_headerstring(self):
        """
        return message header string.
        """
	def reset(self):
        """
        return reset.
        ""
        return _CYBER_RECORD.PyRecordReader_Reset(self.record_reader)

    def get_channellist(self):
        """
        return channel list.
        """
        return _CYBER_RECORD.PyRecordReader_GetChannelList(self.record_reader)


class RecordWriter(object):
    """
    Class for cyber RecordWriter wrapper.
    """
	def open(self, path):
        """
        open record file for write.
        """
	def write_channel(self, channel_name, type_name, proto_desc):
        """
        writer channel by channelname,typename,protodesc
        """
	def write_message(self, channel_name, data, time, raw = True):
        """
        writer msg:channelname,data,time,is data raw
        """

	def set_size_fileseg(self, size_kilobytes):
        """
        return filesegment size.
        """

    def set_intervaltime_fileseg(self, time_sec):
        """
        return file interval time.
        """

    def get_messagenumber(self, channel_name):
        """
        return message count.
        """

    def get_messagetype(self, channel_name):
        """
        return message type.
        """

    def get_protodesc(self, channel_name):
        """
        return message protodesc.
        """

```

### 3.3 Time Interfaces

```python
class Time(object):
	@staticmethod
    def now():
        time_now = Time(_CYBER_TIME.PyTime_now())
        return time_now

    @staticmethod
    def mono_time():
        mono_time = Time(_CYBER_TIME.PyTime_mono_time())
        return mono_time

    def to_sec(self):
        return _CYBER_TIME.PyTime_to_sec(self.time)

    def to_nsec(self):
        return _CYBER_TIME.PyTime_to_nsec(self.time)

    def sleep_until(self, nanoseconds):
        return _CYBER_TIME.PyTime_sleep_until(self.time, nanoseconds)
```

### 3.4 Timer Interfaces

```python
class Timer(object):

    def set_option(self, period, callback, oneshot=0):
        """
        set the option of timer.
        @param period The period of the timer, unit is ms.
        @param callback The tasks that the timer needs to perform.
        @param oneshot 1:perform the callback only after the first timing cycle
        0:perform the callback every timed period
        """

    def start(self):

    def stop(self):

```

## 4. Examples

### 4.1 Read from Channel

See examples/cyber_py3/listener.py

### 4.2 Write to Channel

See examples/cyber_py3/talker.py

### 4.3 Read and Write Messages from/to Record File

See examples/cyber_py3/record.py
