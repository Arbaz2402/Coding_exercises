#include <iostream>
#include <vector>
#include <string>
#include <string>
using namespace std;
// Base class for smart devices
class Device {
protected:
    int deviceID;
    string deviceType;

public:
    Device(int deviceID, string deviceType) : deviceID(deviceID), deviceType(deviceType) {}

    int getDeviceID() const {
        return deviceID;
    }

    virtual string getStatus() = 0;
};

// Light class, a subclass of Device
class Light : public Device {
private:
    string status;

public:
    Light(int deviceID) : Device(deviceID, "Light"), status("off") {}

    void turnOn() {
        status = "on";
    }

    void turnOff() {
        status = "off";
    }

    string getStatus() override {
        return "Light " + to_string(getDeviceID()) + " is " + status + ".";
    }
};

// Thermostat class, a subclass of Device
class Thermostat : public Device {
private:
    int temperature;

public:
    Thermostat(int deviceID) : Device(deviceID, "Thermostat"), temperature(70) {}

    string getStatus() override {
        return "Thermostat is set to " + to_string(temperature) + " degrees.";
    }
};

// DoorLock class, a subclass of Device
class DoorLock : public Device {
private:
    string status;

public:
    DoorLock(int deviceID) : Device(deviceID, "DoorLock"), status("locked") {}

    string getStatus() override {
        return "Door is " + status + ".";
    }
};

// Factory for creating devices
class DeviceFactory {
public:
    static Device* createDevice(int deviceID, string deviceType) {
        if (deviceType == "Light") {
            return new Light(deviceID);
        } else if (deviceType == "Thermostat") {
            return new Thermostat(deviceID);
        } else if (deviceType == "DoorLock") {
            return new DoorLock(deviceID);
        } else {
            return nullptr; // Handle unknown device types
        }
    }
};

// Proxy class for controlling devices
class DeviceController {
private:
    vector<Device*> devices;

public:
    void addDevice(Device* device) {
        devices.push_back(device);
    }

    void turnOn(int deviceID) {
        for (Device* device : devices) {
            if (device->getDeviceID() == deviceID) {
                if (Light* lightDevice = dynamic_cast<Light*>(device)) {
                    lightDevice->turnOn();
                }
            }
        }
    }

    void turnOff(int deviceID) {
        for (Device* device : devices) {
            if (device->getDeviceID() == deviceID) {
                if (Light* lightDevice = dynamic_cast<Light*>(device)) {
                    lightDevice->turnOff();
                }
            }
        }
    }

    string getStatusReport() {
        string report = "";
        for (Device* device : devices) {
            report += device->getStatus() + " ";
        }
        return report;
    }
};

int main() {
    DeviceController controller;
    controller.addDevice(DeviceFactory::createDevice(1, "Light"));
    controller.addDevice(DeviceFactory::createDevice(2, "Thermostat"));
    controller.addDevice(DeviceFactory::createDevice(3, "DoorLock"));
    controller.turnOn(1);
    controller.turnOn(2);
    controller.turnOn(3);
    cout << controller.getStatusReport() << endl;
    return 0;
}
