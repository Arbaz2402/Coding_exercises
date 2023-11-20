#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

// Observer Pattern: Observer Interface
class Observer
{
public:
    virtual void update() = 0;
};

// Observer Pattern: Subject Interface
class Subject
{
public:
    virtual void addObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
    virtual void notify() = 0;
};

// Base class for smart devices
class Device : public Subject
{
protected:
    int deviceID;
    string deviceType;

public:
    Device(int deviceID, string deviceType) : deviceID(deviceID), deviceType(deviceType) {}

    int getDeviceID() const
    {
        return deviceID;
    }

    virtual string getStatus() const = 0;

    // Observer Pattern: Subject methods
    void addObserver(Observer *observer) override {}
    void removeObserver(Observer *observer) override {}
    void notify() override {}
};

// Light class, a subclass of Device
class Light : public Device, public Observer
{
private:
    string status;

public:
    Light(int deviceID) : Device(deviceID, "Light"), status("off") {}

    void turnOn()
    {
        status = "on";
        notify(); // Notify observers (if any) about the change
    }

    void turnOff()
    {
        status = "off";
        notify(); // Notify observers (if any) about the change
    }

    string getStatus() const override
    {
        return "Light " + to_string(getDeviceID()) + " is " + status + ".";
    }

    // Observer Pattern: Observer method
    void update() override
    {
        cout << "Light " << getDeviceID() << "'s status changed: " << getStatus() << endl;
    }
};

// Thermostat class, a subclass of Device
class Thermostat : public Device, public Observer
{
private:
    int temperature;

public:
    Thermostat(int deviceID) : Device(deviceID, "Thermostat"), temperature(70) {}

    void setTemperature(int temp)
    {
        temperature = temp;
        notify(); // Notify observers (if any) about the change
    }

    string getStatus() const override
    {
        return "Thermostat is set to " + to_string(temperature) + " degrees.";
    }

    // Observer Pattern: Observer method
    void update() override
    {
        cout << "Thermostat " << getDeviceID() << "'s status changed: " << getStatus() << endl;
    }
};

// DoorLock class, a subclass of Device
class DoorLock : public Device, public Observer
{
private:
    string status;

public:
    DoorLock(int deviceID) : Device(deviceID, "DoorLock"), status("locked") {}

    void unlock()
    {
        status = "unlocked";
        notify(); // Notify observers (if any) about the change
    }

    void lock()
    {
        status = "locked";
        notify(); // Notify observers (if any) about the change
    }

    string getStatus() const override
    {
        return "Door is " + status + ".";
    }

    // Observer Pattern: Observer method
    void update() override
    {
        cout << "DoorLock " << getDeviceID() << "'s status changed: " << getStatus() << endl;
    }
};

// Factory for creating devices
class DeviceFactory
{
public:
    static Device *createDevice(int deviceID, string deviceType)
    {
        if (deviceType == "Light")
        {
            return new Light(deviceID);
        }
        else if (deviceType == "Thermostat")
        {
            return new Thermostat(deviceID);
        }
        else if (deviceType == "DoorLock")
        {
            return new DoorLock(deviceID);
        }
        else
        {
            return nullptr; // Handle unknown device types
        }
    }
};

class DeviceController : public Observer
{
private:
    vector<Device *> devices;

public:
    void addDevice(Device *device)
    {
        devices.push_back(device);
        device->addObserver(this); // DeviceController is also an observer for all devices
    }

    void removeDevice(int deviceID)
    {
        auto it = find_if(devices.begin(), devices.end(), [deviceID](Device *device) {
            return device->getDeviceID() == deviceID;
        });

        if (it != devices.end())
        {
            devices.erase(it);
        }
    }

    void turnOn(int deviceID)
    {
        for (Device *device : devices)
        {
            if (device->getDeviceID() == deviceID)
            {
                if (Light *lightDevice = dynamic_cast<Light *>(device))
                {
                    lightDevice->turnOn();
                }
            }
        }
    }

    void turnOff(int deviceID)
    {
        for (Device *device : devices)
        {
            if (device->getDeviceID() == deviceID)
            {
                if (Light *lightDevice = dynamic_cast<Light *>(device))
                {
                    lightDevice->turnOff();
                }
            }
        }
    }

    void setTemperature(int deviceID, int temperature)
    {
        for (Device *device : devices)
        {
            if (device->getDeviceID() == deviceID)
            {
                if (Thermostat *thermostatDevice = dynamic_cast<Thermostat *>(device))
                {
                    thermostatDevice->setTemperature(temperature);
                }
            }
        }
    }

    void unlockDoor(int deviceID)
    {
        for (Device *device : devices)
        {
            if (device->getDeviceID() == deviceID)
            {
                if (DoorLock *doorLockDevice = dynamic_cast<DoorLock *>(device))
                {
                    doorLockDevice->unlock();
                }
            }
        }
    }

    void lockDoor(int deviceID)
    {
        for (Device *device : devices)
        {
            if (device->getDeviceID() == deviceID)
            {
                if (DoorLock *doorLockDevice = dynamic_cast<DoorLock *>(device))
                {
                    doorLockDevice->lock();
                }
            }
        }
    }

    // Schedule devices to turn on/off at a particular time
    void setSchedule(int deviceID, const string &time, const string &action)
    {
        cout << "Scheduled action for Device " << deviceID << " at " << time << ": " << action << endl;
    }

    void addTrigger(const string &triggerType, const string &comparison, int threshold, const string &action)
    {
        cout << "Trigger added: " << triggerType << " " << comparison << " " << threshold << " - Action: " << action << endl;
    }

    string getStatusReport() const
    {
        string report = "";
        for (Device *device : devices)
        {
            report += device->getStatus() + " ";
        }
        return report;
    }

    // Observer Pattern: Observer method
    void update() override
    {
        cout << "DeviceController received an update. Status Report: " << getStatusReport() << endl;
    }
};

int main()
{
    DeviceController controller;
    controller.addDevice(DeviceFactory::createDevice(1, "Light"));
    controller.addDevice(DeviceFactory::createDevice(2, "Thermostat"));
    controller.addDevice(DeviceFactory::createDevice(3, "DoorLock"));

    // Example commands based on the provided problem statement
    controller.turnOn(1);
    controller.setTemperature(2, 75);
    controller.addTrigger("temperature", ">", 75, "turnOff(1)");

    // Print the initial status report
    cout << "Initial Status Report: " << controller.getStatusReport() << endl;

    // Simulate the passage of time to trigger scheduled actions
    controller.setSchedule(1, "06:00", "Turn On");

    // Simulate changes in devices to trigger automation
    controller.turnOn(1);
    controller.setTemperature(2, 80);

    return 0;
}
