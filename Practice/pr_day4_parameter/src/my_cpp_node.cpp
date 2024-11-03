#include "rclcpp/rclcpp.hpp"
#include <cstdio>

class MyCppNode : public rclcpp::Node
{
public:
    MyCppNode() : Node("my_cpp_node")
    {
        this->declare_parameter("test_param", 123);
        int test_param = this->get_parameter("test_param").as_int();
        RCLCPP_INFO(this->get_logger(), "Test parameter: %d", test_param);

        parameters_client_ = std::make_shared<rclcpp::AsyncParametersClient>(this);
        while(!parameters_client_->wait_for_service(std::chrono::seconds(1))){
            RCLCPP_INFO(this->get_logger(), "Waiting..");
        }

        auto parameters_callback = [this](const rcl_interfaces::msg::ParameterEvent::SharedPtr event){
            for(auto & changed_parameter : event->changed_parameters){
                RCLCPP_INFO(this->get_logger(), "Parameter event received: %s, %ld", changed_parameter.name.c_str(), changed_parameter.value.integer_value);
            }
        };
        subscription_ = parameters_client_->on_parameter_event(parameters_callback);
    }

    rclcpp::AsyncParametersClient::SharedPtr parameters_client_;
    rclcpp::Subscription<rcl_interfaces::msg::ParameterEvent>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyCppNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}