Industrial Boiler Safety & Monitoring System (IBSMS)
1. Project Overview
   
The Industrial Boiler Safety & Monitoring System (IBSMS) simulates a safety monitoring system used in large industrial plants where boilers generate steam for manufacturing processes.
Industrial boilers operate under high pressure and temperature, and failures can lead to catastrophic accidents. Therefore, modern plants deploy real-time monitoring systems that continuously track parameters such as:
Pressure
Temperature
Water level
Gas leakage
This project simulates such a system using Linux system programming concepts including processes, threads, inter-process communication, signal handling, and file logging.
The system will detect abnormal conditions and trigger automatic safety responses, such as emergency shutdown.
The project is implemented in C and runs on Linux systems like Ubuntu using the GNU Compiler Collection.

2. Real World Scenario in real industrial plants:
   
Boilers generate steam for turbines or production lines.
Multiple sensors continuously monitor safety parameters.
A control system analyzes sensor data.
If a dangerous condition occurs, the system triggers automatic safety mechanisms.
Examples of dangerous conditions:
Boiler pressure too high
Temperature exceeding safe limits
Water level too low
Gas leak detected
In such cases, the control system must:
Alert operators
Shut down the boiler
Log the event
Stop all related processes safely
This project simulates that behavior.

3. System Architecture

                 +---------------------------+
                 |  Boiler Control System   |
                 |   (Parent Process)       |
                 +-------------+------------+
                               |
                               | IPC (Pipe)
                               |
                +--------------v--------------+
                |    Sensor Data Generator    |
                |       (Child Process)       |
                +--------------+--------------+
                               |
                        Worker Threads
                     (Sensor Simulation)

Components:
Boiler Controller
Sensor Data Generator
Sensor Threads
IPC Communication
Signal-based Emergency Shutdown
Logging System

4. System Components
4.1 Boiler Control System (Parent Process)

This process represents the industrial control system.
Responsibilities:
Receive sensor data
Analyze values
Detect unsafe conditions
Trigger emergency shutdown
Log system events
Example output:
Boiler controller started
Sensor process started
Temp:84  Pressure:127  Water:29  Gas:0

Temp:105  Pressure:145  Water:43  Gas:4

WARNING: Gas Leak!

Temp:82  Pressure:127  Water:83  Gas:0

Temp:83  Pressure:184  Water:92  Gas:2

WARNING: High Pressure!

Temp:111  Pressure:155  Water:46  Gas:0

WARNING: Temperature Critical!

Temp:106  Pressure:119  Water:59  Gas:1

Temp:89  Pressure:120  Water:49  Gas:3

Temp:111  Pressure:155  Water:70  Gas:1

WARNING: Temperature Critical!

Emergency Shutdown Triggered

System calls used:
fork()
waitpid()
read()
write()

4.2 Sensor Data Generator (Child Process)
This process simulates hardware sensors.
Responsibilities:
Generate simulated sensor readings
Send readings to controller
Update shared system status
The process creates multiple threads, each simulating a different sensor.

4.3 Sensor Threads
Each thread represents a specific sensor.
Examples:
Thread	Sensor
Thread 1	Temperature sensor
Thread 2	Pressure sensor
Thread 3	Water level sensor
Thread 4	Gas leakage sensor

Threads generate data using random values:
Example:
Temperature :- 80-120°C
Pressure :- 100–200 PSI
Water level :- 10–100 %
Gas :- 0–5 ppm

Thread functions:

pthread_create()
pthread_mutex_lock()
pthread_mutex_unlock()

5. Inter-Process Communication (IPC)
The system uses two IPC mechanisms.
5.1 Pipe Communication
Used to send sensor readings from child process to controller.
Data flow:
Sensors ---- Child Process ---- Pipe ----- Controller

Functions used:
pipe()
read()
write()

5.2 Shared Memory
Shared memory stores current system state.
Example stored values:
Last temperature
Last pressure
Boiler status
Emergency flag

Functions used:
shmget()
shmat()
shmdt()
shmctl()
Shared memory allows fast access to system status.

6. Signal Handling
Signals simulate emergency controls used in industrial systems.
Example signals:
Signal	Purpose
SIGINT	Manual shutdown
SIGTERM	System termination
SIGUSR1	Emergency stop

Example scenario:
Operator presses emergency stop → system sends signal → boiler stops immediately.
Signal functions:
signal()
kill()

7. File Logging System
Industrial systems always maintain event logs for safety audits.
This project writes logs to:
logs/boiler.log
Example log entries:
[INFO] Boiler started
[DATA] Temp=92C Pressure=140PSI
[WARNING] High pressure detected
[ALERT] Emergency shutdown activated

Functions used:
open()
write()
lseek()
close()

lseek() allows updating log headers or metadata.

8. Simulated Data
Since no real sensors exist, the system simulates readings using:
Random Number Generator
rand()
Example values:
Temperature: 70–120
Pressure: 100–200
Water level: 10–100
Gas leak: 0–5
Timers

Each sensor produces data periodically.
Example:
sleep(1)
This simulates real sensor polling intervals.
   
9. System Programming Features Used
    
Requirement	Implementation
Multiple processes	fork()
Process synchronization	waitpid()
Multithreading	pthread_create()
Thread synchronization	mutex
IPC mechanism 1	pipe
IPC mechanism 2	shared memory
Signals	SIGINT emergency stop
File handling	log system
Random simulation	rand()
Timers	sleep()
