#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class RobotNewsStationNode : public rclcpp::Node
{
public:
    RobotNewsStationNode() : Node("robot_news_station"), counter(0), robot_name("R2D2") {
        publisher = this->create_publisher<example_interfaces::msg::String>("robot_new", 10);
        timer = this->create_wall_timer(std::chrono::seconds(1),
                                        std::bind(&RobotNewsStationNode::publishNews, this));
        RCLCPP_INFO(this->get_logger(), "Hello!");
    }

private:
    void publishNews(){
        auto msg = example_interfaces::msg::String();
        msg.data = robot_name + "Hello!" + std::to_string(counter);
        publisher->publish(msg);
        counter++;
    }

    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer;
    int counter;
    std::string robot_name;
};


int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}