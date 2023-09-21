#!/usr/bin/env python3
import rclpy
import random
from rclpy.node import Node

from example_interfaces.msg import Int64

class NumberPublisherNode(Node):
    def __init__(self):
        super().__init__("number_publisher")
        self.declare_parameter("ceil_of_random_number", 10) # default value
        self.declare_parameter("publish_frequency", 1.0)

        self.ceil = self.get_parameter("ceil_of_random_number").value
        self.publisher_ = self.create_publisher(Int64, "number", 10)
        self.timer_ = self.create_timer(1.0/self.get_parameter("publish_frequency").value, self.publish_number)
        self.get_logger().info("Number Publisher has been started, py")

    def publish_number(self):
        msg = Int64()
        msg.data = random.randrange(0, self.ceil)
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode()
    rclpy.spin(node)
    rclpy.shutdown


if __name__ == "__main__":
    main()