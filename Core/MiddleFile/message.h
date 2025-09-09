//
// Created by tKinsde on 2025/5/24.
//

#ifndef AGRICULTURAL_SYSTEM_MESSAGE_H
#define AGRICULTURAL_SYSTEM_MESSAGE_H

enum SensorType_t{
    NONE,
    AHT20,
    LIGHT_SENSOR

};
typedef struct {
    enum SensorType_t type;
    union {
        float light_intensity;  // 光照强度
        struct {
            float temperature;  // 温度
            float humidity;     // 湿度
        }AHT20;
    }DATA;
} SensorMessage_t;



#endif //AGRICULTURAL_SYSTEM_MESSAGE_H
