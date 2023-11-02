#include <iostream>
#include <vector>
#include <string>
#include <ctime>

// Base class for smart devices
class Device {
public:
    Device(int device_id, const std::string& device_type) : device_id(device_id), device_type(device_type) {}

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual std::string getStatus() const = 0;

protected:
    int device_id;
    std::string device_type;
};

// Light class, a subclass of Device
class Light : public Device {
public:
    Light(int device_id) : Device(device_id, "Light"), status("off") {}

    void turnOn() override {
        status = "on";
    }

    void turnOff() override {
        status = "off";
    }

    std::string getStatus() const override {
        return "Light " + std::to_string(device_id) + " is " + status + ".";
    }

private:
    std::string status;
};

// Thermostat class, a subclass of Device
class Thermostat : public Device {
public:
    Thermostat(int device_id) : Device(device_id, "Thermostat"), temperature(70) {}

    void turnOn() override {
        // Implement turnOn logic for Thermostat if needed
    }

    void turnOff() override {
        // Implement turnOff logic for Thermostat if needed
    }

    std::string getStatus() const override {
        return "Thermostat is set to " + std::to_string(temperature) + " degrees.";
    }

private:
    int temperature;
};

// DoorLock class, a subclass of Device
class DoorLock : public Device {
public:
    DoorLock(int device_id) : Device(device_id, "DoorLock"), status("locked") {}

    void turnOn() override {
        // Implement turnOn logic for DoorLock if needed
    }

    void turnOff() override {
        // Implement turnOff logic for DoorLock if needed
    }

    std::string getStatus() const override {
        return "Door is " + status + ".";
    }

private:
    std::string status;
};

// Factory for creating devices
class DeviceFactory {
public:
    static Device* createDevice(int device_id, const std::string& device_type) {
        if (device_type == "Light") {
            return new Light(device_id);
        }
        else if (device_type == "Thermostat") {
            return new Thermostat(device_id);
        }
        else if (device_type == "DoorLock") {
            return new DoorLock(device_id);
        }
        else {
            return nullptr; // Handle unknown device types
        }
    }
};

// Proxy class for controlling devices
class DeviceController {
public:
    void addDevice(Device* device) {
        devices.push_back(device);
    }

    void turnOn(int device_id) {
        for (auto& device : devices) {
            if (device->getStatus().find(" " + std::to_string(device_id) + " ") != std::string::npos) {
                device->turnOn();
            }
        }
    }

    void turnOff(int device_id) {
        for (auto& device : devices) {
            if (device->getStatus().find(" " + std::to_string(device_id) + " ") != std::string::npos) {
                device->turnOff();
            }
        }
    }

    std::string getStatusReport() const {
        std::string report;
        for (const auto& device : devices) {
            report += device->getStatus() + " ";
        }
        return report;
    }

private:
    std::vector<Device*> devices;
};

int main() {
    DeviceController controller;
    controller.addDevice(DeviceFactory::createDevice(1, "Light"));
    controller.addDevice(DeviceFactory::createDevice(2, "Thermostat"));
    controller.addDevice(DeviceFactory::createDevice(3, "DoorLock"));

    controller.turnOn(1);
    controller.turnOn(2);
    controller.turnOn(3);

    std::cout << controller.getStatusReport() << std::endl;

    return 0;
}
