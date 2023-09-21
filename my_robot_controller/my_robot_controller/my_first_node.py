#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class MyNode(Node):

    def __init__(self):
        super().__init__("first_node") # class Node constructor, node_name in ros2, graph 
        self.get_logger().info("Hello ROS2")
        self.counter = 0
        self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        self.get_logger().info("Hello " + str(self.counter))
        self.counter += 1


def main(args=None):
    rclpy.init(args=args)

    node = MyNode()
    rclpy.spin(node)  # spin -> this node is keept alive, until kill with ctrl + c, all callbck will be able to be run.

    rclpy.shutdown()

if __name__ == '__main__':
    main()