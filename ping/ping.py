import socket
import array,struct,time,select

def recive_ping(my_socket,timeout):
    timeleft = timeout
    while True:
        starttime=time.time()
        select_=select.select([my_socket],[],[],timeleft)
        if select_[0]==[]:
            print("timeout")
            return -1
        t=time.time()-starttime
        return  t

def checksum(data):
    if(len(data)%2!=0):
        data+=b'\x00'
    a=array.array('H',data)
    s=0
    for d in a:
        s=s+d
    s=(~s)&0xffff
    return s

def send_packet(my_socket,destination_addr):
    header = struct.pack('bbHh',8,0,1,1)
    data=0
    data=struct.pack('d',data)
    checks=checksum(header+data)
    packet=struct.pack('bbHHh',8,0,checks,1,1)+data
    my_socket.sendto(packet,(destination_addr,1))
    t=recive_ping(my_socket, 5)
    print(t)

def do(addr):
    icmp=socket.getprotobyname('icmp')
    s=socket.socket(socket.AF_INET,socket.SOCK_RAW,icmp)  
    #第一个参数domain协议集 ：AF_INET 表示ipv4网络  AF_INET6表示ipv6  AF_UNIX 表示本地套字节 
    #第二个参数type ：SOCK_STEAM 面向流服务  SOCK_DGRAM 面向报文服务  SOCK_SEQPACKET 可靠的连续的数据包服务 SOCK_RAW 原始套字节
    #第三个参数protocol ：指定实际使用的传输协议
    #原型 int socket(int domain, int type, int protocol);
    send_packet(s, addr)

do("8.8.8.8") 
