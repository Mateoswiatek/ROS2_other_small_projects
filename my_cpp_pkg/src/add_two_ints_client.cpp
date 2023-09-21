#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

// using std::placeholders::_1;

class AddTwoIntsClientNode : public rclcpp::Node{
public:
    AddTwoIntsClientNode() : Node("add_two_ints"){
        //new thread, push back to vector
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoIntsService,
                                            this, 1, 2)));
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoIntsService,
                                            this, 7, 20)));

        RCLCPP_INFO(this->get_logger(), "has been started   ");
    }

    void callAddTwoIntsService(int a, int b){ // call in a different thread
        //client
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        while(!client->wait_for_service(std::chrono::seconds(1))){
            RCLCPP_WARN(this->get_logger(), "W8 for server to be up...");
        }

        //create and fill the request
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        //send request to server
        auto future = client->async_send_request(request);

        // how to w8 for response? we will call the all function in new thread
        // response
        try{
            auto response = future.get(); // we will w8 here for the response

            // processing response
            RCLCPP_INFO(this->get_logger(), "%d + %d = %ld", a, b, response->sum);
        
        } catch(const std::exception &e){
            RCLCPP_ERROR(this->get_logger(), "Service call failed");
        }
    }
private:
    std::vector<std::thread> threads_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsClientNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}