#include <iostream>
#include <limits> 

#define MAX_CAPACITY 10 // ͣ�������������

struct Car {
    int id; // �������
    int arrival_time; // ����ʱ��
    int parking_time; // ͣ��ʱ��
};

struct ParkingLot {
    Car** cars; // ͣ�����ڵĳ���
    int count; // ͣ�����ڳ���������
};

struct WaitingLane {
    Car** cars; // ����ϵĳ���
    int count; // ����ϳ���������
};

// �ڴ���亯��
void allocateMemory(ParkingLot& parkingLot, WaitingLane& waitingLane) {
    parkingLot.cars = new Car*[MAX_CAPACITY];
    parkingLot.count = 0;
    waitingLane.cars = new Car*[MAX_CAPACITY];
    waitingLane.count = 0;
}

// �ڴ��ͷź���
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
		std::cout << "�����뵱ǰʱ��:";
		std::cin >> newCar->arrival_time;
		if (newCar->arrival_time < 24 && newCar->arrival_time > 0)
		{
			break;
		}
		if(typeid(newCar->arrival_time) != typeid(int)){
			std::cout << "ʱ�����������ȷ���Ƿ���ȷ����ʱ�䣡";
			break;
		}
		if (std::cin.fail()) {
                    std::cin.clear();// ��������־
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// ���Ե�ǰ�е�ʣ������ ͷ�ļ�#include <limits> 
		}
		std::cout << "ʱ�����������ȷ���Ƿ���ȷ����ʱ�䣡";
	}
		//std::cout << "��������Ҫͣ����ʱ��:";
		//std::cin >> newCar->parking_time;

    if (parkingLot.count < MAX_CAPACITY) {
        parkingLot.cars[parkingLot.count] = newCar;
        parkingLot.count++;
        std::cout << "���� " << carId << " ����ͣ������ͣ��λ�� " << parkingLot.count << "\n";
    } else {
        waitingLane.cars[waitingLane.count] = newCar;
        waitingLane.count++;
        std::cout << "���� " << carId << " ���������ȴ�����ͣ����\n";
    }
}


void leave(ParkingLot& parkingLot, WaitingLane& waitingLane, int carId, int currentTime) {
    for (int i = 0; i < parkingLot.count; i++) {
        if (parkingLot.cars[i]->id == carId) {
            Car* leavingCar = parkingLot.cars[i];
	while (true)
	{
		std::cout << "�����뵱ǰʱ��:";
		std::cin >> currentTime;
		getchar();
		if (std::cin.fail()) {
			// ��� cin.fail() ���㣬�� cin �������ˣ�
			// ��ô��Ҫ��ջ��������ȴ��û���������

			// ����������������ʱ��cin ��ǳ𡣼���cin ���¼�Լ���״̬��
			// ���״̬����ͨ�� cin.fail() �� cin.good() ��ȡ��
			// ��� cin ״̬��������������������õ���ֵ�ֱ�Ϊ 0 �� 1.
			// ��� cin ״̬�쳣����������������õ���ֵ�ֱ�Ϊ 1 �� 0, �� cin ���ǳ��ˡ�

			std::cin.clear();
			// ���� cin.clear(), ���Խ�� cin �ļǳ�״̬���� cin �ָ�������
			// ������ cin.fail() ��� 0, cin.good() ��� 1.

			// ��������Ӧ����ջ������ˡ���Ϊ���� cin �����������Ȼ�����뻺�����У�
			// ֱ����������Ļ�����Ҫ����

			std::cin.ignore(2048, '\n');
			}
		else if (currentTime >= 0 && currentTime <= 24) {
			// ����ܽ����ⲿ�֣�˵��û�н�����һ���֣�����cin ״̬������Ҳ���� x ����ȷ��ֵ�ˣ����ҷ�Χ��ȷ��
			
			// ��Ϊ��Χ��ȷ�����Բ���Ҫ���������ѭ����ȴ����롣ֱ���������ɡ�
			break;
		}

		// �����û��������
		std::cout << "����������������롣" << std::endl;
		// ���д���֮�󣬳���ص�ѭ����ͷ�����µȴ��û�����...
		// ���֮ǰ�û������˶������ݣ�������״̬��������ô cin ����������뻺�����������ݣ�
		// ���ǻ������Ȼ��ʾ�û��������롱�����ǲ�û�еȴ�������ֱ�Ӵӻ�����������ݵ�����

	}
		//if(isdigit(currentTime) ){
		//	std::cout << "ʱ�����������ȷ���Ƿ���ȷ����ʱ�䣡";
		//	continue;
		//}
		////if (std::cin.fail()) {
  ////                  std::cin.clear();// ��������־
  ////                  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// ���Ե�ǰ�е�ʣ������ ͷ�ļ�#include <limits> 
		////}
		//if (currentTime < 24 && currentTime > 0)
		//{
		//	break;
		//}
		//std::cout << "ʱ�����������ȷ���Ƿ���ȷ����ʱ�䣡";
		//std::cout << "ʱ�����������ȷ���Ƿ���ȷ����ʱ�䣡";
            std::cout << "���� " << leavingCar->id << " �뿪ͣ������ͣ��ʱ��Ϊ " << (currentTime - leavingCar->arrival_time) << "Сʱ��Ӧ���ɷ���Ϊ " << (currentTime - leavingCar->arrival_time) * 10 << "Ԫ\n";
            delete leavingCar;

            // ������ĳ�����ǰ�ƶ�һ��λ��
            for (int j = i + 1; j < parkingLot.count; j++) {
                parkingLot.cars[j - 1] = parkingLot.cars[j];
            }
            parkingLot.count--;

            // ����г����ڱ���ϵȴ������õ�һ��������ͣ����
            if (waitingLane.count > 0) {
                Car* nextCar = waitingLane.cars[0];
                for (int j = 1; j < waitingLane.count; j++) {
                    waitingLane.cars[j - 1] = waitingLane.cars[j];
                }
                waitingLane.count--;

                parkingLot.cars[parkingLot.count] = nextCar;
                parkingLot.count++;
                std::cout << "���� " << nextCar->id << " �ӱ������ͣ������ͣ��λ�� " << parkingLot.count << "\n";
            }
            return;
        }
    }

    // ����Ҳ����뿪�ĳ���������Ƿ��ڱ���ϵȴ�
    for (int i = 0; i < waitingLane.count; i++) {
        if (waitingLane.cars[i]->id == carId) {
            std::cout << "���� " << carId << " �뿪���\n";
            delete waitingLane.cars[i];

            // ������ĳ�����ǰ�ƶ�һ��λ��
            for (int j = i + 1; j < waitingLane.count; j++) {
                waitingLane.cars[j - 1] = waitingLane.cars[j];
            }
            waitingLane.count--;
            return;
        }
    }

    std::cout << "δ�ҵ����� " << carId << "\n";
	}

int main() {
    
    ParkingLot parkingLot;
    WaitingLane waitingLane; //��ʼ�� 

    allocateMemory(parkingLot, waitingLane); //�����ڴ�

    int currentTime = 0;
    char action;
    int carId;

    while (1) {
        std::cout << "�����������(A)���� (L)�뿪 (Q)�˳���";
        std::cin >> action;

        // ��������ַ�ת��Ϊ��д���Ա㴦���Сд����
        action = toupper(action);

        switch (action) {
            case 'A':
                std::cout << "�����복�����(����������������)��";
                std::cin >> carId;
                if (std::cin.fail()) {
                    std::cin.clear();// ��������־
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// ���Ե�ǰ�е�ʣ������ ͷ�ļ�#include <limits> 
                    std::cout << "���������������ȷ�ĳ�����š�\n";
                    break;
                }
                currentTime++; //ʱ���һ
                arrive(parkingLot, waitingLane, carId, currentTime);
                break;

            case 'L':
                std::cout << "�����복�����(����������������)��";
                std::cin >> carId;
                if (std::cin.fail()) {
                    std::cin.clear();// ��������־
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// ���Ե�ǰ�е�ʣ������ 
                    std::cout << "���������������ȷ�ĳ�����š�\n";
                    break;
                }
                currentTime++; //ʱ���һ
                leave(parkingLot, waitingLane, carId, currentTime);
                break;

            case 'Q':
                freeMemory(parkingLot, waitingLane);
                return 0;

            default:
                std::cout << "���������������ȷ�Ĳ���ָ�A, L, Q����\n";
                break;
        }
    }

    return 0;
}
