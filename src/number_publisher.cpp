#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using namespace std::chrono_literals;

class NumberPublisher : public rclcpp::Node
{
public:
  NumberPublisher()
  : Node("number_publisher"), number_to_publish_(2)  // número base que será publicado
  {
    publisher_ = this->create_publisher<example_interfaces::msg::Int64>("/number", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&NumberPublisher::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Publisher iniciado!");
  }

private:
  void timer_callback()
  {
    auto msg = example_interfaces::msg::Int64();
    msg.data = number_to_publish_;
    publisher_->publish(msg);
    RCLCPP_INFO(this->get_logger(), "Publicado: %ld", (long)msg.data);
  }

  rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int64_t number_to_publish_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NumberPublisher>());
  rclcpp::shutdown();
  return 0;
}

