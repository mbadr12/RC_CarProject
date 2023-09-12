# RC Project for Interfacing Mega project of EUI training
- The Project is implemented using a non-preemptive priority-based Scheduler that supports the First delay feature to ensure that the CPU load is normal
- The project requirements are:
  1. The car motors are started using one of the two on-board switches.
  2. The car will stop if the other switch is pressed or a time of one minute has elapsed.
  3. When motors are started, the car moves and swings to the way with the highest illumination.
  4. The Temperature, the LDRs difference, and the elapsed time are displayed on the LCD.
  5. If the car gets closer to an obstacle by a max of 10 centimeters. The ultrasonic sensor fires and the car reverses its direction first, moving to the back then rotates by 90 degrees.
- The project is totally implemented as a set of tasks that are implemented in a priority-based way
- The priorities of Tasks are given based on Gomaa criteria.
- The project aims to achieve Some goals
    1. From the execution mechanism we want
        1. Responsiveness
        2. Determisim
       - So, we Implement our scheduler to achieve these two goals
    2. From the SW Architecture we want
        1. Modularity
        2. Readability
        3. Configurability
        4. Reusability
      - So, We used our Layered Architecture, Design of the system, and robust implementation of Drivers to achieve these goals
- You will find The whole system design in the section of System Design.
- Here you can see the Layered Architecture and Drivers We used.
![Drawing 2023-09-10 23 25 55 excalidraw](https://github.com/mbadr12/RC_CarProject/assets/102329539/971803a1-5ad4-433b-b047-9199315a2892)
