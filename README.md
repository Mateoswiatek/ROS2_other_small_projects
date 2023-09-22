# Introduction
During the implementation of these basic projects, I gained essential experience and good coding practices. In addition to the code itself, I became familiar with numerous useful command-line tools for managing ROS2 projects, as well as for editing, debugging, and controlling running programs (ROS2 tools). I also used these tools to explore existing software, which will undoubtedly be valuable when working on pre-existing code, integration, or adding new functionalities to a smoothly running system.

List of projects in this repository:
======
- [Turtle_killer](https://github.com/Mateoswiatek/ROS2_follow_turtle_robot) - The most **complex completed** project in *ROS2*.
- [Roulette_with_parameters](https://github.com/Mateoswiatek/ROS2_roulette_with_parameters_and_server)

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

# my_cpp_pkg / my_py_pkg
## Brief description
Nodes pisane podczas poznawania kolejnych zagadnień z tematyki ROS2. Zarówno w Pythonie jak i Cpp. Większość samodzielnych zagadnień pisałem w Cpp, gdyż jest niżej poziomowym językiem. Dodatkowo, łatwiej jest zrozumieć co się dzieje, w momencie gdy wszystkie bebechy są na wierzchu. W opisie skupie się na Cpp. Jest tutaj kilka mini projektów.

## Technologies Used
Utilized Features:
- Packages,
- Nodes,
- Custom Topics
  - Publisher and Subscriber,
- Callbacks,
- Custom Services,
- Custom Interfaces,
- Threads,
## Full Description
W folderze "cpp" znajduje się zdecydowanie więcej niż w "py".
**robot_news_station** razem z **smartphone** tworzą miniprojekt opierający się na użyciu Topics w celu przesyłu "podstawowej" wiadomości. Zostały później wykorzystane w **"robots_spam"**.
**"hw_status_publisher"** - posłóżył jako test dla custom Interfaces, publikując informacje na temat symulowanego hardweru. Tutaj stworzyłem własny interfejs razem z wykorzystaniem go w praktyce.
**"add_two_ints"** - Za pośrednictwem tych plików zapoznałem się z zagadnieniem Services w ROS2, za pomocą gotowego interfejsu srv, obsłużyłem server jak i klienta bez OOP jak i z OOP. Zdobyłem wiedzę na temat "obsługi" zapytań jak i zarządzania nimi. Wykorzystałem również "wątki" oraz obiekty "future".  

# my_robot_controller
## Brief description
The first project written in Python, familiarizing oneself with basic ROS2 concepts, creating Nodes, topics, turtlesim, and experimenting with basic turtle movement.
Nodes were created while watching tutorials, browsing guides, websites, and through independent experimentation. Nothing impressive.

## Technologies Used
Utilized Features:
- Basic Concepts of ROS2

# More Complex Projects:
- Follow
- Rullete
- 
