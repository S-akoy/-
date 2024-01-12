#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 10 // 停车场的最大容量

typedef struct {
    int id; // 车辆编号
    int arrival_time; // 到达时间
    int parking_time; // 停留时间
} Car;

typedef struct {
    Car* cars[MAX_CAPACITY]; // 停车场内的车辆
    int count; // 停车场内车辆的数量
} ParkingLot;

typedef struct {
    Car* cars[MAX_CAPACITY]; // 便道上的车辆
    int count; // 便道上车辆的数量
} WaitingLane;

void initializeParkingLot(ParkingLot* parkingLot) {  //初始化停车场
    parkingLot->count = 0;
}

void initializeWaitingLane(WaitingLane* waitingLane) {  //初始化便道
    waitingLane->count = 0;
}

void arrive(ParkingLot* parkingLot, WaitingLane* waitingLane, int carId, int currentTime) {
    Car* newCar = (Car*)malloc(sizeof(Car));
    newCar->id = carId;
    newCar->arrival_time = currentTime;
    newCar->parking_time = 0;

    if (parkingLot->count < MAX_CAPACITY) {
        parkingLot->cars[parkingLot->count] = newCar;
        parkingLot->count++;
        printf("车辆 %d 进入停车场，停在位置 %d\n", carId, parkingLot->count);
    } else {
        waitingLane->cars[waitingLane->count] = newCar;
        waitingLane->count++;
        printf("车辆 %d 进入便道，等待进入停车场\n", carId);
    }
}

void leave(ParkingLot* parkingLot, WaitingLane* waitingLane, int carId, int currentTime) {
    int i;
    for (i = 0; i < parkingLot->count; i++) {
        if (parkingLot->cars[i]->id == carId) {
            Car* leavingCar = parkingLot->cars[i];
            leavingCar->parking_time = currentTime - leavingCar->arrival_time;
            printf("车辆 %d 离开停车场，停留时间为 %d小时，应交纳费用为 %d\n 元", leavingCar->id, leavingCar->parking_time, leavingCar->parking_time * 10);
            free(leavingCar);

            // 将后面的车辆往前移动一个位置
            for (int j = i + 1; j < parkingLot->count; j++) {
                parkingLot->cars[j - 1] = parkingLot->cars[j];
            }
            parkingLot->count--;

            // 如果有车辆在便道上等待，则让第一辆车进入停车场
            if (waitingLane->count > 0) {
                Car* nextCar = waitingLane->cars[0];
                for (int j = 1; j < waitingLane->count; j++) {
                    waitingLane->cars[j - 1] = waitingLane->cars[j];
                }
                waitingLane->count--;

                parkingLot->cars[parkingLot->count] = nextCar;
                parkingLot->count++;
                printf("车辆 %d 从便道进入停车场，停在位置 %d\n", nextCar->id, parkingLot->count);
            }
            return;
        }
    }

    // 如果找不到离开的车辆，检查是否在便道上等待
    for (i = 0; i < waitingLane->count; i++) {
        if (waitingLane->cars[i]->id == carId) {
            printf("车辆 %d 离开便道\n", carId);
            free(waitingLane->cars[i]);

            // 将后面的车辆往前移动一个位置
            for (int j = i + 1; j < waitingLane->count; j++) {
                waitingLane->cars[j - 1] = waitingLane->cars[j];
            }
            waitingLane->count--;
            return;
        }
    }

    printf("未找到车辆 %d\n", carId);
}

int main() {
    ParkingLot parkingLot;
    WaitingLane waitingLane;
    initializeParkingLot(&parkingLot);
    initializeWaitingLane(&waitingLane);

    int currentTime = 0;
    char action;
    int carId;

    while (1) {
        printf("请输入操作：(A)到达 (L)离开 (Q)退出：");
        scanf(" %c", &action);

        if (action == 'Q' || action == 'q') {
            break;
        }

        printf("请输入车辆编号：");
        scanf("%d", &carId);

        currentTime++;

        if (action == 'A' || action == 'a') {
            arrive(&parkingLot, &waitingLane, carId, currentTime);
        } else if (action == 'L' || action == 'l') {
            leave(&parkingLot, &waitingLane, carId, currentTime);
        }
    }

    // 释放停车场和便道上剩余的车辆内存
    for (int i = 0; i < parkingLot.count; i++) {
        free(parkingLot.cars[i]);
    }

    for (int i = 0; i < waitingLane.count; i++) {
        free(waitingLane.cars[i]);
    }

    return 0;
}