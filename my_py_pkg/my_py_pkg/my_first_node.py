#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class MyNode(Node):  # inherit from Node
    def __init__(self):
        super().__init__("py_test")
        self.get_logger().info("Hello there!")
        self.create_timer(0.5, self.timer_callback)
        self.counter = 0
    
    def timer_callback(self):
        self.get_logger().info(str(self.counter))
        self.counter += 1

def main(args=None):
    rclpy.init(args=args)
    node = MyNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()