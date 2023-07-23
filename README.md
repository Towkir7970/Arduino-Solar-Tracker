# Arduino Solar Tracker with Environmental Monitoring

![Arduino Solar Tracker](solar_tracker_banner.png)

The Arduino Solar Tracker is a single-axis solar tracking system that automatically adjusts the position of a solar panel to maximize its exposure to sunlight throughout the day. Additionally, it features environmental monitoring using sensors such as LDR, DHT11, and a flame sensor for added safety and efficiency.

## 📝 Project Overview

In this project, we have utilized the following components:

- **Servo Motor**: To move the solar panel according to the position of the sun.
- **LDR (Light Dependent Resistor)**: To detect the intensity of light and adjust the solar panel's position accordingly.
- **DHT11 Sensor**: To monitor humidity and temperature in the surrounding environment.
- **Flame Sensor**: To detect the presence of fire.
- **Buzzer and LED**: To indicate system status and provide alerts in case of fire.

## ⚙️ System Functionality

1. **Solar Tracking**: The system tracks the sun's movement throughout the day by adjusting the solar panel's position using the servo motor. This ensures maximum solar energy utilization.

2. **Environmental Monitoring**: The DHT11 sensor constantly measures the temperature and humidity of the environment. This information is displayed on an LCD screen connected to the Arduino.

3. **Fire Detection**: The flame sensor is utilized to detect fire. If a fire is detected, the system will shut down immediately for safety purposes.

4. **Safety Shutdown**: If the temperature or humidity levels are not within the desired range, the system will automatically turn off to prevent any damage.

5. **Alarm and LED Indication**: In the event of a fire detection, a buzzer will sound continuously, and an LED will turn on until the fire is extinguished.

## 🚀 How to Set Up

1. Clone the repository to your local machine:

```bash
git clone https://github.com/your-username/arduino-solar-tracker.git
```

2. Connect the Arduino board to your computer.

3. Upload the Arduino code (`solar_tracker_code.ino`) to the board.

4. Assemble the components as per the circuit diagram provided in the repository.

5. Power up the system, and it will start functioning.

## 🛠️ Components Used

- Arduino Board
- Servo Motor
- LDR (Light Dependent Resistor)
- DHT11 Sensor
- Flame Sensor
- Buzzer
- LED
- LCD Display

## 🤝 Contributing

Contributions are welcome! If you have any ideas for improvements or want to extend the functionality of the system, feel free to open an issue or submit a pull request.

## 📄 License

This project is licensed under the [MIT License](LICENSE).

## 📧 Contact

For any questions or suggestions, please contact us at solar.tracker.team@example.com.

## 🎉 Acknowledgments

I would like to thank the open-source community for their valuable contributions and support.

---
