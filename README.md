# Science Olympiad Electric Vehicle Control System

An autonomous electric vehicle designed and built for Science Olympiad. The vehicle uses an Arduino-based control system and Hall-effect encoder feedback to travel a calculated distance along a mechanically configured curved path.

## Vehicle

![Completed electric vehicle](images/vehicle.jpg)

## Project Overview

The objective of this project was to design and build an electric vehicle capable of navigating a curved course and stopping at a designated endpoint.

The vehicle's movement was determined using two geometric inputs:

- The perpendicular distance from the apex of the curve to the straight line between the starting position and endpoint.
- The straight-line distance from the vehicle's starting position to the endpoint.

These measurements were used to determine the vehicle's required mechanical steering adjustment and travel distance.

The front wheels were mechanically adjusted before each run, while an Arduino controlled the motor and monitored vehicle movement.

## Hardware

The vehicle was designed and assembled from the ground up, including its chassis and electronic control system.

**Main Components:**

- Arduino Uno — Main microcontroller responsible for vehicle control.
- DC Motor with Hall-effect Encoder — Provides propulsion and rotational feedback.
- Motor Driver — Interfaces the Arduino with the DC motor.
- Hall-effect Encoder — Measures motor rotation to estimate vehicle displacement.
- Mechanical Steering Assembly — Adjustable front wheels configured before each run.
- Chassis — Custom-designed and assembled vehicle frame.

## Software

The control system was implemented using C++ and the Arduino framework.

**Key Functionality:**

- **Motor Control:** Controls the DC motor through a motor driver.
- **Encoder Feedback:** Reads Hall-effect encoder signals to track motor rotation.
- **Distance Measurement:** Converts encoder counts into estimated vehicle displacement using wheel circumference and encoder resolution.
- **Movement Control:** Uses the measured displacement to determine when the vehicle has reached its programmed travel distance.
- **Start/Reset Controls:** Uses a physical button to initiate and reset vehicle operation.

## Control System

The vehicle uses encoder feedback to regulate its travel distance.

1. Geometric measurements of the course are used to detI dermine the required steering adjustment and travel distance.
2. The front steering assembly is mechanically adjusted before the run.
3. The Arduino begins motor operation after receiving the start input.
4. Encoder signals are monitored to estimate the distance traveled.
5. The motor is controlled based on the remaining distance to the target.
6. The vehicle stops once the programmed travel distance is reached.

## Project Design

The project involved both mechanical and electrical engineering, including:

- Designing and constructing a custom vehicle chassis.
- Integrating a microcontroller with a motor driver and encoder-equipped motor.
- Developing software to translate encoder measurements into physical distance.
- Combining geometric calculations with mechanical steering adjustments to navigate a curved course.

## Technologies

- C++
- Arduino
- Embedded Systems
- Hall-effect Sensors
- Motor Control
- Digital Signal Processing / Encoder Feedback
