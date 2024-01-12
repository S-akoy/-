#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 10 // ͣ�������������

typedef struct {
    int id; // �������
    int arrival_time; // ����ʱ��
    int parking_time; // ͣ��ʱ��
} Car;

typedef struct {
    Car* cars[MAX_CAPACITY]; // ͣ�����ڵĳ���
    int count; // ͣ�����ڳ���������
} ParkingLot;

typedef struct {
    Car* cars[MAX_CAPACITY]; // ����ϵĳ���
    int count; // ����ϳ���������
} WaitingLane;

void initializeParkingLot(ParkingLot* parkingLot) {  //��ʼ��ͣ����
    parkingLot->count = 0;
}

void initializeWaitingLane(WaitingLane* waitingLane) {  //��ʼ�����
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
        printf("���� %d ����ͣ������ͣ��λ�� %d\n", carId, parkingLot->count);
    } else {
        waitingLane->cars[waitingLane->count] = newCar;
        waitingLane->count++;
        printf("���� %d ���������ȴ�����ͣ����\n", carId);
    }
}

void leave(ParkingLot* parkingLot, WaitingLane* waitingLane, int carId, int currentTime) {
    int i;
    for (i = 0; i < parkingLot->count; i++) {
        if (parkingLot->cars[i]->id == carId) {
            Car* leavingCar = parkingLot->cars[i];
            leavingCar->parking_time = currentTime - leavingCar->arrival_time;
            printf("���� %d �뿪ͣ������ͣ��ʱ��Ϊ %dСʱ��Ӧ���ɷ���Ϊ %d\n Ԫ", leavingCar->id, leavingCar->parking_time, leavingCar->parking_time * 10);
            free(leavingCar);

            // ������ĳ�����ǰ�ƶ�һ��λ��
            for (int j = i + 1; j < parkingLot->count; j++) {
                parkingLot->cars[j - 1] = parkingLot->cars[j];
            }
            parkingLot->count--;

            // ����г����ڱ���ϵȴ������õ�һ��������ͣ����
            if (waitingLane->count > 0) {
                Car* nextCar = waitingLane->cars[0];
                for (int j = 1; j < waitingLane->count; j++) {
                    waitingLane->cars[j - 1] = waitingLane->cars[j];
                }
                waitingLane->count--;

                parkingLot->cars[parkingLot->count] = nextCar;
                parkingLot->count++;
                printf("���� %d �ӱ������ͣ������ͣ��λ�� %d\n", nextCar->id, parkingLot->count);
            }
            return;
        }
    }

    // ����Ҳ����뿪�ĳ���������Ƿ��ڱ���ϵȴ�
    for (i = 0; i < waitingLane->count; i++) {
        if (waitingLane->cars[i]->id == carId) {
            printf("���� %d �뿪���\n", carId);
            free(waitingLane->cars[i]);

            // ������ĳ�����ǰ�ƶ�һ��λ��
            for (int j = i + 1; j < waitingLane->count; j++) {
                waitingLane->cars[j - 1] = waitingLane->cars[j];
            }
            waitingLane->count--;
            return;
        }
    }

    printf("δ�ҵ����� %d\n", carId);
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
        printf("�����������(A)���� (L)�뿪 (Q)�˳���");
        scanf(" %c", &action);

        if (action == 'Q' || action == 'q') {
            break;
        }

        printf("�����복����ţ�");
        scanf("%d", &carId);

        currentTime++;

        if (action == 'A' || action == 'a') {
            arrive(&parkingLot, &waitingLane, carId, currentTime);
        } else if (action == 'L' || action == 'l') {
            leave(&parkingLot, &waitingLane, carId, currentTime);
        }
    }

    // �ͷ�ͣ�����ͱ����ʣ��ĳ����ڴ�
    for (int i = 0; i < parkingLot.count; i++) {
        free(parkingLot.cars[i]);
    }

    for (int i = 0; i < waitingLane.count; i++) {
        free(waitingLane.cars[i]);
    }

    return 0;
}