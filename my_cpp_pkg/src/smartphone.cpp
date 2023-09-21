#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class SmrtphoneNode : public rclcpp::Node 
{
public:
    SmrtphoneNode() : Node("smartphone"){
        subscriber_ = this->create_subscription<example_interfaces::msg::String>(
            "robot_news", 10,
        std::bind(&SmrtphoneNode::callbackRobotNews, this, std::placeholders::_1)); // gdyby były dwa, to w ted std::placeholders::_2, etc

        RCLCPP_INFO(this->get_logger(), "Smrtphone je has been started");
    }

private:
    void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg){
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
    }

    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmrtphoneNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}