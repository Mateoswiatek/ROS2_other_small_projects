List of projects:
# Battery_with_leds
## Brief description
Battery control simulation. One Node ('battery') simulates a physical battery along with basic software.
The second Node ('led_panel') serves as an informational panel module displaying the battery status.

## Technologies Used

Utilized Features:
- Packages,
- Nodes,
- Custom Topics
  - Publisher and Subscriber,
- Callbacks,
- Custom Services,
- Custom Interfaces
- Threads,
- Parameters,

*"Custom"* means personally designed
## Full Description
Node 'battery' simulates the discharging and charging of a battery. When the battery level reaches critical values, requests are sent to the server ('led_panel') to change the status of LED indicators. Requests are only sent when the critical level is crossed, and each request is sent in a separate thread.

Node 'led_panel' changes the state of LED indicators when it receives a request from the client ('battery'). Additionally, 'led_panel' publishes the current state of the LED indicators on the 'led_panel_state' topic. The node also has one parameter available: an array of initial LED states.


## Potential for Further Development / Ideas
- Adding a parameter in 'battery' responsible for the discharge and charge rate of the battery.



