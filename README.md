# Robot-Simulator
### Project Overview

The overall goal of the software project is  to develop a rudimentary robot simulator in which robot behavior is visualized within a graphics window, and to set up, observe, and document the results of experiments involving the entities in the simulator. The robots will be modeled after Braitenberg Vehicles, which use a simple design to realize complex behavior. The environment will have multiple robots, as well as stimuli such as lights and food. Robots will exhibit different behavior when they sense the stimuli in the environment, depending on their sensor-motor connections related to that stimulus. For example, some robots will be attracted to the light and some fear the light.

<hr>

#### Robot Arena

The robot arena has entities that are specified in a configuration file. The intent is for the robots specified in the configuration file to carry out their behavior in the Arena with the other entities specified in the configuration file (lights and food). For example:
<ol>
<li>Besides the explore behavior, robots can be configured to exhibit love, fear, and or aggression toward food and/or light entities in the Arena </li>
<li> If a robot bumps into another robot or the wall it should reverse (turn around 180 degrees); advance for 20 simulation time steps, and then turn LEFT 45 degrees (from its current heading) to avoid another collision with the object it collided with. </li>
<li>A robot will change color to illustrate the sensor that is driving its behavior (food or light) </li>
</ol>

#### Graphics Environment

The graphics environment consists primarily of a single window with robots, lights, and food. All objects (except for the wall) in the environment will be composed of circles, which greatly simplifies collision detection. You are welcome to add graphics enhancements, such as color, text, or decorations provided it does not interfere with required functionality. The basic graphics window framework has been provided. You will need to get familiar with the graphics library and with the provided code to learn how to draw objects of particular shape in the environment.

#### Graphical User Interface (GUI) and User Input (UI)

A basic GUI with user buttons and input via mouse and keyboard has been provided. The user currently has the following controls:

-  UI buttons Play and Reset
--  Press the Play  button to start the simulation.  Pressing the Play button again pauses the simulation.
--  The Reset button reloads the configuration file, so the simulation starts from the initial configuration
- UI Entity Button
--Pressing the Entity button enables a user to select and review and/or set the behaviors associated with an Entity in the Arena.

For example, when the default configuration file (default.json) is used to run the simulation:
<ul>
<li> there is one (mobile) Light entity, one (stationary) food entity, and one Braitenberg vehicle with default behavior toward light (meaning the robot ignores input from its light sensor) and explore behavior toward food. </li>
<li> The Entity button GUI enables the user to select a robot in the Arena and then change the robot's behavior toward food (to love, cower, explore, or default) and/or light (to aggressive, love, cower, or explore) - or to leave the current behavior in place.  </li>
<li>The GUI also enables the user to turn the robot's mobility off. </li>
<li>If the user selects a light via the Entity button, the user can turn the light's mobility on or off as well.</li>
</ul>

<hr>

### Compiling and Running the Simulation

Compile the simulation with `make` at the top level of the project directory.

```
./build/bin/arenaviewer  scenes/default.json
```

The JSON files are used to configure:
<ol> <ol>
<li> the size of the Arena, </li>
<li> the number of Food entities in the Arena, </li>
<li> the number of Light entities in the Arena, </li>
<li> and the number of Robot entities in the Arena</li>
</ol></ol>
when the simulation is initialized.
</p>
The initial position and radius of each entity in the Arena (Robots, Lights, and Food) must also be specified.
<ul>
<li>For food, heading (which should be 0.0 degrees) should also be specified </li>
<li> For robots, in addition to position, heading (in degrees) and sensor behavior toward light and food entities must be specified </li>
</ul>

<hr>

One design requirement is the appropriate use of the **__Factory design pattern__** to implement some aspect of the functional requirements. The interaction between Arena and the configuration files (specified in JavaScript Object Notation (JSON)), and the entities that are enclosed by the Arena provide a good opportunity to employ the Factory Pattern. Another design requirement is to create an initial UML design of how you plan to refactor the simulation code to employ the **__Strategy design pattern__**.

Finally, robot behavior (i.e. wheel velocities) is driven by the light and food sensor readings. The drive signal for each wheel from the different types of sensors can be combined in a variety of ways. In this implementation, the drive signals are added together, provided they each contribute. But sometimes, because the particular sensor is not active or because there are no detected stimuli, only one of the sensor signals is driving the wheel speed. To help understand the robot behavior, dynamically set the color of the robot based on which sensor signals are impacting behavior. Use the following colors under the following conditions:
1.  Lights should be white
2.  Food should be green
3.  Robot Color should change depending on which sensor(s) are ACTIVELY driving the robot. Specifically:
- - If neither sensor is actively affecting the robot's behavior, the robot should be Maroon in color (122,0,25).
--  If both sensors are actively affecting the robot's behavior, the robot should be Maroon in color (122,0,25).
- - If ONLY the light sensor is actively affecting the robot's behavior, the robot should be Gold in color (255,204,51).
- - If ONLY the food sensor is actively affecting the robot's behavior, the robot should be Blue in color (0,0,255).
