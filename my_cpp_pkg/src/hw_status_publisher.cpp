#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/hardware_status.hpp"

class HardwarestatusPublisherNode: public rclcpp::Node {
public:
    HardwarestatusPublisherNode(): Node("hardware_status_publisher"){
        pub_ = this->create_publisher<my_robot_interfaces::msg::HardwareStatus>(
            "hardware_status", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&HardwarestatusPublisherNode::publishHardwareStatus, this));
        RCLCPP_INFO(get_logger(), "HW publisher has been started.");
    }
private:
    void publishHardwareStatus(){
        auto msg = my_robot_interfaces::msg::HardwareStatus();
        msg.temperature = 50;
        msg.are_motors_ready = false;
        msg.debug_message = "Motors are too hot.";
        pub_->publish(msg);
    }

    rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<HardwarestatusPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}