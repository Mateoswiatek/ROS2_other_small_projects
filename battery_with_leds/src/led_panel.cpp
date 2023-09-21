#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/led_state_array.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"

using std::placeholders::_1; 
using std::placeholders::_2; 

class LedPanelNode : public rclcpp::Node {
public:
    LedPanelNode() : Node("led_panel"){ //std::array<bool, 3>{false, false, false}; nie można, bo zgodność typów
        this->declare_parameter("led_states", std::vector<bool>{false, true, false});
        leds = this->get_parameter("led_states").as_bool_array();
        server_ = this->create_service<my_robot_interfaces::srv::SetLed>("set_led",
        std::bind(&LedPanelNode::callbackSetLed, this, _1, _2));
        timer_ = this->create_wall_timer(std::chrono::milliseconds(100),
                                         std::bind(&LedPanelNode::publishLedState, this));
        publisher_ = this->create_publisher<my_robot_interfaces::msg::LedStateArray>("led_panel_state", 10);
        RCLCPP_INFO(this->get_logger(), "Led panel has been started.");
    }

private:
    void callbackSetLed(const my_robot_interfaces::srv::SetLed::Request::SharedPtr request,
                        const my_robot_interfaces::srv::SetLed::Response::SharedPtr response){
        if(request->led_number>2){
            response->success = false;
            response->message = "error number, only 0,1,2";
            RCLCPP_WARN(this->get_logger(), "client try change led: %ld, to state: %d", request->led_number, request->state);
        } else{
            leds[request->led_number] = request->state;
            response->message = "OK";
            response->success = 1;
            //RCLCPP_INFO(this->get_logger(), "change led: %ld, to %d", request->led_number, request->state);
        }
        
    }

    void publishLedState(){
        auto msg = my_robot_interfaces::msg::LedStateArray();
        //msg.led_states = leds; // TEGO NIE MOŻNA, BO LED_STATES TO array, a parameter to vector XD
        msg.led_states[0] = leds[0];
        msg.led_states[1] = leds[1];
        msg.led_states[2] = leds[2];
        publisher_->publish(msg);
    }

    rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr server_;
    rclcpp::Publisher<my_robot_interfaces::msg::LedStateArray>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector<bool> leds;
};


int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LedPanelNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}