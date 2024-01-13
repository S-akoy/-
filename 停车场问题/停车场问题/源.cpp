#include <iostream>
#include <limits> 

#define MAX_CAPACITY 10 // 停车场的最大容量

struct Car {
    int id; // 车辆编号
    int arrival_time; // 到达时间
    int parking_time; // 停留时间
};

struct ParkingLot {
    Car** cars; // 停车场内的车辆
    int count; // 停车场内车辆的数量
};

struct WaitingLane {
    Car** cars; // 便道上的车辆
    int count; // 便道上车辆的数量
};

// 内存分配函数
void allocateMemory(ParkingLot& parkingLot, WaitingLane& waitingLane) {
    parkingLot.cars = new Car*[MAX_CAPACITY];
    parkingLot.count = 0;
    waitingLane.cars = new Car*[MAX_CAPACITY];
    waitingLane.count = 0;
}

// 内存释放函数
void freeMemory(ParkingLot& parkingLot, WaitingLane& waitingLane) {
    for (int i = 0; i < parkingLot.count; i++) {
        delete parkingLot.cars[i];
    }
    delete [] parkingLot.cars;

    for (int i = 0; i < waitingLane.count; i++) {
        delete waitingLane.cars[i];
    }
    delete [] waitingLane.cars;
}

void arrive(ParkingLot& parkingLot, WaitingLane& waitingLane, int carId, int currentTime) {
    Car* newCar = new Car;
    newCar->id = carId;
	while (true)
	{
		std::cout << "请输入当前时间:";
		std::cin >> newCar->arrival_time;
		if (newCar->arrival_time < 24 && newCar->arrival_time > 0)
		{
			break;
		}
		std::cout << "时间输入错误，请确定是否正确输入时间！";
	}
		//std::cout << "请输入您要停泊的时间:";
		//std::cin >> newCar->parking_time;

    if (parkingLot.count < MAX_CAPACITY) {
        parkingLot.cars[parkingLot.count] = newCar;
        parkingLot.count++;
        std::cout << "车辆 " << carId << " 进入停车场，停在位置 " << parkingLot.count << "\n";
    } else {
        waitingLane.cars[waitingLane.count] = newCar;
        waitingLane.count++;
        std::cout << "车辆 " << carId << " 进入便道，等待进入停车场\n";
    }
}


void leave(ParkingLot& parkingLot, WaitingLane& waitingLane, int carId, int currentTime) {
    for (int i = 0; i < parkingLot.count; i++) {
        if (parkingLot.cars[i]->id == carId) {
            Car* leavingCar = parkingLot.cars[i];
	while (true)
	{
		std::cout << "请输入当前时间:";
		std::cin >> currentTime;
		if (currentTime < 24 && currentTime > 0)
		{
			break;
		}
		std::cout << "时间输入错误，请确定是否正确输入时间！";
	}
            std::cout << "车辆 " << leavingCar->id << " 离开停车场，停留时间为 " << (currentTime - leavingCar->arrival_time) << "小时，应交纳费用为 " << (currentTime - leavingCar->arrival_time) * 10 << "元\n";
            delete leavingCar;

            // 将后面的车辆往前移动一个位置
            for (int j = i + 1; j < parkingLot.count; j++) {
                parkingLot.cars[j - 1] = parkingLot.cars[j];
            }
            parkingLot.count--;

            // 如果有车辆在便道上等待，则让第一辆车进入停车场
            if (waitingLane.count > 0) {
                Car* nextCar = waitingLane.cars[0];
                for (int j = 1; j < waitingLane.count; j++) {
                    waitingLane.cars[j - 1] = waitingLane.cars[j];
                }
                waitingLane.count--;

                parkingLot.cars[parkingLot.count] = nextCar;
                parkingLot.count++;
                std::cout << "车辆 " << nextCar->id << " 从便道进入停车场，停在位置 " << parkingLot.count << "\n";
            }
            return;
        }
    }

    // 如果找不到离开的车辆，检查是否在便道上等待
    for (int i = 0; i < waitingLane.count; i++) {
        if (waitingLane.cars[i]->id == carId) {
            std::cout << "车辆 " << carId << " 离开便道\n";
            delete waitingLane.cars[i];

            // 将后面的车辆往前移动一个位置
            for (int j = i + 1; j < waitingLane.count; j++) {
                waitingLane.cars[j - 1] = waitingLane.cars[j];
            }
            waitingLane.count--;
            return;
        }
    }

    std::cout << "未找到车辆 " << carId << "\n";
}

int main() {
    
    ParkingLot parkingLot;
    WaitingLane waitingLane; //初始化 

    allocateMemory(parkingLot, waitingLane); //分配内存

    int currentTime = 0;
    char action;
    int carId;

    while (1) {
        std::cout << "请输入操作：(A)到达 (L)离开 (Q)退出：";
        std::cin >> action;

        // 将输入的字符转换为大写，以便处理大小写输入
        action = toupper(action);

        switch (action) {
            case 'A':
                std::cout << "请输入车辆编号(请输入大于零的数字)：";
                std::cin >> carId;
                if (std::cin.fail()) {
                    std::cin.clear();// 清除错误标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 忽略当前行的剩余输入 头文件#include <limits> 
                    std::cout << "输入错误，请输入正确的车辆编号。\n";
                    break;
                }
                currentTime++; //时间加一
                arrive(parkingLot, waitingLane, carId, currentTime);
                break;

            case 'L':
                std::cout << "请输入车辆编号(请输入大于零的数字)：";
                std::cin >> carId;
                if (std::cin.fail()) {
                    std::cin.clear();// 清除错误标志
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// 忽略当前行的剩余输入 
                    std::cout << "输入错误，请输入正确的车辆编号。\n";
                    break;
                }
                currentTime++; //时间加一
                leave(parkingLot, waitingLane, carId, currentTime);
                break;

            case 'Q':
                freeMemory(parkingLot, waitingLane);
                return 0;

            default:
                std::cout << "输入错误，请输入正确的操作指令（A, L, Q）。\n";
                break;
        }
    }

    return 0;
}
