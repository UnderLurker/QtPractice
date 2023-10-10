//
// Created by Administrator on 2023/10/8.
//

#include "NetworkTraffic.h"
#include <QDebug>
#define DEFAULT_BUFFER_SIZE 40960L

NetworkTraffic::NetworkTraffic() {
//    testAllRegedit();
    getInstance();
}

bool NetworkTraffic::getInstance() {
    InterfaceName.clear();
    uint32 type;
    uint32 ret;
    uint32 size = DEFAULT_BUFFER_SIZE;
    auto *data = new uint8_t[size];

    //获取的是下面的宏Counter
    //计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib\CurrentLanguage
    while((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA,"510",nullptr,&type,data,&size))!=ERROR_SUCCESS){
        if(ret == ERROR_MORE_DATA){
            size += DEFAULT_BUFFER_SIZE;
            delete [] data;
            data = new uint8_t [size];
        }
    }

    auto* dataBlock = (PERF_DATA_BLOCK*)data;
    auto* objectType = (PERF_OBJECT_TYPE*)((uint8_t *)dataBlock+dataBlock->HeaderLength);
    //循环遍历后续PERF_OBJECT_TYPE
    for(int i=0;i<dataBlock->NumObjectTypes;i++){
        if(objectType->ObjectNameTitleIndex == 510){
            uint32 offset = ULONG_MAX;
            auto* counterDefinition = (PERF_COUNTER_DEFINITION*)((uint8_t *)objectType+objectType->HeaderLength);
            for(int j=0;j<objectType->NumCounters;j++){
                if(counterDefinition->CounterNameTitleIndex == 520){
                    offset = counterDefinition->CounterOffset;
                    break;
                }
                counterDefinition = (PERF_COUNTER_DEFINITION*)((uint8_t *)counterDefinition + counterDefinition->ByteLength);
            }
            if(offset == ULONG_MAX){
                delete [] data;
                return false;
            }
            auto* instanceDefinition = (PERF_INSTANCE_DEFINITION*)((uint8_t *)objectType + objectType->DefinitionLength);
            for(int j=0;j<objectType->NumInstances;j++){
                auto* inName = (wchar_t *)((uint8_t *)instanceDefinition + instanceDefinition->NameOffset);
                auto *counterBlock = (PERF_COUNTER_BLOCK *)((uint8_t *)instanceDefinition + instanceDefinition->ByteLength);

                uint32 bandWidth = *(uint32*)((uint8_t *)counterBlock + offset);
                uint32 totalTraffic = 0;
                InterfaceName.emplace_back(inName);
                BandWidth.emplace_back(bandWidth);
                TotalTraffic.emplace_back((double)totalTraffic);
                downTotalTraffic.emplace_back(0);
                upTotalTraffic.emplace_back(0);

                instanceDefinition = (PERF_INSTANCE_DEFINITION*) ((uint8_t *)instanceDefinition + instanceDefinition->ByteLength + counterBlock->ByteLength);
            }
        }
        objectType = (PERF_OBJECT_TYPE*)((uint8_t*)objectType+objectType->TotalByteLength);
    }
    delete [] data;
    return true;
}

vector<double> NetworkTraffic::getTraffic(TrafficType _type) {
    vector<double> res(TotalTraffic.size(),0);

    uint32 type;
    uint32 ret;
    uint32 size = 0;
    auto *data = new uint8_t[size];

    //获取的是下面的宏Counter
    //计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib\CurrentLanguage
    while((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA,"510",nullptr,&type,data,&size))!=ERROR_SUCCESS){
        if(ret == ERROR_MORE_DATA){
            size += DEFAULT_BUFFER_SIZE;
            delete [] data;
            data = new uint8_t [size];
        }
    }

    auto* dataBlock = (PERF_DATA_BLOCK*)data;
    auto* objectType = (PERF_OBJECT_TYPE*)((uint8_t *)dataBlock+dataBlock->HeaderLength);
    //循环遍历后续PERF_OBJECT_TYPE
    for(int i=0;i<dataBlock->NumObjectTypes;i++){
        if(objectType->ObjectNameTitleIndex == 510){
            uint32 offset = ULONG_MAX;
            auto* counterDefinition = (PERF_COUNTER_DEFINITION*)((uint8_t *)objectType+objectType->HeaderLength);
            for(int j=0;j<objectType->NumCounters;j++){
                if(counterDefinition->CounterNameTitleIndex == _type){
                    offset = counterDefinition->CounterOffset;
                    break;
                }
                counterDefinition = (PERF_COUNTER_DEFINITION*)((uint8_t *)counterDefinition + counterDefinition->ByteLength);
            }
            if(offset == ULONG_MAX){
                delete [] data;
                return res;
            }
            auto* instanceDefinition = (PERF_INSTANCE_DEFINITION*)((uint8_t *)objectType + objectType->DefinitionLength);
            for(int j=0;j<objectType->NumInstances;j++){
                auto *counterBlock = (PERF_COUNTER_BLOCK *)((uint8_t *)instanceDefinition + instanceDefinition->ByteLength);
                auto* inName = (wchar_t *)((uint8_t *)instanceDefinition + instanceDefinition->NameOffset);
                auto iterator = std::find(InterfaceName.begin(), InterfaceName.end(),wstring(inName));

                if(iterator == InterfaceName.end()){
                    instanceDefinition = (PERF_INSTANCE_DEFINITION*) ((uint8_t *)instanceDefinition + instanceDefinition->ByteLength + counterBlock->ByteLength);
                    continue;
                }
                uint32 traffic = *(uint32*)((uint8_t *)counterBlock + offset);
                auto& vec = _type == AllTraffic == _type ? TotalTraffic : IncomingTraffic == _type ? downTotalTraffic : upTotalTraffic;

                res[iterator-InterfaceName.begin()] = (double)traffic - vec[iterator-InterfaceName.begin()];
                vec[iterator-InterfaceName.begin()] = (double)traffic;
                instanceDefinition = (PERF_INSTANCE_DEFINITION*) ((uint8_t *)instanceDefinition + instanceDefinition->ByteLength + counterBlock->ByteLength);
            }
        }
        objectType = (PERF_OBJECT_TYPE*)((uint8_t*)objectType+objectType->TotalByteLength);
    }
    delete [] data;
    return res;
}

void NetworkTraffic::update(int index){
    auto res1 = getTraffic(IncomingTraffic);
    auto res2 = getTraffic(OutGoingTraffic);
    netDown = QString::number(((int)(res1[index]*100/1000.0))/100.0);
    netUp = QString::number(((int)(res2[index]*100/1000.0))/100.0);
}

void NetworkTraffic::testAllRegedit() {
    uint32 type;
    uint32 ret;
    uint32 size = DEFAULT_BUFFER_SIZE;
    auto *data = new uint8_t[size];

    //获取的是下面的宏Counter
    //计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib\CurrentLanguage
    while((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA,"510",nullptr,&type,data,&size))!=ERROR_SUCCESS){
        if(ret == ERROR_MORE_DATA){
            size += DEFAULT_BUFFER_SIZE;
            delete [] data;
            data = new uint8_t [size];
        }
    }

    auto* dataBlock = (PERF_DATA_BLOCK*)data;
    auto* objectType = (PERF_OBJECT_TYPE*)((uint8_t *)dataBlock+dataBlock->HeaderLength);
    //循环遍历后续PERF_OBJECT_TYPE
    for(int i=0;i<dataBlock->NumObjectTypes;i++){
        qDebug()<<(int)objectType->ObjectNameTitleIndex;
        {
            vector<CounterOffset> offsets;
            auto* counterDefinition = (PERF_COUNTER_DEFINITION*)((uint8_t *)objectType+objectType->HeaderLength);
            for(int j=0;j<objectType->NumCounters;j++){
                CounterOffset counterOffset{};
                counterOffset.offset = counterDefinition->CounterOffset;
                counterOffset.nameIndex = counterDefinition->CounterNameTitleIndex;
                offsets.emplace_back(counterOffset);

                counterDefinition = (PERF_COUNTER_DEFINITION*)((uint8_t *)counterDefinition + counterDefinition->ByteLength);
            }
            auto* instanceDefinition = (PERF_INSTANCE_DEFINITION*)((uint8_t *)objectType + objectType->DefinitionLength);
            for(int j=0;j<objectType->NumInstances;j++){
                auto* inName = (wchar_t *)((uint8_t *)instanceDefinition + instanceDefinition->NameOffset);
                auto *counterBlock = (PERF_COUNTER_BLOCK *)((uint8_t *)instanceDefinition + instanceDefinition->ByteLength);

                qDebug()<<"name:"<<wstring(inName);
                for(CounterOffset item : offsets){
//                    qDebug()<<"nameIndex:"<<item.nameIndex<<"\tvalue:"<<*(uint32*)((uint8_t*)counterBlock+item.offset);
                }

                instanceDefinition = (PERF_INSTANCE_DEFINITION*) ((uint8_t *)instanceDefinition + instanceDefinition->ByteLength + counterBlock->ByteLength);
            }
        }
        objectType = (PERF_OBJECT_TYPE*)((uint8_t*)objectType+objectType->TotalByteLength);
    }
    delete [] data;
}
