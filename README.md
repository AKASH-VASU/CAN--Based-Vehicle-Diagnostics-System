# CAN--Based-Vehicle-Diagnostics-System


Real-time vehicle diagnostics using CAN protocol (MCP2515) with ESP8266 web dashboard and alert system

**🚗 CAN-Based Embedded System for Vehicle Diagnostics (IoT Enabled)**


📌 Project Overview

This project implements a real-time vehicle diagnostic system using CAN protocol, integrating:

  - Arduino Uno + MCP2515 as ECU Simulator
    
  - ESP8266 + MCP2515 as CAN Receiver & IoT Module

The system reads and transmits vehicle data over a CAN Bus, processes it using ESP8266, and displays it on a real-time web dashboard with alerts.


🎯 Objectives

    * Implement CAN communication using MCP2515

    * Simulate ECU data similar to real vehicles

    * Transmit and receive CAN messages
    
    * Display real-time diagnostics on a web dashboard
    
    * Generate alerts for abnormal conditions

    
🛠️ Technologies Used


    * Arduino IDE
    
    * Embedded C
    
    * MCP2515 CAN Controller
    
    * SPI Communication
    
    * ESP8266 (Wi-Fi Module)
    
    * HTML
    
    * IoT (Web Server)

⚙️ System Architecture

*** Arduino + MCP2515 → CAN Bus → ESP8266 + MCP2515 → Wi-Fi → Web Dashboard**

🔄 Working Principle

    1. Arduino generates simulated vehicle parameters
    
    2. MCP2515 converts data into CAN frames and transmits over CAN Bus
    
    3. ESP8266 with MCP2515 receives CAN messages
    
    4. ESP8266 extracts parameter values
    
    5. A web server is hosted on ESP8266
    
    6. Dashboard displays real-time data with alerts
    

📊 Simulated Vehicle Parameters (12 Parameters)

| No | Parameter Name        | Unit  | Alert Condition        |
|----|----------------------|------|------------------------|
| 1  | Engine Temperature   | °C   | > 100°C               |
| 2  | Vehicle Speed        | km/h | > 80 km/h             |
| 3  | Fuel Level           | %    | < 20%                 |
| 4  | Engine RPM           | RPM  | > 4000                |
| 5  | Battery Voltage      | V    | < 11V                 |
| 6  | Oil Pressure         | PSI  | < 20                  |
| 7  | Throttle Position    | %    | Sudden fluctuation    |
| 8  | Coolant Level        | %    | < 30%                 |
| 9  | Intake Air Temp      | °C   | > 50°C                |
| 10 | Engine Load          | %    | > 90%                 |
| 11 | Fuel Efficiency      | km/l | < 10                  |
| 12 | Engine Status        | ON/OFF | Fault detection     |


🚨 Features

    * Real CAN communication using MCP2515
    
    * Real-time vehicle diagnostics
    
    * Web-based dashboard
    
    * Automatic alert system
    
    * Wireless monitoring via Wi-Fi
    
    * Scalable for real OBD-II systems
    

🌐 Web Dashboard

    * Live parameter updates
    
    * Auto-refresh (no manual reload required)
    
    * Alert highlighting
    
    * Accessible via IP address
    

🛠️ Installation & Setup

    #🔌 Hardware Required
    
          - Arduino Uno
          
          - ESP8266 (NodeMCU)
          
          - 2 × MCP2515 CAN Modules
          
          - CAN Bus wires
          
          - Jumper wires

          
💻 Software Required

    * Arduino IDE
    
    * MCP2515 CAN Library
    
    * ESP8266 Board Package
    

⚡ Setup Steps

    1. Connect MCP2515 to Arduino (SPI)
    
    2. Connect MCP2515 to ESP8266 (SPI)
    
    3. Connect CANH and CANL between modules
    
    4. Upload ECU simulation code (Arduino)
    
    5. Upload CAN receiver + web server code (ESP8266)
    
    6. Connect ESP8266 to Wi-Fi
    
    7. Open Serial Monitor → Note IP address
    
    8. Enter IP in browser → View dashboard
    

📡 Data Flow

    * Arduino → CAN Frame → MCP2515 → CAN Bus
    
    * ESP8266 → MCP2515 → Data Processing
    
    * ESP8266 → Web Server → Browser Dashboard  
    

🔮 Future Scope

    * Direct OBD-II integration
    
    * Cloud-based monitoring
    
    * Mobile app interface
    
    * AI-based predictive maintenance  
    

💡 Key Highlight

**This project demonstrates a real implementation of CAN protocol, similar to modern automotive systems used in vehicles for diagnostics and communication. **

👨‍💻 Author

Akash Vasu

akashvasu7977@gmail.com

Electronics & Communication Engineering.
