#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberCounter : public rclcpp::Node
{
public:
    NumberCounter() : Node("number_counter"), counter_(0)
    {
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(&NumberCounter::callbackNumber, this, std::placeholders::_1));

        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);

        RCLCPP_INFO(this->get_logger(), "Nó 'number_counter' iniciado");
    }

private:
    void callbackNumber(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        counter_ += msg->data;

        auto new_msg = example_interfaces::msg::Int64();
        new_msg.data = counter_;

        publisher_->publish(new_msg);

        RCLCPP_INFO(this->get_logger(), "Recebendo: %ld, contador = %ld", msg->data, counter_);
    }

    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    long counter_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NumberCounter>());
    rclcpp::shutdown();
    return 0;
}
