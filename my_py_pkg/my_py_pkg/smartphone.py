#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import String

class SmartphoneNode(Node):
    def __init__(self):
        super().__init__("smartphone")

        self.subscriber = self.create_subscription(String, "robot_news",
                self.callback_robot_news, 10) # topic type, topic_name, callback, queue

        self.get_logger().info(f"{self.__class__.__name__} has been started")

    def callback_robot_news(self, msg):  # callback_[name_of_topic] 
        self.get_logger().info(msg.data)  # bo w String, jest pole data


def main(args=None):
    rclpy.init(args=args)
    node = SmartphoneNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()