# B20_Group34

# River Gauge System for Bolgoda Lake

## Introduction
Monitoring water levels in natural water bodies is crucial for flood prevention, water resource management, and environmental conservation. Bolgoda Lake, one of Sri Lanka’s largest freshwater lakes, experiences fluctuations due to climate change, rainfall patterns, and human activities. Traditional monitoring methods are often costly and inefficient, necessitating an automated solution.

The River Gauge System for Bolgoda Lake is an IoT-based solution designed to provide real-time monitoring of water levels and environmental conditions. By integrating various sensors, microcontrollers, and wireless communication modules, this system ensures efficient and continuous data collection, transmission, and analysis.

## Problem in Brief
Bolgoda Lake plays a significant role in local fisheries, agriculture, and tourism. However, its water levels are subject to unpredictable fluctuations, leading to risks of flooding, droughts, and environmental degradation. Existing monitoring methods require manual effort and are not scalable. A real-time automated system is needed to address these challenges effectively.

## Project Overview
This project implements an IoT-based river gauge system to monitor water levels and temperature variations. The system comprises:
- **HC-SR04 Ultrasonic Sensor**
- **LM35 Analog Temperature Sensor** 
- **DS18B20 Digital Temperature Sensor**
- **Arduino Uno** 
- **ESP32 Wi-Fi Module**

The system continuously collects and transmits data, enabling real-time monitoring through an interactive web application. Automated alerts notify authorities when water levels reach critical thresholds, enhancing disaster preparedness.

## Components Used and Their Functionality

### 1. Microcontrollers & Communication Modules
- **Arduino Uno**: Reads data from sensors, processes it, and communicates with the ESP32.
- **ESP32 Wi-Fi Module**: Transmits collected data to the cloud for remote access.

### 2. Sensors
- **HC-SR04 Ultrasonic Sensor**: Measures water level by calculating the time taken for sound waves to travel to and from the water surface.
- **LM35 Temperature Sensor**: Monitors ambient air temperature.
- **DS18B20 Digital Temperature Sensor**: Measures water temperature with high accuracy.

### 3. Other Components
- **Breadboard**: Used for circuit prototyping and easy modifications.
- **Jumper Wires**: Establish electrical connections between components.
- **Power Supply (Battery/Adapter)**: Ensures continuous operation of the system.

## System Functionality
1. The **HC-SR04 sensor** emits ultrasonic pulses and measures the time taken for the echo to return, determining the water level.
2. The **LM35 and DS18B20 sensors** record air and water temperatures.
3. The **Arduino Uno** processes sensor data and forwards it to the ESP32.
4. The **ESP32** transmits the data wirelessly to a cloud platform for real-time visualization.
5. The system generates **alerts** if water levels exceed critical thresholds.

This project provides a scalable and cost-effective solution for real-time water level monitoring, benefiting environmental management and disaster preparedness.

## Circuit Diagram

