#include <cstdio>
#include<functional>
#include<chrono>
#include<memory>
#include<string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;
auto message = std_msgs::msg::String();
auto num = std_msgs::msg::Int32();


class Publisher : public rclcpp::Node
{
  public: 
  Publisher(): Node("my_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    timer_ = this-> create_wall_timer(500ms,std::bind(&Publisher::timer_callback,this));
    num.data = static_cast<int>(count_) ;
  }

  private:
    void timer_callback(){
      //auto message = std_msgs::msg::String();
      //auto num = std_msgs::msg::Int32();
      //num.data = static_cast<int>(count_) ;
      num.data = num.data + 1;
      message.data = "Your number is: " + std::to_string(num.data);
      RCLCPP_INFO(this->get_logger(),"Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
    //std_msgs::msg::Int32 num;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<Publisher>());
  rclcpp::shutdown();
  return 0;
}
