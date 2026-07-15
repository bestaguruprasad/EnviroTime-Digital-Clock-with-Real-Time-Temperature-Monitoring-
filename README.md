**📌 Overview**

EnviroTime is a real-time embedded system built using the LPC2148 (ARM7TDMI-S) microcontroller. 
    It combines an accurate Real-Time Clock (RTC) with ambient temperature monitoring, displaying both on a 16×2 LCD.
    The system also includes a password-protected configuration mode, allowing authorized users to modify time, date, alarm settings, and the system password.
    The project is designed to demonstrate the integration of multiple embedded peripherals such as RTC, ADC, LCD, keypad, switches, and buzzer in a single real-time application.
    
**✨ Features**
    
🕒 Real-Time Clock (RTC) display
    🌡️ Live ambient temperature monitoring using LM35
    📅 Displays Date, Day, Month, and Year
    🔔 Alarm functionality with buzzer indication
    🔐 Password-protected edit mode
    ⌨️ Keypad-based user interface
    🔄 Editable RTC time/date and alarm settings
    🔑 Password change option
    🚫 Security lock after three incorrect password attempts
    
**🛠️ Hardware Requirements**

LPC2148 Development Board
    16×2 LCD Display
    LM35 Temperature Sensor
    4×4 Matrix Keypad
    Push Button Switches
    Buzzer
    Power Supply (5V)
    Connecting Wires
    
**📚 Software Requirements**

Keil uVision IDE
    Flash Magic
    Embe dded C
    LPC2148 Header Files
    Serial Programmer (for flashing firmware)
    
**🔧 Peripheral Usage**

Peripheral	Purpose
    RTC	Maintains current time and date
    ADC	Reads temperature from LM35
    LCD	Displays time, date, day, and temperature
    Keypad	Password entry and menu navigation
    Switch	Enter edit mode and stop alarm
    Buzzer	Alarm and security indication
    
**⚙️ System Workflow**

1. System Initialization
    The controller initializes all required peripherals:
        RTC
        LCD
        ADC
        Keypad
        Switch Inputs
        Buzzer
        After initialization, the system enters continuous monitoring mode.
    2. Continuous Monitoring
    The application continuously performs the following tasks:
        Read current RTC values
        Read ADC value from LM35
        Convert ADC reading into temperature
        Display information on LCD
        Monitor alarm status
        Check switch inputs
    Example LCD Display:
        12:45:30  T:28°C
        15/07/2026 WED
    3. Alarm Monitoring
    The controller continuously compares the current RTC time with the stored alarm time.
    When the alarm time matches:
        Buzzer turns ON
        Alarm remains active until the user presses the alarm switch
        Buzzer turns OFF after acknowledgment
    4. Secure Edit Mode
    When the Edit Switch is pressed:
        System requests password.
        User enters password using keypad.
        Entered password is verified.
    If correct:
        Edit mode is enabled.
    If incorrect:
        Access denied message displayed
        Wrong attempt counter increases
        Optional buzzer indication
    5. Wrong Password Protection
    If the wrong password is entered three consecutive times:
        System enters locked state
        Editing is disabled temporarily (or until reset)
    LCD displays:
        System Locked
    Optional:
        Buzzer alert
    6. Editable Parameters
    After successful authentication, the following parameters can be modified:
        Current Time
        Current Date
        Day
        Alarm Time
        System Password
    Navigation is performed using the keypad.
    7. Return to Monitoring
    After editing:
        Updated parameters are saved
        Edit mode exits
        Normal monitoring resumes


**🔄 System Flow**

Start
       │
       ▼
    Initialize Peripherals
       │
       ▼
    Display RTC Information
       │
       ▼
    Read Temperature
       │
       ▼
    Display Temperature
       │
       ▼
    Check Alarm
       │
       ├── Alarm Match?
       │       │
       │       ├── Yes → Activate Buzzer
       │       │          │
       │       │          ▼
       │       │   Wait for Alarm Switch
       │       │
       │       └── No
       │
       ▼
    Check Edit Switch
       │
       ├── Pressed?
       │       │
       │       ├── Yes
       │       │
       │       ▼
       │   Enter Password
       │       │
       │       ├── Correct?
       │       │      │
       │       │      ├── Yes → Edit Parameters
       │       │      │
       │       │      └── No
       │       │             │
       │       │             ▼
       │       │      Increment Counter
       │       │             │
       │       │      Counter == 3?
       │       │             │
       │       │        Lock System
       │       │
       │       ▼
       │   Return to Monitoring
       │
       ▼
    Repeat Forever

**👨‍💻 Developed Using**

Microcontroller: LPC2148 (ARM7TDMI-S)
    Programming Language: Embedded C
    Development IDE: Keil uVision
    Programming Tool: Flash Magic

