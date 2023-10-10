//
// Created by Administrator on 2023/10/8.
//

#ifndef CLIONWIDGET_NETWORKTRAFFIC_H
#define CLIONWIDGET_NETWORKTRAFFIC_H

#include <windows.h>
#include <vector>
#include <string>
#include <QString>

using namespace std;

struct CounterOffset{
private:
    using uint32 = unsigned long;
public:
    uint32 nameIndex;
    uint32 offset;
};

//获取流量类型
enum TrafficType{
    AllTraffic		= 388,//总的流量
    IncomingTraffic	= 264,//输入流量
    OutGoingTraffic	= 506 //输出流量
};

class NetworkTraffic {
    using uint32 = unsigned long;
public:
    explicit NetworkTraffic();
    ~NetworkTraffic() = default;
    vector<double> getTraffic(TrafficType _type);
    void update(int index = 0);
    void testAllRegedit();
private:
    vector<wstring> InterfaceName;//PERF_INSTANCE_DEFINITION后面的名字
    vector<uint32> BandWidth;
    vector<double> TotalTraffic;
    vector<double> downTotalTraffic;
    vector<double> upTotalTraffic;
private:
    bool getInstance();
public:
    QString netDown;
    QString netUp;
};


#endif //CLIONWIDGET_NETWORKTRAFFIC_H
