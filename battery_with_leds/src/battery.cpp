#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"

class BatteryNode: public rclcpp::Node{
public:
    BatteryNode(): Node("battery"), battery_level(100), charge(false){
        battery_timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&BatteryNode::callbackFakeBaterry, this));   
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&BatteryNode::check_batery_state, this));
         threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 6, 1)));
        RCLCPP_INFO(this->get_logger(), "Battery node has been started.");
    }
    void callbackFakeBaterry(){
        if(charge == 0){
            battery_level -= 1;
            if(battery_level<=3){
                charge = true;
            }
        } else { // we charging the battery
            battery_level+=2;
            if(battery_level>=99){
                charge = false;
            }
        }
        RCLCPP_INFO(this->get_logger(), "Charge: %d, battery level: %d", charge, battery_level);
    }

    void check_batery_state(){
        if(battery_level >= 75 and status != 4){
            status = 4;
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 2, 1)));
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 1, 1)));
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 0, 1)));
        } else if(battery_level >= 50 and battery_level < 75 and status != 3){
            status = 3;
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 2, 1)));
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 1, 1)));
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 0, 0)));
        } else if(battery_level >= 25 and battery_level < 50 and status != 2){
            status = 2;
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 2, 1)));
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 1, 0)));
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 0, 0)));
        } else if(battery_level < 25 and status != 1){
            status = 1;
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 2, 0)));
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 1, 0)));
            threads_.push_back(std::thread(std::bind(&BatteryNode::callSetLed, this, 0, 0)));
        }
    }

    void callSetLed(int led_number, bool state){
        auto client = this->create_client<my_robot_interfaces::srv::SetLed>("set_led");
        while(!client->wait_for_service(std::chrono::seconds(1))){
            RCLCPP_WARN(this->get_logger(), "W8 for server...");
        }
        //request
        auto request = std::make_shared<my_robot_interfaces::srv::SetLed_Request>();
        request->led_number = led_number;
        request->state = state;

        //send to server
        auto future = client->async_send_request(request);

        try{
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(),
            "Led: %d, request state: %d, success: %d, mess: %s",
            led_number, state, response->success, response->message.c_str());

        } catch(const std::exception &e){
            RCLCPP_ERROR(this->get_logger(), "Service call failed");
        }
    }

private:
    int status = 0; // 4 = >=75;  3 = >=50; 2 = >= 25; 1 = >=0;
    int battery_level;
    bool charge;
    std::vector<std::thread> threads_;
    rclcpp::TimerBase::SharedPtr battery_timer_, timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BatteryNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}