#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from my_robot_interfaces.msg import HardwareStatus

class HardwarestatusPublisherNode(Node):
    def __init__(self):
        super().__init__("hardware_status_publisher")
        self.hw_status_publisher = self.create_publisher(HardwareStatus, "hardware_status", 10)
        self.timer_ = self.create_timer(1.0, self.publish_hw_status)
        self.get_logger().info("HW Publisher has been started.")

    def publish_hw_status(self):
        msg = HardwareStatus()
        msg.temperature = 1
        msg.are_motors_ready = True
        msg.debug_message = "Nothing special here"

        self.hw_status_publisher.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = HardwarestatusPublisherNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()